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

private slots:
    void on_resetBtn_clicked();

    void on_animationSlider_valueChanged(int value);

    void on_startBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    int currentIterationLevel = 0;
    int maxIterationLevel = 5;

    QChar axiom;
    QList <std::pair <QString, double>> rules;
    QString megarule;
    double angle;
    double l;

};
#endif // MAINWINDOW_H
