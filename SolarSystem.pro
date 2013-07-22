#-------------------------------------------------
#
# Project created by QtCreator 2013-07-16T22:46:34
#
#-------------------------------------------------

QT       += core sql network

QT       -= gui

TARGET = SolarSystem
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    device.cpp \
    power.cpp \
    solarsystem.cpp \
    systemdatabase.cpp \
    powerreader.cpp \
    ipfinder.cpp \
    logger.cpp \
    poweroutput.cpp \
    solarsystemutils.cpp \
    webservice.cpp

HEADERS += \
    device.h \
    power.h \
    solarsystem.h \
    systemdatabase.h \
    powerreader.h \
    ipfinder.h \
    logger.h \
    poweroutput.h \
    solarsystemutils.h \
    webservice.h
