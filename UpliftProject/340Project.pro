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
    DataAccessLayer.cpp \
    BusinessLayer.cpp \
    widget.cpp \
    stats.cpp

HEADERS  += \
    DataAccessLayer.h \
    BusinessLayer.h \
    widget.h

FORMS    += widget.ui

OTHER_FILES += \
    Assets/UpliftBack.png

RESOURCES += \
    UIResources.qrc
