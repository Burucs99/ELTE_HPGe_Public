#ifndef YOURUNRMESSENGER_HH
#define YOURUNRMESSENGER_HH

#include "G4UImessenger.hh"
#include "YourRunAction.hh"
#include <G4Types.hh>
#include <G4UIcommand.hh>
#include <G4UImanager.hh>

class YourRunAction;
class YouRunrConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4String;
class G4UIcommandTree;

class YourRunMessenger : public G4UImessenger {

public:
    YourRunMessenger(YourRunAction* runaction);
    ~YourRunMessenger();

    void SetNewValue(G4UIcommand*, G4String) override;


private:
    YourRunAction* fYourRunAction;
    G4UIdirectory* fDirCMD;      
    G4UIcommand*   fEdepHist;
    G4UIcommand*   fOutPut;

};

#endif