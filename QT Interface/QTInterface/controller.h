#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

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
    void updateTemperature(int value);
    void updateTemperatureOutside(int value);
    void updateHumidity(int value);
    void updateHumidityOutside(int value);
    void updateLight(int value);

public slots:
    void getTemperature(int value);
    void getTemperatureOutside(int value);
    void getHumidity(int value);
    void getHumidityOutside(int value);
    void getLight(int value);

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

    float temperature;
    float temperatureOutside;
    float humidity;
    float humidityOutside;
    int light;
};

#endif // CONTROLLER_H
