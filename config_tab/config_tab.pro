! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

LIBS += -lShapes

INCLUDEPATH += \
    ../Sources \
    ../Shapes

HEADERS += \
    configwindow.h \
    configtabtwo.h \
    configtabthree.h \
    configtabone.h \
    configtab.h \
    defaultconfig.h \
    config_data.h

SOURCES += \
    configwindow.cpp \
    configtabtwo.cpp \
    configtabthree.cpp \
    configtabone.cpp \
    configtab.cpp
