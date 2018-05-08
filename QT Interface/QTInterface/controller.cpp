#include "controller.h"
#include "serialportreader.h"

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    temperatureMin = 22;
    temperatureMax = 25;
    humidityMin = 40;
    humidityMax = 60;
    lightMin = 40;
    lightMax = 60;
    serialReader = new SerialPortReader();

    QTextStream standardOutput(stdout);
    const QString serialPortName = "COM3";
    int baudRate = 115200;
    if (!serialReader->AttachToSerial(serialPortName, baudRate)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                          .arg(serialPortName)
                          .arg(serialReader->GetLatestError())
                       << endl;
    }

    connect(serialReader, &SerialPortReader::sensorsChanged, this, &Controller::setSensorValues);
}

void Controller::fanOn()
{
    serialReader->SendData(fanPin,'d',1);
}
void Controller::fanOff()
{
    serialReader->SendData(fanPin,'d',0);
}
void Controller::lightOn()
{
    serialReader->SendData(lightPinG,'d',1);
    serialReader->SendData(lightPinB,'d',1);
}
void Controller::lightOff()
{
    serialReader->SendData(lightPinG,'d',0);
    serialReader->SendData(lightPinB,'d',0);
}
void Controller::waterOn()
{
    serialReader->SendData(waterPin,'d',1);
}
void Controller::waterOff()
{
    serialReader->SendData(waterPin,'d',0);
}
void Controller::heatOn()
{
    serialReader->SendData(heatPin,'d',1);
}
void Controller::heatOff()
{
    serialReader->SendData(heatPin,'d',0);
}

void Controller::setSensorValues(double temperature, double temperatureOutside, double humidity, double humidityOutside, double light){
    this->temperature = temperature;
    this->temperatureOutside = temperatureOutside;
    this->humidity = humidity;
    this->humidityOutside = humidityOutside;
    this->light = light;
}

void Controller::doLogic()
{
    if(temperature < temperatureMin){
        if(temperatureOutside>temperature){
            fanOn(); //using hotter outside air
            heatOff();
        } else {
            heatOn(); //using heater
            fanOff();
        }
    } else if(temperature > temperatureMax){
        if(temperatureOutside < temperature){
            fanOn(); //using cooler outside air
        } else {
            fanOff(); //no way to cool down
        }
    } else {
        heatOff(); //in range, shutting devices down
        fanOff();
    }

    if(light < lightMin){
        lightOn();
    } else if (light > lightMax) {
        lightOff();
    }
}
