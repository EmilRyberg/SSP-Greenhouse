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
    const QString serialPortName = "COM7";
    int baudRate = 115200;
    if (!serialPortReader->AttachToSerial(serialPortName, baudRate)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                          .arg(serialPortName)
                          .arg(serialPortReader->GetLatestError())
                       << endl;
    }

    connect(serialPortReader, &SerialPortReader::temperatureChanged, this, &MainWindow::updateTemperature);
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
