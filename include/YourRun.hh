#ifndef YOURRUN_HH
#define YOURRUN_HH

#include "G4Run.hh"

class YourDetectorConstruction;
class YourPrimaryGeneratorAction;

class YourRun : public G4Run {
public:
    YourRun(YourDetectorConstruction* det, YourPrimaryGeneratorAction* prim);
    ~YourRun() override;

    void Merge(const G4Run*);

    void AddEnergyDepositPerEvent(G4double edep){};
private:
    YourDetectorConstruction*    fYourDetector;
    YourPrimaryGeneratorAction*  fYourPrimary;
};

#endif