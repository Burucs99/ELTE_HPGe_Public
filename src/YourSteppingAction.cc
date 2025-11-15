#include "YourSteppingAction.hh"
#include "YourDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "YourEventAction.hh"
#include "YourTrackInfo.hh"
#include "G4VProcess.hh"  
#include "G4String.hh"
#include "G4Alpha.hh"
#include "G4Electron.hh"
#include "G4RunManager.hh"
#
YourSteppingAction::YourSteppingAction(YourDetectorConstruction* det,YourEventAction* actEvt)
: G4UserSteppingAction(),
  fDetector(det),
  fEventAction(actEvt){}

YourSteppingAction::~YourSteppingAction() {};


void YourSteppingAction::UserSteppingAction(const G4Step* step) {

    G4Track* track = step->GetTrack();

    const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();

    G4String processName = process->GetProcessName();
    G4VPhysicalVolume* prePV = step->GetPreStepPoint()->GetPhysicalVolume();

    G4String volName = prePV->GetName();
    YourTrackInfo* info = dynamic_cast<YourTrackInfo*>(track->GetUserInformation());
    G4ParticleDefinition* particle = track->GetDefinition();

    if (particle == G4Alpha::Definition()) {
        track->SetTrackStatus(fStopAndKill);
        return;
    }
   
    if (!info) {
        info = new YourTrackInfo();
        track->SetUserInformation(info);
    }

    if (G4StrUtil::contains(volName, "Aluminum_Phys") && processName == "compt") {
    info->AddComptonScattering();

}
}


