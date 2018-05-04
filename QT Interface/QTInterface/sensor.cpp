#include "sensor.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <numeric>

Sensor::Sensor(SerialPortReader *serialPortReader, int sensorType, QObject *parent)
    : QObject(parent),
    serial(serialPortReader),
    sensorType(sensorType)
{
    connect(serial, &SerialPortReader::dataChanged, this, &Sensor::NewData);
}

time_t Time()
{
    time_t rawtime;
      struct tm * timeinfo;

      time (&rawtime);
      timeinfo = localtime (&rawtime);
      return asctime(timeinfo)
};



double Sensor::GetAverage(std::vector<double> Data)
{
    double averageData = accumulate(Data.begin(), Data.end(), 0.0/Data.size);
    buffer.clear();
    return averageData;
}

void Sensor::NewData(std::vector<double> data)
{
    buffer.push_back(data[sensorType]);
}

