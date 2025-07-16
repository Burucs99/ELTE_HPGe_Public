#ifndef YOURSENSITIVEDETECTOR__HH
#define YOURSENSITIVEDETECTOR__HH

#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "YourHitCollection.hh"
#include <G4HCofThisEvent.hh>
#include <G4Step.hh>
#include <G4String.hh>
#include <G4TouchableHistory.hh>
#include <G4Types.hh>

class YourHitCollection;

class YourSensitiveDetector : public G4VSensitiveDetector{
public:
    YourSensitiveDetector(G4String);
    ~YourSensitiveDetector();

private:
    
    YourHitCollection* fHitsCollection;
    G4int fHCID; 
    G4double fTotalEnergy;
    virtual void Initialize(G4HCofThisEvent *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;
    virtual G4bool ProcessHits(G4Step*, G4TouchableHistory *) override;
};


#endif