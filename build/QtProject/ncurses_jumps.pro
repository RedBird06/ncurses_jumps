TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread -lncurses
QMAKE_CXXFLAGS += -std=c++11

OBJECTS_DIR = ../../obj
DESTDIR = ../../bin
TARGET = ncurses_jumps

INCLUDEPATH += ../../headers \

SOURCES += \
    ../../source/NJCanvas.cpp \
    ../../source/NJGame.cpp \
    ../../source/NJMovableSprite.cpp \
    ../../source/NJSprite.cpp \
    ../../source/main.cpp

HEADERS += \
    ../../headers/NJCanvas.h \
    ../../headers/NJConfig.h \
    ../../headers/NJGame.h \
    ../../headers/NJMovableSprite.h \
    ../../headers/NJSprite.h \
    ../../headers/NJStructs.h

