
#include "YourEventAction.hh"
#include <G4String.hh>
#include "G4AnalysisManager.hh"

YourEventAction::YourEventAction()
: G4UserEventAction(),feventData(nullptr){


    feventData = new EventData();
}


YourEventAction::~YourEventAction(){};


void YourEventAction::BeginOfEventAction(const G4Event* anEvent){
    
}
void YourEventAction::EndOfEventAction(const G4Event* anEvent){
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    for (const auto& td : fdetectedTracks) {
        G4int trackID = td.first;
        G4int detID   = td.second;
    
        
        for (const auto& step : feventData->steps){
            if(step.TrackID == trackID){
                analysisManager->FillNtupleIColumn(0, 0,step.RunID);
                analysisManager->FillNtupleIColumn(0, 1,step.EventID);
                analysisManager->FillNtupleIColumn(0, 2,trackID);
                analysisManager->FillNtupleIColumn(0, 3,step.StepID);
                analysisManager->FillNtupleIColumn(0, 4,detID);
                analysisManager->FillNtupleDColumn(0, 5,step.energyDeposited);
                analysisManager->FillNtupleDColumn(0, 6,step.position.x());
                analysisManager->FillNtupleDColumn(0, 7,step.position.y());
                analysisManager->FillNtupleDColumn(0, 8,step.position.z());
                analysisManager->AddNtupleRow(0);
               
            }
        
    }
    }
    

    feventData->steps.clear();
    fdetectedTracks.clear();
}