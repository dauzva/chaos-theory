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
    ui->canvas->resize(this->width()-400, this->height());


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
    timer->start(10); // Timer fires every 1 milliseconds
}

MainWindow::~MainWindow()
{
    delete ui;
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

    // Start position in the middle of the canvas
    double x = ax + aw / 2.0;
    double y = ay + ah;

    // Initial angle (pointing up)
    double currentAngle = -90;

    // Stack to store state (position and angle)
    QStack<QPair<QPointF, double>> stateStack;

    foreach (QChar c, megarule)
    {
        double len = 60 * pow(l, currentIterationLevel - 1);

        if (c == 'F')
        {
            // Calculate end point based on current angle and length
            double endX = x + len * cos(qDegreesToRadians(currentAngle));
            double endY = y + len * sin(qDegreesToRadians(currentAngle));

            // Draw the line
            painter.drawLine(QPointF(x, y), QPointF(endX, endY));

            // Update current position
            x = endX;
            y = endY;
        }
        else if (c == '+')
        {
            // Rotate clockwise
            currentAngle += angle;
        }
        else if (c == '-')
        {
            // Rotate counterclockwise
            currentAngle -= angle;
        }
        else if (c == '[')
        {
            // Push current state (position and angle) to the stack
            stateStack.push(QPair<QPointF, double>(QPointF(x, y), currentAngle));
        }
        else if (c == ']')
        {
            // Pop the previous state from the stack
            if (!stateStack.isEmpty())
            {
                QPair<QPointF, double> previousState = stateStack.pop();

                // Restore position and angle
                x = previousState.first.x();
                y = previousState.first.y();
                currentAngle = previousState.second;
            }
        }
    }
}

void MainWindow::on_resetBtn_clicked()
{

}

void MainWindow::updateTimer()
{
    this->update();
}


void MainWindow::on_animationSlider_valueChanged(int value)
{
    ui->animationLabel->setText(QString::number(value));
}


void MainWindow::on_startBtn_clicked()
{
    currentIterationLevel++;

    for(int i = 0; i < megarule.size(); ++i)
    {
        QChar c = megarule[i];
        if(c == axiom)
        {
            int r = rand() % 100;
            double acc = 0;
            for(int j = 0; j < rules.size(); j++)
            {
                acc += rules[j].second;
                if(acc*100 >= r)
                {
                    int a = rules[j].first.mid(3).size();
                    megarule.replace(i, 1, rules[j].first.mid(3));
                    i+=(a-1);
                    break;
                }
            }
        }
    }
}

