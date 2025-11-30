#include "displaymanager.h"
#include <algorithm>
#include <cmath>
#include "Data.h"

DisplayManager::DisplayManager() {
}

QImage DisplayManager::processFrame(const Frame& frame) {

    if (!isValidFrame(frame)) {
        return QImage();
    }

    int height = static_cast<int>(frame.size());
    int width = static_cast<int>(frame[0].size());

    // Find min/max for normalization
    double minVal = frame[0][0];
    double maxVal = frame[0][0];

    for (const auto& row : frame) {
        for (double val : row) {
            minVal = std::min(minVal, val);
            maxVal = std::max(maxVal, val);
        }
    }

    // Avoid division by zero
    if (maxVal - minVal < 1e-10) {
        maxVal = minVal + 1.0;
    }

    // Create image
    QImage image(width, height, QImage::Format_RGB32);

    // Apply colormap
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Normalize to [0, 1]
            double normalized = (frame[y][x] - minVal) / (maxVal - minVal);

            // Apply colormap and set pixel
            QRgb color = applyColormap(normalized);
            image.setPixel(x, y, color);
        }
    }

    return image;
}

QRgb DisplayManager::applyColormap(double value) {
    // Clamp value to [0, 1]
    value = std::max(0.0, std::min(1.0, value));

    // VIRIDIS-like colormap (simplified)
    // Interpolate between key colors

    if (value < 0.25) {
        // Violet to Blue
        double t = value / 0.25;
        int r = static_cast<int>(68 + (59 - 68) * t);
        int g = static_cast<int>(1 + (82 - 1) * t);
        int b = static_cast<int>(84 + (139 - 84) * t);
        return qRgb(r, g, b);
    } else if (value < 0.5) {
        // Blue to Cyan
        double t = (value - 0.25) / 0.25;
        int r = static_cast<int>(59 + (33 - 59) * t);
        int g = static_cast<int>(82 + (145 - 82) * t);
        int b = static_cast<int>(139 + (140 - 139) * t);
        return qRgb(r, g, b);
    } else if (value < 0.75) {
        // Cyan to Green
        double t = (value - 0.5) / 0.25;
        int r = static_cast<int>(33 + (94 - 33) * t);
        int g = static_cast<int>(145 + (201 - 145) * t);
        int b = static_cast<int>(140 + (98 - 140) * t);
        return qRgb(r, g, b);
    } else {
        // Green to Yellow
        double t = (value - 0.75) / 0.25;
        int r = static_cast<int>(94 + (253 - 94) * t);
        int g = static_cast<int>(201 + (231 - 201) * t);
        int b = static_cast<int>(98 + (37 - 98) * t);
        return qRgb(r, g, b);
    }
}

bool DisplayManager::isValidFrame(const Frame& frame) const {
    if (frame.empty()) {
        return false;
    }

    if (frame[0].empty()) {
        return false;
    }

    // Check consistent dimensions
    size_t width = frame[0].size();
    for (const auto& row : frame) {
        if (row.size() != width) {
            return false;
        }
    }

    return true;
}
