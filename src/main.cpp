#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    // Create Qt application
    QApplication app(argc, argv);
    
    // Set application metadata
    app.setApplicationName("Microscope Viewer");
    app.setOrganizationName("OWLO");
    app.setApplicationVersion("1.0.0");
    
    // Create and show main window
    MainWindow window;
    window.show();
    
    // Start event loop
    return app.exec();
}
