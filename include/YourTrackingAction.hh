#ifndef YOURTRACKINGACTION
#define YOURTRACKINGACTION

#include "G4UserTrackingAction.hh"
#include "G4TrackingManager.hh"

class YourTrackingAction :public G4UserTrackingAction{
public:
    YourTrackingAction();
    ~YourTrackingAction();
    void PreUserTrackingAction(const G4Track*);
    void PostUserTrackingAction(const G4Track*);





private:



};



#endif