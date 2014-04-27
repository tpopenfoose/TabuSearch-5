TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += \
    ../Sources
HEADERS += \
    shape.h \
    circle.h \
    rectangle.h \
    square.h \
    triangle.h \
    generator.h \
    result.h

SOURCES += \
    shape.cpp \
    circle.cpp \
    rectangle.cpp \
    square.cpp \
    triangle.cpp \
    generator.cpp \
    result.cpp

CONFIG += c++11
