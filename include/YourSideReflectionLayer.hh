#ifndef YOURSIDEREFLEXTIONLAYER_HH
#define YOURSIDEREFLEXTIONLAYER_HH

#include <G4LogicalVolume.hh>
#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4Material.hh>
#include <G4PVPlacement.hh>
#include <G4Types.hh>
#include <G4VisAttributes.hh>
#include <G4SystemOfUnits.hh>

class YourSideReflexionLayer {
    public:
        YourSideReflexionLayer();
        ~YourSideReflexionLayer();

        void Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial, G4ThreeVector translate, G4int id);

    private:
        void InitialiseAttributes();

        G4double pRmin, pRmax, pDz;
        G4Tubs* sideReflectionLayerVolume;
        G4LogicalVolume* sideReflectionLayerLogicalVolume;
        G4VPhysicalVolume* sideReflectionLayerPhysicalVolume;

        G4RotationMatrix* rotationMatrix;
};

#endif