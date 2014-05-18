! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

LIBS += \
    -lShapes
INCLUDEPATH += \
    ../files \
    ../Shapes \
    ../config_tab

HEADERS  += \
    taskmainwindow.h \
    toolbar.h \
    statusbox.h \
    progressbox.h \
    scrollarea.h \
    messagebox.h \
    board.h

SOURCES += \
    taskmainwindow.cpp \
    toolbar.cpp \
    statusbox.cpp \
    progressbox.cpp \
    scrollarea.cpp \
    messagebox.cpp \
    board.cpp
