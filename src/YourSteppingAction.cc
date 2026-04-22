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
#include "G4AnalysisManager.hh"

YourSteppingAction::YourSteppingAction(YourDetectorConstruction* det,YourEventAction* actEvt)
: G4UserSteppingAction(),
  fDetector(det),
  fEventAction(actEvt){}

YourSteppingAction::~YourSteppingAction() {};


void YourSteppingAction::UserSteppingAction(const G4Step* step) {

    //G4Track* track = step->GetTrack();

    /* const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();

    G4String processName = process->GetProcessName();
    G4VPhysicalVolume* prePV = step->GetPreStepPoint()->GetPhysicalVolume();

    G4String volName = prePV->GetName();
    YourTrackInfo* info = dynamic_cast<YourTrackInfo*>(track->GetUserInformation()); */
    /* G4ParticleDefinition* particle = track->GetDefinition();

    if (particle == G4Alpha::Definition()) {
        track->SetTrackStatus(fStopAndKill);
        return;
    } */

    /* if (track->GetDefinition()->GetParticleName() != "gamma") return;
    /* if (!info) {
        info = new YourTrackInfo();
        track->SetUserInformation(info);
    }
    
    G4StepPoint* prePoint = step->GetPreStepPoint();
    G4StepPoint* postPoint = step->GetPostStepPoint();
    
    G4VPhysicalVolume* preVol = prePoint->GetPhysicalVolume();
    G4VPhysicalVolume* postVol = postPoint->GetPhysicalVolume();
    
    G4String preVolName = "";
    G4String postVolName = "";
    
    if (preVol) preVolName = preVol->GetName();
    if (postVol) postVolName = postVol->GetName();
    if (!G4StrUtil::contains(preVolName, "Aluminum_Phys") && 
        G4StrUtil::contains(postVolName, "Aluminum_Phys")) 
    {
        
    }
    
    if (G4StrUtil::contains(preVolName, "Aluminum_Phys") && 
        !G4StrUtil::contains(postVolName, "Aluminum_Phys")) 
    {
        
        
        G4double trackLength = track->GetTrackLength();
         G4cout << "  A dobozban megtett út: " << trackLength / mm << " mm" << G4endl;
        G4cout << "====================================" << G4endl; 
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(1,trackLength,1);
    }    
   */
    
}


