TEMPLATE = lib
CONFIG += staticlib
LIBS += -L../Shapes/debug -lShapes -L../UserInterface/debug -lUserInterface
INCLUDEPATH += \
    ../files \
    ../Shapes \
    ../UserInterface

HEADERS  += \
    tabusearch.h \
    inserter.h \
    globalne.h \
    generator.h \
    mainwindow.h \
    mainscreen.h \
    taskthread.h \
    taskmainwindow.h \
    tasklayout.h \
    taskbuttongroup.h \
    taskbutton.h \
    task.h \
    sharedmemory.h \
    board.h

SOURCES += \
    tabusearch.cpp \
    inserter.cpp \
    generator.cpp \
    mainwindow.cpp \
    mainscreen.cpp \
    taskthread.cpp \
    taskmainwindow.cpp \
    tasklayout.cpp \
    taskbuttongroup.cpp \
    taskbutton.cpp \
    task.cpp \
    sharedmemory.cpp \
    board.cpp

QT += widgets
