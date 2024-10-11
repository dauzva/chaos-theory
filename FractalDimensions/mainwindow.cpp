#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap img(pngFolder+"koch.png");
    ui->image->setPixmap(img);
    ui->image->setAlignment(Qt::AlignCenter);
    resize(img.size());
    setWindowTitle("Fractal Dimension Calculator");

}

MainWindow::~MainWindow()
{
    delete ui;
}
