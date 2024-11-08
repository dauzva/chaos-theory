#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

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

private slots:
    void on_loadButton_clicked();

    void on_calculateButton_clicked();

private:
    QString pngFolder = "D:\\chaos-theory\\FractalDimensions\\png\\";
    Ui::MainWindow *ui;
    QPixmap img;
    QVector<QVector<bool>> photoPixels;

    std::pair<int, int> countGrid(QVector<QVector<bool>> M, int n);
};
#endif // MAINWINDOW_H
