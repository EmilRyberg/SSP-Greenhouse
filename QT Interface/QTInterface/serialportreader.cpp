#include "serialportreader.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <stdio.h>
#include <vector>

SerialPortReader::SerialPortReader(QObject *parent) :
    QObject(parent),
    serialPort(new QSerialPort()),
    m_standardOutput(stdout)
{
}

SerialPortReader::~SerialPortReader()
{
    delete serialPort;
}

bool SerialPortReader::AttachToSerial(QString name, int baudRate)
{
    serialPort->setPortName(name);
    serialPort->setBaudRate(baudRate);

    if (!serialPort->open(QIODevice::ReadOnly)) {
        latestError = serialPort->errorString();
        return false;
    }


    connect(serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
    return true;
}

QString SerialPortReader::GetLatestError() const
{
    return latestError;
}

void SerialPortReader::handleReadyRead()
{
    m_readData.append(serialPort->readAll());
    std::vector<double> parsedData = dataParser.parseData(&m_readData);

    if (!parsedData.empty())
    {
        for(double f : parsedData)
        {
            std::cout << f << std::endl;
        }
        double temperature = parsedData[0];
        emit temperatureChanged(temperature);
    }
}


