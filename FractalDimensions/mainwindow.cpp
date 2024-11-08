#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QImageReader>
#include <vector>
#include <QGenericMatrix>
#include <QtMath>
#include "D:\chaos-theory\FractalDimensions\eigen\Eigen\Dense"
#include <iostream>

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open photo"), "", tr("Png Files (*.png *.jpg *.jpeg)"));
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
    // reads black pixels from photo
    QString filename="D:\\Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
    {
        QTextStream stream( &file );
        for(int i = 0; i < img.height(); ++i)
        {
            photoPixels.resize(img.height());
            for(int j = 0; j < img.width(); ++j)
            {
                photoPixels[i].resize(img.width());
                QColor color = img.toImage().pixelColor(j,i);
                stream << (color.black() > 1 ? 1 : 0);
                photoPixels[i][j] = (color.black() > 1 ? 1 : 0);
            }
            stream << Qt::endl;
        }
    }
    file.close();
    qDebug() << "closed";
    auto l3 = countGrid(photoPixels, 3);
    qDebug() << l3.first << "/" << l3.second << " " << (float)l3.first/l3.second;
    auto l5 =  countGrid(photoPixels, 5);
    qDebug() << l5.first << "/" << l5.second << " " << (float)l5.first/l5.second;
    auto l11 =  countGrid(photoPixels, 11);
    qDebug() << l11.first << "/" << l11.second << " " << (float)l11.first/l11.second;

    Eigen::Matrix<double, 3, 2> A;
    Eigen::Matrix<double, 3, 1> Y;
    double a = qLn(2);
    A <<    2*a, 1,
            3*a, 1,
            4*a, 1;

    Y <<    qLn(13),
            qLn(33),
            qLn(130);

    auto D = (A.transpose()*A).determinant();

    auto M = (A.transpose()*A).inverse() * A.transpose() * Y;

    std::cout << A << "\n" << A.transpose() << "\n\n";
    std::cout << Y << "\n\n";
    std::cout << M;

}

std::pair<int, int> MainWindow::countGrid(QVector<QVector<bool>> M, int n)
{
    int count = 0;
    int all = 0;
    for(int i = 0; i < M.size(); i+=n)
    {
        for(int j = 0; j < M.at(0).size(); j+=n)
        {
            bool included = false;
            for(int ii = i; ii < (i+1)*n && !included; ++ii)
            {
                for(int jj = j; jj < (j+1)*n && !included; ++jj)
                {
                    included = (ii >= M.size() ? 0 : jj >= M.at(0).size() ? 0 : M[ii][jj]);
                }
            }
            if(included)
                count++;
            all++;
        }
    }
    return {count, all};
}

