#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStack>

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
    void iterate();
    void startDrawingAnimation();
    void updateDrawing();
    bool parseAndAppendRules();

private slots:
    void on_resetBtn_clicked();

    void on_startBtn_clicked();

    void on_angleSelect_valueChanged(double arg1);

    void on_lenghtSelect_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    int currentIterationLevel = 0;
    int maxIterationLevel = 6;

    QChar axiom;
    QList <std::pair <QString, double>> rules;
    QString megarule;
    double angle;
    double l;
    bool fastdraw = false;
    bool isUpdating = false;


    QTimer *drawTimer;                        // Timer for animation
    int currentStep;                          // Current step in drawing
    QVector<QChar> drawingSteps;              // Sequence of steps to draw
    double x, y;                              // Current position
    double currentAngle;                      // Current angle
    QStack<QPair<QPointF, double>> localStateStack;
};
#endif // MAINWINDOW_H
