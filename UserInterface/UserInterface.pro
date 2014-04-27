TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += \
    ../Sources \
    ../Shapes
QT += widgets
HEADERS += \
    configwindow.h \
    configtabtwo.h \
    configtabthree.h \
    configtabone.h \
    configtab.h \
    defaultconfig.h

SOURCES += \
    configwindow.cpp \
    configtabtwo.cpp \
    configtabthree.cpp \
    configtabone.cpp \
    configtab.cpp

CONFIG += c++11
