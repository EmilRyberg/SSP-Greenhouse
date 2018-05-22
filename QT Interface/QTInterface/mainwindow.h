#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialportreader.h"
#include "controller.h"
#include "chart.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateValues(double temperature, double temperatureOutside, double humidity, double humidityOutside, double light);
    void updateTemperatureGraph(double temperature, double temperatureOutside, QDateTime time);
    void updateHumidityGraph(double humidity, double humidityOutside, QDateTime time);
    void updateLightGraph(double light, QDateTime time);
    void updateSerialStatus(bool s);
    void updateFanStatus(bool s);
    void updateHeaterStatus(bool s);
    void updateLightStatus(bool s);
    void updateWaterStatus(bool s);

private:
    Ui::MainWindow *ui;
    SerialPortReader *serialPortReader;
    Controller *controller;
    Chart *chartTemperature;
    Chart *chartHumidity;
    Chart *chartLight;
};

#endif // MAINWINDOW_H
