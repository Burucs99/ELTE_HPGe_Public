#ifndef YOURBARRELSIDEWALL_HH
#define YOURBARRELSIDEWALL_HH

#include <G4LogicalVolume.hh>
#include <G4RotationMatrix.hh>
#include <G4Tubs.hh>
#include <G4Material.hh>
#include <G4PVPlacement.hh>
#include <G4VisAttributes.hh>
#include <G4SystemOfUnits.hh>

class YourBarrelSideWall{

    public:
        YourBarrelSideWall();
        ~YourBarrelSideWall();
    
    void Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial);
    G4LogicalVolume* GetLogicalVolume() const { return this->barrelSideWallLogicalVolume; }

    private:

        void InitialiseAttributes();

        G4double pRmin, pRmax, pDz;
        G4Tubs* barrelSideWallVolume;
        G4LogicalVolume* barrelSideWallLogicalVolume;
        G4VPhysicalVolume* barrelSideWallPhysicalVolume;
        G4RotationMatrix* rotationMatrix;
    
};


#endif