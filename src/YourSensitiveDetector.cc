#include "YourSensitiveDetector.hh"
#include <CLHEP/Units/PhysicalConstants.h>
#include <CLHEP/Vector/LorentzVector.h>
#include <G4AnalysisManagerState.hh>
#include <G4AnalysisUtilities.hh>
#include <G4HCofThisEvent.hh>
#include <G4Run.hh>
#include <G4SDManager.hh>
#include <G4StepPoint.hh>
#include <G4TouchableHistory.hh>
#include <G4Types.hh>
#include <G4VSensitiveDetector.hh>
#include <G4ios.hh>
#include "YourHit.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "YourHitCollection.hh"



YourSensitiveDetector::YourSensitiveDetector(G4String name) 
:G4VSensitiveDetector(name),fHitsCollection(nullptr),fHCID(-1),fTotalEnergy(-1)
{
    collectionName.insert("MyHitsCollection");

}
YourSensitiveDetector::~YourSensitiveDetector(){
    

}

void YourSensitiveDetector::Initialize(G4HCofThisEvent * hce) 
{

    fHitsCollection = new YourHitCollection(SensitiveDetectorName,collectionName[0]);
    

    if(fHCID<0){
        fHCID=G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

    }
    hce->AddHitsCollection(fHCID,fHitsCollection);
}

void YourSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    /* analysisManager->SetNtupleMerging(true);
    const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent();
    G4int eventID = event->GetEventID();
    const G4Run* run = G4RunManager::GetRunManager()->GetCurrentRun();
    G4int runID = run->GetRunID();
    G4double fTotalEnergy = 0;
    
    G4int numberOfHits = fHitsCollection->GetSize();
    
    std::vector<G4ThreeVector> positions;
    std::vector<G4double> energies;
    positions.reserve(numberOfHits);
    energies.reserve(numberOfHits); */
    /* for(size_t i = 0; i < numberOfHits; i++) {
        YourHit* hit = fHitsCollection->GetHit(i);
        hit->SetEventID(eventID);
        hit->SetRunID(runID);
        fTotalEnergy += hit->GetEnergy();
        positions.push_back(hit->GetPosition());
        energies.push_back(hit->GetEnergy());
    } */
    if(fTotalEnergy!=0){
        analysisManager->FillH1(0, fTotalEnergy);
    }
    
    /* for(size_t i = 0; i < positions.size(); i++) {
        analysisManager->FillNtupleDColumn(0, 0, positions[i].x());
        analysisManager->FillNtupleDColumn(0, 1, positions[i].y());
        analysisManager->FillNtupleDColumn(0, 2, positions[i].z());
        analysisManager->FillNtupleDColumn(0, 3, energies[i]);
        analysisManager->FillNtupleIColumn(0, 4, eventID);
        analysisManager->FillNtupleIColumn(0, 5, runID);
        analysisManager->AddNtupleRow(0);  
    } */
    fTotalEnergy = 0;
}


G4bool YourSensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory* )
{   

    

    //G4StepPoint* preStepPoint = aStep->GetPreStepPoint();

    
    //const G4ThreeVector globalPos = aStep->GetPreStepPoint()->GetPosition();
    //const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
   // G4ThreeVector localPos = touchable->GetHistory()->GetTopTransform().TransformPoint(globalPos);

    fTotalEnergy+= aStep->GetTotalEnergyDeposit();
    
    //YourHit* newHit = new YourHit();
    //newHit->SetEnergy(EnergyDeposit);
    //newHit->SetPosition(localPos);
    //fHitsCollection->insert(newHit);

    return true;
}
