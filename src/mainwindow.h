#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include "imagewidget.h"
#include "plotwidget.h"
#include "camera_emulator.h"
#include "displaymanager.h"

/**
 * @brief Main application window
 * 
 * Provides:
 * - Start/Stop button for live display
 * - Image display widget with camera frames
 * - Automatic frame updates using QTimer
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
    
private slots:
    /**
     * @brief Handle Start/Stop button click
     */
    void onStartStopClicked();
    
    /**
     * @brief Update display with new camera frame
     * Called by timer at regular intervals
     */
    void onTimerUpdate();
    
private:
    /**
     * @brief Setup the user interface
     */
    void setupUI();
    
    // UI Components
    QPushButton* startStopButton;
    ImageWidget* imageWidget;
    PlotWidget* xProfilePlot;
    PlotWidget* yProfilePlot;
    QLabel* statusLabel;
    QLabel* fpsLabel;
    DisplayManager* displayManager;
    
    // Timer for live updates
    QTimer* updateTimer;
    
    // State
    bool isRunning;
    int frameCount;
    qint64 lastFpsUpdate;
};

#endif // MAINWINDOW_H
