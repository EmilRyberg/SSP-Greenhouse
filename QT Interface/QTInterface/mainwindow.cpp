#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportreader.h"
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serialPortReader;
}

void MainWindow::updateTemperature(double value)
{
    ui->temperatureNumber->display(value);
}

void MainWindow::updateTemperatureOutside(double value)
{
    ui->temperatureOutsideNumber->display(value);
}

void MainWindow::updateHumidityInside(double value)
{
    ui->humidityInsideNumber->display(value);
}

void MainWindow::updateHumidityOutside(double value)
{
    ui->humidityOutsideNumber->display(value);
}

void MainWindow::updateLight(double value)
{
    ui->lightNumber->display(value);
}
