#include <map>
#include <utility>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include <iostream>
//HARDCODED FOR THE MOST PART 
void process_energy(double energy, TString eStr, int nThreads, double vetoZ, TFile* outFile) {
    TString histName = "hEnergy_" + eStr;
    TString histVetoName = "hEnergyVeto_" + eStr;

    TH1D* hEnergy = new TH1D(histName, "Total Deposited Energy per Event",
                             2000, 0, 3.0);
    TH1D* hEnergyVeto = new TH1D(histVetoName, "Total Deposited Energy per Event (Vetoed)",
                                 2000, 0, 3.0);

    std::map<std::pair<int, int>, double> eventEnergy;
    std::map<std::pair<int, int>, double> eventEnergyVetoed;

    for (int t = 0; t < nThreads; ++t) {
        TString fileName = "Energy_" + eStr + Form("_t%d.root", t);
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

        double x, y, z, energyDep;
        int runID, eventID;

        tree->SetBranchAddress("X", &x);
        tree->SetBranchAddress("Y", &y);
        tree->SetBranchAddress("Z", &z);
        tree->SetBranchAddress("Energy", &energyDep);
        tree->SetBranchAddress("RunID", &runID);
        tree->SetBranchAddress("EventID", &eventID);

        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; ++i) {
            tree->GetEntry(i);
            std::pair<int, int> evtKey = {runID, eventID};

            eventEnergy[evtKey] += energyDep;
            if (z > vetoZ) {
                eventEnergyVetoed[evtKey] += energyDep;
            }
        }

        inFile->Close();
        delete inFile;
    }

    for (const auto& entry : eventEnergy) {
        hEnergy->Fill(entry.second);
    }

    for (const auto& entry : eventEnergyVetoed) {
        hEnergyVeto->Fill(entry.second);
    }

    outFile->cd();
    hEnergy->Write();
    hEnergyVeto->Write();

    std::cout << "Processed energy: " << eStr << " MeV" << std::endl;
}

void MakeEnergyHistograms() {
    const int nThreads = 6;
    const double VetoSize = 12;
    const double vetoZ = -27.25 + VetoSize;

    TFile* outFile = new TFile("EnergyHistograms.root", "RECREATE");


    for (double energy = 0.05; energy <= 0.2 + 1e-6; energy += 0.01) {
        TString eStr; eStr.Form("%.3f", energy);
        while (eStr.EndsWith("0")) eStr.Chop();
        if (eStr.EndsWith(".")) eStr.Chop();

        process_energy(energy, eStr, nThreads, vetoZ, outFile);
    }


    for (double energy = 0.3; energy <= 2.9 + 1e-6; energy += 0.1) {
        TString eStr; eStr.Form("%.1f", energy);
        while (eStr.EndsWith("0")) eStr.Chop();
        if (eStr.EndsWith(".")) eStr.Chop();

        process_energy(energy, eStr, nThreads, vetoZ, outFile);
    }

    outFile->Close();
    std::cout << "All histograms saved to EnergyHistograms.root" << std::endl;
}
