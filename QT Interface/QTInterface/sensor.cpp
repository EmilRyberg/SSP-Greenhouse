#include "sensor.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <numeric>
#include <ctime>

// Constructor that establishes a connection between SerialPortReader and Sensor
Sensor::Sensor(SerialPortReader *serialPortReader, int sensorType, QObject *parent)
    : QObject(parent),
    serial(serialPortReader),
    sensorType(sensorType)
{
    //connection between the dataChanged signal and NewData slot
    connect(serial, &SerialPortReader::dataChanged, this, &Sensor::NewData);
}

double Sensor::GetAverage()
{
    if (buffer.size() == 0) //checks if the buffer is empty
    {
        std::cout << "Buffer is empty, likely no data from Arduino!" << endl;
        return -1;
    }
    else
    {
        //Gets the average of the buffer through the use of accumulate, then clears the buffer
        double averageData = std::accumulate(buffer.begin(), buffer.end(), 0) / buffer.size();
        buffer.clear();
        return averageData;
    }
}

QDateTime Sensor::CurrentTime() //uses the Qt function QDataTime to get the current time
{
    return QDateTime::currentDateTime();
}

void Sensor::NewData(std::vector<double> data)
{
    //Gets called when data is changed, pushing the new data into the buffer
    buffer.push_back(data[sensorType]);
}

