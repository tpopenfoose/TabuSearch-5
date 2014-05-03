TEMPLATE = lib
#CONFIG += staticlib
LIBS += -L../Shapes/debug -lShapes
INCLUDEPATH += \
    ../files \
    ../Shapes \
    ../Sources

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

QT += widgets
CONFIG += c++11
