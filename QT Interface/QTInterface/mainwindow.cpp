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
    serialPortReader = new SerialPortReader();

    QTextStream standardOutput(stdout);
    const QString serialPortName = "COM3";
    int baudRate = 115200;
    if (!serialPortReader->AttachToSerial(serialPortName, baudRate)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                          .arg(serialPortName)
                          .arg(serialPortReader->GetLatestError())
                       << endl;
    }

    connect(serialPortReader, &SerialPortReader::temperatureChanged, this, &MainWindow::updateTemperature);
    connect(serialPortReader, &SerialPortReader::temperatureOutsideChanged, this, &MainWindow::updateTemperatureOutside);
    connect(serialPortReader, &SerialPortReader::humidityInsideChanged, this, &MainWindow::updateHumidityInside);
    connect(serialPortReader, &SerialPortReader::humidityOutsideChanged, this, &MainWindow::updateHumidityOutside);
    connect(serialPortReader, &SerialPortReader::lightChanged, this, &MainWindow::updateLight);
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
