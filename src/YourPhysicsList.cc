#include <G4EmStandardPhysics.hh>
#include "YourPhysicsList.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
YourPhysicsList::YourPhysicsList(){

    
    RegisterPhysics(new G4EmPenelopePhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    RegisterPhysics(new G4DecayPhysics());

   
}

YourPhysicsList::~YourPhysicsList(){}
