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
<<<<<<< HEAD
        explicit Sensor(SerialPortReader *serialPortReader, int sensorType, QObject *parent = nullptr);
        time_t Time();
=======
        explicit Sensor(SerialPortReader *serialPortReader, int sensorType, QObject *parent = (QObject *)0);
        tm* CurrentTime();

>>>>>>> a641f34ef067b162365737d00da0dc495d192288
        double GetAverage(std::vector<double> data);

    public slots:
        void NewData(std::vector<double> data);

    private:
        SerialPortReader *serial;
        int sensorType;
        std::vector<double> buffer;
};

#endif // SENSOR_H
