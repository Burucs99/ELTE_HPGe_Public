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
#include "G4EventManager.hh"
#include "YourEventAction.hh"
#include "YourTrackInfo.hh"
#include <map>
#include "G4Cache.hh"


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
void YourSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    /* const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent();
    G4int eventID = event->GetEventID();
    const G4Run* run = G4RunManager::GetRunManager()->GetCurrentRun();
    G4int runID = run->GetRunID();

    
    G4int numberOfHits = fHitsCollection->GetSize();
    
    
    for (G4int i = 0; i < numberOfHits; ++i) {
        YourHit* hit = fHitsCollection->GetHit(i);        
        if (!hit) continue;
        
        G4double energy = hit->GetEnergy();
        if(energy > 0.0) {
            analysisManager->FillNtupleDColumn(0, 0, energy);
            analysisManager->FillNtupleIColumn(0, 1, hit->GetCoulombID());
            analysisManager->FillNtupleIColumn(0, 2, hit->GetRunID());
            analysisManager->FillNtupleIColumn(0, 3, hit->GetEventID());
            analysisManager->AddNtupleRow(0);
        }
        
    } */

    
    if(fTotalEnergy>0.0) analysisManager->FillH1(0,fTotalEnergy,1);
   

    fTotalEnergy = 0.;
}







G4bool YourSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4double edep = step->GetTotalEnergyDeposit();
    
    /* G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID();
    G4int uniqueEventID = runID * 1000000 + eventID;
    G4Track* track = step->GetTrack(); */
    fTotalEnergy += edep;
    /* YourTrackInfo* info = dynamic_cast<YourTrackInfo*>(track->GetUserInformation());
    G4int comptonIDX = (info) ? info->GetComptonCount() : 0;

    YourHit* hit = new YourHit();
    hit->SetEnergy(edep);
    hit->SetEventID(uniqueEventID);
    hit->SetRunID(runID);
    hit->SetTrackID(track->GetTrackID());
    hit->SetComptonID(comptonIDX);
    fHitsCollection->insert(hit); */

    return true;
}
