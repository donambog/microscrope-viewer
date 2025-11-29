QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

TEMPLATE = app

SOURCES += \
    test_camera_emulator.cpp \
    ../src/camera_emulator.cpp

HEADERS += \
    ../src/camera_emulator.h

INCLUDEPATH += ../src
