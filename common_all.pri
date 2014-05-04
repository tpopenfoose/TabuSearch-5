#Includes common configuration for all subdirectory .pro files.
LIBS += -L../libs
CONFIG += c++11
QT += widgets

# The following keeps the generated files at least somewhat separate 
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs
