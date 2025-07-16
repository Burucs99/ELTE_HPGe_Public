#include <TFile.h>
#include <TH1D.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

void EfficiencyScan(int eventsPerRun = 100, const char* basePath = "./", double binWindow = 1.0) {
    std::vector<TString> distances;

    TSystemDirectory baseDir("base", basePath);
    TList* files = baseDir.GetListOfFiles();
    if (!files) return;

    TIter next(files);
    TSystemFile* file;
    while ((file = (TSystemFile*)next())) {
        TString fname = file->GetName();
        if (file->IsDirectory() && fname.BeginsWith("distance"))
            distances.push_back(fname);
    }

    std::sort(distances.begin(), distances.end());

    std::vector<std::pair<TString, double>> energies = {
        {"1.17", 1.1732},
        {"1.33", 1.3325}
    };
    double radius_mm = 24.0;
    double A2 = 0.102;
    double A4 = 0.008;
   
    for (const auto& dist : distances) {
        std::cout << "\n=== Processing " << dist << " ===\n";
        

        TString distStr = dist;
        distStr.ReplaceAll("distance", "");
        double d_cm = distStr.Atof();
        double d_mm = d_cm * 10.0;
        double beta_max = atan(radius_mm / d_mm);

        std::vector<double> Betas(200, 0.0);
        std::vector<double> sinbeta(200, 0.0);
        std::vector<double> cosbeta(200, 0.0);
        std::vector<double> P0(200, 0.0);
        std::vector<double> P2(200, 0.0);
        std::vector<double> P4(200, 0.0);
        std::vector<double> Efficiencies_117(200, 0.0);
        std::vector<double> Efficiencies_133(200, 0.0);
        std::vector<double> Errors_117(200, 0.0);    
        std::vector<double> Errors_133(200, 0.0);    
        double J0_117{0};
        double J0_133{0};
        double J2_117{0};
        double J2_133{0};
        double J4_117{0};
        double J4_133{0};
      
        double Q2_117{0};
        double Q2_133{0};
        double Q4_117{0};
        double Q4_133{0};
        double dBeta =  (beta_max * 1/ (200 - 1));
        double varJ0_117{0}, varJ0_133{0};
        double varJ2_117{0}, varJ2_133{0};
        double varJ4_117{0}, varJ4_133{0};
      
        std::vector<double> weights(200, dBeta);
        weights[0] = dBeta / 2.0;
        weights[199] = dBeta / 2.0;
        for (int beta_idx = 0; beta_idx < 200; ++beta_idx) {
            Betas[beta_idx] = beta_max * beta_idx/ (200 - 1);
            cosbeta[beta_idx] = cos(Betas[beta_idx]);
            sinbeta[beta_idx] = sin(Betas[beta_idx]);
            P0[beta_idx] =legendre(0,cosbeta[beta_idx]); 
            P2[beta_idx] =legendre(2,cosbeta[beta_idx]); 
            P4[beta_idx] =legendre(4,cosbeta[beta_idx]); 
            for (const auto& [label, energy] : energies) {
                TString filepath = Form("%s/%s/%s/Beta_%d.root", basePath, dist.Data(), label.Data(), beta_idx);

                TFile* f = TFile::Open(filepath);
                if (!f || f->IsZombie()) {
                    std::cerr << "  Could not open: " << filepath << "\n";
                    continue;
                }

                TH1D* h = (TH1D*)f->Get("Edep");
                if (!h) {
                    std::cerr << "  Missing histogram in " << filepath << "\n";
                    f->Close();
                    continue;
                }

                int bin = h->FindBin(energy);
                double sum = h->GetBinContent(bin);

                if (binWindow > 1.0) {
                    int half = int((binWindow - 1) / 2);
                    for (int b = bin - half; b <= bin + half; ++b) {
                        if (b != bin && b >= 1 && b <= h->GetNbinsX())
                            sum += h->GetBinContent(b);
                    }
                }

                double efficiency = sum / eventsPerRun;
                double error = std::sqrt(efficiency * (1 - efficiency) / eventsPerRun);

                if (label == "1.17"){ 
                    Efficiencies_117[beta_idx] = efficiency;
                    Errors_117[beta_idx] = error;
                    J0_117+=P0[beta_idx] *sinbeta[beta_idx] * Efficiencies_117[beta_idx] *weights[beta_idx];
                    J2_117+=P2[beta_idx] *sinbeta[beta_idx] * Efficiencies_117[beta_idx] *weights[beta_idx];
                    J4_117+=P4[beta_idx] *sinbeta[beta_idx] * Efficiencies_117[beta_idx] *weights[beta_idx];
                    varJ4_117 += pow(P4[beta_idx] * sinbeta[beta_idx] * Errors_117[beta_idx] * dBeta, 2);
                    varJ2_117 += pow(P2[beta_idx] * sinbeta[beta_idx] * Errors_117[beta_idx] * dBeta, 2);
                    varJ0_117 += pow(P0[beta_idx] * sinbeta[beta_idx] * Errors_117[beta_idx] * dBeta, 2);

            }
                    
                else{                 
                    Efficiencies_133[beta_idx] = efficiency;
                    Errors_133[beta_idx] = error;
                    J0_133+=P0[beta_idx] *sinbeta[beta_idx] * Efficiencies_133[beta_idx] *weights[beta_idx];
                    J2_133+=P2[beta_idx] *sinbeta[beta_idx] * Efficiencies_133[beta_idx] *weights[beta_idx];
                    J4_133+=P4[beta_idx] *sinbeta[beta_idx] * Efficiencies_133[beta_idx] *weights[beta_idx];
                    varJ4_133 += pow(P4[beta_idx] * sinbeta[beta_idx] * Errors_133[beta_idx] * dBeta, 2);
                    varJ2_133 += pow(P2[beta_idx] * sinbeta[beta_idx] * Errors_133[beta_idx] * dBeta, 2);
                    varJ0_133 += pow(P0[beta_idx] * sinbeta[beta_idx] * Errors_133[beta_idx] * dBeta, 2);
                }
                f->Close();
            }

           
        }
    
        Q2_117 = J2_117 / J0_117;
        Q4_117 = J4_117 / J0_117;
        Q2_133 = J2_133 / J0_133;
        Q4_133 = J4_133 / J0_133;

        double Q2_117_err = std::sqrt(varJ2_117 / (J0_117 * J0_117) + (J2_117 * J2_117 * varJ0_117) / std::pow(J0_117, 4));
        double Q4_117_err = std::sqrt(varJ4_117 / (J0_117 * J0_117) + (J4_117 * J4_117 * varJ0_117) / std::pow(J0_117, 4));

        double Q2_133_err = std::sqrt(varJ2_133 / (J0_133 * J0_133) + (J2_133 * J2_133 * varJ0_133) / std::pow(J0_133, 4));
        double Q4_133_err = std::sqrt(varJ4_133 / (J0_133 * J0_133) + (J4_133 * J4_133 * varJ0_133) / std::pow(J0_133, 4));


        // W(0) = sum_k even A_kk P_k(1) Q_k_117 * Q_k_133
        double W0{0};
        //k=0 , 2, 4 where Q_0 = 1
        /// K=0 A_00 is what??? 
       
        W0+=1 ;
        // K=2
        W0+=A2*legendre(2,1)*Q2_117*Q2_133;

        //K=4

        W0+=A4 *legendre(4,1)*Q4_117*Q4_133;
        double P2_1 = legendre(2, 1);
        double P4_1 = legendre(4, 1);

        double term2 = A2 * A2 * P2_1;
        double term4 = A4 * A4 * P4_1;

        double err2 = term2 * sqrt(pow(Q2_117 * Q2_133_err, 2) + pow(Q2_133 * Q2_117_err, 2));
        double err4 = term4 * sqrt(pow(Q4_117 * Q4_133_err, 2) + pow(Q4_133 * Q4_117_err, 2));

        double W0_error = sqrt(err2 * err2 + err4 * err4);
        TString outName = Form("W0_%s.txt", dist.Data());
        std::ofstream outTxt(outName);
        outTxt << "# Angular Correlation W(0) for " << dist << "\n";
        outTxt << "# beta_index  eff_1.17     err_1.17     eff_1.33     err_1.33\n";
        outTxt<<"Final result : W(0) = "<<W0<<" ± " << W0_error << std::endl;
        for (int i = 0; i < 200; ++i) {
            outTxt << Form("%.6f          %.6f    %.6f    %.6f    %.6f\n", 
                          Betas[i], 
                          Efficiencies_117[i], Errors_117[i],
                          Efficiencies_133[i], Errors_133[i]);
        }

        

        std::cout<<"Finished the analysis"<<std::endl;
        std::cout<<"                           \n";
        std::cout<<"Final result : W(0) = "<<W0<<" ± " << W0_error << std::endl;


        outTxt.close();

    }
    

}
