#include <QtTest>
#include <QApplication>
#include "imagewidget.h"

class TestImageWidget : public QObject
{
    Q_OBJECT

private slots:
    void testConstructorDefault();
    void testConstructorCustomData();
    void testDisplayImageValid();
    void testDisplayImageNull();
};

void TestImageWidget::testConstructorDefault()
{
    ImageWidget widget;

    QCOMPARE(widget.minimumSize().width(), 400);
    QCOMPARE(widget.minimumSize().height(), 200);
    QCOMPARE(widget.text(), QString("Waiting for camera frames..."));
}

void TestImageWidget::testConstructorCustomData()
{
    ImageWidgetData data;
    data.minWidth = 800;
    data.minHeight = 600;
    data.initialText = "Test Mode";

    ImageWidget widget(nullptr, data);

    QCOMPARE(widget.minimumSize().width(), 800);
    QCOMPARE(widget.minimumSize().height(), 600);
    QCOMPARE(widget.text(), QString("Test Mode"));
}

void TestImageWidget::testDisplayImageValid()
{
    ImageWidget widget;

    // Créer une image de test
    QImage testImage(200, 100, QImage::Format_RGB32);
    testImage.fill(Qt::red);

    // Ne doit pas crasher
    widget.displayImage(testImage);

    QVERIFY(true);  // Si on arrive ici, pas de crash
}

void TestImageWidget::testDisplayImageNull()
{
    ImageWidget widget;

    QImage nullImage;

    // Ne doit pas crasher avec image nulle
    widget.displayImage(nullImage);

    QVERIFY(true);
}


QTEST_MAIN(TestImageWidget)

#include "test_imagewidget.moc"
