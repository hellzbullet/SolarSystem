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
    logentry.cpp \
    power.cpp \
    solarsystem.cpp \
    systemdatabase.cpp \
    powerreader.cpp \
    ipfinder.cpp \
    logger.cpp \
    poweroutput.cpp

HEADERS += \
    device.h \
    logentry.h \
    power.h \
    solarsystem.h \
    systemdatabase.h \
    powerreader.h \
    ipfinder.h \
    logger.h \
    poweroutput.h
