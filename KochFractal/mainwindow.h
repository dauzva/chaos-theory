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
    void updateKochPoints();

private slots:
    void on_iterateBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    int iterationLevel = 0;
    int kochSize = 2;
    QList<QPointF> kochPoints;
    QList<QPointF> savedKochPoints;


};
#endif // MAINWINDOW_H
