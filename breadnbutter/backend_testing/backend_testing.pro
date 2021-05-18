TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core
QT += sql

# if you have pthread errors, comment/uncomment the next line
LIBS += -pthread
SOURCES += ../../gtest/googletest/src/gtest-all.cc

INCLUDEPATH += ../../gtest \
 ../../gtest/googletest \
 ../../gtest/googletest/include \
 ../../gtest/googletest/include/gtest

HEADERS += ../backend/*.h

SOURCES += main.cpp \
           ../backend/petowner.cpp \
           ../backend/pet.cpp \
           ../backend/user.cpp \
           ../backend/shelter.cpp \
           ../backend/location.cpp
