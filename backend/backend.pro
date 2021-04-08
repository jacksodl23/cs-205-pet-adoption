TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += pet.h \
           petowner.h \
shelter.h

SOURCES += main.cpp \
           pet.cpp \
           petowner.cpp \
shelter.cpp

