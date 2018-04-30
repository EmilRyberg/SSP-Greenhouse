#include "serialportreader.h"
#include "mainwindow.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <stdio.h>
#include <vector>

SerialPortReader::SerialPortReader(QSerialPort *serialPort, Ui::MainWindow *ui ,QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
    this->ui = ui;
}



void SerialPortReader::handleReadyRead()
{
    m_readData.append(m_serialPort->readAll());
    std::vector<double> parsedData = dataParser.parseData(&m_readData);

    if (!parsedData.empty())
    {
        for(double f : parsedData)
        {
            std::cout << f << std::endl;
        }
        double temperature = parsedData[0];
        ui->temperatureNumber->display(temperature);
    }
}


