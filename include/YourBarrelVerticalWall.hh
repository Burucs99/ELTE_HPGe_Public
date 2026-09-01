#ifndef YOYURBARRELTOPWALL_HH
#define YOYURBARRELTOPWALL_HH

#include <G4LogicalVolume.hh>
#include <G4RotationMatrix.hh>
#include <G4Tubs.hh>
#include <G4Material.hh>
#include <G4PVPlacement.hh>
#include <G4VisAttributes.hh>
#include <G4SystemOfUnits.hh>


class YourBarrelVerticalWall{

    public:
        YourBarrelVerticalWall();
        ~YourBarrelVerticalWall();

        void Build(G4LogicalVolume* motherLogicalVolume, G4Material* buildMaterial, G4ThreeVector translation = G4ThreeVector(0.0, 0.0, 0.0));
        G4LogicalVolume* GetLogicalVolume() const { return this->barrelVerticalWallLogicalVolume; }

    private:

        void InitialiseAttributes();

        G4double pRmin, pRmax, pDz;
        G4Tubs* barrelVerticalWallVolume;
        G4LogicalVolume* barrelVerticalWallLogicalVolume;
        G4VPhysicalVolume* barrelVerticalWallPhysicalVolume;
        G4RotationMatrix* rotationMatrix;

};


#endif