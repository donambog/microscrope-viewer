QT += testlib widgets
QT += gui
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++17

TEMPLATE = app

HEADERS += ../src/Data.h \
           ../src/displaymanager.h

SOURCES +=  \
    test_displaymanager.cpp \
    ../src/displaymanager.cpp
INCLUDEPATH += ../src
