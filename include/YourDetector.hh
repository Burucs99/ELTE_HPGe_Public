#ifndef YOURDETECTOR_HH
#define YOURDETECTOR_HH

#include "YourScintillatorCrystal.hh"
#include "YourSideReflectionLayer.hh"
#include "YourTopReflectionLayer.hh"
#include "YourScintillatorOuterCoverage.hh"
#include "YourScintillatorCoverageCap.hh"
#include <G4LogicalVolume.hh>

class YourDetector{

    public:
        YourDetector();
        ~YourDetector();

        void Build(G4LogicalVolume* motherVolume, G4Material* scintillatorCrystalMaterial, G4ThreeVector translate, G4int id,
                        G4Material* sideReflectionLayerMaterial,
                        G4Material* topReflectionLayerMaterial,
                        G4Material* outerCoverageMaterial,
                        G4Material* scintillatorCoverageCapMaterial);

        G4LogicalVolume* GetLogicalVolume() const { return this->scintillatorCrystal->GetLogicalVolume(); }

    private:

        YourScintillatorCrystal* scintillatorCrystal;
        YourSideReflexionLayer* sideReflectionLayer;
        YourTopReflectionLayer* topReflectionLayer;
        YourScintillatorOuterCoverage* scintillatorOuterCoverage;
        YourScintillatorCoverageCap* scintillatorCoverageCap;

        G4ThreeVector topReflectionLayerOffset, outerCoverageOffset, scintillatorCoverageCapOffset, detectorBodyOffset;
        G4int id;


};


#endif