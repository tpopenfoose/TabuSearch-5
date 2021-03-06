TEMPLATE = lib
CONFIG += staticlib
LIBS += -L../Interfaces/debug -lInterfaces
INCLUDEPATH += \
    ../files \
    ../Interfaces

HEADERS  += \
    taskthread.h \
    taskmainwindow.h \
    tasklayout.h \
    taskbuttongroup.h \
    taskbutton.h \
    task.h \
    tabusearch.h \
    sharedmemory.h \
    mainwindow.h \
    mainscreen.h \
    inserter.h \
    globalne.h \
    configwindow.h \
    configtabtwo.h \
    configtabthree.h \
    configtabone.h \
    configtabfour.h \
    configtab.h \
    board.h \
    circle.h \
    square.h \
    triangle.h \
    rectangle.h \
    generator.h

SOURCES += \
    taskthread.cpp \
    taskmainwindow.cpp \
    tasklayout.cpp \
    taskbuttongroup.cpp \
    taskbutton.cpp \
    task.cpp \
    tabusearch.cpp \
    sharedmemory.cpp \
    mainwindow.cpp \
    mainscreen.cpp \
    inserter.cpp \
    configwindow.cpp \
    configtabtwo.cpp \
    configtabthree.cpp \
    configtabone.cpp \
    configtabfour.cpp \
    configtab.cpp \
    board.cpp \
    circle.cpp \
    square.cpp \
    triangle.cpp \
    rectangle.cpp \
    generator.cpp

QT += widgets
