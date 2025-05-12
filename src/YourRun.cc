#include "YourRun.hh"
#include "G4SystemOfUnits.hh"
#include "YourDetectorConstruction.hh"
#include "YourPrimaryGeneratorAction.hh"

YourRun::YourRun(YourDetectorConstruction* det, YourPrimaryGeneratorAction* prim)
:   fYourDetector(det),
    fYourPrimary(prim){
        

}

YourRun::~YourRun(){
}

void YourRun::Merge(const G4Run* run) {
    const YourRun* localrun = static_cast<const YourRun*>(run);
    G4Run::Merge(run);
}