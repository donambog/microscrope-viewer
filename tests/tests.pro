######################################################################
# Unit Tests for Microscope Viewer
######################################################################

TEMPLATE = subdirs

SUBDIRS += \
    test_camera_emulator \
    test_imagewidget \
    test_plotwidget

# Configuration for each test
test_camera_emulator.file = test_camera_emulator.pro
test_imagewidget.file = test_imagewidget.pro
test_plotwidget.file = test_plotwidget.pro
