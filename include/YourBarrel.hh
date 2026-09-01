#ifndef YOURBARREL_HH
#define YOURBARREL_HH

#include "YourBarrelContent.hh"
#include "YourBarrelSideWall.hh"
#include "YourBarrelVerticalWall.hh"
#include <G4LogicalVolume.hh>


class YourBarrel{

    public:
        YourBarrel();
        ~YourBarrel();

        void Build(G4LogicalVolume* contentMotherLogicalVolume, G4Material* contentBuildMaterial,
                       G4LogicalVolume* sideWallMotherLogicalVolume, G4Material* sideWallBuildMaterial,
                       G4LogicalVolume* topWallMotherLogicalVolume, G4Material* topWallBuildMaterial,
                       G4LogicalVolume* bottomWallMotherLogicalVolume, G4Material* bottomWallBuildMaterial);

        G4LogicalVolume* GetBarrelContentLogicalVolume() { return this->barrelContent->GetLogicalVolume(); }
        G4LogicalVolume* GetBarrelSideWallLogicalVolume() { return this->barrelSideWall->GetLogicalVolume(); }
        G4LogicalVolume* GetBarrelTopWallLogicalVolume() { return this->barrelTopWall->GetLogicalVolume(); }
        G4LogicalVolume* GetBarrelBottomWallLogicalVolume() { return this->barrelBottomWall->GetLogicalVolume(); }

    private:
        YourBarrelContent* barrelContent;
        YourBarrelSideWall* barrelSideWall;
        YourBarrelVerticalWall *barrelTopWall, *barrelBottomWall;
        G4ThreeVector topWallTranslation, bottomWallTranslation; // These translations are used to position the top and bottom walls correctly in the barrel structure.

};



#endif 