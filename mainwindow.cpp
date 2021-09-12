#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    h = 0.1;
    xBegin = 0;
    xEnd = 10 + h;

    ui->widget->xAxis->setRange(0, 10);
    ui->widget->yAxis->setRange(-4, 4);

    for (X = xBegin; X <= xEnd; X+=h) {
        x.push_back(X);
        y.push_back(sin(X));
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
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

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}

