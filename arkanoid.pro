#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T17:08:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arkanoid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameobject.cpp \
    screen.cpp \
    board.cpp \
    ball.cpp \
    brick.cpp

HEADERS  += mainwindow.h \
    gameobject.h \
    screen.h \
    board.h \
    ball.h \
    brick.h

FORMS    += mainwindow.ui
