#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportreader.h"
#include "controller.h"
#include "chart.h"
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>
#include <QChart>
#include <QLineSeries>
#include <QChartView>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(new Controller)
{
    ui->setupUi(this);
    chart = new Chart;
    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartView = new QChartView(chart, ui->temperatureFrame);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(ui->temperatureFrame->size());
    connect(controller, &Controller::updateUiValues, this, &MainWindow::updateValues);
    connect(controller, &Controller::updateTemperatureGraph, this, &MainWindow::updateTemperatureGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
}

void MainWindow::updateValues(double temperature, double temperatureOutside, double humidity, double humidityOutside, double light)
{
    ui->temperatureNumber->display(temperature);
    ui->temperatureOutsideNumber->display(temperatureOutside);
    ui->humidityInsideNumber->display(humidity);
    ui->humidityOutsideNumber->display(humidityOutside);
    ui->lightNumber->display(light);
}

void MainWindow::updateTemperatureGraph(double temperature, double temperatureOutside, int seconds)
{
    chart->Append(seconds, temperature);
}
