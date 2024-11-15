#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <complex>

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
    void generateKochLine();
    void animation();
    void animateFrame();

private slots:
    void on_resetButton_clicked();

    void on_f1Button_clicked();

    void on_f2Button_2_clicked();

    void on_f3Button_3_clicked();

private:
    Ui::MainWindow *ui;
    int iterationLevel = 0;
    int kochSize = 2;
    QList<QPointF> kochPoints;
    QList<QPointF> k3;
    QList<QPointF> savedKochPoints;
    QPointF bestPoint;
    bool isReset = false;

    QVector<QPointF> initialPoints; // Original points before transformation
    QVector<QPointF> targetPoints;  // Target points after transformation
    int currentFrame = 0;           // Current frame in the animation
    int totalFrames = 120;           // Total frames for smooth animation
    QTimer *animationTimer;         // Timer for controlling frame rate

    std::complex<double> a;
    std::complex<double> b;
    std::complex<double> c;
    std::complex<double> d;

    std::complex<double> (*transformFunc) (std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double>);

};
#endif // MAINWINDOW_H
