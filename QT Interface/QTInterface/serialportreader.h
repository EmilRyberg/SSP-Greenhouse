#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QByteArray>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QTimer>
#include <QMainWindow>
#include "dataparser.h"

class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortReader(QObject *parent = (QObject *)0);
    bool AttachToSerial(QString name, int baudRate);
    QString GetLatestError() const;
    ~SerialPortReader();
    void SendData(int pin, char method, int value);

public slots:


private slots:
    void handleReadyRead();
    void emulateSerialData();

signals:
    void dataChanged(std::vector<double> value);

private:
    QSerialPort *serialPort = (QSerialPort *)0;
    QByteArray m_readData;
    QTextStream m_standardOutput;
    DataParser dataParser;
    QString latestError;
};

#endif // SERIALPORTREADER_H
