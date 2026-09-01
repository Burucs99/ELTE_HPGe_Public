#include "YourBarrelVerticalWall.hh"

YourBarrelVerticalWall::YourBarrelVerticalWall() {
    this->pRmin = 0.0 * mm;
    this->pRmax = 287.5 * mm;
    this->pDz = 0.75 * mm;
    this->rotationMatrix = new G4RotationMatrix();
    this->rotationMatrix->rotateX(90.0 * deg);
}


void YourBarrelVerticalWall::Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial, G4ThreeVector translation) {
    this->barrelVerticalWallVolume = new G4Tubs("BarrelVerticalWallVolume", this->pRmin, this->pRmax, this->pDz, 0.0 * deg, 360.0 * deg);
    this->barrelVerticalWallLogicalVolume = new G4LogicalVolume(this->barrelVerticalWallVolume, buildMaterial, "BarrelVerticalWallLogicalVolume");
    this->barrelVerticalWallPhysicalVolume = new G4PVPlacement(this->rotationMatrix, translation, this->barrelVerticalWallLogicalVolume, "BarrelVerticalWallPhysicalVolume", motherLogicalVolume, false, 0, true);
    this->InitialiseAttributes();
}

void YourBarrelVerticalWall::InitialiseAttributes() {
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Color(1.0, 1.0, 1.0, 1.0));
    visAttributes->SetForceSolid(true);
    this->barrelVerticalWallLogicalVolume->SetVisAttributes(visAttributes);
}


YourBarrelVerticalWall::~YourBarrelVerticalWall() {
    delete this->barrelVerticalWallVolume;
    delete this->barrelVerticalWallLogicalVolume;
    delete this->barrelVerticalWallPhysicalVolume;
}