#include <G4EmStandardPhysics.hh>
#include "YourPhysicsList.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
YourPhysicsList::YourPhysicsList(){

    
    RegisterPhysics(new G4EmStandardPhysics_option4());

    RegisterPhysics(new G4RadioactiveDecayPhysics());

    RegisterPhysics(new G4DecayPhysics());

   
}

YourPhysicsList::~YourPhysicsList(){}
