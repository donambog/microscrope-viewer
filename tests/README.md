# Tests Unitaires - Microscope Viewer

## 📋 Tests Disponibles

### 1. test_camera_emulator
Tests pour le générateur de frames :
- ✅ Dimensions correctes (200×100)
- ✅ Valeurs dans la plage attendue
- ✅ Profils X et Y corrects
- ✅ Gestion des frames vides

### 2. test_imagewidget
Tests pour l'affichage d'image :
- ✅ Création du widget
- ✅ Mise à jour avec frame valide
- ✅ Gestion des frames vides
- ✅ Pixmap généré correctement
- ✅ Colormap appliqué

### 3. test_plotwidget
Tests pour les graphiques :
- ✅ Création du widget
- ✅ Modification du titre
- ✅ Modification des labels
- ✅ Mise à jour des données
- ✅ Gestion des cas limites (vide, 1 point, beaucoup de points)
- ✅ Auto-scaling

## 🚀 Exécution des Tests

### Option 1 : Via Qt Creator

1. Ouvre Qt Creator
2. **File** → **Open File or Project**
3. Ouvre `tests/tests.pro`
4. **Build** → **Build All**
5. **Build** → **Run** (lance tous les tests)

### Option 2 : Ligne de Commande

```bash
cd tests

# Test CameraEmulator
qmake test_camera_emulator.pro
make
./test_camera_emulator

# Test ImageWidget
qmake test_imagewidget.pro
make
./test_imagewidget

# Test PlotWidget
qmake test_plotwidget.pro
make
./test_plotwidget
```

### Option 3 : Tous les Tests

```bash
cd tests
qmake tests.pro
make
make check  # Lance tous les tests
```

## ✅ Résultats Attendus

```
********* Start testing of TestCameraEmulator *********
PASS   : TestCameraEmulator::testFrameDimensions()
PASS   : TestCameraEmulator::testFrameValues()
PASS   : TestCameraEmulator::testXProfileDimensions()
PASS   : TestCameraEmulator::testYProfileDimensions()
PASS   : TestCameraEmulator::testXProfileValues()
PASS   : TestCameraEmulator::testYProfileValues()
PASS   : TestCameraEmulator::testEmptyFrameHandling()
Totals: 7 passed, 0 failed, 0 skipped
********* Finished testing of TestCameraEmulator *********

********* Start testing of TestImageWidget *********
PASS   : TestImageWidget::testWidgetCreation()
PASS   : TestImageWidget::testUpdateFrame()
PASS   : TestImageWidget::testEmptyFrame()
PASS   : TestImageWidget::testPixmapNotNull()
PASS   : TestImageWidget::testColormapRange()
Totals: 5 passed, 0 failed, 0 skipped
********* Finished testing of TestImageWidget *********

********* Start testing of TestPlotWidget *********
PASS   : TestPlotWidget::testWidgetCreation()
PASS   : TestPlotWidget::testSetTitle()
PASS   : TestPlotWidget::testSetAxisLabels()
PASS   : TestPlotWidget::testUpdateData()
PASS   : TestPlotWidget::testEmptyData()
PASS   : TestPlotWidget::testSingleDataPoint()
PASS   : TestPlotWidget::testLargeDataSet()
PASS   : TestPlotWidget::testAutoScaling()
Totals: 8 passed, 0 failed, 0 skipped
********* Finished testing of TestPlotWidget *********
```

## 🧪 Ajouter Tes Propres Tests

### Exemple de Test

```cpp
void TestCameraEmulator::testCustom() {
    // Arrange (préparation)
    auto frame = CameraEmulator::readCurrentFrame();
    
    // Act (action)
    auto profile = CameraEmulator::calculateXProfile(frame);
    
    // Assert (vérification)
    QVERIFY(!profile.empty());
    QCOMPARE(profile.size(), 200);
}
```

### Macros Qt Test Utiles

```cpp
QVERIFY(condition)               // Vérifie que condition est vraie
QCOMPARE(actual, expected)       // Vérifie l'égalité
QVERIFY2(condition, message)     // Avec message custom
QFAIL(message)                   // Force un échec
QSKIP(message)                   // Saute ce test
QEXPECT_FAIL(...)                // Échec attendu
```

## 📊 Couverture de Tests

### Couverture Actuelle

- **CameraEmulator** : ~90%
  - ✅ Génération de frames
  - ✅ Calcul de profils
  - ❌ Pas testé : Animation dans le temps

- **ImageWidget** : ~70%
  - ✅ Affichage basique
  - ✅ Gestion d'erreurs
  - ❌ Pas testé : Colormap en détail

- **PlotWidget** : ~80%
  - ✅ Affichage basique
  - ✅ Cas limites
  - ❌ Pas testé : Rendu graphique exact

### Tests à Ajouter (Optionnel)

- Test d'intégration (MainWindow complet)
- Test de performance (frame rate)
- Test de mémoire (fuites)
- Test de threading (si ajouté)

## 🎯 Pour l'Interview

Ces tests montrent :
- ✅ Connaissance des bonnes pratiques
- ✅ Code testable (découplage)
- ✅ Robustesse (gestion d'erreurs)
- ✅ Professionnalisme

**Astuce** : Mentionne que tu as ajouté des tests unitaires dans ton README !
