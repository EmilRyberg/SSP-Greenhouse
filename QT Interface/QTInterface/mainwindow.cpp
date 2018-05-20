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
#include <iostream>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(new Controller)
{
    ui->setupUi(this);

    chartTemperature = new Chart(0, 40);
    chartTemperature->legend()->setAlignment(Qt::AlignBottom);
    chartTemperature->setAnimationOptions(QChart::AllAnimations);
    chartTemperature->SetLabels("Temp. inside", "Temp. outside");
    QChartView *chartView = new QChartView(chartTemperature);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartsLayout->addWidget(chartView);

    chartHumidity = new Chart(0, 40);
    chartHumidity->legend()->setAlignment(Qt::AlignBottom);
    chartHumidity->setAnimationOptions(QChart::AllAnimations);
    chartHumidity->SetLabels("Humidity inside", "Humidity outside");
    QChartView *chartView2 = new QChartView(chartHumidity);
    chartView2->setRenderHint(QPainter::Antialiasing);
    ui->chartsLayout->addWidget(chartView2);

    chartLight = new Chart(0, 80, false);
    chartLight->legend()->setAlignment(Qt::AlignBottom);
    chartLight->setAnimationOptions(QChart::AllAnimations);
    chartLight->SetLabels("Light");
    QChartView *chartViewLight = new QChartView(chartLight);
    chartView2->setRenderHint(QPainter::Antialiasing);
    ui->chartsLayout->addWidget(chartViewLight);

    connect(controller, &Controller::updateUiValues, this, &MainWindow::updateValues);
    connect(controller, &Controller::updateTemperatureGraph, this, &MainWindow::updateTemperatureGraph);
    connect(controller, &Controller::updateHumidityGraph, this, &MainWindow::updateHumidityGraph);
    connect(controller, &Controller::updateLightGraph, this, &MainWindow::updateLightGraph);
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

void MainWindow::updateTemperatureGraph(double temperature, double temperatureOutside, QDateTime time)
{
    chartTemperature->Append(time, temperature, temperatureOutside);
}

void MainWindow::updateHumidityGraph(double humidity, double humidityOutside, QDateTime time)
{
    chartHumidity->Append(time, humidity, humidityOutside);
}

void MainWindow::updateLightGraph(double light, QDateTime time)
{
    chartLight->AppendSingle(time, light);
}
