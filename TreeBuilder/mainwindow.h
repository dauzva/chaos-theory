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
    void updateTree();
    void updateMath();

private slots:
    void on_resetBtn_clicked();
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void resizeEvent(QResizeEvent* event) override;
    void on_iterationSlider_sliderMoved(int position);
    void on_iterationSlider_valueChanged(int value);

    void on_newLineBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    int iterationLevel = 1;
    int maxInitLines = 10;
    int initLinesCount = 0;
    QList<QPointF> initEndpoints;
    QList<QLineF> treeLines;
    QList<QLineF> currentTreeLines;
    QList<std::pair<qreal, qreal>> initMath;
    QPointF initPoint;
    QPointF currentEndpoint;
    bool isMouse = false;
    bool isNewLine = false;

};
#endif // MAINWINDOW_H
