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
  fGun(nullptr) {
    fGun = new G4ParticleGun();
    SetDefault();
  }

YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction(){

    delete fGun;
}
void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
 
    
    G4double R1 = 78.0 / 4 * mm;
    G4double R2 = 73.0 / 4 * mm;
    G4double h = 45.0 * mm;

    G4double z = G4UniformRand() * h;

    G4double rmin = R1 + (R2 - R1) * (z / h);
    G4double r = rmin * std::sqrt(G4UniformRand());
    G4double phi = 2 * CLHEP::pi * G4UniformRand();

    G4double x = r * std::cos(phi);
    G4double y = r * std::sin(phi);
    G4double z_pos = z - h/2.0 - 0.9 * mm;  

    G4ThreeVector position(x, y, z_pos);
    G4IonTable* ionTable = G4IonTable::GetIonTable();
    G4ParticleDefinition* ion_def = ionTable->GetIon(19,40,0); 
    fGun->SetParticlePosition(position);
    fGun->SetParticleEnergy(0.0*MeV);  
    fGun->SetParticleDefinition(ion_def);  
    fGun->GeneratePrimaryVertex(anEvent);
} 

void YourPrimaryGeneratorAction::SetDefault(){

    
}

void YourPrimaryGeneratorAction::UpdateGunPosition(){

}
