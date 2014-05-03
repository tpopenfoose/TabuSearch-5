INCLUDEPATH =+ \
    ../Sources
    ../Shapes

TEMPLATE = app
SOURCES += main.cpp
LIBS += \
    -L../files/debug -lfiles \
    -L../Sources/debug -lSources \
    -L../UserInterface/debug -lUserInterface \
    -L../Shapes/debug -lShapes \
    -L../task_main_window/debug -ltask_main_window

TARGET = ../TabuSearch
QT += widgets
CONFIG += c++11
