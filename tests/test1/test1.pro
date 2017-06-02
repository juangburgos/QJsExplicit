QT += core
QT -= gui

CONFIG += c++11

TARGET = test1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

CONFIG   -= flat

include(./../../src/qjsexplicit.pri)

SOURCES += main.cpp
