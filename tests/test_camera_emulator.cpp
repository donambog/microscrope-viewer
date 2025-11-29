#include <QtTest/QtTest>
#include "../src/camera_emulator.h"

class TestCameraEmulator : public QObject {
    Q_OBJECT
    
private slots:
    void testFrameDimensions();
    void testFrameValues();
    void testXProfileDimensions();
    void testYProfileDimensions();
    void testXProfileValues();
    void testYProfileValues();
    void testEmptyFrameHandling();
};

void TestCameraEmulator::testFrameDimensions() {
    // Test que la frame a les bonnes dimensions
    auto frame = CameraEmulator::readCurrentFrame();
    
    QCOMPARE(frame.size(), static_cast<size_t>(CameraEmulator::HEIGHT));
    QCOMPARE(frame[0].size(), static_cast<size_t>(CameraEmulator::WIDTH));
}

void TestCameraEmulator::testFrameValues() {
    // Test que les valeurs sont dans une plage raisonnable
    auto frame = CameraEmulator::readCurrentFrame();
    
    for (const auto& row : frame) {
        for (double val : row) {
            QVERIFY(val >= 0.0);
            QVERIFY(val <= 5.0);  // Valeur max théorique (3 spots à 1.0)
        }
    }
}

void TestCameraEmulator::testXProfileDimensions() {
    // Test que le profil X a la bonne taille
    auto frame = CameraEmulator::readCurrentFrame();
    auto profile = CameraEmulator::calculateXProfile(frame);
    
    QCOMPARE(profile.size(), static_cast<size_t>(CameraEmulator::WIDTH));
}

void TestCameraEmulator::testYProfileDimensions() {
    // Test que le profil Y a la bonne taille
    auto frame = CameraEmulator::readCurrentFrame();
    auto profile = CameraEmulator::calculateYProfile(frame);
    
    QCOMPARE(profile.size(), static_cast<size_t>(CameraEmulator::HEIGHT));
}

void TestCameraEmulator::testXProfileValues() {
    // Test que le profil X contient des valeurs valides
    auto frame = CameraEmulator::readCurrentFrame();
    auto profile = CameraEmulator::calculateXProfile(frame);
    
    for (double val : profile) {
        QVERIFY(val >= 0.0);
        QVERIFY(val <= 5.0);
    }
    
    // Test que le profil X a au moins un pic (spot visible)
    double maxVal = *std::max_element(profile.begin(), profile.end());
    QVERIFY(maxVal > 0.1);  // Au moins un spot visible
}

void TestCameraEmulator::testYProfileValues() {
    // Test que le profil Y contient des valeurs valides
    auto frame = CameraEmulator::readCurrentFrame();
    auto profile = CameraEmulator::calculateYProfile(frame);
    
    for (double val : profile) {
        QVERIFY(val >= 0.0);
        QVERIFY(val <= 5.0);
    }
    
    // Test que le profil Y a au moins un pic
    double maxVal = *std::max_element(profile.begin(), profile.end());
    QVERIFY(maxVal > 0.1);
}

void TestCameraEmulator::testEmptyFrameHandling() {
    // Test avec une frame vide
    CameraEmulator::Frame emptyFrame;
    
    auto xProfile = CameraEmulator::calculateXProfile(emptyFrame);
    auto yProfile = CameraEmulator::calculateYProfile(emptyFrame);
    
    QVERIFY(xProfile.empty());
    QVERIFY(yProfile.empty());
}

QTEST_MAIN(TestCameraEmulator)
#include "test_camera_emulator.moc"
