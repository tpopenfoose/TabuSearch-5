#QT       += core gui
INCLUDEPATH =+ \
    ../Sources

TEMPLATE = app
SOURCES += main.cpp
LIBS += -L../files/debug -L../Sources/debug -L../UserInterface/debug \
    -lfiles -lSources -lUserInterface
TARGET = ../TabuSearch
QT += widgets
