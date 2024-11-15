#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <complex>

std::complex<double> f1(std::complex<double> z, std::complex<double> a, std::complex<double> b, std::complex<double> c, std::complex<double> d) {
    return a * z * (1.0 - z);
}

std::complex<double> f2(std::complex<double> z, std::complex<double> a, std::complex<double> b, std::complex<double> c, std::complex<double> d) {
    return (a * z + b) / (c * z - d);
}

std::complex<double> f3(std::complex<double> z, std::complex<double> a, std::complex<double> b, std::complex<double> c, std::complex<double> d) {
    return a * z + b;
}

QVector<std::complex<double>> convertToComplex(const QVector<QPointF> &points) {
    QVector<std::complex<double>> complexPoints;
    for (const QPointF &point : points) {
        complexPoints.append(std::complex<double>(point.x(), point.y()));
    }
    return complexPoints;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->resize(this->width()-400, this->height());


    iterationLevel = 3;
    generateKochLine();


    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::animateFrame);
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

void MainWindow::generateKochLine()
{
    kochPoints.clear();
    QRect rect = ui->canvas->geometry();
    int ax, ay, aw, ah;
    rect.getRect(&ax, &ay, &aw, &ah);

    kochPoints.append(QPointF(ax, 2*(ay+ah)/3));
    kochPoints.append(QPointF(ax+aw, 2*(ay+ah)/3));
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
                QLineF l21 = QLineF(l1.p2(), l.pointAt((qreal)1/2));
                QLineF l22 = QLineF(l1.p2(), l.pointAt((qreal)2/3)).normalVector();
                QLineF l2 = QLineF(l1.p2(), QPointF(l21.p2().x()+l22.p2().x()-l1.p2().x(), l21.p2().y()+l22.p2().y()-l1.p2().y()));
                QLineF l3 = QLineF(l2.p2(), l.pointAt((qreal)2/3));
                QLineF l4 = QLineF(l3.p2(), p1);

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

void MainWindow::animation()
{
    QVector<std::complex<double>> newPoints;
    QVector<std::complex<double>> kochComplex = convertToComplex(kochPoints);

    // Clear previous points and calculate new transformed points
    kochPoints.clear();
    for (std::complex<double> point : kochComplex) {
        newPoints.append(transformFunc(point, a, b, c, d));
    }

    // Step 1: Calculate the bounding box of the transformed points
    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto &point : newPoints) {
        minX = std::min(minX, point.real());
        maxX = std::max(maxX, point.real());
        minY = std::min(minY, point.imag());
        maxY = std::max(maxY, point.imag());
    }

    // Step 2: Calculate scaling factors to fit within the QRect
    QRect rect = ui->canvas->geometry();
    double scaleX = rect.width() / (maxX - minX);
    double scaleY = rect.height() / (maxY - minY);
    double scale = std::min(scaleX, scaleY) * 0.9;

    // Step 3: Calculate offset to center points within rect
    double offsetX = rect.x() + rect.width() / 2;
    double offsetY = rect.y() + rect.height() / 2;

    // Step 4: Scale and translate points to fit in the QRect
    for (const auto &point : newPoints) {
        double x = (point.real() - (minX + maxX) / 2) * scale + offsetX;
        double y = (point.imag() - (minY + maxY) / 2) * scale + offsetY;
        kochPoints.append(QPointF(x, y));
    }
}

void MainWindow::animateFrame()
{
    if(isReset)
    {
        currentFrame = 0;
        update();
        return;
    }
    if (currentFrame == 0) {
        initialPoints = kochPoints;
        animation();
        targetPoints = kochPoints;
    }
    else if (currentFrame > totalFrames)
    {
        currentFrame = 0;
        initialPoints = kochPoints;
        animation();
        targetPoints = kochPoints;
    }


    kochPoints.clear(); // Clear current points for the next frame


    // Interpolate each point between initialPoints and targetPoints
    double t = static_cast<double>(currentFrame) / totalFrames; // Interpolation factor (0 to 1)
    for (int i = 0; i < initialPoints.size(); ++i) {
        double x = (1 - t) * initialPoints[i].x() + t * targetPoints[i].x();
        double y = (1 - t) * initialPoints[i].y() + t * targetPoints[i].y();
        kochPoints.append(QPointF(x, y));
    }

    currentFrame++;    // Move to the next frame
    update();          // Redraw the widget
}





void MainWindow::on_resetButton_clicked()
{
    isReset = true;
    kochPoints.clear();
    generateKochLine();
}


void MainWindow::on_f1Button_clicked()
{
    isReset = false;
    transformFunc = f1;
    a.real(ui->arBox->value());
    a.imag(ui->aiBox->value());
    b.real(ui->brBox->value());
    b.imag(ui->biBox->value());
    c.real(ui->crBox->value());
    c.imag(ui->ciBox->value());
    d.real(ui->drBox->value());
    d.imag(ui->diBox->value());
    animationTimer->start(10);
}


void MainWindow::on_f2Button_2_clicked()
{
    isReset = false;
    transformFunc = f2;
    a.real(ui->arBox->value());
    a.imag(ui->aiBox->value());
    b.real(ui->brBox->value());
    b.imag(ui->biBox->value());
    c.real(ui->crBox->value());
    c.imag(ui->ciBox->value());
    d.real(ui->drBox->value());
    d.imag(ui->diBox->value());
    animationTimer->start(10);
}


void MainWindow::on_f3Button_3_clicked()
{
    isReset = false;
    transformFunc = f3;
    a.real(ui->arBox->value());
    a.imag(ui->aiBox->value());
    b.real(ui->brBox->value());
    b.imag(ui->biBox->value());
    c.real(ui->crBox->value());
    c.imag(ui->ciBox->value());
    d.real(ui->drBox->value());
    d.imag(ui->diBox->value());
    animationTimer->start(10);
}

