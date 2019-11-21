#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T12:01:05
#
#-------------------------------------------------

QT       += core

TARGET = Eyecare
TEMPLATE = app
LIBS+=-lUser32 -lGdi32

SOURCES += main.cpp\
    CNativeWindow.cpp \
    CQWindow.cpp

HEADERS  +=\
    CNativeWindow.h \
    CQWindow.h

