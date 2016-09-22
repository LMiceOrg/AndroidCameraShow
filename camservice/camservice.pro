TEMPLATE = app

win32{
#qml quick webview multimedia
    QT += network core
}
android{
#qml quick webview multimedia androidextras
    QT += network core
}
CONFIG += c++11


SOURCES += \
    source/cpp/main.cpp \
source/cpp/myudp.cpp

HEADERS += source/cpp/myudp.h

RESOURCES += qml.qrc

# Default rules for deployment.
include(deployment.pri)


DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/gradle.properties \
    android/local.properties

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    ANDROID_JAVA_SOURCES.path = /src/cn/edu/tsinghua/rtlab/camphoto
    ANDROID_JAVA_SOURCES.files = $$files($$PWD/source/java/*.java)
    INSTALLS += ANDROID_JAVA_SOURCES
}
