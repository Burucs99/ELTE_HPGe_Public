#include "YourSteppingAction.hh"
#include "YourDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "YourEventAction.hh"
YourSteppingAction::YourSteppingAction(YourDetectorConstruction* det,YourEventAction* actEvt)
: G4UserSteppingAction(),
  fDetector(det),
  fEventAction(actEvt){}

YourSteppingAction::~YourSteppingAction() {};


void YourSteppingAction::UserSteppingAction(const G4Step* theStep){

}
