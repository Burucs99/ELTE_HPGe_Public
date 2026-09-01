#include "YourTrackingAction.hh"
#include "YourTrackInfo.hh"
#include "G4TrackVector.hh"
#include "G4Track.hh"
YourTrackingAction::YourTrackingAction(YourEventAction* actEvt)
:G4UserTrackingAction(),fEvtAct(actEvt){}
YourTrackingAction::~YourTrackingAction(){}


void YourTrackingAction::PreUserTrackingAction(const G4Track* track){


    /* if(!(track->GetUserInformation())){

        track->SetUserInformation(new YourTrackInfo());
    }
 */
}

void YourTrackingAction::PostUserTrackingAction(const G4Track* track){

    /* if(!track) return;
     */
    
}


