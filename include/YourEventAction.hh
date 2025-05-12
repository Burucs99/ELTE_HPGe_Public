#ifndef YOUREVENTACTION_HH
#define YOUREVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Types.hh"



class YourEventAction : public G4UserEventAction {
public:
    YourEventAction();
    ~YourEventAction() override;
 
    void BeginOfEventAction(const G4Event* anEvent) override;
    void EndOfEventAction(const G4Event* anEvent) override;

   
private:

};

#endif
