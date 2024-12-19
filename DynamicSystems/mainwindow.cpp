#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QPainterPath>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->resize(this->width()/2, this->height()/2);
    ui->canvas2->resize(this->width()/2, this->height()/2);
    ui->canvas3->resize(this->width()/2, this->height()/2);

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
    painter.setRenderHint(QPainter::Antialiasing);

    const int margin = 0;
    const int canvasWidth = ui->canvas->width();
    const int canvasHeight = ui->canvas->height();


    double c = 5; // <---------------------------------------------- to be transformed by slider
    double e = 0.0001;
    double xMin = 0, xMax = e; // Increased xMax to 4
    double yMin = std::numeric_limits<double>::max();
    double yMax = std::numeric_limits<double>::lowest();

    QVector<QPointF> points;
    bool ok = false;
    bool bi = false;
    bool printed = false;


    for (double x = xMin; x <= xMax; x += e) {
        double y = 0.2;
        ok = false;
        for (int iter = 0; iter < 300; ++iter) {
            y = x * y * (1 + c * (1 - y));
            if (iter > 250) {

                y = std::min(std::max(y, 0.0), 10.0);

                yMin = std::min(yMin, y);
                yMax = std::max(yMax, y);
                points.append(QPointF(x, y));


                if((y > e && !ok && x+e>xMax) )
                {
                    ok = true;
                    bi =true;
                    xMax+=e;
                    if(!printed)
                        qDebug() << x;
                    printed = true;
                }
                else if(y < e && !bi && !ok)
                {
                    ok = true;
                    xMax+=e;
                }
            }
        }
    }

    // Scale factors
    double xScale = canvasWidth / (xMax - xMin);
    double yScale = canvasHeight / (yMax - yMin);

    // Draw axes
    drawAxes(painter, margin, canvasWidth, canvasHeight, xMin, xMax, yMin, yMax, xScale, yScale, ui->canvas);
    drawAxes(painter, margin, ui->canvas2->width(), ui->canvas2->height(), xMin, xMax, yMin, yMax, xScale, yScale, ui->canvas2);
    drawAxes(painter, margin, ui->canvas3->width(), ui->canvas3->height(), xMin, xMax, yMin, yMax, xScale, yScale, ui->canvas3);

    // Draw points
    painter.setPen(QPen(Qt::red, 1));
    for (const QPointF &point : points) {
        int graphX = margin + (point.x() - xMin) * xScale;
        int graphY = height() - margin - (point.y() - yMin) * yScale;
        painter.drawPoint(graphX, graphY);
    }
}

void MainWindow::drawAxes(QPainter &painter, int margin, int canvasWidth, int canvasHeight,
                          double xMin, double xMax, double yMin, double yMax,
                          double xScale, double yScale, QWidget* _canvas)
{
    // Draw X-axis
    painter.drawLine(_canvas->x()+margin, _canvas->y()+canvasHeight , _canvas->x()+ margin + canvasWidth, _canvas->y()+canvasHeight );
    //painter.drawText(margin + canvasWidth + 10, _canvas->y() - margin, "X Axis");

    // Draw Y-axis
    painter.drawLine(_canvas->x()+margin, _canvas->y()+canvasHeight , _canvas->x()+margin, _canvas->y() );
    //painter.drawText(_canvas->x()+margin - 30, _canvas->y()+canvasHeight - 10, "Y Axis");

    // Add tick marks and labels for X-axis
    const int numXTicks = 10;
    for (int i = 0; i <= numXTicks; ++i) {
        double xValue = xMin + i * (xMax - xMin) / numXTicks;
        int x = _canvas->x()+margin + (xValue - xMin) * xScale;
        painter.drawLine(x, _canvas->y()+canvasHeight - margin - 5, x, _canvas->y()+canvasHeight - margin + 5);
        painter.drawText(x - 10, _canvas->y()+canvasHeight - margin + 20, QString::number(xValue, 'f', 2));
    }

    // Add tick marks and labels for Y-axis
    const int numYTicks = 10;
    for (int i = 0; i <= numYTicks; ++i) {
        double yValue = yMin + i * (yMax - yMin) / numYTicks;
        int y = _canvas->y() - margin - (yValue - yMin) * yScale;
        painter.drawLine(_canvas->x() + margin - 5, y+canvasHeight, _canvas->x() + margin + 5, y+canvasHeight);
        painter.drawText(_canvas->x() + margin - 35, y+canvasHeight + 5, QString::number(yValue, 'f', 2));
    }
}

void MainWindow::on_iterateBtn_clicked()
{

}

void MainWindow::on_resetBtn_clicked()
{

}

void MainWindow::updateTimer()
{
    this->update();
}




