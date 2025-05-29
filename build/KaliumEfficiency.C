#include <map>
#include <utility>
#include <vector>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include <iostream>
#include <cmath>

void KaliumEfficiency() {
    const int nThreads = 6;
    const double E_target = 1.460;      
    const double E_window = 0.010;      
    const int NumberOfEvents = 2000000; 

    std::map<std::pair<int, int>, double> eventEnergy;

    for (int t = 0; t < nThreads; ++t) {
        TString fileName = Form("Dead_Layer_t%d.root", t);
        TFile* inFile = TFile::Open(fileName);
        if (!inFile || inFile->IsZombie()) {
            std::cerr << "Could not open file: " << fileName << std::endl;
            continue;
        }

        TTree* tree = (TTree*)inFile->Get("Positions");
        if (!tree) {
            std::cerr << "No tree 'Positions' in " << fileName << std::endl;
            inFile->Close();
            delete inFile;
            continue;
        }

        double energyDep;
        int runID, eventID;
        double x, y, z;

        tree->SetBranchAddress("Energy", &energyDep);
        tree->SetBranchAddress("RunID", &runID);
        tree->SetBranchAddress("EventID", &eventID);
        tree->SetBranchAddress("X", &x);
        tree->SetBranchAddress("Y", &y);
        tree->SetBranchAddress("Z", &z);

        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; ++i) {
            tree->GetEntry(i);
            std::pair<int, int> evtKey = {runID, eventID};
            eventEnergy[evtKey] += energyDep;
        }

        inFile->Close();
        delete inFile;
    }

    int nEventsInWindow = 0;
    for (const auto& entry : eventEnergy) {
        double energy = entry.second;
        if (energy >= (E_target - E_window) && energy <= (E_target + E_window)) {
            ++nEventsInWindow;
        }
    }

    double efficiency = static_cast<double>(nEventsInWindow) / NumberOfEvents;
    double error = 0.0;
    if (NumberOfEvents > 0) {
        error = std::sqrt(efficiency * (1.0 - efficiency) / NumberOfEvents);
    }

    std::ofstream outTxt("KaliumEfficiencies.txt");
    outTxt << "Number of generated events: " << NumberOfEvents << std::endl;
    outTxt << "Number of events in energy window: " << nEventsInWindow << std::endl;
    outTxt << "Energy window: " << E_target - E_window << " MeV to " << E_target + E_window << " MeV" << std::endl;
    outTxt << "Efficiency: " << efficiency << std::endl;
    outTxt << "Statistical error on efficiency: " << error << std::endl;
    outTxt.close();

    TH1D* hEnergy_all = new TH1D("hEnergy_all", "Total Energy per Event (All)", 2000, 0, 3.0);
    for (const auto& entry : eventEnergy) {
        hEnergy_all->Fill(entry.second);
    }

    TFile* outFile = new TFile("Efficiency_Kalium.root", "RECREATE");
    hEnergy_all->Write();
    outFile->Close();
}
