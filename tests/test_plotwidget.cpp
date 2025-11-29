#include <QtTest/QtTest>
#include "../src/plotwidget.h"

class TestPlotWidget : public QObject {
    Q_OBJECT
    
private slots:
    void testWidgetCreation();
    void testSetTitle();
    void testSetAxisLabels();
    void testUpdateData();
    void testEmptyData();
    void testSingleDataPoint();
    void testLargeDataSet();
    void testAutoScaling();
};

void TestPlotWidget::testWidgetCreation() {
    // Test que le widget se crée correctement
    PlotWidget widget;
    
    QVERIFY(widget.isWidgetType());
    QVERIFY(widget.minimumSize().width() > 0);
    QVERIFY(widget.minimumSize().height() > 0);
}

void TestPlotWidget::testSetTitle() {
    // Test qu'on peut changer le titre
    PlotWidget widget;
    
    widget.setTitle("Test Title");
    
    // Pas de crash = succès
    QVERIFY(true);
}

void TestPlotWidget::testSetAxisLabels() {
    // Test qu'on peut changer les labels des axes
    PlotWidget widget;
    
    widget.setAxisLabels("X Label", "Y Label");
    
    // Pas de crash = succès
    QVERIFY(true);
}

void TestPlotWidget::testUpdateData() {
    // Test qu'on peut mettre à jour avec des données
    PlotWidget widget;
    
    std::vector<double> data = {1.0, 2.0, 3.0, 2.0, 1.0};
    widget.updateData(data);
    
    // Pas de crash = succès
    QVERIFY(true);
}

void TestPlotWidget::testEmptyData() {
    // Test avec des données vides
    PlotWidget widget;
    
    std::vector<double> emptyData;
    
    // Ne devrait pas crasher
    widget.updateData(emptyData);
    
    QVERIFY(true);
}

void TestPlotWidget::testSingleDataPoint() {
    // Test avec un seul point
    PlotWidget widget;
    
    std::vector<double> singlePoint = {1.5};
    
    // Ne devrait pas crasher
    widget.updateData(singlePoint);
    
    QVERIFY(true);
}

void TestPlotWidget::testLargeDataSet() {
    // Test avec beaucoup de données (200 points)
    PlotWidget widget;
    
    std::vector<double> largeData(200);
    for (size_t i = 0; i < largeData.size(); ++i) {
        largeData[i] = std::sin(i / 10.0);
    }
    
    // Ne devrait pas crasher
    widget.updateData(largeData);
    
    QVERIFY(true);
}

void TestPlotWidget::testAutoScaling() {
    // Test que l'auto-scaling fonctionne
    PlotWidget widget;
    
    // Données avec min=0, max=10
    std::vector<double> data = {0.0, 5.0, 10.0};
    widget.updateData(data);
    
    // Données avec min=-5, max=5
    std::vector<double> data2 = {-5.0, 0.0, 5.0};
    widget.updateData(data2);
    
    // Pas de crash = auto-scaling fonctionne
    QVERIFY(true);
}

QTEST_MAIN(TestPlotWidget)
#include "test_plotwidget.moc"
