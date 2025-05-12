#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TMath.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
// HARDCODED FOR THE MOST PART

void PlotEfficiencyFromHistograms() {
    TFile* file = TFile::Open("EnergyHistograms.root");
    if (!file || file->IsZombie()) {
        std::cerr << "Could not open EnergyHistograms.root" << std::endl;
        return;
    }

    const double totalEvents = 1000000;

    std::vector<double> energies;
    std::vector<double> eff, err;
    std::vector<double> effVeto, errVeto;
    std::vector<double> refEff;

    std::ofstream out("EfficiencyResults.txt");
    out << "# Energy [MeV]\tEff\tSigma\tEffVeto\tSigmaVeto\tReference\n";

    auto compute_eff = [&](double energy, TString eStr) {
        TString histName = "hEnergy_" + eStr;
        TString histVeto = "hEnergyVeto_" + eStr;

        TH1D* h = (TH1D*)file->Get(histName);
        TH1D* hVeto = (TH1D*)file->Get(histVeto);
        if (!h || !hVeto) {
            std::cerr << "Missing histogram: " << histName << " or " << histVeto << std::endl;
            return;
        }

        int binLow, binHigh;
        if (energy < 0.3)
            binLow = h->FindBin(energy - 0.001), binHigh = h->FindBin(energy + 0.001);
        else
            binLow = h->FindBin(energy - 0.08), binHigh = h->FindBin(energy + 0.08);

        double count = h->Integral(binLow, binHigh);
        double countVeto = hVeto->Integral(binLow, binHigh);

        double e = count / totalEvents;
        double s = std::sqrt(count) / totalEvents;

        double eV = countVeto / totalEvents;
        double sV = std::sqrt(countVeto); // To be fixed.

        double ref = 5e-4 * std::pow((energy * 1e3) / 1332.492, -0.9065);

        energies.push_back(energy);
        eff.push_back(e); err.push_back(s);
        effVeto.push_back(eV); errVeto.push_back(sV);
        refEff.push_back(ref);

        out << std::fixed << std::setprecision(3) << energy << "\t"
            << std::setprecision(6) << e << "\t" << s << "\t"
            << eV << "\t" << sV << "\t"
            << ref << "\n";
    };

    // Fine steps: 0.05 - 0.2 MeV
    for (double energy = 0.05; energy <= 0.2 + 1e-6; energy += 0.01) {
        TString eStr; eStr.Form("%.3f", energy);
        eStr = eStr.Strip(TString::kTrailing, '0');
        eStr = eStr.Strip(TString::kTrailing, '.');
        compute_eff(energy, eStr);
    }

    // Coarse steps: 0.3 - 3.0 MeV
    for (double energy = 0.3; energy <= 2.9 + 1e-6; energy += 0.1) {
        TString eStr; eStr.Form("%.1f", energy);
        eStr = eStr.Strip(TString::kTrailing, '0');
        eStr = eStr.Strip(TString::kTrailing, '.');
        compute_eff(energy, eStr);
    }

    out.close();

    // Plotting
    TCanvas* c1 = new TCanvas("c1", "Detection Efficiency", 900, 700);
    c1->SetGrid();

    // Create graphs for full, vetoed, and reference efficiencies
    TGraphErrors* gFull = new TGraphErrors(energies.size(), &energies[0], &eff[0], 0, &err[0]);
    TGraphErrors* gVeto = new TGraphErrors(energies.size(), &energies[0], &effVeto[0], 0, &errVeto[0]);
    TGraph* gRef = new TGraph(energies.size(), &energies[0], &refEff[0]);

    // Style for the full efficiency plot
    gFull->SetMarkerStyle(20); gFull->SetMarkerColor(kBlue); gFull->SetLineColor(kBlue);
    // Style for the vetoed efficiency plot
    gVeto->SetMarkerStyle(21); gVeto->SetMarkerColor(kRed); gVeto->SetLineColor(kRed);
    // Style for the reference efficiency plot
    gRef->SetLineColor(kGreen+2); gRef->SetLineWidth(2); gRef->SetLineStyle(2);

    gFull->SetTitle("Detection Efficiency vs. Energy;Photon Energy [MeV];Efficiency");

    gFull->Draw("APL");
    gVeto->Draw("PL SAME");
    gRef->Draw("L SAME");

    // Add a legend
    TLegend* legend = new TLegend(0.58, 0.68, 0.88, 0.88);
    legend->AddEntry(gFull, "All Events", "lp");
    legend->AddEntry(gVeto, "Z < Veto Limit", "lp");
    legend->AddEntry(gRef, "Reference Efficiency", "l");
    legend->Draw();

    // Save the canvas as a PDF
    c1->SaveAs("EfficiencyPlot.pdf");

    file->Close();
    std::cout << "Efficiency results saved to EfficiencyResults.txt\n";
    std::cout << "Plot saved to EfficiencyPlot.pdf\n";
}
