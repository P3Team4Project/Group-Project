#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T12:26:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GP2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    sor.cpp \
    tgrid.cpp \
    fgrid.cpp \
    gs.cpp \
    ttgrid.cpp \
    jac.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    sor.h \
    tgrid.h \
    fgrid.h \
    gs.h \
    ttgrid.h \
    main.h \
    jac.h

FORMS    += mainwindow.ui
