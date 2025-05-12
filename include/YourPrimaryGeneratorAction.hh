#ifndef YOURPRIMARYGENERATORACTION_HH
#define YOURPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include <G4GeneralParticleSource.hh>
#include "G4GeneralParticleSource.hh"
class YourDetectorConstruction;
class G4GeneralParticleSource;
class YourPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    YourPrimaryGeneratorAction(YourDetectorConstruction* det);
    ~YourPrimaryGeneratorAction() override;
    
    void GeneratePrimaries(G4Event* anEvent) override;
    void SetDefault();
    void UpdateGunPosition();
private:
    YourDetectorConstruction* fDetector;
    G4GeneralParticleSource* fGps;
    
};


#endif // YOURPRIMARYGENERATORACTION.HH