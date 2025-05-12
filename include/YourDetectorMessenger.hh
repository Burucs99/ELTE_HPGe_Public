#ifndef YOURDETECTORMESSENGER_HH
#define YOURDETECTORMESSENGER_HH

#include "G4UImessenger.hh"
#include <G4TrackingMessenger.hh>
#include <G4Types.hh>
#include <G4UIcommand.hh>
#include <G4UImanager.hh>

class YourDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4String;
class G4UIcommandTree;

class YourDetectorMessenger : public G4UImessenger {

public:
YourDetectorMessenger(YourDetectorConstruction* det);
~YourDetectorMessenger();

 void SetNewValue(G4UIcommand*, G4String) override;


private:
    YourDetectorConstruction* fYourDetector;
    G4UIdirectory*            fDirCMD;      
    G4UIcommand*  fIsotopeCMD;
    G4UIcommand*  fElementCMD;
    G4UIcommand*  fMaterialCMD;
    G4UIcommand*  fBoxCmd;
    G4UIcommand*  fTubCmd
    ;

};

#endif