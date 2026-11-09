#include "YourSteppingAction.hh"
#include "YourDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "YourEventAction.hh"
#include "G4ParticleDefinition.hh"
YourSteppingAction::YourSteppingAction(YourDetectorConstruction* det,YourEventAction* actEvt)
: G4UserSteppingAction(),
  fDetector(det),
  fEventAction(actEvt){


    
   
  }

YourSteppingAction::~YourSteppingAction() {};


void YourSteppingAction::UserSteppingAction(const G4Step* theStep){
/*    
    G4Track* track = theStep->GetTrack();
    const G4ParticleDefinition*def = track->GetParticleDefinition();
	if(!def) return;
	auto Name = def->GetParticleName();
	if(Name!="gamma") return;
	G4StepPoint* prePoint  = theStep->GetPreStepPoint();
    G4StepPoint* postPoint = theStep->GetPostStepPoint();

    G4VPhysicalVolume* prePV  = prePoint->GetPhysicalVolume();
    G4VPhysicalVolume* postPV = postPoint->GetPhysicalVolume();
    if (!prePV || !postPV) return;

    G4String volName = prePV->GetName();
    
    G4String volNamePost = postPV->GetName();
    if (prePV->GetName() == "Calorimeter"){
	G4double edep = theStep->GetTotalEnergyDeposit();
	const G4VProcess* process = postPoint->GetProcessDefinedStep();
	G4bool isInt = (process&&process->GetProcessName()!="Transportation");
	if(edep>0.0 || isInt){
		G4double steplength = postPoint->GetPosition().mag();
		G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
		analysisManager->FillH1(0, steplength/mm);	
		track->SetTrackStatus(fStopAndKill);
		}
}
*/
}   
