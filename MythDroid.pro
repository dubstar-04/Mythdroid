#-------------------------------------------------
#
# Project created by QtCreator 2011-04-07T19:39:04
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = MythDroid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    getImage.cpp \
    parseData.cpp \
    manageDB.cpp \
    manageGuideData.cpp \
    program.cpp \
    timeBar.cpp \
    channel.cpp \
    programinfo.cpp

HEADERS  += mainwindow.h \
    program.h \
    timeBar.h \
    channel.h \
    programinfo.h

FORMS    += mainwindow.ui \
    programinfo.ui

RESOURCES += \
    MythDroid.qrc

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl
