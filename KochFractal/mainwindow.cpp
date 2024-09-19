#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->resize(this->width()-300, this->height());

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
    painter.drawLines(kochPoints);
}

void MainWindow::on_iterateBtn_clicked()
{
    if(iterationLevel < 5)
        ui->iterationLabel->setText(QString::number(++iterationLevel));
}

void MainWindow::updateTimer()
{
    this->update();
    this->updateKochPoints();
}

void MainWindow::updateKochPoints()
{
    // 0 - 2
    // 1 - 5 (+3)
    // 2 - 17 (+12)
    kochPoints.clear();
    QRect rect = ui->canvas->geometry();
    int ax, ay, aw, ah;
    rect.getRect(&ax, &ay, &aw, &ah);

    kochPoints.append(QPointF(ax, ay+ah/2));
    kochPoints.append(QPointF(ax+aw, ay+ah/2));
    savedKochPoints = kochPoints;
    if(iterationLevel != 0)
    {
        for(int j = 0; j < iterationLevel; ++j)
        {
            kochPoints.clear();
            for(int i = 0; i < savedKochPoints.size()-1; ++i)
            {
                QPointF p = savedKochPoints.at(i);
                kochPoints.append(p);
                QPointF p1 = savedKochPoints.at(i+1);
                QLineF l = QLineF(p,p1);
                QLineF l1 = QLineF(p, l.pointAt((qreal)1/3));
                QLineF l21 = QLineF(l.pointAt((qreal)1/3), l.pointAt((qreal)1/2));
                QLineF l22 = QLineF(l.pointAt((qreal)1/3), l.pointAt((qreal)2/3)).normalVector();
                QLineF l2 = QLineF(l1.p2(), QPointF(l21.p2().x()+l22.p2().x()-l1.p2().x(), l21.p2().y()+l22.p2().y()-l1.p2().y()));
                QLineF l3 = QLineF(l2.p2(), l.pointAt((qreal)2/3));
                QLineF l4 = QLineF(l.pointAt((qreal)2/3), p1);

                kochPoints.append(l1.p2());
                kochPoints.append(l1.p2());
                kochPoints.append(l2.p2());
                kochPoints.append(l2.p2());
                kochPoints.append(l3.p2());
                kochPoints.append(l3.p2());
                kochPoints.append(l4.p2());
            }
            savedKochPoints.resize(kochPoints.size());
            savedKochPoints = kochPoints;
        }
    }
}

