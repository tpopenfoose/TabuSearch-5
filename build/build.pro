QT       += core gui
INCLUDEPATH =+ \
    ../Sources

TEMPLATE = app
SOURCES += main.cpp
LIBS += -L../Sources/debug -L../files/debug -lSources -lfiles
TARGET = ../TabuSearch
