#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <vector>
#include <QPainter>
#include <QString>

/**
 * @brief Simple plot widget to display 1D data (X or Y profiles)
 * 
 * Displays a line plot with:
 * - Automatic scaling
 * - Grid lines
 * - Axis labels
 * - Title
 */
class PlotWidget : public QWidget {
    Q_OBJECT
    
public:
    explicit PlotWidget(QWidget* parent = nullptr);
    
    /**
     * @brief Set the title of the plot
     */
    void setTitle(const QString& title);
    
    /**
     * @brief Set X and Y axis labels
     */
    void setAxisLabels(const QString& xLabel, const QString& yLabel);
    
public slots:
    /**
     * @brief Update the plot with new data
     * @param data Vector of values to plot
     */
    void updateData(const std::vector<double>& data);
    
protected:
    /**
     * @brief Paint event to draw the plot
     */
    void paintEvent(QPaintEvent* event) override;
    
private:
    /**
     * @brief Draw the plot axes and grid
     */
    void drawAxes(QPainter& painter);
    
    /**
     * @brief Draw the data curve
     */
    void drawCurve(QPainter& painter);
    
    /**
     * @brief Map data coordinates to widget coordinates
     */
    QPointF dataToWidget(double x, double y) const;
    
    // Data
    std::vector<double> m_data;
    
    // Labels
    QString m_title;
    QString m_xLabel;
    QString m_yLabel;
    
    // Plot margins
    static constexpr int LEFT_MARGIN = 50;
    static constexpr int RIGHT_MARGIN = 20;
    static constexpr int TOP_MARGIN = 40;
    static constexpr int BOTTOM_MARGIN = 40;
    
    // Auto-scaling
    double m_minValue;
    double m_maxValue;
};

#endif // PLOTWIDGET_H
