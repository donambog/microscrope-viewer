# Microscope Viewer - Qt Only Version

Simple camera frame viewer using **Qt only** - no OpenCV required!

## Features

- ✅ Live camera frame display
- ✅ Start/Stop button control
- ✅ FPS counter
- ✅ VIRIDIS-like colormap (pure Qt implementation)
- ✅ **X-axis profile plot** (average intensity along X)
- ✅ **Y-axis profile plot** (average intensity along Y)
- ✅ Synchronized display (all plots from same frame)
- ✅ Works with MinGW or MSVC
- ✅ **No external dependencies** except Qt!

## Prerequisites

**Just Qt!** That's it!

- Qt 6.x (6.9.2, 6.9.3, or any 6.x version)
- Any compiler: MinGW, MSVC, GCC
- Any platform: Windows, macOS, Linux

## Build Instructions

### Using Qt Creator

1. Open Qt Creator
2. **File** → **Open File or Project**
3. Select `MicroscopeViewer.pro`
4. Choose any available kit (MinGW or MSVC, doesn't matter!)
5. **Build** → **Build All** (Ctrl+B)
6. **Build** → **Run** (Ctrl+R)

### Command Line (Windows)

```bash
# Make sure qmake is in your PATH
qmake
make  # or nmake for MSVC, mingw32-make for MinGW
```

## Usage

1. Launch the application
2. Click **"Start"** button
3. Watch the three animated spots:
   - Two fixed spots (left and right)
   - One moving spot (center)
4. Click **"Stop"** to pause
5. FPS counter shows current frame rate (~10 FPS)

## Technical Details

### Camera Emulation
- Frame size: 200×100 pixels
- Update rate: 10 Hz (100ms intervals)
- Three Gaussian spots with different behaviors

### Display Pipeline
```
CameraEmulator → std::vector<vector<double>>
       ↓
Custom VIRIDIS colormap (Qt native)
       ↓
    QImage (RGB32)
       ↓
    QPixmap → QLabel
```

### Colormap Implementation

Pure Qt/C++ implementation of VIRIDIS-like colormap:
- No external libraries
- Linear interpolation between color stops
- Smooth gradients from purple → blue → cyan → green → yellow

## Project Structure

```
microscope-viewer-qt/
├── MicroscopeViewer.pro    # Qt project file
├── README.md               # This file
└── src/
    ├── main.cpp            # Entry point
    ├── camera_emulator.h   # Camera simulation
    ├── camera_emulator.cpp
    ├── mainwindow.h        # Main window
    ├── mainwindow.cpp
    ├── imagewidget.h       # Image display with colormap
    └── imagewidget.cpp
```

## Advantages of This Approach

✅ **No dependencies** - Just Qt, nothing else to install!
✅ **Cross-platform** - Works on Windows, macOS, Linux
✅ **Any compiler** - MinGW, MSVC, GCC all work
✅ **Faster setup** - No OpenCV configuration needed
✅ **Lightweight** - Smaller binary size
✅ **Educational** - Shows Qt image processing capabilities

## Next Steps

This is the foundation. You can easily add:
- X-axis profile plot
- Y-axis profile plot
- Export functionality
- Multiple colormaps
- Adjustable frame rate

## License

Interview project for OWLO
