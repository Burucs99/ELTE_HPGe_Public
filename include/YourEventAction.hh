

#pragma once
#include "G4UserEventAction.hh"
#include <G4SystemOfUnits.hh>
#include "YourEventAction.hh"
#include "G4ThreeVector.hh"

#include <G4String.hh>
#include "YourDetectorConstruction.hh"
#include "G4Types.hh"
#include "EventData.hh"
#include <set>
class YourEventAction : public G4UserEventAction{
public:
    YourEventAction();
    ~YourEventAction() override;

    void BeginOfEventAction(const G4Event* anEvent) override;
    void EndOfEventAction(const G4Event* anEvent) override;

    EventData* GetEventData(){return feventData;};
    void PushBackEvent(StepData step){feventData->pushStep(step);};
    void PushBackTrack(G4int trackID, G4int detID) {
            fdetectedTracks.insert({trackID, detID});
        }
private:
    EventData* feventData;
    std::set<std::pair<G4int, G4int>> fdetectedTracks;
   
};


