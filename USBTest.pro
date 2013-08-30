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

PKGCONFIG += glib-2.0 bluez

TEMPLATE = app


SOURCES += main.cpp \
    USBConnector.cpp \
    BTTest.cpp \
    BTServer.cpp \
    BTClient.cpp

HEADERS += \
    USBConnector.h \
    BTTest.h \
    BTServer.h \
    BTClient.h
