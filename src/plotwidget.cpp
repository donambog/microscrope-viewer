#include "plotwidget.h"
#include <QPaintEvent>
#include <QPen>
#include <algorithm>
#include <cmath>

PlotWidget::PlotWidget(QWidget* parent)
    : QWidget(parent)
    , m_title("Plot")
    , m_xLabel("X")
    , m_yLabel("Y")
    , m_minValue(0.0)
    , m_maxValue(1.0)
{
    setMinimumSize(400, 200);
    setStyleSheet("QWidget { background-color: white; }");
}

void PlotWidget::setTitle(const QString& title) {
    m_title = title;
    update();
}

void PlotWidget::setAxisLabels(const QString& xLabel, const QString& yLabel) {
    m_xLabel = xLabel;
    m_yLabel = yLabel;
    update();
}

void PlotWidget::updateData(const std::vector<double>& data) {
    if (data.empty()) {
        return;
    }
    
    m_data = data;
    
    // Calculate min/max for auto-scaling
    m_minValue = *std::min_element(data.begin(), data.end());
    m_maxValue = *std::max_element(data.begin(), data.end());
    
    // Add 10% margin
    double range = m_maxValue - m_minValue;
    if (range < 1e-10) {
        range = 1.0;
    }
    m_minValue -= range * 0.1;
    m_maxValue += range * 0.1;
    
    // Trigger repaint
    update();
}

void PlotWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Draw white background
    painter.fillRect(rect(), Qt::white);
    
    // Draw axes and grid
    drawAxes(painter);
    
    // Draw curve if we have data
    if (!m_data.empty()) {
        drawCurve(painter);
    }
}

void PlotWidget::drawAxes(QPainter& painter) {
    int w = width();
    int h = height();
    
    // Plot area
    int plotLeft = LEFT_MARGIN;
    int plotRight = w - RIGHT_MARGIN;
    int plotTop = TOP_MARGIN;
    int plotBottom = h - BOTTOM_MARGIN;
    
    // Draw title
    painter.setPen(Qt::black);
    QFont titleFont = painter.font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(QRect(0, 5, w, 30), Qt::AlignCenter, m_title);
    
    // Reset font
    QFont normalFont = painter.font();
    normalFont.setPointSize(9);
    normalFont.setBold(false);
    painter.setFont(normalFont);
    
    // Draw axes
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(plotLeft, plotBottom, plotRight, plotBottom); // X axis
    painter.drawLine(plotLeft, plotTop, plotLeft, plotBottom);     // Y axis
    
    // Draw grid
    painter.setPen(QPen(QColor(200, 200, 200), 1));
    
    // Horizontal grid lines (5 lines)
    for (int i = 1; i < 5; ++i) {
        int y = plotBottom - i * (plotBottom - plotTop) / 5;
        painter.drawLine(plotLeft, y, plotRight, y);
    }
    
    // Vertical grid lines (10 lines)
    for (int i = 1; i < 10; ++i) {
        int x = plotLeft + i * (plotRight - plotLeft) / 10;
        painter.drawLine(x, plotTop, x, plotBottom);
    }
    
    // Draw Y axis labels
    painter.setPen(Qt::black);
    for (int i = 0; i <= 5; ++i) {
        int y = plotBottom - i * (plotBottom - plotTop) / 5;
        double value = m_minValue + i * (m_maxValue - m_minValue) / 5;
        QString label = QString::number(value, 'f', 2);
        painter.drawText(QRect(0, y - 10, plotLeft - 5, 20), 
                        Qt::AlignRight | Qt::AlignVCenter, label);
    }
    
    // Draw X axis labels
    int numXLabels = std::min(10, static_cast<int>(m_data.size()));
    if (numXLabels > 0) {
        for (int i = 0; i <= numXLabels; ++i) {
            int x = plotLeft + i * (plotRight - plotLeft) / numXLabels;
            int dataIndex = i * (m_data.size() - 1) / numXLabels;
            QString label = QString::number(dataIndex);
            painter.drawText(QRect(x - 20, plotBottom + 5, 40, 20),
                            Qt::AlignCenter, label);
        }
    }
    
    // Draw axis labels
    painter.drawText(QRect(plotLeft, plotBottom + 25, plotRight - plotLeft, 20),
                    Qt::AlignCenter, m_xLabel);
    
    painter.save();
    painter.translate(10, (plotTop + plotBottom) / 2);
    painter.rotate(-90);
    painter.drawText(QRect(-50, -10, 100, 20), Qt::AlignCenter, m_yLabel);
    painter.restore();
}

void PlotWidget::drawCurve(QPainter& painter) {
    if (m_data.size() < 2) {
        return;
    }
    
    // Draw the curve
    painter.setPen(QPen(QColor(0, 120, 212), 2)); // Blue line
    
    QPointF prevPoint = dataToWidget(0, m_data[0]);
    
    for (size_t i = 1; i < m_data.size(); ++i) {
        QPointF point = dataToWidget(i, m_data[i]);
        painter.drawLine(prevPoint, point);
        prevPoint = point;
    }
}

QPointF PlotWidget::dataToWidget(double x, double y) const {
    int w = width();
    int h = height();
    
    int plotLeft = LEFT_MARGIN;
    int plotRight = w - RIGHT_MARGIN;
    int plotTop = TOP_MARGIN;
    int plotBottom = h - BOTTOM_MARGIN;
    
    // Normalize x to [0, 1]
    double xNorm = x / (m_data.size() - 1);
    
    // Normalize y to [0, 1]
    double yNorm = (y - m_minValue) / (m_maxValue - m_minValue);
    
    // Map to widget coordinates
    double widgetX = plotLeft + xNorm * (plotRight - plotLeft);
    double widgetY = plotBottom - yNorm * (plotBottom - plotTop);
    
    return QPointF(widgetX, widgetY);
}
