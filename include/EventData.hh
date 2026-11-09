#pragma once
#include <vector>
#include "G4ThreeVector.hh"
struct StepData { 
    G4int RunID;
    G4int EventID;
    G4int TrackID;
    G4int StepID;
    G4int detectorID = -1;
    G4double energyDeposited;
    G4ThreeVector position;

};

class EventData{
public:
    EventData(){} ;
    std::vector<StepData> steps;
    void pushStep(StepData step){
        steps.push_back(step);
    }

};