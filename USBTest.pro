#-------------------------------------------------
#
# Project created by QtCreator 2013-07-11T10:04:27
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

TARGET = USBTest
CONFIG   -= app_bundle
CONFIG   += console link_pkgconfig plugin

PKGCONFIG += glib-2.0

TEMPLATE = app


SOURCES += main.cpp \
    USBConnector.cpp \
    BTTest.cpp

HEADERS += \
    USBConnector.h \
    BTTest.h
