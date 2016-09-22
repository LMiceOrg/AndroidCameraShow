#-------------------------------------------------
#
# Project created by QtCreator 2016-09-20T15:05:03
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = android_sample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mbclient.cpp

HEADERS  += mainwindow.h \
    mbclient.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    sample.qrc

#DISTFILES += \
#    android/AndroidManifest.xml \
#    android/gradle/wrapper/gradle-wrapper.jar \
#    android/gradlew \
#    android/res/values/libs.xml \
#    android/build.gradle \
#    android/gradle/wrapper/gradle-wrapper.properties \
#    android/gradlew.bat \
#    android/gradle.properties \
#    android/local.properties

#android {
#    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
#    ANDROID_JAVA_SOURCES.path = /src/cn/edu/tsinghua/rtlab/camphoto
#    ANDROID_JAVA_SOURCES.files = $$files($$PWD/source/java/*.java)
#    INSTALLS += ANDROID_JAVA_SOURCES
#}
