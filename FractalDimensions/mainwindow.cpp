#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Fractal Dimension Calculator");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open photo"), "", tr("Png Files (*.png)"));
    QImageReader reader(fileName);
    QImage image = reader.read();

    QSize originalSize = image.size();
    QSize maxSize(720, 400);
    QSize scaledSize = originalSize.scaled(maxSize, Qt::KeepAspectRatio);

    QImage scaledImage = image.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    img = QPixmap::fromImage(scaledImage);

    ui->image->setPixmap(img);
    ui->image->setAlignment(Qt::AlignCenter);
    resize(img.size());
}


void MainWindow::on_calculateButton_clicked()
{
    QString filename="D:\\Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        for(int i = 0; i < img.height(); ++i)
        {
            for(int j = 0; j < img.width(); ++j)
            {
                QColor color = img.toImage().pixelColor(j,i);
                stream << qSetFieldWidth(3) << color.black() << " ";
            }
            stream << Qt::endl;
        }
    }
    file.close();
    qDebug() << "closed";

}

