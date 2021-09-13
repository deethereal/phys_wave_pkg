#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFont>

QVector<wave> waves;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(QColor(40, 110, 255),2));
    ui->widget->graph(0)->setAntialiasedFill(false);
    wave test_wave = wave(2, 0.5, 0);
    wave new_wave = wave(0.5, 10,0);
    waves.push_back(test_wave);
    waves.push_back(new_wave);
    //ui->widget->yAxis->setRange(-1.5, 1.5);

   ui->widget->yAxis->setLabel("Value");


/* Make top and right axis visible, but without ticks and label */
   ui->widget->xAxis->setVisible(false);
   ui->widget->yAxis->setVisible(true);

   ui->widget->xAxis->setTicks(false);
   ui->widget->yAxis->setTicks(true);

   ui->widget->xAxis->setTickLabels(false);
   ui->widget->yAxis->setTickLabels(true);
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
    timer_plot.start(0);
}

void MainWindow::realtimePlot()
{
    double key = my_timer->elapsed() / 1000.0;
    static double lastPointKey = 0;
    if(key - lastPointKey > 0.002)
    {
        ui->widget->graph(0)->addData(key, wave_pkg(key)); // добавляет точку
        ui->widget->graph(0)->rescaleValueAxis();

        lastPointKey = key;
    }

    /* make key axis range scroll right with the data at a constant range of 8. */
    ui->widget->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->widget->replot(); //строит
}

double MainWindow::wave_pkg(double x)
{
    double amp, frq, phs;
    double result;
    result = 0;
    for (auto& iterator : waves) {
        amp = iterator.get_amplitude();
        frq = iterator.get_frequency();
        phs = iterator.get_phase();

        result += amp*sin(frq*x + phs);
    }
    return result;
}

void MainWindow::on_pushButton_clicked()
{
    new QWidget();
}

