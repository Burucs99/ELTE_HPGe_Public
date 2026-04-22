#include "YourTrackingAction.hh"
#include "YourTrackInfo.hh"
#include "G4TrackVector.hh"
#include "G4Track.hh"

YourTrackingAction::YourTrackingAction()
:G4UserTrackingAction(){}
YourTrackingAction::~YourTrackingAction(){}


void YourTrackingAction::PreUserTrackingAction(const G4Track* track){


    /* if(!(track->GetUserInformation())){

        track->SetUserInformation(new YourTrackInfo());
    } */

}

void YourTrackingAction::PostUserTrackingAction(const G4Track* track){

    /* if(!track) return;
    G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();

    if(!secondaries) return;
    

    auto* parentInfo = dynamic_cast<YourTrackInfo*>(track->GetUserInformation());
    if (!parentInfo) return;
    G4int parentCompton = parentInfo->GetComptonCount();

    for (auto* sec : *secondaries) {

        auto* info = new YourTrackInfo();
        info->SetComptonCount(parentCompton);
        sec->SetUserInformation(info);
    } */
}


