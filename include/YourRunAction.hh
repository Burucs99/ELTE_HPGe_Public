#ifndef YOURRUNACTION_hh
#define YOURRUNACTION_hh

#include "G4UserRunAction.hh"
#include "YourDetectorConstruction.hh"
#include "YourEventAction.hh"
#include "G4Timer.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "YourRunMessenger.hh"


class YourPrimaryGeneratorAction;
class G4Run;
class YourRun;
class YourRunMessenger;
class YourRunAction : public G4UserRunAction {
public:
    YourRunAction(YourPrimaryGeneratorAction* primGen,YourDetectorConstruction* det);
    ~YourRunAction() override;
    
    G4Run* GenerateRun();

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    struct HistogramFlags {
        G4String Name, Title;
        G4int edepBins = 100;
        G4double edepMin = 0.0;
        G4double edepMax = 1.1*MeV;
    };
    struct NTupleFlags {
        G4String  	name;
        G4String  	title;
    };

    void SetFile(G4String dir, G4String filename){
        fOutPutDir=dir;
        fFileName=filename;
    }

    void AddHistogram(HistogramFlags flag){
        fHistConfigs[flag.Name] = flag;
    }

    void AddNTuple(NTupleFlags flag){
        fNTupleConfigs[flag.name] = flag;
    }


private:
    YourRunMessenger* fRunMessenger;
    YourDetectorConstruction* fDetector;
    YourPrimaryGeneratorAction* fPrimGen ;
    YourRun* fYourRun;
    G4Timer* timer;
    G4String fOutPutDir;
    G4String fFileName;


    std::map<G4String,HistogramFlags> fHistConfigs; 
    std::map<G4String,NTupleFlags> fNTupleConfigs; 

};

#endif