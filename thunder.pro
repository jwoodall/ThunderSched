#-------------------------------------------------
#
# Project created by QtCreator 2014-02-18T19:55:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = thunder
TEMPLATE = app


SOURCES += main.cpp\
           team.cpp \
           schedule.cpp \
           game.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
           team.h \
           schedule.h \
           game.h

FORMS    += mainwindow.ui
