#include <map>
#include <utility>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include <iostream>
#include <tuple>

void process_energy(int nThreads, TFile* outFile) {
    // Három különböző histogram
    TH1D* hEnergyAll = new TH1D("Edep_All", "Total Deposited Energy per Event - All", 3000, 0, 0.7);
    TH1D* hEnergyC0 = new TH1D("Edep_C0", "Total Deposited Energy - CoulombIDX = 0", 3000, 0, 0.7);
    TH1D* hEnergyC1 = new TH1D("Edep_C1", "Total Deposited Energy - CoulombIDX = 1", 3000, 0, 0.7);
    TH1D* hEnergyC2p = new TH1D("Edep_C2p", "Total Deposited Energy - CoulombIDX > 1", 3000, 0, 0.7);

    // Map-ek a különböző CoulombIDX értékekhez
    std::map< std::tuple<int, int>, double> eventEnergyAll;
    std::map< std::tuple<int, int>, double> eventEnergyC0;
    std::map< std::tuple<int, int>, double> eventEnergyC1;
    std::map< std::tuple<int, int>, double> eventEnergyC2p;

    for (int t = 0; t < nThreads; ++t) {
        TString fileName = TString::Format("Compt_1_t%d.root", t);
        TFile* inFile = TFile::Open(fileName);
        if (!inFile || inFile->IsZombie()) {
            std::cerr << "Could not open file: " << fileName << std::endl;
            continue;
        }

        TTree* tree = (TTree*)inFile->Get("Edep");
        if (!tree) {
            std::cerr << "No tree 'Edep' in " << fileName << std::endl;
            inFile->Close();
            delete inFile;
            continue;
        }

        double energyDep;
        int runID, eventID, trackID, comptonID;

        tree->SetBranchAddress("Energy", &energyDep);
        tree->SetBranchAddress("RunID", &runID);
        tree->SetBranchAddress("EventID", &eventID);
        tree->SetBranchAddress("CoulombIDX", &comptonID);
        
        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; ++i) {
            tree->GetEntry(i);
          
            std::tuple<int, int> evtKey = { eventID,comptonID};
            
            // Mindig hozzáadjuk a teljes összeghez
            eventEnergyAll[evtKey] += energyDep;
            
            if (comptonID == 0) {

                eventEnergyC0[evtKey] += energyDep;
            } else if (comptonID == 1) {

                eventEnergyC1[evtKey] += energyDep;
            } 
            else if (comptonID > 1) {

                eventEnergyC2p[evtKey] += energyDep;
            } 
        }

        inFile->Close();
        delete inFile;
    }

    // Histogramok feltöltése
    for (const auto& entry : eventEnergyAll) {
        hEnergyAll->Fill(entry.second);
    }
    for (const auto& entry : eventEnergyC0) {
        hEnergyC0->Fill(entry.second);
    }
    for (const auto& entry : eventEnergyC1) {
        hEnergyC1->Fill(entry.second);
    }
    for (const auto& entry : eventEnergyC2p) {
        hEnergyC2p->Fill(entry.second);
    }

    // Statisztikák kiírása
    std::cout << "Statisztikák:" << std::endl;
    std::cout << "Összes event: " << eventEnergyAll.size() << std::endl;
    std::cout << "CoulombIDX=0 eventek: " << eventEnergyC0.size() << std::endl;
    std::cout << "CoulombIDX=1 eventek: " << eventEnergyC1.size() << std::endl;
    std::cout << "CoulombIDX>1 eventek: " << eventEnergyC2p.size() << std::endl;

    outFile->cd();
    hEnergyAll->Write();
    hEnergyC0->Write();
    hEnergyC1->Write();
    hEnergyC2p->Write();

    // Takarítás
    delete hEnergyAll;
    delete hEnergyC0;
    delete hEnergyC1;
    delete hEnergyC2p;
}

void Analysis() {
    const int nThreads = 8;
    
    TFile* outFile = new TFile("EnergyHistograms.root", "RECREATE");
    process_energy(nThreads, outFile);
    
    outFile->Close();
    delete outFile;
    std::cout << "All histograms saved to EnergyHistograms.root" << std::endl;
}