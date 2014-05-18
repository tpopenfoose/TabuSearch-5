TEMPLATE = app
INCLUDEPATH += \
    ../Shapes \
    ../gmock-1.7.0/gtest/include \
    ../gmock-1.7.0/include \
    ../config_tab
LIBS += -L../libs \
    -lgmock-1.7.0 \
    -lShapes
SOURCES += \
    main.cpp \
    GeneretorTestSuite.cpp

CONFIG += c++11

HEADERS += \
    ResultMock.h \
    GeneretorMock.h \
    ShapeMock.h
