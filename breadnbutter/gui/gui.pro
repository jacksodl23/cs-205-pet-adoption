QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createaccount.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    petdisplay.cpp \
    ../backend/globals.cpp \
    ../backend/simplecrypt.cpp \
    ../backend/pet.cpp \
    ../backend/petowner.cpp \
    ../backend/shelter.cpp \
    shelterupload.cpp \
    petprofile.cpp \
    shelterprofile.cpp

HEADERS += \
    createaccount.h \
    login.h \
    mainwindow.h \
    petdisplay.h \
    ../backend/*.h \
    shelterupload.h \
    petprofile.h \
    shelterprofile.h

FORMS += \
    createaccount.ui \
    login.ui \
    mainwindow.ui \
    petdisplay.ui \
    shelterupload.ui \
    petprofile.ui \
    shelterprofile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    petPhotos.qrc
