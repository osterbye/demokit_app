#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T10:53:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demokit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pubnubreceiver.cpp

HEADERS  += mainwindow.h \
    pubnubreceiver.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

include(pubnub/pubnub.pri)
