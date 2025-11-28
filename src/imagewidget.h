#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include <QImage>
#include <vector>

/**
 * @brief Widget to display camera frames using Qt native functions
 * 
 * This widget receives raw frame data and displays it with
 * automatic normalization and colormap (VIRIDIS-like).
 * No OpenCV required - pure Qt!
 */
class ImageWidget : public QLabel {
    Q_OBJECT
    
public:
    explicit ImageWidget(QWidget* parent = nullptr);
    
public slots:
    /**
     * @brief Update display with a new frame
     * @param frame Input frame as 2D vector of doubles
     */
    void updateFrame(const std::vector<std::vector<double>>& frame);
    
private:
    /**
     * @brief Apply VIRIDIS-like colormap to a normalized value [0-1]
     * @param value Normalized value between 0 and 1
     * @return RGB color
     */
    QRgb applyColormap(double value);
    
    /**
     * @brief Convert frame data to QImage
     * @param frame Raw frame data
     * @return QImage with colormap applied
     */
    QImage frameToImage(const std::vector<std::vector<double>>& frame);
};

#endif // IMAGEWIDGET_H
