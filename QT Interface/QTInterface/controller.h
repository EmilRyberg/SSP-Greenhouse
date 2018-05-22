#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "serialportreader.h"
#include "sensor.h"
#include "sensorlight.h"

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
    void updateTemperatureGraph(double temperature, double temperatureOutside, QDateTime time);
    void updateHumidityGraph(double humidity, double humidityOutside, QDateTime time);
    void updateLightGraph(double light, QDateTime time);

    void updateUiSerialStatus(bool s);
    void updateUiFanStatus(bool s);
    void updateUiHeaterStatus(bool s);
    void updateUiLightStatus(bool s);

public slots:
    void update();
    void updateMinTemperature(int n);
    void updateMaxTemperature(int n);
    void updateMinHumidity(int n);
    void updateMaxHumidity(int n);

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
    SensorLight *lightSensor;

    QTimer *timer;

    bool serialStatus;

    void doLogic();
};

#endif // CONTROLLER_H
