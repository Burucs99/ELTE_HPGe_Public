#include "YourBarrelContent.hh"
#include <G4ThreeVector.hh>

YourBarrelContent::YourBarrelContent() {
    this->pRmin = 0.0 * mm;
    this->pRmax = 286.0 * mm;
    this->pDz = 438.0 * mm;
    this->rotationMatrix = new G4RotationMatrix();
    this->rotationMatrix->rotateX(90.0 * deg);
}

void YourBarrelContent::Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial) {
    this->barrelContentVolume = new G4Tubs("BarrelContentVolume", this->pRmin, this->pRmax, this->pDz, 0.0 * deg, 360.0 * deg);
    this->barrelContentLogicalVolume = new G4LogicalVolume(this->barrelContentVolume, buildMaterial, "BarrelContentLogicalVolume");
    this->barrelContentPhysicalVolume = new G4PVPlacement(this->rotationMatrix, G4ThreeVector(0.0, 439.5 * mm, 0.0), this->barrelContentLogicalVolume, "BarrelContentPhysicalVolume", motherLogicalVolume, false, 0, true);
    this->InitialiseAttributes();
}

void YourBarrelContent::InitialiseAttributes() {
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Color(0.263, 0.757, 0.969, 1.0));
    visAttributes->SetForceSolid(true);
    this->barrelContentLogicalVolume->SetVisAttributes(visAttributes);
}


YourBarrelContent::~YourBarrelContent() {
    delete this->barrelContentVolume;
    delete this->barrelContentLogicalVolume;
    delete this->barrelContentPhysicalVolume;
}