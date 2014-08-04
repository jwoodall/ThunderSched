#-------------------------------------------------
#
# Project created by QtCreator 2014-02-16T10:32:35
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += sql

TARGET = ThunderSched
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


HEADERS += team.h \
           schedule.h \
           game.h \
           coach.h \
    sql_queries.h

SOURCES += main.cpp \
           team.cpp \
           schedule.cpp \
           game.cpp \
           coach.cpp
