#ifndef YOURSCINTILLATORCRYSTAL_HH
#define YOURSCINTILLATORCRYSTAL_HH

#include <G4LogicalVolume.hh>
#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4Material.hh>
#include <G4PVPlacement.hh>
#include <G4Types.hh>
#include <G4VisAttributes.hh>
#include <G4SystemOfUnits.hh>

class YourScintillatorCrystal {

    public:

        YourScintillatorCrystal();
        ~YourScintillatorCrystal();

        void Build(G4LogicalVolume* motherVolume, G4Material* material, G4ThreeVector translate, G4int id);
        G4LogicalVolume* GetLogicalVolume() const { return scintillatorCrystalLogicalVolume; }
        G4int GetId() const { return id; }

    private:

        void InitialiseAttributes();

        G4double pRmin, pRmax, pDz;
        G4Tubs* scintillatorCrystalVolume;
        G4LogicalVolume* scintillatorCrystalLogicalVolume;
        G4VPhysicalVolume* scintillatorCrystalPhysicalVolume;
        G4RotationMatrix* rotationMatrix;

        G4int id;

};


#endif