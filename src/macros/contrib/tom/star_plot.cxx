//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                      //
// Make "star plot".                                                                                    //
//                                                                                                      //
// Expects an even number of input fits with a + & - variation for each systematic of interst. When     //
// generating toy experiment, one parameters is varied whilst the others remain at nominal value        //
// (with some injected osc params). When running the fit on toy exp. the inititally varied params is    //
// fixed to the nominal value whilst all others are allowed to float.                                   //
//                                                                                                      //
// Example command to run;                                                                              //
// valor star_plot.cxx'("path/to/root/files/*.root",1,1)'                                               //
//                                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////                                                                              

#include <iostream>
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"
#include "TF1.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TArrow.h"
#include "TColor.h"

#include <cmath>

using namespace valor;

void star_plot(
    const char *files,
    bool draw_ellipse           = false,       // draw stats ellipse - optional 
    bool draw_zoomed_plot       = false        // draw zoomed plot - optional
){

// Get the x-y params for the plot
auto px = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuMu");
auto py = util::NameRegistry::Instance()->PhysParamFromString("dm41sq");

// maybe add more, but might get cluttered if using too many at once
std::vector<Color_t> colors = {kBlack, kRed, kBlue, kMagenta+1,  kGreen+2, kOrange-1, kYellow+1, kCyan};

// vector to hold the params that were varied
std::vector<int> varied_params;

// Read the files
TChain ch("valor_dune_nd_ntp");
ch.Add(files);
std::cout << "Found " << ch.GetEntries() << " fit files. " << std::endl;

if(ch.GetEntries() % 2 != 0){
    std::cerr << "WARNING: Found odd number of files. May fail to draw parts of legend." << std::endl;
}

FitParamList    * gbfparam      = 0;   // global best-fit params
PhysParamList   * iparam        = 0;   // input params

ch.SetBranchAddress("best_fit_params", &gbfparam);
ch.SetBranchAddress("true_params", &iparam);

// Get max difference in x and y values 
double max_x = 0;
double max_y = 0;
// Get min difference in x and y values 
double min_x = 999;
double min_y = 999;

// Loops over all the fit files
for(auto fit = 0; fit < ch.GetEntries(); fit++){
    ch.GetEntry(fit);

    // The max x and y values
    if(abs(iparam->Value(px) - gbfparam->BestFitValue(px)) > max_x){
        max_x = abs(iparam->Value(px) - gbfparam->BestFitValue(px));
    }
    if(abs(iparam->Value(py) - gbfparam->BestFitValue(py)) > max_y){
        max_y = abs(iparam->Value(py) - gbfparam->BestFitValue(py));
    }

    // The min x and y values - check variation isn't too small (zero)
    if(abs(iparam->Value(px) - gbfparam->BestFitValue(px)) < min_x && iparam->Value(px) - gbfparam->BestFitValue(px) > 0.0001){
        min_x = abs(iparam->Value(px) - gbfparam->BestFitValue(px));
    }
    if(abs(iparam->Value(py) - gbfparam->BestFitValue(py)) < min_y && iparam->Value(py) - gbfparam->BestFitValue(py) > 0.0001){
        min_y = abs(iparam->Value(py) - gbfparam->BestFitValue(py));
    }


    // Loop over all the parameters
    for(int i = 0; i < gbfparam->Size(); i++){
        // Find the syst params that were varied
        //if(gbfparam->IsFixed(gbfparam->WhichParam(i)) == true && gbfparam->IsNuisance(gbfparam->WhichParam(i)) == true){
        if(gbfparam->InitValue(gbfparam->WhichParam(i)) != iparam->Value(gbfparam->WhichParam(i)) && gbfparam->IsNuisance(gbfparam->WhichParam(i)) == true){
            varied_params.push_back(i);
        }
    }
    // order vector and then get only unique entries 
    sort(varied_params.begin(), varied_params.end());
    varied_params.erase(unique(varied_params.begin(), varied_params.end()), varied_params.end());

}

if(varied_params.size() > colors.size()){
    std::cerr << "The number of varied parameters exceeds the defined number of colours. Stopping." << std::endl;
    std::exit(-1);
}

// All interaction syst
TCanvas *All = new TCanvas("All","All");
All->Draw();
// Draw frame etc for canvas
TH2F * hfAll = (TH2F*) All->DrawFrame(iparam->Value(px)+max_x*(-1.2), iparam->Value(py)+max_y*(-1.2), iparam->Value(px)+max_x*(1.2), iparam->Value(py)+max_y*(1.2));
hfAll->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu}");
hfAll->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hfAll->GetYaxis()->SetTitleOffset(0.9);

