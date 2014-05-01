TEMPLATE = lib
#CONFIG += staticlib
LIBS += -L../Shapes/debug -lShapes
INCLUDEPATH += \
    ../Sources \
    ../Shapes
QT += widgets
HEADERS += \
    board.h \
    configwindow.h \
    configtabtwo.h \
    configtabthree.h \
    configtabone.h \
    configtab.h \
    defaultconfig.h

SOURCES += \
    board.cpp \
    configwindow.cpp \
    configtabtwo.cpp \
    configtabthree.cpp \
    configtabone.cpp \
    configtab.cpp

CONFIG += c++11
