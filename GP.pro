#-------------------------------------------------
#
# Project created by QtCreator 2017-01-31T16:43:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    sor.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    main.h \
    sor.h

FORMS    += mainwindow.ui
