#include "controller.h"
#include "serialportreader.h"
#include "stdlib.h"
#include "string"
#include "iostream"
#include "fstream"

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    temperatureMin = 22;
    temperatureMax = 25;
    humidityMin = 40;
    humidityMax = 60;
    lightMin = 40;
    lightMax = 60;
    time = 0;
    serialReader = new SerialPortReader();

    std::string line;
    std::fstream configFile;
    configFile.open("../QTInterface/config.txt");
    if (configFile.is_open())
    {
        std::getline(configFile,line);
        configFile.close();
    }
    else
    {
        std::cout << "WARNING: Error opening config.txt file! Using COM3 as fallback." << std::endl;
        line = "COM3";
    }

    QString serialPortName = QString::fromStdString(line);
    QTextStream standardOutput(stdout);
    int baudRate = 115200;
    if (!serialReader->AttachToSerial(serialPortName, baudRate))
    {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                          .arg(serialPortName)
                          .arg(serialReader->GetLatestError())
                       << endl;
        serialStatus = false;
    }
    else
    {
        serialStatus = true;
    }
    temperatureSensor = new Sensor(serialReader, 0, parent);
    temperatureOutsideSensor = new Sensor(serialReader, 1, parent);
    humiditySensor = new Sensor(serialReader, 2, parent);
    humidityOutsideSensor = new Sensor(serialReader, 3, parent);
    lightSensor = new SensorLight(serialReader, 4, parent);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Controller::update);
    timer->start(10000);
}

void Controller::update()
{
    time += 10; // seconds
    std::cout << "timer fired" << std::endl;
    temperature = temperatureSensor->GetAverage();
    temperatureOutside = temperatureOutsideSensor->GetAverage();
    humidity = humiditySensor->GetAverage();
    humidityOutside = humidityOutsideSensor->GetAverage();
    light = lightSensor->GetTrimmedAverage();

    emit updateUiValues(temperature, temperatureOutside, humidity, humidityOutside, light);
    emit updateTemperatureGraph(temperature, temperatureOutside, temperatureSensor->CurrentTime());
    emit updateHumidityGraph(humidity, humidityOutside, humiditySensor->CurrentTime());
    emit updateLightGraph(light, lightSensor->CurrentTime());

    emit updateUiSerialStatus(serialStatus);

    doLogic();
}

void Controller::updateMinTemperature(int n)
{
    temperatureMin = n;
}
void Controller::updateMaxTemperature(int n)
{
    temperatureMax = n;
}
void Controller::updateMinHumidity(int n)
{
    humidityMin = n;
}
void Controller::updateMaxHumidity(int n)
{
    humidityMax = n;
}

void Controller::fanOn()
{
    serialReader->SendData(fanPin,'d',1);
    emit updateUiFanStatus(true);
}
void Controller::fanOff()
{
    serialReader->SendData(fanPin,'d',0);
    emit updateUiFanStatus(false);
}
void Controller::lightOn()
{
    serialReader->SendData(lightPinG,'d',1);
    serialReader->SendData(lightPinB,'d',1);
    emit updateUiLightStatus(true);
}
void Controller::lightOff()
{
    serialReader->SendData(lightPinG,'d',0);
    serialReader->SendData(lightPinB,'d',0);
    emit updateUiLightStatus(false);
}
void Controller::waterOn()
{
    serialReader->SendData(waterPin,'d',1);
    emit updateUiWaterStatus(true);
}
void Controller::waterOff()
{
    serialReader->SendData(waterPin,'d',0);
    emit updateUiWaterStatus(false);
}
void Controller::heatOn()
{
    serialReader->SendData(heatPin,'d',1);
    emit updateUiHeaterStatus(true);
}
void Controller::heatOff()
{
    serialReader->SendData(heatPin,'d',0);
    emit updateUiHeaterStatus(false);
}

void Controller::doLogic()
{
    if(temperature < temperatureMin)
    {
        if(temperatureOutside>temperature)
        {
            fanOn(); //using hotter outside air
            heatOff();
        }
        else
        {
            heatOn(); //using heater
            fanOff();
        }
    }
    else if(temperature > temperatureMax)
    {
        if(temperatureOutside < temperature)
        {
            fanOn(); //using cooler outside air
        }
        else
        {
            fanOff(); //no way to cool down
        }
    }
    else
    {
        heatOff(); //in range, shutting devices down
        fanOff();
    }

    if(humidity < humidityMin)
    {
        waterOn();
    }
    else if(humidity > humidityMax)
    {
        waterOff();
    }

    if(light < lightMin)
    {
        lightOn();
    }
    else if (light > lightMax)
    {
        lightOff();
    }
}
