#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(QColor(0, 0, 0), 4));
    ui->widget->addGraph();
    ui->widget->graph(0)->setAntialiasedFill(false);
    ui->widget->graph(1)->setPen(QPen(QColor(0, 191, 255), 2));
    ui->widget->graph(1)->setAntialiasedFill(false);

    double A =1;
    double k1=10;
    double k2= 9;
    double dw=0.001;
    double w = 8;//*dw*k1/(k1-k2);

    wave test_wave_1 = wave(A, w, 0 , k1);
    wave test_wave_2 = wave(A, w+dw, 0, k2);
    wave test_wave_3 = wave(A, w-dw, 0, 3);
    waves.push_back(test_wave_1);
    waves.push_back(test_wave_2);
    //waves.push_back(test_wave_3);

    ui->widget->xAxis->setRange(0, 20);
    ui->widget->yAxis->setRange(-5, 5);

    ui->widget->yAxis->setLabel("Value");


/* Make top and right axis visible, but without ticks and label */
    ui->widget->xAxis->setVisible(false);
    ui->widget->yAxis->setVisible(true);

    ui->widget->xAxis->setTicks(false);
    ui->widget->yAxis->setTicks(true);

    ui->widget->xAxis->setTickLabels(false);
    ui->widget->yAxis->setTickLabels(true);

    h = 0.1;
    x.push_back(0);
    for (int i=1; i<=20/h; i++)
    {
        x.push_back(i*h);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    my_timer->start();
    /* Set up and initialize the graph plotting timer */
    connect(&timer_plot, SIGNAL(timeout()), this, SLOT(realtimePlot()));
    timer_plot.start(30);
}

void MainWindow::realtimePlot()
{
    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(1)->data()->clear();

    double key = my_timer->elapsed() / 1000.0;
    static double lastPointKey = 0;

    if(key - lastPointKey > 0.002)
    {
        for (auto& iter : x) {
            ui->widget->graph(0)->addData(iter, wave_pkg(iter, key));
            ui->widget->graph(1)->addData(iter, true_wave_pkg(iter, key));
        }
        //ui->widget->graph(0)->rescaleValueAxis();
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

    result = 2*amp[0]*cos((frq[0]-frq[1])*T/2 - (k[0]-k[1])*X/2)*cos((frq[0]+frq[1])*T/2 - (k[0]+k[1])*X/2);
    return result;
}

void MainWindow::on_pushButton_clicked()
{
    new QWidget();
}

