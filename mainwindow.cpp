#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    //ui->widget->graph(0)->setAntialiasedFill(false);

   ui->widget->xAxis->setLabel("Time(s)");
   ui->widget->yAxis->setLabel("Value");


   /* Make top and right axis visible, but without ticks and label */
   ui->widget->xAxis->setVisible(false);
   ui->widget->yAxis->setVisible(true);
   ui->widget->xAxis->setTicks(false);
   ui->widget->yAxis->setTicks(false);
   ui->widget->xAxis->setTickLabels(false);
   ui->widget->yAxis->setTickLabels(true);

   // make left and bottom axes transfer their ranges to right and top axes:
   connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
   connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));
   /* Set up and initialize the graph plotting timer */
   connect(&timer_plot, SIGNAL(timeout()),this,SLOT(realtimePlot()));
   timer_plot.start(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    ui->widget->clearGraphs();
    timer->start(20);
    X = xBegin;
    x.clear();
    y.clear();
}

void MainWindow::realtimePlot()
{
    static QTime time(QTime::currentTime());
    double key = time.msecsSinceStartOfDay()/1000.0;
    static double lastPointKey = 0;
    if(key - lastPointKey > 0.002)
    {
        ui->widget->graph(0)->addData(key, 0.5);

        lastPointKey = key;
    }

    /* make key axis range scroll right with the data at a constant range of 8. */

    ui->widget->graph(0)->rescaleValueAxis();
    ui->widget->xAxis->setRange(key, 4, Qt::AlignRight);
    ui->widget->replot();
}

void MainWindow::TimerSlot()
{
    if (time <= 20*N) {
        if (X <= xEnd) {
            x.push_back(X);
            y.push_back(sin(X));
            X += h;
        }
        time += 20;
    }
    else {
        time = 0;
        timer->stop();
    }
}

