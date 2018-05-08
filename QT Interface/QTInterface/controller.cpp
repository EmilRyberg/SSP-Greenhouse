#include "controller.h"
#include "serialportreader.h"

Controller::Controller(SerialPortReader &serialPortReader, QObject *parent)
    : QObject(parent)
{
    temperatureMin = 22;
    temperatureMax = 25;
    humidityMin = 40;
    humidityMax = 60;
    lightMin = 40;
    lightMax = 60;
    serialReader = &serialPortReader;
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

void Controller::getTemperature(int value){
    temperature = value;
}
void Controller::getTemperatureOutside(int value){
    temperatureOutside = value;
}
void Controller::getHumidity(int value){
    humidity = value;
}
void Controller::getHumidityOutside(int value){
    humidityOutside = value;
}
void Controller::getLight(int value){
    light = value;
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
