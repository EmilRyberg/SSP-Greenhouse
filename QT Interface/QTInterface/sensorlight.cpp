#include "sensorlight.h"
#include "sensor.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <numeric>
#include <ctime>

SensorLight::SensorLight(SerialPortReader *serialPortReader, int sensorType, QObject *parent) :
    Sensor::Sensor(serialPortReader, sensorType, parent)
{
}

float SensorLight::scale(double A, double A1, double A2, double Min, double Max)
{
    double percentage = (A-A1)/(A1-A2);
    return (percentage) * (Min-Max)+Min;
}

double SensorLight::GetTrimmedAverage()
{
    double averageData = std::accumulate(buffer.begin(), buffer.end(), 0) / buffer.size();
    averageData = scale(averageData, 500, 1023, 0, 100);
    if (averageData < 0)
    {
        averageData = 0;
    }
    else if (averageData > 100)
    {
        averageData = 100;
    }
    buffer.clear();
    return averageData;
}
