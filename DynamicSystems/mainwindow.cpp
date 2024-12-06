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
    ui->canvas->resize(this->width()-400, this->height());

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(10); // Timer fires every 1 milliseconds
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Enable antialiasing for smoother rendering
    painter.setRenderHint(QPainter::Antialiasing);

    // Define graph margins
    int margin = 50;
    int canvasWidth = ui->canvas->width() - 2 * margin;
    int canvasHeight = ui->canvas->height() - 2 * margin;

    // Variables for dynamic scaling
    double numTicks =3.3;
    double xMin =0, xMax = numTicks;
    double yMin = std::numeric_limits<double>::max();
    double yMax = std::numeric_limits<double>::lowest();

    // Buffer to store calculated points
    QVector<QPointF> points;
    double c = 0.2;
    // **Step 1: Perform calculations and determine ranges**
    for (double x = xMin; x <= xMax; x += 0.001) {
        double y = 0.2;
        for (int j = 0; j < 200; ++j) {
            y = x*y*(1+c*(1-y));
            if (j > 50) { // Skip the first 50 iterations
                // Update min and max y-values dynamically
                yMin = std::min(yMin, y);
                yMax = std::max(yMax, y);

                // Store the point
                points.append(QPointF(x, y));
            }
        }
    }

    // Scale factors for mapping values to canvas
    double xScale = canvasWidth / (xMax - xMin);
    double yScale = canvasHeight / (yMax - yMin);

    // **Step 2: Draw Axes**
    // Draw x-axis
    painter.drawLine(margin, height() - margin, margin + canvasWidth, height() - margin);
    painter.drawText(margin + canvasWidth + 10, height() - margin, "X Axis");

    // Draw y-axis
    painter.drawLine(margin, height() - margin, margin, margin);
    painter.drawText(margin - 30, margin - 10, "Y Axis");

    // **Step 3: Draw Tick Marks and Labels**
    // X-axis ticks
    int numXTicks = 10;
    for (int i = 0; i <= numXTicks; ++i) {
        double xValue = xMin + i * (xMax - xMin) / numXTicks;
        int x = margin + (xValue - xMin) * xScale;
        painter.drawLine(x, height() - margin - 5, x, height() - margin + 5);
        painter.drawText(x - 10, height() - margin + 20, QString::number(xValue, 'f', 2));
    }

    // Y-axis ticks
    int numYTicks = 10;
    for (int i = 0; i <= numYTicks; ++i) {
        double yValue = yMin + i * (yMax - yMin) / numYTicks;
        int y = height() - margin - (yValue - yMin) * yScale;
        painter.drawLine(margin - 5, y, margin + 5, y);
        painter.drawText(margin - 40, y + 5, QString::number(yValue, 'f', 2));
    }

    // **Step 4: Plot Points**
    painter.setPen(QPen(Qt::red, 1)); // Set red pen for points
    for (const QPointF &point : points) {
        int graphX = margin + (point.x() - xMin) * xScale;
        int graphY = height() - margin - (point.y() - yMin) * yScale;
        painter.drawPoint(graphX, graphY);
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




