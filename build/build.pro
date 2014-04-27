#QT       += core gui
INCLUDEPATH =+ \
    ../Sources
    ../Shapes

TEMPLATE = app
SOURCES += main.cpp
LIBS += -L../files/debug -L../Sources/debug -L../UserInterface/debug -L../Shapes/debug \
    -lSources -lUserInterface -lShapes -lfiles
TARGET = ../TabuSearch
QT += widgets
CONFIG += c++11
