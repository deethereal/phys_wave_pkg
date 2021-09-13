#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QElapsedTimer>
#include "wave.h"

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
    void realtimePlot();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    double xBegin, xEnd, h, X;
    int N;
    unsigned long adc_data_g;

    QVector <double> x, y;

    QTimer timer_plot;
    int time;
    QTimer *timer;
    QElapsedTimer *my_timer;

private:
    double wave_pkg(double x);
};
#endif // MAINWINDOW_H
