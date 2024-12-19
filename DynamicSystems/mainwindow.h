#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event) override;

public slots:
    void updateTimer();
    void drawAxes(QPainter &painter, int margin, int canvasWidth, int canvasHeight,
                              double xMin, double xMax, double yMin, double yMax,
                  double xScale, double yScale);

private slots:
    void on_iterateBtn_clicked();
    void on_resetBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
};
#endif // MAINWINDOW_H
