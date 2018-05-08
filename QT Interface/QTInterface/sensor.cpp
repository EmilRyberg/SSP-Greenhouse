#include "sensor.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <numeric>

Sensor::Sensor(SerialPortReader *serialPortReader, int sensorType, QObject *parent = nullptr)
    : QObject(parent),
    serial(serialPortReader),
    sensorType(sensorType)
{
    connect(serial, &SerialPortReader::dataChanged, this, &Sensor::NewData);
}

double Sensor::GetAverage(std::vector<double> Data)
{
    double averageData = std::accumulate(Data.begin(), Data.end(), 0);
    buffer.clear();
    return averageData;
}

void Sensor::NewData(std::vector<double> data)
{
    buffer.push_back(data[sensorType]);
}

