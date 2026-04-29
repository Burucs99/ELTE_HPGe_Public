#include "YourScintillatorCrystal.hh"
#include <string>

YourScintillatorCrystal::YourScintillatorCrystal(){
    this->pRmin = 0.0 * mm;
    this->pRmax = 25.0 * mm;
    this->pDz = 25.0 * mm; // csökkentett méretű RadNdI kristály
    this->rotationMatrix = new G4RotationMatrix();
    this->rotationMatrix->rotateX(90.0 * deg);
}

void YourScintillatorCrystal::Build(G4LogicalVolume* motherVolume, G4Material* material, G4ThreeVector translate, G4int id){
    this->scintillatorCrystalVolume = new G4Tubs("ScintillatorCrystal" + std::to_string(id), pRmin, pRmax, pDz, 0.0, 360.0 * deg);
    this->scintillatorCrystalLogicalVolume = new G4LogicalVolume(scintillatorCrystalVolume, material, "ScintillatorCrystalLogical" + std::to_string(id));
    this->scintillatorCrystalPhysicalVolume = new G4PVPlacement(this->rotationMatrix, translate, scintillatorCrystalLogicalVolume, "ScintillatorCrystalPhysical" + std::to_string(id), motherVolume, false, id, true);
    this->InitialiseAttributes();
}

void YourScintillatorCrystal::InitialiseAttributes() {
    // greenish color
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.325, 0.788, 0.341, 1.0)); // Green color with 50% transparency
    visAttributes->SetForceSolid(true);
    scintillatorCrystalLogicalVolume->SetVisAttributes(visAttributes);
}

YourScintillatorCrystal::~YourScintillatorCrystal() {
    delete scintillatorCrystalVolume;
    delete scintillatorCrystalLogicalVolume;
    delete scintillatorCrystalPhysicalVolume;
    delete rotationMatrix;
}