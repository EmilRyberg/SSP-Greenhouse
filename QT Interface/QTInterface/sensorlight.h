#ifndef SENSORLIGHT_H
#define SENSORLIGHT_H

#include <QObject>
#include "sensor.h"

class SensorLight : public Sensor
{
    Q_OBJECT
public:
    explicit SensorLight(SerialPortReader *serialPortReader, int sensorType, QObject *parent = (QObject*)0);
    double GetTrimmedAverage();

signals:

public slots:

private:
    float scale(double A, double A1, double A2, double Min, double Max);
};

#endif // SENSORLIGHT_H
