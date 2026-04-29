#include "YourTopReflectionLayer.hh"
#include <G4ThreeVector.hh>
#include <string>

YourTopReflectionLayer::YourTopReflectionLayer() {
    this->pRmin = 0 * mm;
    this->pRmax = 25.5 * mm;
    this->pDz = 0.25 * mm;
    this->rotationMatrix = new G4RotationMatrix();
    this->rotationMatrix->rotateX(90.0 * deg);
}

void YourTopReflectionLayer::Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial, G4ThreeVector translate, G4int id) {

    this->topReflectionLayerVolume = new G4Tubs("TopReflectionLayerVolume" + std::to_string(id), this->pRmin, this->pRmax, this->pDz, 0.0 * deg, 360.0 * deg);
    this->topReflectionLayerLogicalVolume = new G4LogicalVolume(this->topReflectionLayerVolume, buildMaterial, "TopReflectionLayerLogicalVolume" + std::to_string(id));
    this->topReflectionLayerPhysicalVolume = new G4PVPlacement(this->rotationMatrix, translate, this->topReflectionLayerLogicalVolume, "TopReflectionLayerPhysicalVolume" + std::to_string(id), motherLogicalVolume, false, id, true);

    this->InitialiseAttributes();
}

void YourTopReflectionLayer::InitialiseAttributes() {
    G4VisAttributes* topReflectionLayerVisAttributes = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 1.0));
    topReflectionLayerVisAttributes->SetForceSolid(true);
    this->topReflectionLayerLogicalVolume->SetVisAttributes(topReflectionLayerVisAttributes);
}

YourTopReflectionLayer::~YourTopReflectionLayer() {
    delete this->topReflectionLayerVolume;
    delete this->topReflectionLayerLogicalVolume;
    delete this->topReflectionLayerPhysicalVolume;
}