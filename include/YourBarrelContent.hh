#ifndef YOURBARRELCONTENT_HH
#define YOURBARRELCONTENT_HH

#include <G4LogicalVolume.hh>
#include <G4RotationMatrix.hh>
#include <G4Tubs.hh>
#include <G4Material.hh>
#include <G4PVPlacement.hh>
#include <G4VisAttributes.hh>
#include <G4SystemOfUnits.hh>

class YourBarrelContent{

    public:
        YourBarrelContent();
        ~YourBarrelContent();

        void Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial);
        G4LogicalVolume* GetLogicalVolume() const { return this->barrelContentLogicalVolume; }

    private:

        void InitialiseAttributes();

        G4double pRmin, pRmax, pDz;
        G4Tubs* barrelContentVolume;
        G4LogicalVolume* barrelContentLogicalVolume;
        G4VPhysicalVolume* barrelContentPhysicalVolume;
        G4RotationMatrix* rotationMatrix;

};


#endif