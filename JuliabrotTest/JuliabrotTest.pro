QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testvec2.cpp \
    ../JuliabrotApp/vec2.cpp

SUBDIRS += \
    ../JuliabrotApp/Juliabrot.pro

HEADERS += \
    ../JuliabrotApp/vec2.h
