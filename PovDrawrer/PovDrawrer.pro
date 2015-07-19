#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T19:42:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PovDrawrer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Led.cpp \
    PovLibrary/Led.cpp

HEADERS  += MainWindow.h \
    Led.h \
    PovLibrary/Led.h

FORMS    += MainWindow.ui
