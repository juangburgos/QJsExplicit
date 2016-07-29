#-------------------------------------------------
#
# Project created by QtCreator 2016-07-28T18:03:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qjsnode.cpp \
    qjsobject.cpp \
    qjsnodedata.cpp \
    qjsobjectdata.cpp \
    qjsarray.cpp \
    qjsarraydata.cpp \
    qjsdocument.cpp \
    qjsdocumentdata.cpp

HEADERS  += mainwindow.h \
    qjsnode.h \
    qjsobject.h \
    qjsnodedata.h \
    qjsobjectdata.h \
    qjsarray.h \
    qjsarraydata.h \
    qjsdocument.h \
    qjsdocumentdata.h

FORMS    += mainwindow.ui
