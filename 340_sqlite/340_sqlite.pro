#-------------------------------------------------
#
# Project created by QtCreator 2013-11-10T07:40:04
#
#-------------------------------------------------

QT       += core sql

QT       -= gui


TARGET = 340_sqlite
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    BusinessLayer.cpp \
    DataAccessLayer.cpp \
    PresentationLayer.cpp \
    exercise_set.cpp \
    workout.cpp \
    exercise.cpp \
    user.cpp

HEADERS += \
    BusinessLayer.h \
    DataAccessLayer.h \
    exercise_set.h \
    workout.h \
    exercise.h \
    user.h
