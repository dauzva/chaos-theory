#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QImageReader>
#include <QGenericMatrix>
#include <QtMath>
#include "D:\chaos-theory\FractalDimensions\eigen\Eigen\Dense"

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
    for(int i = 0; i < img.height(); ++i)
    {
        photoPixels.resize(img.height());
        for(int j = 0; j < img.width(); ++j)
        {
            photoPixels[i].resize(img.width());
            QColor color = img.toImage().pixelColor(j,i);
            photoPixels[i][j] = (color.black() > 1 && color.alpha() != 0 ? 1 : 0);    // 1 if some black and not transparent
        }
    }

    calculateDimension(photoPixels, 3, 5, 51);
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
            for(int ii = i; ii < (i/n+1)*n && !included; ++ii)
            {
                for(int jj = j; jj < (j/n+1)*n && !included; ++jj)
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

void MainWindow::calculateDimension(QVector<QVector<bool>> photoPixels, int l1, int l2, int l3)
{
    auto x1 =  countGrid(photoPixels, l1);
    auto x2 =  countGrid(photoPixels, l2);
    auto x3 =  countGrid(photoPixels, l3);

    Eigen::Matrix<double, 3, 2> A;
    Eigen::Matrix<double, 3, 1> Y;

    // matrix of ln of inverse of box lenghts
    A <<    -qLn(l1),  1,
            -qLn(l2),  1,
            -qLn(l3),  1;

    // matrix of ln of box counts
    Y <<    qLn(x1.first),
            qLn(x2.first),
            qLn(x3.first);

    auto M = (A.transpose()*A).inverse() * A.transpose() * Y;

    ui->dimensionLabel->setText(QString::number(M(0,0)));
}

