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

tm* CurrentTime()
{
    time_t t = time(NULL);
           tm* timePtr = localtime(&t);

           return timePtr;

};



double Sensor::GetAverage(std::vector<double> Data)
{
    double averageData = accumulate(Data.begin(), Data.end(), 0);
    buffer.clear();
    return averageData;
}

void Sensor::NewData(std::vector<double> data)
{
    buffer.push_back(data[sensorType]);
}

