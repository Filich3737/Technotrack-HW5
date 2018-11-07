TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    cpu.cpp \
    stack.cpp \
    assembler.cpp \
    files.cpp

HEADERS += \
    cpu.h \
    assembler.h \
    stack.h \
    files.h
