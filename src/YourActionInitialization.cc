#include "YourActionInitialization.hh"
#include "YourPrimaryGeneratorAction.hh"
#include "YourDetectorConstruction.hh"
#include "YourRun.hh"
#include "YourEventAction.hh"
#include "YourRunAction.hh"
#include "YourSteppingAction.hh"
YourActionInitialization::YourActionInitialization(YourDetectorConstruction* det)
: G4VUserActionInitialization(),
  fDetector(det) {

  }
YourActionInitialization::~YourActionInitialization() {}

void YourActionInitialization::BuildForMaster() const {


    YourPrimaryGeneratorAction* primGen = new YourPrimaryGeneratorAction(fDetector);


    
    YourRunAction* actRun = new YourRunAction(primGen,fDetector);

    
    SetUserAction(actRun);
    G4cout<<"BuildForMaster Finished"<<G4endl;

}   

void YourActionInitialization::Build() const {

    
    
    YourPrimaryGeneratorAction* primGen = new YourPrimaryGeneratorAction(fDetector);

    SetUserAction(primGen);

    

    YourRunAction* actRun = new YourRunAction(primGen,fDetector);

    SetUserAction(actRun);

    YourEventAction* actEvt = new YourEventAction();

    SetUserAction(actEvt);

    

    YourSteppingAction* actStep = new YourSteppingAction(fDetector,actEvt);

    SetUserAction(actStep);

   
}
