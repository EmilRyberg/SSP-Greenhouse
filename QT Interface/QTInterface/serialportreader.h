#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QByteArray>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QTimer>
#include <QMainWindow>
#include "mainwindow.h"
#include "dataparser.h"

class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortReader(QSerialPort *serialPort, Ui::MainWindow *ui, QObject *parent = (QObject *)0);

private slots:
    void handleReadyRead();

private:
    QSerialPort *m_serialPort = (QSerialPort *)0;
    QByteArray m_readData;
    QTextStream m_standardOutput;
    Ui::MainWindow *ui;
    DataParser dataParser;
};

#endif // SERIALPORTREADER_H
