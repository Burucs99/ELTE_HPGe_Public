
#include "YourRunMessenger.hh"
#include "YourRunAction.hh"
#include <G4String.hh>
#include <G4UIcommand.hh>
#include <G4UIparameter.hh>


YourRunMessenger::YourRunMessenger(YourRunAction* runaction)
: fDirCMD(nullptr),fEdepHist(nullptr),fOutPut(nullptr),
fYourRunAction(runaction)
{

    fDirCMD = new G4UIdirectory("/HPGe/run/");
    fDirCMD->SetGuidance("UI commands specific to the run, histogram, data collection of this application");
    

    fEdepHist = new G4UIcommand("/HPGe/run/EdepHist",this);
    fEdepHist->SetGuidance("Histogram for all deposited Energies during a run");
    fEdepHist->SetGuidance("Calls ROOTs CreateH1:  bin number,  range min, range max in MeV");
    G4UIparameter* HistNamePrm = new G4UIparameter("Histogram Name", 's',false);
    G4UIparameter* HistTitlePrm = new G4UIparameter("Histogram Title", 's',false);
    fEdepHist->SetParameter(HistNamePrm);
    fEdepHist->SetParameter(HistTitlePrm);
    G4UIparameter* BinNumberPrm = new G4UIparameter("Bin number",'i',false);
    fEdepHist->SetParameter(BinNumberPrm);
    G4UIparameter* rangeMin = new G4UIparameter("Minimum range", 'd',false);
    fEdepHist->SetParameter(rangeMin);
    G4UIparameter* rangeMax = new G4UIparameter("Maximum of range", 'd',false);
    fEdepHist->SetParameter(rangeMax);


    fOutPut = new G4UIcommand("/HPGe/run/OutputName",this);
    fOutPut->SetGuidance("Sets output folder + Output fileName");
    G4UIparameter* OutFolderPrm = new G4UIparameter("Output folder", 's',false);
    G4UIparameter* FileNamePrm = new G4UIparameter("FileName",'s',false);
    fOutPut->SetParameter(OutFolderPrm);
    fOutPut->SetParameter(FileNamePrm);

}
YourRunMessenger::~YourRunMessenger(){
    delete fEdepHist;
    delete fOutPut;
    delete fDirCMD;
    
}

void YourRunMessenger::SetNewValue(G4UIcommand* command , G4String newValue){


    if(command == fEdepHist){
        YourRunAction::HistogramFlags analysisflag;
        std::istringstream iss(newValue);
        G4String Name,Title;
        G4int bins; G4double min, max;
        iss >>Name>>Title>> bins >> min >> max;
        analysisflag.Name=Name;
        analysisflag.Title=Title;
        analysisflag.edepBins = bins;
        analysisflag.edepMin = min;
        analysisflag.edepMax = max;
        fYourRunAction->AddHistogram(analysisflag);
        
    }
    if(command == fOutPut){
        std::istringstream iss(newValue);
        G4String Directory,FileName;
        iss>>Directory>>FileName;
        fYourRunAction->SetFile(Directory,FileName);

    }


}
