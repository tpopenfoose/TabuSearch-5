! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

LIBS += \
    -lconfig_tab \
    -lShapes \
    -ltask_main_window
INCLUDEPATH += \
    ../files \
    ../Shapes \
    ../config_tab \
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
