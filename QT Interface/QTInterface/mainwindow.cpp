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

    //Sets up chart for temperature
    chartTemperature = new Chart(0, 40);
    chartTemperature->legend()->setAlignment(Qt::AlignBottom);
    chartTemperature->setAnimationOptions(QChart::AllAnimations);
    chartTemperature->SetLabels("Temp. inside", "Temp. outside");
    QChartView *chartView = new QChartView(chartTemperature);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartsLayout->addWidget(chartView);

    //Sets up chart for humidity
    chartHumidity = new Chart(0, 40);
    chartHumidity->legend()->setAlignment(Qt::AlignBottom);
    chartHumidity->setAnimationOptions(QChart::AllAnimations);
    chartHumidity->SetLabels("Humidity inside", "Humidity outside");
    QChartView *chartView2 = new QChartView(chartHumidity);
    chartView2->setRenderHint(QPainter::Antialiasing);
    ui->chartsLayout->addWidget(chartView2);

    //Sets up chart for light
    chartLight = new Chart(0, 80, false);
    chartLight->legend()->setAlignment(Qt::AlignBottom);
    chartLight->setAnimationOptions(QChart::AllAnimations);
    chartLight->SetLabels("Light");
    QChartView *chartViewLight = new QChartView(chartLight);
    chartView2->setRenderHint(QPainter::Antialiasing);
    ui->chartsLayout->addWidget(chartViewLight);

    //Connects to  get data from controller.cpp
    connect(controller, &Controller::updateUiValues, this, &MainWindow::updateValues);
    connect(controller, &Controller::updateTemperatureGraph, this, &MainWindow::updateTemperatureGraph);
    connect(controller, &Controller::updateHumidityGraph, this, &MainWindow::updateHumidityGraph);
    connect(controller, &Controller::updateLightGraph, this, &MainWindow::updateLightGraph);

    connect(ui->minTemperatureInput, SIGNAL(valueChanged(int)), controller, SLOT(updateMinTemperature(int)));
    connect(ui->maxTemperatureInput, SIGNAL(valueChanged(int)), controller, SLOT(updateMaxTemperature(int)));
    connect(ui->minHumidityInput, SIGNAL(valueChanged(int)), controller, SLOT(updateMinHumidity(int)));
    connect(ui->maxHumidityInput, SIGNAL(valueChanged(int)), controller, SLOT(updateMaxHumidity(int)));

    connect(controller, &Controller::updateUiSerialStatus, this, &MainWindow::updateSerialStatus);
    connect(controller, &Controller::updateUiFanStatus, this, &MainWindow::updateFanStatus);
    connect(controller, &Controller::updateUiHeaterStatus, this, &MainWindow::updateHeaterStatus);
    connect(controller, &Controller::updateUiLightStatus, this, &MainWindow::updateLightStatus);
    connect(controller, &Controller::updateUiWaterStatus, this, &MainWindow::updateWaterStatus);

    ui->serialStatus->setStyleSheet("QCheckBox::indicator:unchecked {image: url(../QTInterface/img/red.png);} QCheckBox::indicator:checked {image: url(../QTInterface/img/green.png);}");
    ui->fanStatus->setStyleSheet("QCheckBox::indicator:unchecked {image: url(../QTInterface/img/darkGreen.png);} QCheckBox::indicator:checked {image: url(../QTInterface/img/green.png);}");
    ui->heatStatus->setStyleSheet("QCheckBox::indicator:unchecked {image: url(../QTInterface/img/darkGreen.png);} QCheckBox::indicator:checked {image: url(../QTInterface/img/green.png);}");
    ui->lightStatus->setStyleSheet("QCheckBox::indicator:unchecked {image: url(../QTInterface/img/darkGreen.png);} QCheckBox::indicator:checked {image: url(../QTInterface/img/green.png);}");
    ui->waterStatus->setStyleSheet("QCheckBox::indicator:unchecked {image: url(../QTInterface/img/darkGreen.png);} QCheckBox::indicator:checked {image: url(../QTInterface/img/green.png);}");


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

void MainWindow::updateSerialStatus(bool s)
{
    ui->serialStatus->setChecked(s);
}
void MainWindow::updateFanStatus(bool s)
{
    ui->fanStatus->setChecked(s);
}
void MainWindow::updateHeaterStatus(bool s)
{
    ui->heatStatus->setChecked(s);
}
void MainWindow::updateLightStatus(bool s)
{
    ui->lightStatus->setChecked(s);
}
void MainWindow::updateWaterStatus(bool s)
{
    ui->waterStatus->setChecked(s);
}
