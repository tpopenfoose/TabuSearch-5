! include( ../common_all.pri ) {
    error( "Couldn't find the common.pri file!" )
}

INCLUDEPATH =+ \
    ../Sources
    ../Shapes

TEMPLATE = app
SOURCES += main.cpp
LIBS += \
    -lfiles \
    -lSources \
    -lconfig_tab \
    -lShapes \
    -ltask_main_window

TARGET = ../TabuSearch
