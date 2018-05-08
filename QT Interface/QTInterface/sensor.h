#ifndef SENSOR_H
#define SENSOR_H

#include <QByteArray>
#include <QTextStream>
#include <vector>
#include <serialportreader.h>
#include <time.h>
#include <stdio.h>

class Sensor: public QObject
{
    Q_OBJECT

    public:
        explicit Sensor(SerialPortReader *serialPortReader, int sensorType, QObject *parent = (QObject *)0);
        tm* CurrentTime();

        double GetAverage(std::vector<double> data);

    public slots:
        void NewData(std::vector<double> data);

    private:
        SerialPortReader *serial;
        int sensorType;
        std::vector<double> buffer;
};

#endif // SENSOR_H
