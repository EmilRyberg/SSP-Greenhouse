#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialportreader.h"

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

private:
    Ui::MainWindow *ui;
    SerialPortReader *serialPortReader;
};

#endif // MAINWINDOW_H
