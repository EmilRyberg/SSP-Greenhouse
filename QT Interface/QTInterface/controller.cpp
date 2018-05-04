#include "controller.h"
#include "serialportreader.h"

Controller::controller(QObject *parent) : QObject(parent)
{
    temperatureMin = 22;
    temperatureMax = 25;
    humidityMin = 40;
    humidityMax = 60;
    lightMin = 40;
    lightMax = 60;
}

Controller::fanOn(){
    SerialPortReader::sendData(fanPin,'d',1);
}
Controller::fanOff(){
    SerialPortReader::sendData(fanPin,'d',0);
}
Controller::lightOn(){
    SerialPortReader::sendData(lightPinG,'d',1);
    SerialPortReader::sendData(lightPinB,'d',1);
}
Controller::lightOff(){
    SerialPortReader::sendData(lightPinG,'d',0);
    SerialPortReader::sendData(lightPinB,'d',0);
}
Controller::waterOn(){
    SerialPortReader::sendData(waterPin,'d',1);
}
Controller::waterOff(){
    SerialPortReader::sendData(waterPin,'d',0);
}
Controller::heatOn(){
    SerialPortReader::sendData(heatPin,'d',1);
}
Controller::heatOff(){
    SerialPortReader::sendData(heatPin,'d',0);
}

Controller::getTemperature(int value){
    temperature = value;
}
Controller::getTemperatureOutside(int value){
    temperatureOutside = value;
}
Controller::getHumidity(int value){
    humidity = value;
}
Controller::getHumidityOutside(int value){
    humidityOutside = value;
}
Controller::getLight(int value){
    light = value;
}

Controller::doLogic()
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
