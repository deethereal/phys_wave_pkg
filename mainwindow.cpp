#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <iostream>>
#include <QtMath>

double A =1.3;
double k1=6;
double k2= 5;
double w2=7;
double w1 = 10; //*dw*k1/(k1-k2);
double x_len = 6*M_PI;
double start_x=M_PI;

double key;
double lastPointKey;
double value;
double phase_dot;
double value1,value2,value3;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(QColor(0, 191, 255), 3));
    ui->widget->graph(0)->setAntialiasedFill(true);
    ui->widget->graph(0)->setName(QString("Wave packet"));


    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(QColor(0, 255, 0), 4));
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->widget->graph(1)->setName(QString("Group speed"));


    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(QColor(0, 255, 0), 4));
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);


    ui->widget->addGraph();
    ui->widget->graph(3)->setPen(QPen(QColor(0, 255, 0), 4));
    ui->widget->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);


    ui->widget->addGraph();
    ui->widget->graph(4)->setPen(QPen(QColor(255, 0, 0), 5));
    ui->widget->graph(4)->setScatterStyle(QCPScatterStyle::ssSquare);

    ui->widget->graph(4)->setName(QString("Phase speed"));



    ui->widget->xAxis->setRange(0, x_len);
    ui->widget->yAxis->setRange(-5, 7);

    ui->widget->yAxis->setLabel("Value");

    ui->widget->xAxis->setVisible(true);
    ui->widget->yAxis->setVisible(true);

    ui->widget->xAxis->setTicks(true);
    ui->widget->yAxis->setTicks(true);

    ui->widget->xAxis->setTickLabels(true);
    ui->widget->yAxis->setTickLabels(true);
    QCPLegend *arLegend = new QCPLegend;
    ui->widget->axisRect()->insetLayout()->addElement(arLegend, Qt::AlignTop|Qt::AlignRight);
    arLegend->setLayer("legend");
    ui->widget->setAutoAddPlottableToLegend(false); // would add to the main legend (in the primary axis rect)
    arLegend->addItem(new QCPPlottableLegendItem(arLegend, ui->widget->graph(0)));
    arLegend->addItem(new QCPPlottableLegendItem(arLegend, ui->widget->graph(1)));

    arLegend->addItem(new QCPPlottableLegendItem(arLegend, ui->widget->graph(4)));
    arLegend->setIconSize(10,10);
    h = 0.05;

    x.push_back(0);
    for (int i=1; i<=x_len/h; i++)
    {
        x.push_back(i*h);
    }

    connect(&timer_plot, SIGNAL(timeout()), this, SLOT(realtimePlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    w1 = ui->w1->text().toDouble();
    w2 = ui->w2->text().toDouble();
    k1 = ui->k1->text().toDouble();
    k2 = ui->k2->text().toDouble();

    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(1)->data()->clear();
    ui->widget->graph(2)->data()->clear();
    ui->widget->graph(3)->data()->clear();
    ui->widget->graph(4)->data()->clear();

    //ui->widget->replot();

    waves.clear();
    wave test_wave_1 = wave(A, w1, 0 , k1);
    wave test_wave_2 = wave(A, w2, 0, k2);
    waves.push_back(test_wave_1);
    waves.push_back(test_wave_2);
    my_timer.restart();
    timer_plot.start(1);

}

void MainWindow::realtimePlot()
{

    key = my_timer.elapsed() / 1000.0 + pause_duration;

    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(1)->data()->clear();
    ui->widget->graph(2)->data()->clear();
    ui->widget->graph(3)->data()->clear();
    ui->widget->graph(4)->data()->clear();

    lastPointKey = 0;
    value = key*(w1-w2)/(k1-k2);
    phase_dot = key*(w1+w2)/(k1+k2);

    int n=1;
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
                if (int(k1+k2)%2!=0)
                    n=-n;
            }

            value1 = value+start_x;
            value2 = value-start_x;
            value3 = value+3*start_x;

            //value1 = value1+(value1<0)*x_len-(x_len>=value1)*x_len; почему-то не сработало(

            while (value1>=x_len)
            {
                value1-=x_len;

            }
            while (value1<0)
            {
                value1+=x_len;
                //QTextStream(stdout) <<"был тут"<< "\n";

            }
            while (value2>=x_len)
            {
                value2-=x_len;
            }
            while (value2<0)
            {
                value2+=x_len;
            }
            while (value3>=x_len)
            {
                value3-=x_len;
            }
            while (value3<0)
            {
                value3+=x_len;
            }
            //QTextStream(stdout) <<value1<< "\n";


            ui->widget->graph(0)->addData(iter, wave_pkg(iter, key));

            ui->widget->graph(1)->addData(value1, 0);
            ui->widget->graph(2)->addData(value2, 0);
            ui->widget->graph(3)->addData(value3, 0);

            ui->widget->graph(4)->addData(phase_dot, n*true_wave_pkg(phase_dot, key));
        }
        lastPointKey = key;
    }
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

void MainWindow::on_pushButton_3_clicked()
{
    if (timer_plot.isActive()) {
        timer_plot.stop();
        pause_duration+= my_timer.elapsed()/1000.0;
    }
    else {
        my_timer.restart();
        timer_plot.start();
    }
}
