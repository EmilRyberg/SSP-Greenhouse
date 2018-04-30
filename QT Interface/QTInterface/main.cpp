#include "mainwindow.h"
#include "serialportreader.h"
#include <QApplication>
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextStream standardOutput(stdout);
    QSerialPort serialPort;
    const QString serialPortName = "COM3";

    serialPort.setPortName(serialPortName);
    serialPort.setBaudRate(115200);

    w.show();

    if (!serialPort.open(QIODevice::ReadOnly)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                          .arg(serialPortName)
                          .arg(serialPort.errorString())
                       << endl;
    }

    SerialPortReader serialPortReader(&serialPort, w.ui);

    return a.exec();
}
