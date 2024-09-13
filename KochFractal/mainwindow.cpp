#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    painter.drawLine(ax, ay+ah/2, ax+aw, ay+ah/2);
}
