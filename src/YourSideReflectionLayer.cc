#include "YourSideReflectionLayer.hh"
#include <G4ThreeVector.hh>
#include <string>


YourSideReflexionLayer::YourSideReflexionLayer() {
    this->pRmin = 25.0 * mm;
    this->pRmax = 25.5 * mm;
    this->pDz = 25 * mm;

    this->rotationMatrix = new G4RotationMatrix();
    this->rotationMatrix->rotateX(90.0 * deg);
}

void YourSideReflexionLayer::Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial, G4ThreeVector translate, G4int id){
    this->sideReflectionLayerVolume = new G4Tubs("SideReflectionLayerVolume" + std::to_string(id), this->pRmin, this->pRmax, this->pDz, 0.0 * deg, 360.0 * deg);
    this->sideReflectionLayerLogicalVolume = new G4LogicalVolume(this->sideReflectionLayerVolume, buildMaterial, "SideReflectionLayerLogicalVolume" + std::to_string(id));
    this->sideReflectionLayerPhysicalVolume = new G4PVPlacement(this->rotationMatrix, translate, this->sideReflectionLayerLogicalVolume, "SideReflectionLayerPhysicalVolume" + std::to_string(id), motherLogicalVolume, false, 0, true);
    this->InitialiseAttributes();
}

void YourSideReflexionLayer::InitialiseAttributes() {
    G4VisAttributes* sideReflectionLayerVisAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 1.0));
    sideReflectionLayerVisAttributes->SetForceSolid(true);
    this->sideReflectionLayerLogicalVolume->SetVisAttributes(sideReflectionLayerVisAttributes);
}

YourSideReflexionLayer::~YourSideReflexionLayer() {
    delete this->sideReflectionLayerVolume;
    delete this->sideReflectionLayerLogicalVolume;
    delete this->sideReflectionLayerPhysicalVolume;
}