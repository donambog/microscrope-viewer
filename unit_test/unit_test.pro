QT += testlib widgets
QT += gui
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++17

TEMPLATE = app

HEADERS += ../src/imagewidget.h
SOURCES +=  \
    test_imagewidget.cpp \
    ../src/imagewidget.cpp

INCLUDEPATH += ../src
