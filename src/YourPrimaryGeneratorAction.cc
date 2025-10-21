#include "YourPrimaryGeneratorAction.hh"
#include "YourDetectorConstruction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4GeneralParticleSource.hh"
#include "Randomize.hh"

YourPrimaryGeneratorAction::YourPrimaryGeneratorAction(YourDetectorConstruction* det)
: G4VUserPrimaryGeneratorAction(),
  fDetector(det),
  fGps(nullptr) {
    fGps = new G4GeneralParticleSource();
    SetDefault();
  }

YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction(){

    delete fGps;
}
// A PrimaryGeneratorAction-ben
void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Véletlen pozíció a gyűrűben
    G4double inner_r = 15.0 * mm;
    G4double outer_r = 16.5 * mm;
    G4double halfz = 1.0 * mm;
    G4double center_z = -150.0 * mm;
    
    G4double r, phi, x, y, z;
    
    // Addig generálj, amíg a pont a gyűrűben van
    do {
        r = G4RandFlat::shoot(inner_r, outer_r);
        phi = G4RandFlat::shoot(0.0, 2.0 * CLHEP::pi);
        x = r * std::cos(phi);
        y = r * std::sin(phi);
        z = G4RandFlat::shoot(center_z - halfz, center_z + halfz);
    } while (r < inner_r); // Ez biztosítja, hogy a gyűrűben legyen
    
    fGps->GetCurrentSource()->GetPosDist()->SetPosDisType("Point");
    fGps->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(x, y, z));
    
    fGps->GeneratePrimaryVertex(anEvent);
}
void YourPrimaryGeneratorAction::SetDefault(){

    
}

void YourPrimaryGeneratorAction::UpdateGunPosition(){

}
