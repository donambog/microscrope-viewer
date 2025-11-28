######################################################################
# Microscope Viewer - Qt Only (No OpenCV)
######################################################################

QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MicroscopeViewer
TEMPLATE = app

CONFIG += c++17

# Source files
SOURCES += \
    src/main.cpp \
    src/camera_emulator.cpp \
    src/mainwindow.cpp \
    src/imagewidget.cpp \
    src/plotwidget.cpp

HEADERS += \
    src/camera_emulator.h \
    src/mainwindow.h \
    src/imagewidget.h \
    src/plotwidget.h \
    src/plotwidget.h

INCLUDEPATH += src

# Output directories
CONFIG(debug, debug|release) {
    DESTDIR = debug
    OBJECTS_DIR = debug/obj
    MOC_DIR = debug/moc
    RCC_DIR = debug/rcc
    UI_DIR = debug/ui
} else {
    DESTDIR = release
    OBJECTS_DIR = release/obj
    MOC_DIR = release/moc
    RCC_DIR = release/rcc
    UI_DIR = release/ui
}

DEFINES += QT_DEPRECATED_WARNINGS
