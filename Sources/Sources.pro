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
    mainwindow.h \
    mainscreen.h \
    taskthread.h \
    tasklayout.h \
    taskbutton.h \
    task.h \

SOURCES += \
    tabusearch.cpp \
    inserter.cpp \
    mainwindow.cpp \
    mainscreen.cpp \
    taskthread.cpp \
    tasklayout.cpp \
    taskbutton.cpp \
    task.cpp \
