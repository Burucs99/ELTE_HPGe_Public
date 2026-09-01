#include "YourBarrelSideWall.hh"

YourBarrelSideWall::YourBarrelSideWall() {
    this->pRmin = 286.0 * mm;
    this->pRmax = 287.5 * mm;
    this->pDz = 438.0 * mm;
    this->rotationMatrix = new G4RotationMatrix();
    this->rotationMatrix->rotateX(90.0 * deg);
}

void YourBarrelSideWall::Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial){
    this->barrelSideWallVolume = new G4Tubs("BarrelSideWallVolume", this->pRmin, this->pRmax, this->pDz, 0.0 * deg, 360.0 * deg);
    this->barrelSideWallLogicalVolume = new G4LogicalVolume(this->barrelSideWallVolume, buildMaterial, "BarrelSideWallLogicalVolume");
    this->barrelSideWallPhysicalVolume = new G4PVPlacement(this->rotationMatrix, G4ThreeVector(0.0 * m, 439.5 * mm, 0.0 * m), this->barrelSideWallLogicalVolume, "BarrelSideWallPhysicalVolume", motherLogicalVolume, false, 0, true);
    this->InitialiseAttributes();
}

void YourBarrelSideWall::InitialiseAttributes() {
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Color(1.0, 1.0, 1.0, 1.0));
    visAttributes->SetForceSolid(true);
    this->barrelSideWallLogicalVolume->SetVisAttributes(visAttributes);
}


YourBarrelSideWall::~YourBarrelSideWall() {
    delete this->barrelSideWallVolume;
    delete this->barrelSideWallLogicalVolume;
    delete this->barrelSideWallPhysicalVolume;
}