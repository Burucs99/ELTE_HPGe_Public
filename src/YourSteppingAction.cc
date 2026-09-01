#include "YourSteppingAction.hh"
#include "YourDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "YourEventAction.hh"
#include "EventData.hh"
#include "YourTrackInfo.hh"
#include "YourTrackingAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Run.hh"
YourSteppingAction::YourSteppingAction(YourEventAction* actEvt)
: G4UserSteppingAction(),fEvtAct(actEvt){}

YourSteppingAction::~YourSteppingAction() {};


void YourSteppingAction::UserSteppingAction(const G4Step* theStep){

    /* StepData myData;
    const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent();
    G4int eventID = event->GetEventID();
    const G4Run* run = G4RunManager::GetRunManager()->GetCurrentRun();
    G4int runID = run->GetRunID();
    G4Track* track = theStep->GetTrack();
    G4int trackID = track->GetTrackID();
    G4String Volume = track->GetVolume()->GetName(); 
    G4int StepNumber = track->GetCurrentStepNumber();
    myData.RunID = runID;
    myData.TrackID = trackID;
    myData.EventID = eventID;
    myData.StepID = StepNumber;
    myData.energyDeposited = theStep->GetTotalEnergyDeposit();
    G4ThreeVector pos = theStep->GetPreStepPoint()->GetPosition();
    myData.position = pos;
    
    if(G4StrUtil::contains(Volume, "ActiveCrystal") && theStep->GetTotalEnergyDeposit()!=0 ){
        
        G4int id = 0;
        fEvtAct->PushBackTrack(trackID,id);
            
        
        
    }
    
    fEvtAct->PushBackEvent(myData);
 */

}
