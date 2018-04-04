QT += core
QT -= gui

CONFIG += c++11

TARGET = 01_chain
CONFIG += console
CONFIG -= app_bundle

DEFINES += JS_DEBUG

include(./../../src/qjsexplicit.pri)
include(./../add_qt_path.pri)

TEMPLATE = app

SOURCES += main.cpp
