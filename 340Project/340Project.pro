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
        mainwindow.cpp \
    label.cpp \
    newExerciseDialog.cpp

HEADERS  += mainwindow.h \
    label.h \
    newExerciseDialog.h

FORMS    += mainwindow.ui \
    form.ui \
    newExerciseDialog.ui
