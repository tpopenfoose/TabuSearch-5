TEMPLATE = lib
#CONFIG += staticlib
LIBS += \
    -L../Shapes/debug -lShapes \
    -L../UserInterface/debug -lUserInterface \
    -L../task_main_window/debug -ltask_main_window
INCLUDEPATH += \
    ../files \
    ../Shapes \
    ../UserInterface \
    ../task_main_window

HEADERS  += \
    tabusearch.h \
    inserter.h \
    globalne.h \
    mainwindow.h \
    mainscreen.h \
    taskthread.h \
    tasklayout.h \
    taskbuttongroup.h \
    taskbutton.h \
    task.h \
    sharedmemory.h \

SOURCES += \
    tabusearch.cpp \
    inserter.cpp \
    mainwindow.cpp \
    mainscreen.cpp \
    taskthread.cpp \
    tasklayout.cpp \
    taskbuttongroup.cpp \
    taskbutton.cpp \
    task.cpp \
    sharedmemory.cpp \

QT += widgets
CONFIG += c++11
