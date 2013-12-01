#-------------------------------------------------
#
# Project created by QtCreator 2013-09-29T18:34:06
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 340Project
TEMPLATE = app


SOURCES += main.cpp\
    exercise_set.cpp \
    exercise.cpp \
    DataAccessLayer.cpp \
    BusinessLayer.cpp \
    workout.cpp \
    widget.cpp \
    ExerciseStats.cpp

HEADERS  += exercise_set.h \
    exercise.h \
    DataAccessLayer.h \
    BusinessLayer.h \
    workout.h \
    widget.h \
    ExerciseStats.h

FORMS    += widget.ui

OTHER_FILES += \
    Assets/UpliftBack.png

RESOURCES += \
    UIResources.qrc
