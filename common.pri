! include( common_all.pri ) {
    error( "Couldn't find the common.pri file!" )
}

#Includes common configuration for all subdirectory .pro files.
TEMPLATE = lib
#CONFIG += staticlib
DESTDIR = ../libs
