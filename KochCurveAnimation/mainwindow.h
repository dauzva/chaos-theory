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
    void generateKochLine();
    void animation();
    void animateFrame();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    int iterationLevel = 0;
    int kochSize = 2;
    QList<QPointF> kochPoints;
    QList<QPointF> k3;
    QList<QPointF> savedKochPoints;
    QPointF bestPoint;

    QVector<QPointF> initialPoints; // Original points before transformation
    QVector<QPointF> targetPoints;  // Target points after transformation
    int currentFrame = 0;           // Current frame in the animation
    int totalFrames = 120;           // Total frames for smooth animation
    QTimer *animationTimer;         // Timer for controlling frame rate

};
#endif // MAINWINDOW_H
