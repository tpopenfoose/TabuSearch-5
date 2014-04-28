GMOCK_VERSION = 1.7.0

TEMPLATE = subdirs
SUBDIRS = \
    files \
    Shapes \
    UserInterface \
    Sources \
    gmock-$$GMOCK_VERSION \
    tests \
    build

CONFIG += ordered
CONFIG += debug
CONFIG += qt
CONFIG += c++11
