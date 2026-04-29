#include "YourScintillatorOuterCoverage.hh"
#include <G4PVPlacement.hh>

YourScintillatorOuterCoverage::YourScintillatorOuterCoverage(){

    this->pRmin = 25.5 * mm;
    this->pRmax = 26.5 * mm;
    this->pDz = 25.25 * mm;
    this->rotationMatrix = new G4RotationMatrix();
    this->rotationMatrix->rotateX(90.0 * deg);
}

void YourScintillatorOuterCoverage::Build(G4LogicalVolume* motherVolume, G4Material* material, G4ThreeVector translate, G4int id){

    this->ScintillatorOuterCoverageVolume = new G4Tubs("ScintillatorOuterCoverageVolume" + std::to_string(id), this->pRmin, this->pRmax, this->pDz, 0.0 * deg, 360.0 * deg);
    this->ScintillatorOuterCoverageLogicalVolume = new G4LogicalVolume(this->ScintillatorOuterCoverageVolume, material, "ScintillatorOuterCoverageLogicalVolume" + std::to_string(id));
    this->ScintillatorOuterCoveragePhysicalVolume = new G4PVPlacement(this->rotationMatrix, translate, this->ScintillatorOuterCoverageLogicalVolume, "ScintillatorOuterCoveragePhysicalVolume" + std::to_string(id), motherVolume, false, 0, true);

    this->InitialiseAttributes();
}

void YourScintillatorOuterCoverage::InitialiseAttributes(){

    G4VisAttributes* scintillatorOuterCoverageVisAttributes = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 1.0)); // brownish color
    scintillatorOuterCoverageVisAttributes->SetForceSolid(true);
    this->ScintillatorOuterCoverageLogicalVolume->SetVisAttributes(scintillatorOuterCoverageVisAttributes);
}

YourScintillatorOuterCoverage::~YourScintillatorOuterCoverage(){
    delete this->ScintillatorOuterCoverageVolume;
    delete this->ScintillatorOuterCoverageLogicalVolume;
    delete this->ScintillatorOuterCoveragePhysicalVolume;
    delete this->rotationMatrix;
}