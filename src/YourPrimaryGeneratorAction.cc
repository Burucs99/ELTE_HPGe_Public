#include "YourPrimaryGeneratorAction.hh"
#include "YourDetectorConstruction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4GeneralParticleSource.hh"
#include "Randomize.hh"
#include "YourDetectorMessenger.hh"

YourPrimaryGeneratorAction::YourPrimaryGeneratorAction(YourDetectorConstruction* det)
: G4VUserPrimaryGeneratorAction(),
  fDetector(det),
  fGps(nullptr),fDetMessenger(nullptr) {
    fGps = new G4GeneralParticleSource();
    fDetMessenger = new YourDetectorMessenger(fDetector);
    SetDefault();
  }

YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction(){

    delete fGps;
}
// A PrimaryGeneratorAction-ben
void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Véletlen pozíció a gyűrűben
    /*  */
    fGps->GeneratePrimaryVertex(anEvent);
}
void YourPrimaryGeneratorAction::SetDefault(){

    
}

void YourPrimaryGeneratorAction::UpdateGunPosition(){

}
