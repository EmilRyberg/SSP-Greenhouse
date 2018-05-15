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

    chartTemperature = new Chart;
    chartTemperature->setTitle("Dynamic spline chart");
    chartTemperature->legend()->hide();
    chartTemperature->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartView = new QChartView(chartTemperature, ui->temperatureFrame);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(ui->temperatureFrame->size());

    chartHumidity = new Chart;
    chartHumidity->setTitle("Dynamic spline chart");
    chartHumidity->legend()->hide();
    chartHumidity->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartView2 = new QChartView(chartHumidity, ui->humidityFrame);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->resize(ui->humidityFrame->size());

    connect(controller, &Controller::updateUiValues, this, &MainWindow::updateValues);
    connect(controller, &Controller::updateTemperatureGraph, this, &MainWindow::updateTemperatureGraph);
    connect(controller, &Controller::updateHumidityGraph, this, &MainWindow::updateHumidityGraph);
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
    chartTemperature->Append(seconds, temperature);
}

void MainWindow::updateHumidityGraph(double humidity, double humidityOutside, int seconds)
{
    chartHumidity->Append(seconds, humidity);
}
