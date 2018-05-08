#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportreader.h"
#include "controller.h"
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(new Controller)
{
    ui->setupUi(this);
    connect(controller, &Controller::updateUiValues, this, &MainWindow::updateValues);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serialPortReader;
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
