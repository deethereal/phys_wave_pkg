#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void TimerSlot();

private:
    Ui::MainWindow *ui;
    double xBegin, xEnd, h, X;
    int N;

    QVector <double> x, y;
    QTimer *timer;
    int time;
};
#endif // MAINWINDOW_H
