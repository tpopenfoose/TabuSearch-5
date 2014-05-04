TEMPLATE = lib
CONFIG = staticlib
DESTDIR = ../libs
#DESTDIR = lib
TARGET = gmock-1.7.0

INCLUDEPATH += . include gtest gtest/include

SOURCES = gtest/src/gtest-all.cc src/gmock-all.cc

