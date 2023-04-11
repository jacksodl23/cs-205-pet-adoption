QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = Breadnbutter

macx {
    sql_database.files = ../database/db.sqlite
    sql_database.path = Contents/MacOS
    QMAKE_BUNDLE_DATA += sql_database
}

SOURCES += \
    createaccount.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    petdisplay.cpp \
    ../backend/globals.cpp \
    ../backend/pet.cpp \
    ../backend/petowner.cpp \
    ../backend/shelter.cpp \
    ../backend/shelterowner.cpp \
    ../backend/user.cpp \
    ../backend/location.cpp \
    ../backend/utils.cpp \
    shelteradopters.cpp \
    shelterupload.cpp \
    petprofile.cpp \
    shelterprofile.cpp \
    petliked.cpp \
    petownerhelp.cpp \
    shelterhelp.cpp \
    shelterprofilesqlmodel.cpp

HEADERS += \
    createaccount.h \
    login.h \
    mainwindow.h \
    petdisplay.h \
    ../backend/*.h \
    ../backend/shelterowner.h \
    ../backend/user.h \
    shelteradopters.h \
    shelterupload.h \
    petprofile.h \
    shelterprofile.h \
    petliked.h \
    petownerhelp.h \
    shelterhelp.h \
    shelterprofilesqlmodel.h

FORMS += \
    createaccount.ui \
    login.ui \
    mainwindow.ui \
    petdisplay.ui \
    shelteradopters.ui \
    shelterupload.ui \
    petprofile.ui \
    shelterprofile.ui \
    petliked.ui \
    petownerhelp.ui \
    shelterhelp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    petPhotos.qrc
