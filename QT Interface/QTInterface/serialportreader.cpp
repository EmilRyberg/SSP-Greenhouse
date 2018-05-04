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
        double outsideTemperature = parsedData[1];
        double humidityInside = parsedData[2];
        double humidityOutside = parsedData[3];
        double light = parsedData[4];
        std::vector<double> sensorData = parsedData;
        emit temperatureChanged(temperature);
        emit temperatureOutsideChanged(outsideTemperature);
        emit humidityInsideChanged(humidityInside);
        emit humidityOutsideChanged(humidityOutside);
        emit lightChanged(light);

        emit dataChanged(sensorData); //new general datavector
    }
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


