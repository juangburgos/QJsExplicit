#-------------------------------------------------
#
# Project created by QtCreator 2016-07-28T18:03:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app

CONFIG   -= flat

include(./../src/qjsexplicit.pri)

SOURCES  += main.cpp      \
            mainwindow.cpp 

HEADERS  += mainwindow.h 

FORMS    += mainwindow.ui
