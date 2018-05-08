#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialportreader.h"
#include "controller.h"

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
    void updateTemperature(double value);
    void updateTemperatureOutside(double value);
    void updateHumidityInside(double value);
    void updateHumidityOutside(double value);
    void updateLight(double value);

private:
    Ui::MainWindow *ui;
    SerialPortReader *serialPortReader;
    Controller *controller;
};

#endif // MAINWINDOW_H
