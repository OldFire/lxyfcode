#-------------------------------------------------
#
# Project created by QtCreator 2018-01-12T09:02:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CEWEI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    gts.h \
    mythread.h

FORMS    += mainwindow.ui

RESOURCES += \
    src/imgs.qrc

CONFIG+= C++11

LIBS+="G:\Qtprogram\Windows\CEWEI\gts.lib"
