#include <QtTest/QtTest>
#include <QImage>
#include "../src/imagewidget.h"
#include "../src/camera_emulator.h"

class TestImageWidget : public QObject {
    Q_OBJECT
    
private slots:
    void testWidgetCreation();
    void testUpdateFrame();
    void testEmptyFrame();
    void testPixmapNotNull();
    void testColormapRange();
};

void TestImageWidget::testWidgetCreation() {
    // Test que le widget se crée correctement
    ImageWidget widget;
    
    QVERIFY(widget.isWidgetType());
    QVERIFY(widget.minimumSize().width() > 0);
    QVERIFY(widget.minimumSize().height() > 0);
}

void TestImageWidget::testUpdateFrame() {
    // Test qu'on peut mettre à jour avec une frame valide
    ImageWidget widget;
    auto frame = CameraEmulator::readCurrentFrame();
    
    // Ne devrait pas crasher
    widget.updateFrame(frame);
    
    // Le pixmap devrait exister
    QVERIFY(!widget.pixmap()->isNull());
}

void TestImageWidget::testEmptyFrame() {
    // Test avec une frame vide
    ImageWidget widget;
    std::vector<std::vector<double>> emptyFrame;
    
    // Ne devrait pas crasher
    widget.updateFrame(emptyFrame);
    
    // Le pixmap devrait être null ou inchangé
    // (comportement défensif)
}

void TestImageWidget::testPixmapNotNull() {
    // Test que le pixmap n'est pas null après update
    ImageWidget widget;
    auto frame = CameraEmulator::readCurrentFrame();
    
    widget.updateFrame(frame);
    
    const QPixmap* pm = widget.pixmap();
    QVERIFY(pm != nullptr);
    QVERIFY(!pm->isNull());
    QCOMPARE(pm->width(), 200);
    QCOMPARE(pm->height(), 100);
}

void TestImageWidget::testColormapRange() {
    // Test que le colormap fonctionne pour différentes valeurs
    ImageWidget widget;
    
    // Frame avec valeurs connues
    std::vector<std::vector<double>> testFrame(100, std::vector<double>(200, 0.5));
    
    // Ne devrait pas crasher
    widget.updateFrame(testFrame);
    
    QVERIFY(!widget.pixmap()->isNull());
}

QTEST_MAIN(TestImageWidget)
#include "test_imagewidget.moc"
