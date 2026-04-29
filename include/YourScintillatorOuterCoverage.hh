#ifndef YOURSCINTILLATOROUTERCOVERAGE_HH
#define YOURSCINTILLATOROUTERCOVERAGE_HH

#include <G4LogicalVolume.hh>
#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4Material.hh>
#include <G4PVPlacement.hh>
#include <G4Types.hh>
#include <G4VisAttributes.hh>
#include <G4SystemOfUnits.hh>

class YourScintillatorOuterCoverage{

    public:
        YourScintillatorOuterCoverage();
        ~YourScintillatorOuterCoverage();

        void Build(G4LogicalVolume* motherVolume, G4Material* material, G4ThreeVector translate, G4int id);

    private:

        void InitialiseAttributes();

        G4double pRmin, pRmax, pDz;
        G4Tubs* ScintillatorOuterCoverageVolume;
        G4LogicalVolume* ScintillatorOuterCoverageLogicalVolume;
        G4VPhysicalVolume* ScintillatorOuterCoveragePhysicalVolume;
        
        G4RotationMatrix* rotationMatrix;

};


#endif