#-------------------------------------------------
#
# Project created by QtCreator 2013-04-20T17:41:43
#
#-------------------------------------------------

QT       += core gui network
QMAKE_CXXFLAGS += -D__STRICT_ANSI__ -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Web_Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qftp/qurlinfo.cpp \
    qftp/qftp.cpp \
    credencialdialog.cpp \
    localstoragedialog.cpp \
    opendialog.cpp \
    blogpost.cpp

HEADERS  += mainwindow.h \
    qftp/qurlinfo.h \
    qftp/qftp.h \
    credencialdialog.h \
    localstoragedialog.h \
    opendialog.h \
    blogpost.h

FORMS    += mainwindow.ui \
    credencialdialog.ui \
    localstoragedialog.ui \
    opendialog.ui

OTHER_FILES += \
    qftp/qftp.pro \
    android/java.pro \
    android/version.xml \
    android/libjava.so \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/AndroidManifest.xml \
    android/res/values-ro/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-id/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-et/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-de/strings.xml \
    android/Makefile
