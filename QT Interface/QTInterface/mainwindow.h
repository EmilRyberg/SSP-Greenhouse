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
    void updateValues(double temperature, double temperatureOutside, double humidity, double humidityOutside, double light);

private:
    Ui::MainWindow *ui;
    SerialPortReader *serialPortReader;
    Controller *controller;
};

#endif // MAINWINDOW_H
