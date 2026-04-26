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
:G4VSensitiveDetector(name),fHitsCollection(nullptr),fHCID(-1)
{
    collectionName.insert("MyHitsCollection");
    fEdep = 0.0;

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
    analysisManager->SetNtupleMerging(true);
    
    if(fEdep!=0){
        analysisManager->FillH1(0, fEdep);
    }
    fEdep = 0.0;
}


G4bool YourSensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory* )
{   

    



    G4double EnergyDeposit = aStep->GetTotalEnergyDeposit();
    fEdep+=EnergyDeposit;
    

    return true;
}