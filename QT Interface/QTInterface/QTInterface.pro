#-------------------------------------------------
#
# Project created by QtCreator 2018-04-30T09:15:59
#
#-------------------------------------------------

QT       += core gui serialport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = QTInterface
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        serialportreader.cpp \
        mainwindow.cpp \
        dataparser.cpp \
        controller.cpp \
        sensor.cpp \
    chart.cpp

HEADERS += \
        serialportreader.h \
        mainwindow.h \
        dataparser.h \
        controller.h \
        sensor.h \
    chart.h

FORMS += \
        mainwindow.ui
