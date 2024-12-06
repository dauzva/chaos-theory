#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QStack>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->resize(this->width()-550, this->height());


    axiom = 'F';
    angle = 25.7;
    l = 1.0/2;
    qDebug() << l;
    megarule = axiom;

    rules.append(std::make_pair("F->F[+F]F[-F]F", 1.0/3));
    rules.append(std::make_pair("F->F[+F]F", 1.0/3));
    rules.append(std::make_pair("F->F[-F]F", 1.0/3));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1); // Timer fires every 1 milliseconds
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::parseAndAppendRules() {
    QString inputText = ui->ruleBox->toPlainText(); // Get text from UI
    QStringList ruleLines = inputText.split('\n', Qt::SkipEmptyParts); // Split by lines
    rules.clear();
    for (const QString &line : ruleLines)
    {
        QStringList parts = line.split(' '); // Split rule and probability
        if (parts.size() == 2)
        {
            QString rule = parts[0].trimmed();        // Extract the rule
            QStringList prob = parts[1].split('/');
            double probability = prob[0].toInt()*1.0/prob[1].toInt(); // Extract the probability

            // Validate the rule and probability
            if (!rule.isEmpty() && probability > 0 && probability <= 1)
            {
                rules.append(std::make_pair(rule, probability)); // Append rule
            }
            else
            {
                qDebug() << "Invalid rule or probability:" << line;
                return false;
            }
        }
        else
        {
            qDebug() << "Invalid rule format:" << line;
            return false;
        }
    }

    // Log the updated rules for debugging
    qDebug() << "Updated Rules:";
    for (const auto &rule : rules) {
        qDebug() << "Rule:" << rule.first << "Probability:" << rule.second;
    }

    return true;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = ui->canvas->geometry();
    int ax, ay, aw, ah;
    rect.getRect(&ax, &ay, &aw, &ah);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect, Qt::white);
    painter.setPen(QPen(Qt::black, 1));

    // Draw the completed steps
    double len = 80 * pow(l, currentIterationLevel - 1);
    double localX = ax + aw / 2.0;
    double localY = ay + ah;
    double localAngle = -90;

    if(fastdraw)
    {
        foreach (QChar c, megarule)
        {
            if (c == 'F')
            {
                double endX = localX + len * cos(qDegreesToRadians(localAngle));
                double endY = localY + len * sin(qDegreesToRadians(localAngle));
                painter.drawLine(QPointF(localX, localY), QPointF(endX, endY));
                localX = endX;
                localY = endY;
            }
            else if (c == '+')
            {
                localAngle += angle;
            }
            else if (c == '-')
            {
                localAngle -= angle;
            }
            else if (c == '[')
            {
                localStateStack.push(QPair<QPointF, double>(QPointF(localX, localY), localAngle));
            }
            else if (c == ']')
            {
                if (!localStateStack.isEmpty())
                {
                    QPair<QPointF, double> previousState = localStateStack.pop();
                    localX = previousState.first.x();
                    localY = previousState.first.y();
                    localAngle = previousState.second;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < currentStep; ++i)
        {
            QChar c = drawingSteps[i];
            if (c == 'F')
            {
                double endX = localX + len * cos(qDegreesToRadians(localAngle));
                double endY = localY + len * sin(qDegreesToRadians(localAngle));
                painter.drawLine(QPointF(localX, localY), QPointF(endX, endY));
                localX = endX;
                localY = endY;
            }
            else if (c == '+')
            {
                localAngle += angle;
            }
            else if (c == '-')
            {
                localAngle -= angle;
            }
            else if (c == '[')
            {
                localStateStack.push(QPair<QPointF, double>(QPointF(localX, localY), localAngle));
            }
            else if (c == ']')
            {
                if (!localStateStack.isEmpty())
                {
                    QPair<QPointF, double> previousState = localStateStack.pop();
                    localX = previousState.first.x();
                    localY = previousState.first.y();
                    localAngle = previousState.second;
                }
            }
        }
    }

}

void MainWindow::startDrawingAnimation()
{
    // Initialize variables
    QRect rect = ui->canvas->geometry();
    int ax, ay, aw, ah;
    rect.getRect(&ax, &ay, &aw, &ah);

    x = ax + aw / 2.0;
    y = ay + ah;
    currentAngle = -90;
    currentStep = 0;
    localStateStack.clear();

    // Prepare drawing steps
    drawingSteps = QVector<QChar>(megarule.begin(), megarule.end());
}

void MainWindow::updateDrawing()
{
    if (!drawingSteps.isEmpty() && currentStep < drawingSteps.size()) {
        ++currentStep;
    }
}

void MainWindow::on_resetBtn_clicked()
{
    if(parseAndAppendRules())
    {
        megarule.clear();
        megarule = axiom;
        currentIterationLevel = 0;
        localStateStack.clear();
        while(currentIterationLevel < maxIterationLevel)
        {
            this->iterate();
        }
        fastdraw = true;
    }
}

void MainWindow::updateTimer() {
    if (isUpdating) return;
    isUpdating = true;

    this->update();
    this->updateDrawing();
    this->update();

    isUpdating = false;
}

void MainWindow::iterate()
{
    currentIterationLevel++;

    QString newMegarule;
    for (int i = 0; i < megarule.size(); ++i) {
        QChar c = megarule[i];
        if (c == axiom) {
            int r = rand() % 100;
            double acc = 0;
            for (const auto &rule : rules) {
                acc += rule.second;
                if (acc * 100 >= r) {
                    newMegarule.append(rule.first.mid(3)); // Append replacement
                    break;
                }
            }
        } else {
            newMegarule.append(c);
        }
    }
    megarule = newMegarule;

}

void MainWindow::on_startBtn_clicked()
{
    if(parseAndAppendRules())
    {
        fastdraw = false;
        megarule.clear();
        megarule = axiom;
        currentIterationLevel = 0;
        while(currentIterationLevel < maxIterationLevel)
        {
            this->iterate();
        }
        startDrawingAnimation();
    }

}


void MainWindow::on_angleSelect_valueChanged(double arg1)
{
    angle = arg1;
}


void MainWindow::on_lenghtSelect_valueChanged(int arg1)
{
    l = 1.0/arg1;
}

