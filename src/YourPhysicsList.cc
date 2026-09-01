#include "YourPhysicsList.hh"

#include "G4EmStandardPhysics_option4.hh"
#include "G4ProductionCutsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmParameters.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
YourPhysicsList::YourPhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics_option4());

    // Ha kell:
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    /* G4EmParameters::Instance()->SetFluo(false);
    G4EmParameters::Instance()->SetAuger(false); */
}

YourPhysicsList::~YourPhysicsList(){}


void YourPhysicsList::SetCuts()
{
    /* SetCutsWithDefault();

    G4ProductionCutsTable::GetProductionCutsTable()
        ->SetEnergyRange(1*keV,10*MeV);

    SetCutValue(0.1*mm,"gamma");
    SetCutValue(0.1*mm,"e-");
    SetCutValue(0.1*mm,"e+");

    G4cout
        << "Cuts applied:"
        << "\n gamma: " << GetCutValue("gamma")/mm << " mm"
        << "\n e-: " << GetCutValue("e-")/mm << " mm"
        << "\n e+: " << GetCutValue("e+")/mm << " mm"
        << G4endl; */
}