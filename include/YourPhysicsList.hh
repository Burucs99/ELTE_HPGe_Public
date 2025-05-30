#ifndef PMPHYSICSLISTS_HH
#define PMPHYSICSLISTS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

class YourPhysicsList : public G4VModularPhysicsList
{
public:
    YourPhysicsList();
    ~YourPhysicsList();
};

#endif