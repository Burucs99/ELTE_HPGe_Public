#ifndef PMPHYSICSLISTS_HH
#define PMPHYSICSLISTS_HH

#include "G4VModularPhysicsList.hh"


class YourPhysicsList : public G4VModularPhysicsList
{
public:
    YourPhysicsList();
    virtual ~YourPhysicsList();

    virtual void SetCuts() override;
};
#endif