#include "serialportreader.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <stdio.h>
#include <vector>
#include "QTimer"

SerialPortReader::SerialPortReader(QObject *parent) :
    QObject(parent),
    serialPort(new QSerialPort()),
    m_standardOutput(stdout)
{
    srand(123456);
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

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SerialPortReader::emulateSerialData);
        timer->start(2000);

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
        double outsideTemperature = parsedData[1];
        double humidityInside = parsedData[2];
        double humidityOutside = parsedData[3];
        double light = parsedData[4];
        std::vector<double> sensorData = parsedData;

        emit dataChanged(sensorData); //new general datavector
    }
}

void SerialPortReader::emulateSerialData()
{
    std::cout << "fake data emitted" << std::endl;
    std::vector<double> fakeSensorData(5);
    fakeSensorData[0] = rand() % 10 + 25;
    fakeSensorData[1] = rand() % 10 + 15;
    fakeSensorData[2] = rand() % 20 + 60;
    fakeSensorData[3] = rand() % 20 + 40;
    fakeSensorData[4] = rand() % 80 + 10;
    emit dataChanged(fakeSensorData);
}
    
void SerialPortReader::SendData(int pin, char method, int value)
{
    std::string command = "{" + pin;
    command += ",";
    command += method;
    command += ",";
    command += value;
    command += "}";
    serialPort->write(command.c_str());
    std::cout << "sent " << command << std::endl;
}


