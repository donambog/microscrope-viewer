#include <QCoreApplication>
#include <QtTest>
#include <QApplication>
#include "imagewidget.h"

// helper to access protected methods
class TestableImageWidget : public ImageWidget {
public:
    using ImageWidget::applyColormap;
    using ImageWidget::frameToImage;
};

class TestImageWidget : public QObject
{
    Q_OBJECT

private slots:
    void testConstructorDefault();
    void testConstructorCustomData();
    void testApplyColormapLimits();
    void testFrameToImageDimensions();
    void testUpdateFrameNoCrash();
};

void TestImageWidget::testConstructorDefault()
{
    ImageWidget widget;
    QCOMPARE(widget.minimumSize().width(), 400);
    QCOMPARE(widget.minimumSize().height(), 200);
}

void TestImageWidget::testConstructorCustomData()
{
    ImageWidgetData data;
    data.minWidth = 800;
    data.minHeight = 600;
    data.initialText = "Test";

    ImageWidget widget(nullptr, data);
    QCOMPARE(widget.minimumSize().width(), 800);
    QCOMPARE(widget.minimumSize().height(), 600);
    QCOMPARE(widget.text(), QString("Test"));
}

void TestImageWidget::testApplyColormapLimits()
{
    TestableImageWidget widget;

    QRgb color0 = widget.applyColormap(0.0);
    QRgb color1 = widget.applyColormap(1.0);

    // checks that color are differents
    QVERIFY(color0 != color1);
}

void TestImageWidget::testFrameToImageDimensions()
{
    TestableImageWidget widget;

    // test frame 100x200
    Frame frame(100, std::vector<double>(200, 0.5));

    QImage image = widget.frameToImage(frame);

    QVERIFY(!image.isNull());
    QCOMPARE(image.width(), 200);
    QCOMPARE(image.height(), 100);
}

void TestImageWidget::testUpdateFrameNoCrash()
{
    ImageWidget widget;

    // Frame de test
    Frame frame(100, std::vector<double>(200, 0.5));

    // Ne doit pas crasher
    widget.updateDisplay(frame);

    QVERIFY(true);
}

QTEST_MAIN(TestImageWidget)

#include "test_imagewidget.moc"

