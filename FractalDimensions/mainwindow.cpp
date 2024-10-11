#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap img(pngFolder+"koch.png");
    QLabel *label = new QLabel(this);
    label->setScaledContents( true );
    label->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    label->setPixmap(img.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

MainWindow::~MainWindow()
{
    delete ui;
}