TLegend *leg_All = new TLegend(0.15,0.6,0.5,0.9);
leg_All->SetFillStyle(0);
leg_All->SetBorderSize(0);

TArrow *arr[ch.GetEntries()];


// Draw the arrows and fill the legend
for(auto fit = 0; fit < ch.GetEntries(); fit++){
    ch.GetEntry(fit);

    for(auto i = 0; i < varied_params.size(); i++){
        if(gbfparam->IsFixed(gbfparam->WhichParam(varied_params[i])) == true){
            arr[fit] = new TArrow(iparam->Value(px), iparam->Value(py), gbfparam->BestFitValue(px), gbfparam->BestFitValue(py),0.01,"|>");
            arr[fit]->SetFillColor(colors[i]);
            arr[fit]->SetLineColor(colors[i]);
            arr[fit]->Draw();
            
        
            // Try and think of way to make this handle sytematics with only one variation 
            if(iparam->Value(gbfparam->WhichParam(varied_params[i])) - gbfparam->InitValue(gbfparam->WhichParam(varied_params[i])) > 0){ 
                leg_All->AddEntry(arr[fit], gbfparam->Name(gbfparam->WhichParam(varied_params[i])).c_str(), "l");
            }
        }
    }       
}

leg_All->Draw();

// Option to draw stats ellipse
if(draw_ellipse){
    // Get stats contour 
    TFile *f_valor_numu_stats   = new TFile("/sbnd/app/users/tham/VALOR_master/star_plot/numu_disappearance_injection_stat-only.root");
    TGraph *VALOR_SBN_1SC       = (TGraph*) f_valor_numu_stats->Get("contour_1sigma_lin_0;1");

    VALOR_SBN_1SC->SetLineStyle(kDotted);
    VALOR_SBN_1SC->Draw();
} 


// Attempt to guess sensible values to draw a zoomed in version of the above plot. Probably need to adjust values.
if(draw_zoomed_plot){
    // Zoomed interaction syst
    TCanvas *Zoom = new TCanvas("Zoom","Zoom");
    Zoom->Draw();
    // Draw frame etc for canvas
    TH2F * hfZoom = (TH2F*) Zoom->DrawFrame(iparam->Value(px)+min_x*(-6), iparam->Value(py)+min_y*(-6), iparam->Value(px)+min_x*(6), iparam->Value(py)+min_y*(6));
    hfZoom->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu}");
    hfZoom->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
    hfZoom->GetYaxis()->SetTitleOffset(0.9);

    TLegend *leg_Zoom = new TLegend(0.15,0.6,0.5,0.9);
    leg_Zoom->SetFillStyle(0);
    leg_Zoom->SetBorderSize(0);

    // Draw the arrows and fill the legend
    for(auto fit = 0; fit < ch.GetEntries(); fit++){
        ch.GetEntry(fit);

        for(auto i = 0; i < varied_params.size(); i++){
            if(gbfparam->IsFixed(gbfparam->WhichParam(varied_params[i])) == true
                && abs(iparam->Value(px) - gbfparam->BestFitValue(px)) <  min_x*(5)
                && abs(iparam->Value(py) - gbfparam->BestFitValue(py)) <  min_y*(5)){
           
                arr[fit] = new TArrow(iparam->Value(px), iparam->Value(py), gbfparam->BestFitValue(px), gbfparam->BestFitValue(py),0.01,"|>");
                arr[fit]->SetFillColor(colors[i]);
                arr[fit]->SetLineColor(colors[i]);
                arr[fit]->Draw();
            
                // Try and think of way to make this handle sytematics with only one variation 
                if(iparam->Value(gbfparam->WhichParam(varied_params[i])) - gbfparam->InitValue(gbfparam->WhichParam(varied_params[i])) > 0){ 
                    leg_Zoom->AddEntry(arr[fit], gbfparam->Name(gbfparam->WhichParam(varied_params[i])).c_str(), "l");
                }
            }
        }
    }

    leg_Zoom->Draw();
}


}









