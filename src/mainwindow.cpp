#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDateTime>
#include <QStatusBar>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , isRunning(false)
    , frameCount(0)
    , lastFpsUpdate(0)
{
    setupUI();
    
    // Create and configure timer (100ms = 10 FPS)
    updateTimer = new QTimer(this);
    updateTimer->setInterval(100);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::onTimerUpdate);
    
    setWindowTitle("Microscope Viewer");
    resize(800, 600);
}

MainWindow::~MainWindow() {
    if (updateTimer->isActive()) {
        updateTimer->stop();
    }
}

void MainWindow::setupUI() {
    // Create central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    // Control panel at top
    QHBoxLayout* controlLayout = new QHBoxLayout();
    
    startStopButton = new QPushButton("Start", this);
    startStopButton->setMinimumSize(100, 40);
    startStopButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #3d8b40;"
        "}"
    );
    connect(startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    
    statusLabel = new QLabel("Status: Stopped", this);
    statusLabel->setStyleSheet("QLabel { font-size: 12px; padding: 5px; }");
    
    fpsLabel = new QLabel("FPS: 0.0", this);
    fpsLabel->setStyleSheet("QLabel { font-size: 12px; padding: 5px; }");
    
    controlLayout->addWidget(startStopButton);
    controlLayout->addWidget(statusLabel);
    controlLayout->addWidget(fpsLabel);
    controlLayout->addStretch();
    
    mainLayout->addLayout(controlLayout);
    
    // Create horizontal layout for image and plots
    QHBoxLayout* displayLayout = new QHBoxLayout();
    
    imageWidget = new ImageWidget(this);
    int stretchFactor1 = 2;
    displayLayout->addWidget(imageWidget, stretchFactor1); // stretch factor = 2
    
    QVBoxLayout* plotsLayout = new QVBoxLayout();
    
    xProfilePlot = new PlotWidget(this);
    xProfilePlot->setTitle("X-Axis Profile");
    xProfilePlot->setAxisLabels("X Position (pixels)", "Average Intensity");
    plotsLayout->addWidget(xProfilePlot);
    
    yProfilePlot = new PlotWidget(this);
    yProfilePlot->setTitle("Y-Axis Profile");
    yProfilePlot->setAxisLabels("Y Position (pixels)", "Average Intensity");
    plotsLayout->addWidget(yProfilePlot);
    int stretchFactor2 = 1 ;
    displayLayout->addLayout(plotsLayout, stretchFactor2);
    mainLayout->addLayout(displayLayout, stretchFactor2);
    
    statusBar()->showMessage("Ready!");
}

void MainWindow::onStartStopClicked() {
    isRunning = !isRunning;
    
    if (isRunning) {
        // Start live display
        startStopButton->setText("Stop");
        startStopButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #f44336;"
            "   color: white;"
            "   font-size: 14px;"
            "   font-weight: bold;"
            "   border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #da190b;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #c41100;"
            "}"
        );
        statusLabel->setText("Status: Running");
        updateTimer->start();
        frameCount = 0;
        lastFpsUpdate = QDateTime::currentMSecsSinceEpoch();
        statusBar()->showMessage("Live display started");
    } else {
        // Stop live display
        startStopButton->setText("Start");
        startStopButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #4CAF50;"
            "   color: white;"
            "   font-size: 14px;"
            "   font-weight: bold;"
            "   border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #45a049;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #3d8b40;"
            "}"
        );
        statusLabel->setText("Status: Stopped");
        updateTimer->stop();
        fpsLabel->setText("FPS: 0.0");
        statusBar()->showMessage("Live display stopped");
    }
}

void MainWindow::onTimerUpdate() {
    // Read current frame from camera
    const Frame frame = CameraEmulator::readCurrentFrame();
    
    // Update image display (ImageWidget handles conversion to QImage)
    imageWidget->updateDisplay(frame);
    
    // Calculate and update X profile
    auto xProfile = CameraEmulator::calculateXProfile(frame);
    xProfilePlot->updateData(xProfile);
    
    // Calculate and update Y profile
    auto yProfile = CameraEmulator::calculateYProfile(frame);
    yProfilePlot->updateData(yProfile);
    
    // Update FPS counter
    frameCount++;
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed = currentTime - lastFpsUpdate;
    
    if (elapsed >= 1000) { // Update FPS every second
        double fps = (frameCount * 1000.0) / elapsed;
        fpsLabel->setText(QString("FPS: %1").arg(fps, 0, 'f', 1));
        frameCount = 0;
        lastFpsUpdate = currentTime;
    }
}
