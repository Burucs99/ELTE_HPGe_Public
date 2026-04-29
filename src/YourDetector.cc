#include "YourDetector.hh"
#include <G4ThreeVector.hh>


YourDetector::YourDetector() 
{
    this->scintillatorCrystal = new YourScintillatorCrystal();
    this->sideReflectionLayer = new YourSideReflexionLayer();
    this->topReflectionLayer = new YourTopReflectionLayer();
    this->scintillatorOuterCoverage = new YourScintillatorOuterCoverage();
    this->scintillatorCoverageCap = new YourScintillatorCoverageCap();

}

void YourDetector::Build(G4LogicalVolume* motherVolume, G4Material* scintillatorCrystalMaterial, G4ThreeVector translate, G4int id,
                        G4Material* sideReflectionLayerMaterial,
                        G4Material* topReflectionLayerMaterial,
                        G4Material* outerCoverageMaterial,
                        G4Material* scintillatorCoverageCapMaterial)
{
    this->id = id;

    this->topReflectionLayerOffset = translate + G4ThreeVector(0 * mm, -25.25 * mm, 0 * mm);
    this->scintillatorCoverageCapOffset = translate + G4ThreeVector(0.0 * mm, -26.0 * mm, 0 * mm);
    this->outerCoverageOffset = translate + G4ThreeVector(0.0 * mm, -0.25 * mm * mm, 0 * mm);

    this->scintillatorCrystal->Build(motherVolume, scintillatorCrystalMaterial, translate, id);
    this->sideReflectionLayer->Build(motherVolume, sideReflectionLayerMaterial, translate, id);
    this->topReflectionLayer->Build(motherVolume, topReflectionLayerMaterial, this->topReflectionLayerOffset, id);
    this->scintillatorOuterCoverage->Build(motherVolume, outerCoverageMaterial, this->outerCoverageOffset, id);
    this->scintillatorCoverageCap->Build(motherVolume, scintillatorCoverageCapMaterial, this->scintillatorCoverageCapOffset, id);
}

YourDetector::~YourDetector() {
    delete this->scintillatorCrystal;
    delete this->sideReflectionLayer;
    delete this->topReflectionLayer;
    delete this->scintillatorOuterCoverage;
    delete this->scintillatorCoverageCap;
}