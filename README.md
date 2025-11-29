# Microscope Viewer - Qt Only Version

Simple camera frame viewer using **Qt only** - no OpenCV required!

## Existing Features translate from the Python assignement input data

- Live camera frame display
- Start/Stop button control
- FPS counter
- VIRIDIS-like colormap (pure Qt implementation)
- Works with MinGW or MSVC
- **No external dependencies** except Qt!

## Prerequisites

**Just Qt!**

- Qt 6.9.3
- Any compiler: MinGW
- Any platform: Windows

## Build Instructions

### Using Qt Creator

1. Open Qt Creator
2. **File** → **Open File or Project**
3. Select `MicroscopeViewer.pro`
4. Choose MinGW or MSVC
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
|── src/
|    ├── main.cpp            # Entry point
|    ├── camera_emulator.h   # Camera simulation
|    ├── camera_emulator.cpp
|    ├── mainwindow.h        # Main window
|    ├── mainwindow.cpp
|    ├── imagewidget.h       # Image display with colormap
|    └── imagewidget.cpp
|    └──   plotwidget.cpp
|──unit_test/
     ├── test_imagewidget.cpp
```
## Next Steps
- UnitTest still need to be completed
## License
Interview project for OWLO
