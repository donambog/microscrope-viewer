#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include <QImage>
#include "Data.h"

/**
 * @brief Widget to display processed images
 *
 * Responsibilities: Display only (no processing)
 */

class ImageWidget : public QLabel {
    Q_OBJECT
    
public:
    explicit ImageWidget(
        QWidget* parent = nullptr,
        const ImageWidgetData& data = ImageWidgetData(),
        const ImageWidgetStyle& style = ImageWidgetStyle()
        );
    
public slots:
    /**
     * @brief Display a processed image
     * @param image Already processed QImage ready for display
     */
    void displayImage(const QImage& image);
};

#endif // IMAGEWIDGET_H
