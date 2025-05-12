#include "YourEventAction.hh"
#include "G4Event.hh"
#include "G4Types.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "YourRun.hh"
#include "G4SDManager.hh"
#include "G4AnalysisManager.hh"
YourEventAction::YourEventAction()
: G4UserEventAction(){}

YourEventAction::~YourEventAction() {}


void YourEventAction::BeginOfEventAction(const G4Event* /* anEvent */) {
}


void YourEventAction::EndOfEventAction(const G4Event* event) {
    YourRun* run = static_cast<YourRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
}

