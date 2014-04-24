QT       += core gui
INCLUDEPATH = ../Sources
TEMPLATE = app
SOURCES += main.cpp
LIBS += -L../sources/debug -L../files/debug -lfiles -lsources
TARGET = ../TabuSearch