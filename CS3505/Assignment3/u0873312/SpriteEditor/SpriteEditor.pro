#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T21:01:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editorserver.cpp \
    image.cpp \
    previewwidget.cpp

HEADERS  += mainwindow.h \
    editorserver.h \
    image.h \
    pixel.h \
    previewwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
