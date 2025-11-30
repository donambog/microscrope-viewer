#include "imagewidget.h"
#include <QPixmap>
#include <cmath>

ImageWidget::ImageWidget(
    QWidget* parent,
    const ImageWidgetData& data,
    const ImageWidgetStyle& style
    ) : QLabel(parent) {
    // Configure size
    setMinimumSize(data.minWidth, data.minHeight);
    setText(data.initialText);
    // Configure style
    setScaledContents(style.scaledContents);
    setFrameStyle(style.frameShape | style.frameShadow);
    setAlignment(style.alignment);
    setStyleSheet(style.buildStyleSheet());
}

void ImageWidget::displayImage(const QImage& image) {
    if (!image.isNull()) {
        setPixmap(QPixmap::fromImage(image));
    }
}

