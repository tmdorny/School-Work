#-------------------------------------------------
#
# Project created by QtCreator 2016-02-23T15:04:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = ASimonGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model.cpp

HEADERS  += mainwindow.h \
    model.h

FORMS    += mainwindow.ui

RESOURCES += \
    sounds.qrc
