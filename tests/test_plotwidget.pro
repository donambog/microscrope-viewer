QT += testlib widgets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

TEMPLATE = app

SOURCES += \
    test_plotwidget.cpp \
    ../src/plotwidget.cpp

HEADERS += \
    ../src/plotwidget.h

INCLUDEPATH += ../src
