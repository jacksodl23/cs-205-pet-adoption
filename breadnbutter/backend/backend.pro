TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core
QT += sql

HEADERS += pet.h \
           petowner.h \
shelter.h \
    globals.h \
    shelterowner.h \
    user.h \
    location.h \
    utils.h

SOURCES += main.cpp \
           pet.cpp \
           petowner.cpp \
shelter.cpp \
    globals.cpp \
    shelterowner.cpp \
    user.cpp \
    location.cpp \
    utils.cpp

