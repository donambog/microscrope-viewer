#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "Data.h"
#include <QImage>
#include <QRgb>

/**
 * @brief Manages frame processing and conversion to displayable images
 *
 * Separates data processing logic from display widgets.
 * Responsibilities:
 * - Frame validation
 * - Data normalization
 * - Colormap application
 * - QImage generation
 */
class DisplayManager {
public:
    DisplayManager();

    /**
     * @brief Process raw frame into displayable QImage
     * @param frame Raw frame data (HEIGHT x WIDTH)
     * @return Processed QImage with colormap applied
     */
    QImage processFrame(const Frame& frame);

private:
    /**
     * @brief Apply VIRIDIS-like colormap to normalized value [0-1]
     * @param value Normalized value between 0 and 1
     * @return RGB color
     */
    QRgb applyColormap(double value);

    /**
     * @brief Validate frame dimensions and content
     */
    bool isValidFrame(const Frame& frame) const;
};

#endif // DISPLAYMANAGER_H
