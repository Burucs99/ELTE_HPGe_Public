#ifndef YOURTOPREFLECTIONLAYER_HH
#define YOURTOPREFLECTIONLAYER_HH

#include <G4LogicalVolume.hh>
#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4Material.hh>
#include <G4PVPlacement.hh>
#include <G4Types.hh>
#include <G4VisAttributes.hh>
#include <G4SystemOfUnits.hh>

class YourTopReflectionLayer {
    public:
        YourTopReflectionLayer();
        ~YourTopReflectionLayer();

        void Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial, G4ThreeVector translate, G4int id);

    private:
        void InitialiseAttributes();

        G4double pRmin, pRmax, pDz;
        G4Tubs* topReflectionLayerVolume;
        G4LogicalVolume* topReflectionLayerLogicalVolume;
        G4VPhysicalVolume* topReflectionLayerPhysicalVolume;

        G4RotationMatrix* rotationMatrix;
};


#endif