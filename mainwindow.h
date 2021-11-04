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
    QVector<wave> waves;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void realtimePlot();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    double xBegin, xEnd, h, X;
    int N;
    unsigned long adc_data_g;

    QVector<double> x;
    QVector<double> y;

    QTimer timer_plot;
    QElapsedTimer tmp_timer;
    double pause_duration = 0;
    QElapsedTimer my_timer;


private:
    double wave_pkg(double x, double t);
    double true_wave_pkg(double x, double t);
};
#endif // MAINWINDOW_H
