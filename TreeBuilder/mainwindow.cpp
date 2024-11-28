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
    timer->start(10); // Timer fires every 1 milliseconds

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
    painter.setPen(QPen(Qt::black, 1));
    painter.drawLines(treeLines);
}

void MainWindow::on_resetBtn_clicked()
{
    iterationLevel = 1;
    ui->iterationSlider->setSliderPosition(iterationLevel);
    ui->iterationLabel->setText(QString::number(iterationLevel));
    treeLines.clear();
    initEndpoints.clear();
    initMath.clear();
    currentTreeLines.clear();
    initLinesCount = 0;
    this->updateTree();
}

void MainWindow::updateTimer()
{
    this->updateMath();
    this->update();
}

void MainWindow::updateMath()
{
}

void MainWindow::updateTree()
{
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
    foreach (QPointF point, initEndpoints)
    {
        QLineF temp = QLineF(initPoint, point);
        initMath[initLinesCount-1] = std::make_pair((double)temp.length()/initLenght,temp.angle()-90);
        qDebug() << initMath;
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
        currentEndpoint = mapFromGlobal(QCursor::pos());
        if(isNewLine)
        {
            initEndpoints.append(currentEndpoint);
            initLinesCount++;
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

