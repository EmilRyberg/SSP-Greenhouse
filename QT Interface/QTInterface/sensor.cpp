#include "sensor.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <numeric>
#include <ctime>

Sensor::Sensor(SerialPortReader *serialPortReader, int sensorType, QObject *parent)
    : QObject(parent),
    serial(serialPortReader),
    sensorType(sensorType)
{
    connect(serial, &SerialPortReader::dataChanged, this, &Sensor::NewData);
}

double Sensor::GetAverage()
{
    if (buffer.size() == 0)
    {
        std::cout << "Buffer is empty, likely no data from Arduino!" << endl;
        return -1;
    }
    else
    {
        double averageData = std::accumulate(buffer.begin(), buffer.end(), 0) / buffer.size();
        buffer.clear();
        return averageData;
    }
}

QDateTime Sensor::CurrentTime()
{
    return QDateTime::currentDateTime();
}

void Sensor::NewData(std::vector<double> data)
{
    buffer.push_back(data[sensorType]);
}

