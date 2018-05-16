#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "serialportreader.h"
#include "sensor.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    void fanOn();
    void fanOff();
    void lightOn();
    void lightOff();
    void waterOn();
    void waterOff();
    void heatOn();
    void heatOff();

signals:
    void updateUiValues(double temperature, double temperatureOutside, double humidity, double humidityOutside, double light);
    void updateTemperatureGraph(double temperature, double temperatureOutside, int seconds);
    void updateHumidityGraph(double humidity, double humidityOutside, int seconds);
    void updateLightGraph(double light, int seconds);

public slots:
    void update();

private:
    const int fanPin = 2;
    const int lightPinR = 3;
    const int lightPinG = 3;
    const int lightPinB = 3;
    const int waterPin = 4;
    const int heatPin = 5;

    float temperatureMin, temperatureMax;
    float humidityMin, humidityMax;
    int lightMin, lightMax;

    double temperature;
    double temperatureOutside;
    double humidity;
    double humidityOutside;
    double light;

    int time;

    SerialPortReader *serialReader = nullptr;

    Sensor *temperatureSensor;
    Sensor *temperatureOutsideSensor;
    Sensor *humiditySensor;
    Sensor *humidityOutsideSensor;
    Sensor *lightSensor;

    QTimer *timer;

    void doLogic();
};

#endif // CONTROLLER_H
