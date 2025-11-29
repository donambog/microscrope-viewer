#ifndef DATA_H
#define DATA_H
#include <vector>
#include <QLabel>

using Frame = std::vector<std::vector<double>>;

// Logic data
struct ImageWidgetData {
    int minWidth = 400;
    int minHeight = 200;
    QString initialText = "Waiting for camera frames...";
};

// Style
struct ImageWidgetStyle {
    QString backgroundColor = "#2b2b2b";
    QFrame::Shape frameShape = QFrame::Box;
    QFrame::Shadow frameShadow = QFrame::Sunken;
    Qt::Alignment alignment = Qt::AlignCenter;
    bool scaledContents = true;
    QString buildStyleSheet() const {
        return QString("QLabel { background-color: %1; }").arg(backgroundColor);
    }
};
#endif // DATA_H
