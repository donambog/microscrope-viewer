#include "imagewidget.h"
#include <QPixmap>
#include <algorithm>
#include <cmath>

ImageWidget::ImageWidget(QWidget* parent) : QLabel(parent) {
    // Configure label for image display
    setScaledContents(true);
    setMinimumSize(400, 200);
    setFrameStyle(QFrame::Box | QFrame::Sunken);
    setAlignment(Qt::AlignCenter);
    
    // Set initial background
    setStyleSheet("QLabel { background-color: #2b2b2b; }");
    setText("Waiting for camera frames...");
}

void ImageWidget::updateFrame(const std::vector<std::vector<double>>& frame) {
    QImage image = frameToImage(frame);
    if (!image.isNull()) {
        setPixmap(QPixmap::fromImage(image));
    }
}

QRgb ImageWidget::applyColormap(double value) {
    // VIRIDIS-like colormap approximation
    // value should be between 0.0 and 1.0
    value = std::max(0.0, std::min(1.0, value));
    
    int r, g, b;
    
    if (value < 0.25) {
        // Dark purple to blue
        double t = value / 0.25;
        r = static_cast<int>(68 * (1-t) + 59 * t);
        g = static_cast<int>(1 * (1-t) + 82 * t);
        b = static_cast<int>(84 * (1-t) + 139 * t);
    } else if (value < 0.5) {
        // Blue to cyan
        double t = (value - 0.25) / 0.25;
        r = static_cast<int>(59 * (1-t) + 33 * t);
        g = static_cast<int>(82 * (1-t) + 145 * t);
        b = static_cast<int>(139 * (1-t) + 140 * t);
    } else if (value < 0.75) {
        // Cyan to green/yellow
        double t = (value - 0.5) / 0.25;
        r = static_cast<int>(33 * (1-t) + 94 * t);
        g = static_cast<int>(145 * (1-t) + 201 * t);
        b = static_cast<int>(140 * (1-t) + 98 * t);
    } else {
        // Green/yellow to yellow
        double t = (value - 0.75) / 0.25;
        r = static_cast<int>(94 * (1-t) + 253 * t);
        g = static_cast<int>(201 * (1-t) + 231 * t);
        b = static_cast<int>(98 * (1-t) + 37 * t);
    }
    
    return qRgb(r, g, b);
}

QImage ImageWidget::frameToImage(const std::vector<std::vector<double>>& frame) {
    if (frame.empty() || frame[0].empty()) {
        return QImage();
    }
    
    int height = static_cast<int>(frame.size());
    int width = static_cast<int>(frame[0].size());
    
    // Find min and max for normalization
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
    
    // Create QImage
    QImage image(width, height, QImage::Format_RGB32);
    
    // Fill image with colormap
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            //Normalize to [0, 1] for color map
            double normalized = (frame[y][x] - minVal) / (maxVal - minVal);
            
            // Apply colormap
            QRgb color = applyColormap(normalized);
            
            // Set pixel
            image.setPixel(x, y, color);
        }
    }
    
    return image;
}
