#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFont>
#include <QtMath>

double A =1.3;
double k1=6;
double k2= 5;
double w2=7;
double w1 = 10;//*dw*k1/(k1-k2);
double x_len = 6*M_PI;
double start_x=M_PI;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(QColor(0, 191, 255), 3));
    ui->widget->graph(1)->setPen(QPen(QColor(0, 255, 0), 6));
    ui->widget->graph(2)->setPen(QPen(QColor(0, 255, 0), 6));
    ui->widget->graph(3)->setPen(QPen(QColor(0, 255, 0), 6));
    ui->widget->graph(4)->setPen(QPen(QColor(255, 0, 0), 8));
    ui->widget->graph(0)->setAntialiasedFill(true);


    ui->widget->xAxis->setRange(0, x_len);
    ui->widget->yAxis->setRange(-5, 5);

    ui->widget->yAxis->setLabel("Value");


/* Make top and right axis visible, but without ticks and label */
    ui->widget->xAxis->setVisible(true);
    ui->widget->yAxis->setVisible(true);
    ui->widget->xAxis->setTicks(true);
    ui->widget->yAxis->setTicks(true);

    ui->widget->xAxis->setTickLabels(true);
    ui->widget->yAxis->setTickLabels(true);

    h = 0.05;
    x.push_back(0);
    for (int i=1; i<=x_len/h; i++)
    {
        x.push_back(i*h);
    }
    connect(&timer_plot, SIGNAL(timeout()), this, SLOT(realtimePlot()));
    //connect(&speed_plot, SIGNAL(timeout()), this, SLOT(grSpeed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    w1 = ui->w1->text().toDouble();
    w2 = ui->w2->text().toDouble();
    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(1)->data()->clear();
    ui->widget->graph(2)->data()->clear();
    ui->widget->graph(3)->data()->clear();
    ui->widget->graph(4)->data()->clear();
    ui->widget->replot();
    waves.clear();
    wave test_wave_1 = wave(A, w1, 0 , k1);
    wave test_wave_2 = wave(A, w2, 0, k2);
    waves.push_back(test_wave_1);
    waves.push_back(test_wave_2);
    /* Set up and initialize the graph plotting timer */
    my_timer->start();
    timer_plot.start(1);


}

void MainWindow::realtimePlot()
{


    double key = my_timer->elapsed() / 1000.0;

    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(1)->data()->clear();
    ui->widget->graph(2)->data()->clear();
    ui->widget->graph(3)->data()->clear();
    ui->widget->graph(4)->data()->clear();


    double lastPointKey = 0;
    double value = key*(w1-w2)/(k1-k2);
    double phase_dot = key*(w1+w2)/(k1+k2);
    int n=1;
    double value1,value2,value3;
    if(key - lastPointKey > 0.001)
    {

        for (auto& iter : x) {
            while (value>=x_len)
            {
                value-=x_len;
            }
            while (phase_dot>=x_len)
            {
                phase_dot-=x_len;
                n=-n;

            }

             value1 = value+start_x;
             value2 = value-start_x;
             value3 = value+3*start_x;
            if (value1>=x_len)
            {
                value1-=x_len;
            }
            if (value2>=x_len)
            {
                value2-=x_len;
            }
            if (value3>=x_len)
            {
                value3-=x_len;
            }

            ui->widget->graph(0)->addData(iter, wave_pkg(iter, key));
            ui->widget->graph(1)->addData(value1, 0);
            ui->widget->graph(2)->addData(value2, 0);
            ui->widget->graph(3)->addData(value3, 0);
            ui->widget->graph(4)->addData(phase_dot, n*true_wave_pkg(phase_dot, key));
        }
        lastPointKey = key;
    }
    //ui->widget->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->widget->replot();
}

double MainWindow::wave_pkg(double X, double T)
{
    double amp, frq, phs,k;
    double result;
    result = 0;

    for (auto& iterator : waves) {
        amp = iterator.get_amplitude();
        frq = iterator.get_frequency();
        phs = iterator.get_phase();
        k  = iterator.get_kvalue();

        result += amp*cos(frq*T - k*X + phs);
    }
    return result;
}

double MainWindow::true_wave_pkg(double X, double T)
{
    int size = waves.size();
    double amp[size], frq[size], phs[size],k[size];
    double result;
    int i=0;
    for (auto& iterator : waves) {
        amp[i] = iterator.get_amplitude();
        frq[i] = iterator.get_frequency();
        phs[i] = iterator.get_phase();
        k[i]  = iterator.get_kvalue();
        i++;
    }

    result = 2*amp[0]*cos((frq[0]-frq[1])*T/2 - (k[0]-k[1])*X/2);
    return result;
}

void MainWindow::on_pushButton_clicked()
{
    new QWidget();
}

