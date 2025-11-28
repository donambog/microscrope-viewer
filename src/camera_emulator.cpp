#include "camera_emulator.h"

int CameraEmulator::getCurrentIndex() {
    // Python equivalent: int(time.time() * 10) % 100
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    
    // Divide by 100ms to get 10 updates per second
    return static_cast<int>((millis / 100)) % 100;
}

CameraEmulator::Frame CameraEmulator::readCurrentFrame() {
    int index = getCurrentIndex();
    
    // Create frame (100 rows x 200 columns matrix)
    Frame frame(HEIGHT, std::vector<double>(WIDTH, 0.0));
    
    // Fill frame with 3 Gaussian spots
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // First spot: fixed at bottom left, centered at (0, 50)
            double spot1 = std::exp(-(x*x + (y-50)*(y-50)) / 400.0);
            
            // Second spot: fixed at bottom right, centered at (199, 50)
            double spot2 = std::exp(-((x-199)*(x-199) + (y-50)*(y-50)) / 400.0);
            
            // Third spot: moving
            // X position: 2*index (moves horizontally)
            // Y position: 50 + sin(index/10.0)*40 (oscillates vertically)
            double centerX = 2.0 * index;
            double centerY = 50.0 + std::sin(index / 10.0) * 40.0;
            double spot3 = std::exp(-((x-centerX)*(x-centerX) + (y-centerY)*(y-centerY)) / 1000.0);
            
            // Sum of the three spots
            frame[y][x] = spot1 + spot2 + spot3;
        }
    }
    
    return frame;
}

std::vector<double> CameraEmulator::calculateXProfile(const Frame& frame) {
    if (frame.empty() || frame[0].empty()) {
        return std::vector<double>();
    }
    
    int height = static_cast<int>(frame.size());
    int width = static_cast<int>(frame[0].size());
    
    std::vector<double> profile(width, 0.0);
    
    // For each column x, average all rows
    for (int x = 0; x < width; ++x) {
        double sum = 0.0;
        for (int y = 0; y < height; ++y) {
            sum += frame[y][x];
        }
        profile[x] = sum / height;
    }
    
    return profile;
}

std::vector<double> CameraEmulator::calculateYProfile(const Frame& frame) {
    if (frame.empty() || frame[0].empty()) {
        return std::vector<double>();
    }
    
    int height = static_cast<int>(frame.size());
    int width = static_cast<int>(frame[0].size());
    
    std::vector<double> profile(height, 0.0);
    
    // For each row y, average all columns
    for (int y = 0; y < height; ++y) {
        double sum = 0.0;
        for (int x = 0; x < width; ++x) {
            sum += frame[y][x];
        }
        profile[y] = sum / width;
    }
    
    return profile;
}
