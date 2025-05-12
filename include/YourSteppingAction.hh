#ifndef YOURSTEPPINGACTION_HH
#define YOURSTEPPINGACTION_HH

 
#include "G4UserSteppingAction.hh"


class YourEventAction ;
class YourDetectorConstruction;

class YourSteppingAction : public G4UserSteppingAction {
public:
    YourSteppingAction(YourDetectorConstruction* det, YourEventAction* actEvt);
    ~YourSteppingAction() override;

    void UserSteppingAction(const G4Step*) override;
private:
    YourDetectorConstruction* fDetector;
    YourEventAction* fEventAction;
};

#endif
