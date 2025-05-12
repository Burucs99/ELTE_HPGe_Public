
#include "YourRunAction.hh"
#include "YourPrimaryGeneratorAction.hh"
#include "YourRun.hh"
#include "YourDetectorConstruction.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include <filesystem> 
YourRunAction::YourRunAction(YourPrimaryGeneratorAction* primGen,YourDetectorConstruction* det)
: G4UserRunAction(),
 fDetector(det),
 fPrimGen(primGen),
  fYourRun(nullptr){
  
  timer = new G4Timer();
  fRunMessenger = new YourRunMessenger(this);
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  
  analysisManager->CreateNtuple("Positions","Positions");
  analysisManager->CreateNtupleDColumn("X"); 
  analysisManager->CreateNtupleDColumn("Y");
  analysisManager->CreateNtupleDColumn("Z");
  analysisManager->CreateNtupleDColumn("Energy");
  analysisManager->CreateNtupleIColumn("EventID");
  analysisManager->CreateNtupleIColumn("RunID");

  analysisManager->FinishNtuple(0); 
}

YourRunAction::~YourRunAction() { delete timer; }


G4Run* YourRunAction::GenerateRun() {
    fYourRun = new YourRun(fDetector, fPrimGen);
    return fYourRun;
}




void YourRunAction::BeginOfRunAction(const G4Run* run) {
    timer->Start();
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    for (const auto& [name, config] : fHistConfigs) {
        if (analysisManager->GetH1Id(name) == -1) {  
            G4cout << "Creating Histogram '" << name << "' with "
                   << config.edepBins << " bins from " 
                   << config.edepMin << " to " << config.edepMax << " MeV" << G4endl;
            
            analysisManager->CreateH1(
                name,
                config.Title,
                config.edepBins,
                config.edepMin,
                config.edepMax*MeV
            );
        } else {
        }
    }
    
    G4int runID = run->GetRunID();
    G4int eventNum =run->GetNumberOfEvent();
    std::stringstream strRunID,streventNumber;
    strRunID << runID;
    streventNumber<<eventNum;
    
    if(fOutPutDir.empty()){
        fOutPutDir="OutPutDirectory";
        /* G4cout<<"No outputDirectory Defined"<<G4endl; */
    }
    if(fFileName.empty()){
        fFileName="OutFile";
        /* G4cout<<"No FileName Defined"<<G4endl; */
    }
    std::string outputDir =fOutPutDir;
    std::string FileName = fFileName;
    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directory(outputDir);
    }

    std::string fileName = outputDir + FileName + /* strRunID.str() + */
                           /* "-Events=" + streventNumber.str() + */ ".root";

    analysisManager->OpenFile(fileName);
}



void YourRunAction::EndOfRunAction(const G4Run * run){
    
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();

    analysisManager->CloseFile();
    timer->Stop();
    G4cout << "Simulation run time: " << timer->GetRealElapsed() << " seconds" << G4endl;
    G4int runID = run->GetRunID();
    G4cout<<"In this "<<runID<< " the number of events were"<< run->GetNumberOfEvent()<<G4endl;
}
