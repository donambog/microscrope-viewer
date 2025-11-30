#include <QtTest>
#include "displaymanager.h"
#include "Data.h"



class TestDisplayManager : public QObject
{
    Q_OBJECT

private slots:
    void testProcessFrameValidDimensions();
    void testProcessFrameNormalization();
    void testProcessFrameEmptyFrame();
    void testProcessFrameInvalidDimensions();
    void testApplyColormapLimits();
};

void TestDisplayManager::testProcessFrameValidDimensions()
{
    DisplayManager manager;

    // Frame 100x200
    Frame frame(100, std::vector<double>(200, 0.5));

    QImage result = manager.processFrame(frame);

    QVERIFY(!result.isNull());
    QCOMPARE(result.width(), 200);
    QCOMPARE(result.height(), 100);
}

void TestDisplayManager::testProcessFrameNormalization()
{
    DisplayManager manager;

    // Frame avec valeurs connues
    Frame frame = {
        {0.0, 0.5, 1.0},
        {0.0, 0.5, 1.0}
    };

    QImage result = manager.processFrame(frame);

    QVERIFY(!result.isNull());
    QCOMPARE(result.width(), 3);
    QCOMPARE(result.height(), 2);

    // Vérifier que les couleurs sont différentes (normalisation appliquée)
    QRgb color0 = result.pixel(0, 0);  // min → violet
    QRgb color2 = result.pixel(2, 0);  // max → jaune
    QVERIFY(color0 != color2);
}

void TestDisplayManager::testProcessFrameEmptyFrame()
{
    DisplayManager manager;

    Frame emptyFrame;

    QImage result = manager.processFrame(emptyFrame);

    // Doit retourner image nulle
    QVERIFY(result.isNull());
}

void TestDisplayManager::testProcessFrameInvalidDimensions()
{
    DisplayManager manager;

    // Frame avec lignes de tailles différentes
    Frame invalidFrame = {
        {1.0, 2.0, 3.0},
        {1.0, 2.0}        // ← Taille différente !
    };

    QImage result = manager.processFrame(invalidFrame);

    // Doit retourner image nulle
    QVERIFY(result.isNull());
}

void TestDisplayManager::testApplyColormapLimits()
{
    DisplayManager manager;

    // Frame avec valeurs limites
    Frame frame = {
        {0.0, 1.0}
    };

    QImage result = manager.processFrame(frame);

    QRgb colorMin = result.pixel(0, 0);  // Violet
    QRgb colorMax = result.pixel(1, 0);  // Jaune

    // Les couleurs doivent être très différentes
    QVERIFY(colorMin != colorMax);

    // Optionnel: vérifier couleurs approximatives
    // Violet ≈ (68, 1, 84)
    QVERIFY(qRed(colorMin) < 100);
    QVERIFY(qBlue(colorMin) > 50);

    // Jaune ≈ (253, 231, 37)
    QVERIFY(qRed(colorMax) > 200);
    QVERIFY(qGreen(colorMax) > 200);
}

QTEST_APPLESS_MAIN(TestDisplayManager)

#include "test_displaymanager.moc"
