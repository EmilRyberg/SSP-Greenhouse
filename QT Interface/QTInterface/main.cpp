#include "mainwindow.h"
#include <QApplication>
#include <QChart>
#include <QLineSeries>
#include <QChartView>

using namespace QtCharts;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();
}
