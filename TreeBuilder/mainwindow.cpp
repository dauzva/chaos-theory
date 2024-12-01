#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->resize(this->width()-400, this->height());
    ui->iterationLabel->setText("1");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(50); // Timer fires every 1 milliseconds

    QTimer::singleShot(0, this, SLOT(updateTree())); // Defer updateTree until after setup
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
    int trunksize = 10;
    painter.setPen(QPen(QColor(114,92,66), trunksize));

    QList<QColor> leaf = {QColor(30,119,67), QColor	(9,95,64),QColor(45,70,47),QColor(52,109,34),QColor(48,113,12)};
    if(!treeLines.empty())
        painter.drawLine(treeLines[0]);

    int totalLines = 1;
    for(int j = 1; j <= iterationLevel && !initEndpoints.empty(); ++j)
    {
        int _total = totalLines;
        painter.setPen(QPen(QColor(114*pow(0.8,j),92*pow(0.8,j),66*pow(0.8,j)), trunksize*pow(0.8,j)));
        for(int i = totalLines; i < pow(initLinesCount,j)+ _total; ++i)
        {
            if(j+2 > iterationLevel)
            {
                QColor a = leaf.at(0);
                painter.setPen(QPen(leaf.at(0), trunksize * pow(0.8,j)));
                leaf.remove(0);
                leaf.append(a);
            }
            painter.drawLine(treeLines[i]);
            totalLines++;
        }
    }
}

void MainWindow::on_resetBtn_clicked()
{
    iterationLevel = 1;
    ui->iterationSlider->setSliderPosition(iterationLevel);
    ui->iterationLabel->setText(QString::number(iterationLevel));
    treeLines.clear();
    initEndpoints.clear();
    initMath.clear();
    leafCache.clear();
    currentTreeLines.clear();
    initLinesCount = 0;
    isWind = false;
    this->updateTree();
}

void MainWindow::updateTimer()
{
    if(isMouse && !initEndpoints.empty())
        this->updateMath();
    if(isWind)
    {
        this->updateTree();
        this->animateWind();
    }
    this->update();
}

void MainWindow::animateWind()
{
    static qreal time = 0;
    //time += 0.01;
    time += time < 62.8 ? 0.01 : -62.8;

    qreal amplitude = 1.0 + 0.2 * std::sin(0.1 * time);
    qreal frequency = 0.5 + 0.05 * std::sin(10 * time);
    qreal baseWave = std::sin(2 * M_PI * frequency * time);
    qreal randomNoise = 0.1 * (((   std::rand() % 2000) / 1000.0) - 1.0); // Random between -0.1 and 0.1

    qreal baseWindStrength = amplitude * baseWave + randomNoise;

    for (int i = 0; i < initMath.count(); ++i)
    {
        qreal windStrength = baseWindStrength;
        qreal angleChange = windStrength/5;

        initMath[i].second += (double)angleChange;
    }
}

void MainWindow::updateMath()
{
    initEndpoints[initLinesCount-1] = mapFromGlobal(QCursor::pos());
    this->updateTree();
}

void MainWindow::updateTree()
{
    leafCache.clear();
    treeLines.clear();
    QRect rect = ui->canvas->geometry();
    int ax, ay, aw, ah;
    rect.getRect(&ax, &ay, &aw, &ah);

    initPoint = QPointF((ax+aw)/2, 3*(ay+ah)/5);
    QLineF initLine = QLineF(QPointF((ax+aw)/2, ah), initPoint);
    qreal initLenght = initLine.length();
    treeLines.append(initLine);
    currentTreeLines = treeLines;

    // calculate angles and distances
    if(!isWind)
        foreach (QPointF point, initEndpoints)
        {
            QLineF temp = QLineF(initPoint, point);
            initMath[initLinesCount-1] = std::make_pair((double)temp.length()/initLenght,temp.angle()-90);
        }


    for(int j = 1; j <= iterationLevel && !initEndpoints.empty(); ++j)
    {
        QList<QLineF> _currentTreeLines;
        foreach (QLineF prev, currentTreeLines)
        {
            for(int i = 0; i < initLinesCount; ++i)
            {
                QLineF temp = QLineF(prev.p2(), prev.p1());
                double l = initMath[i].first;   // lenght
                double a = initMath[i].second;  // angle
                temp.setLength(l*prev.length());
                temp.setAngle(a+prev.angle());
                treeLines.append(temp);
                _currentTreeLines.append(temp);
            }
        }
        currentTreeLines.clear();
        currentTreeLines = _currentTreeLines;
        _currentTreeLines.clear();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QRect rect = ui->canvas->geometry();
    if(rect.contains(mapFromGlobal(QCursor::pos())))
    {
        isMouse = true;
        currentEndpoint = mapFromGlobal(QCursor::pos());
        if(isNewLine)
        {
            initLinesCount++;
            initEndpoints.append(currentEndpoint);
            initMath.append(std::make_pair(0,0));
            isNewLine = false;
        }
        if(!initEndpoints.empty())
            initEndpoints[initLinesCount-1] = currentEndpoint;
        this->updateTree();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    isMouse=false;
}



void MainWindow::on_iterationSlider_sliderMoved(int position)
{
    ui->iterationLabel->setText(QString::number(position));
    iterationLevel = position;
    this->updateTree();
}


void MainWindow::on_iterationSlider_valueChanged(int value)
{
    ui->iterationLabel->setText(QString::number(value));
    iterationLevel = value;
    this->updateTree();
}


void MainWindow::on_newLineBtn_clicked()
{
    isNewLine = true;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    this->updateTree();

}


void MainWindow::on_windBtn_clicked()
{
    isWind = isWind ? false : true;
}

