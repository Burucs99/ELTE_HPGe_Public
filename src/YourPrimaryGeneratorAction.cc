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
void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
 
    fGps->GeneratePrimaryVertex(anEvent);

} 

void YourPrimaryGeneratorAction::SetDefault(){

    
}

void YourPrimaryGeneratorAction::UpdateGunPosition(){

}
