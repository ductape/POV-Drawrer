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
    PovLibrary/Led.cpp \
    PovLibrary/LedColumn.cpp

HEADERS  += MainWindow.h \
    PovLibrary/Led.h \
    PovLibrary/LedColumn.h

FORMS    += MainWindow.ui
