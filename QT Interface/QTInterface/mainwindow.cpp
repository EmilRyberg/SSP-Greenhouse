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

    QTextStream standardOutput(stdout);
    QSerialPort serialPort;
    const QString serialPortName = "COM7";

    serialPort.setPortName(serialPortName);
    serialPort.setBaudRate(115200);
    if (!serialPort.open(QIODevice::ReadOnly)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                          .arg(serialPortName)
                          .arg(serialPort.errorString())
                       << endl;
    }

    SerialPortReader serialPortReader(&serialPort, ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}
