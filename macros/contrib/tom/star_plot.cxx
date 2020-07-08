//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                      //
// Make "star plot".                                                                                    //
//                                                                                                      //
// Expects an even number of input fits with a + & - variation for each systematic of interest. When    //
// generating toy experiment, one parameters is varied whilst the others remain at nominal value        //
// (with some injected osc params). When running the fit on toy exp. the inititally varied param is     //
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
auto px = util::NameRegistry::Instance()->PhysParamFromString("");
auto py = util::NameRegistry::Instance()->PhysParamFromString("dm41sq");

auto mumu = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuMu");
auto mue  = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuE");
auto ee   = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thEE");

auto x_label = "";

std::vector<Color_t> colors = {kBlack, kRed, kBlue, kMagenta+1,  kGreen+2, kOrange-1, kYellow+1, kCyan};

// vector to hold the params that were varied
std::vector<int> varied_params;

FitParamList    * gbfparam      = 0;   // global best-fit params
PhysParamList   * iparam        = 0;   // input params

// Read the files
TChain ch("valor_fit_ntp");
ch.SetBranchAddress("best_fit_params", &gbfparam);
ch.SetBranchAddress("true_params", &iparam);
ch.Add(files);
if(ch.GetEntries() == 0){
    std::cerr << "No files found - check the path. Stopping." << std::endl; 
    std::exit(-1);
}
else{
    std::cout << "Found " << ch.GetEntries() << " fit files. " << std::endl;
}

// Look at one file to determine what sample we have.
ch.GetEntry(0);
if(gbfparam->IsFixed(mumu) == true && gbfparam->IsFixed(mue) == true){
    std::cout << "Looking at a nue disappearance sample." << std::endl;
    px = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thEE");
    x_label = "sin^{2}2#theta_{ee}";
}
else if(gbfparam->IsFixed(mumu) == true && gbfparam->IsFixed(ee) == true){
    std::cout << "Looking at a nue appearance sample." << std::endl;
    px = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuE");
    x_label = "sin^{2}2#theta_{#mue}";
}
else if(gbfparam->IsFixed(ee) == true && gbfparam->IsFixed(mue) == true){
    std::cout << "Looking at a numu disappearance sample." << std::endl;
    px = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuMu");
    x_label = "sin^{2}2#theta_{#mu#mu}";
}
else{
    std::cerr << "Not sure what sample we're looking at here. Was expecting only one of sinsq2thMuMu, sinsq2thMuE or sinsq2thEE to be allowed to float. Stopping" << std::endl;
    std::exit(-1);  
}

// Get max variation in x and y values 
double max_x = 0;
double max_y = 0;
// Get min variation in x and y values 
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
    if(abs(iparam->Value(px) - gbfparam->BestFitValue(px)) < min_x && abs(iparam->Value(px) - gbfparam->BestFitValue(px)) > 0.0001){
        min_x = abs(iparam->Value(px) - gbfparam->BestFitValue(px));
    }
    if(abs(iparam->Value(py) - gbfparam->BestFitValue(py)) < min_y && abs(iparam->Value(py) - gbfparam->BestFitValue(py)) > 0.0001){
        min_y = abs(iparam->Value(py) - gbfparam->BestFitValue(py));
    }


    // Loop over all the parameters
    for(int i = 0; i < gbfparam->Size(); i++){
        //if(gbfparam->IsFixed(gbfparam->WhichParam(i)) == true && gbfparam->IsNuisance(gbfparam->WhichParam(i)) == true){
        if(gbfparam->InitValue(gbfparam->WhichParam(i)) != iparam->Value(gbfparam->WhichParam(i)) && gbfparam->IsNuisance(gbfparam->WhichParam(i)) == true){
            varied_params.push_back(i);
        }
    }
    // order vector and then get only unique entries 
    sort(varied_params.begin(), varied_params.end());
    varied_params.erase(unique(varied_params.begin(), varied_params.end()), varied_params.end());

}

// Check num colours > varied params - could add more colours, but maybe better to run with fewer varied params to avoid making the plot too cluttered
if(varied_params.size() > colors.size()){
    std::cerr << "The number of varied parameters exceeds the defined number of colours. Stopping." << std::endl;
    std::exit(-1);
}

// Make plot for all systematics
TCanvas *All = new TCanvas("All","All",1100,800);
All->SetRightMargin(0.25);
All->GetFrame()->SetY1(5);
All->Draw();
// Draw frame etc for canvas
TH2F * hfAll = (TH2F*) All->DrawFrame(iparam->Value(px)+max_x*(-1.2), iparam->Value(py)+max_y*(-1.2), iparam->Value(px)+max_x*(1.2), iparam->Value(py)+max_y*(1.2));

hfAll->GetXaxis()->SetTitle(x_label);
hfAll->GetXaxis()->SetNdivisions(5, 5, kTRUE);

hfAll->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hfAll->GetYaxis()->SetTitleOffset(1.1);

TLegend *leg_All = new TLegend(0.75,0.16,1,0.95);
leg_All->SetHeader("Systematic","C"); 
leg_All->SetFillStyle(0);
//leg_All->SetBorderSize(0);
leg_All->SetTextSize(0.02);

TArrow *arr[ch.GetEntries()];

// Draw the arrows and fill the legend
for(auto fit = 0; fit < ch.GetEntries(); fit++){
    ch.GetEntry(fit);

    for(auto i = 0; i < varied_params.size(); i++){
        if(gbfparam->IsFixed(gbfparam->WhichParam(varied_params[i])) == true){
            arr[fit] = new TArrow(iparam->Value(px), iparam->Value(py), gbfparam->BestFitValue(px), gbfparam->BestFitValue(py),0.01,"|>");
            arr[fit]->SetFillColor(colors[i]);
            arr[fit]->SetLineColor(colors[i]);
            arr[fit]->SetLineWidth(2);
            arr[fit]->Draw();
           
            // draw the legend for the vaired params and make sure we're not double counting - might not be the most elegent method but works so going with it
            int param;
            if(iparam->Value(gbfparam->WhichParam(varied_params[i])) - gbfparam->InitValue(gbfparam->WhichParam(varied_params[i])) > 0){ 
                leg_All->AddEntry(arr[fit], gbfparam->Name(gbfparam->WhichParam(varied_params[i])).c_str(), "l");
                param = gbfparam->WhichParam(varied_params[i]);
            }
            else if(iparam->Value(gbfparam->WhichParam(varied_params[i])) - gbfparam->InitValue(gbfparam->WhichParam(varied_params[i])) < 0 
                    && param != gbfparam->WhichParam(varied_params[i])){
                leg_All->AddEntry(arr[fit], gbfparam->Name(gbfparam->WhichParam(varied_params[i])).c_str(), "l");
            }
        }
    }       
}

// Option to draw stats ellipse
if(draw_ellipse){
    // Get stats contour 
    TFile *f_valor_numu_stats   = new TFile("/sbnd/app/users/tham/VALOR_master/star_plot/output_contours_as_graphs_inclusion_2sided.root");
    TGraph *VALOR_SBN_1SC       = (TGraph*) f_valor_numu_stats->Get("contour_1sigma_lin_0;1");

    VALOR_SBN_1SC->SetLineStyle(kDotted);
    VALOR_SBN_1SC->Draw();
    
    leg_All->AddEntry(VALOR_SBN_1SC, "1#sigma CL stats", "l");
} 

leg_All->Draw();


// Attempt to guess sensible values to draw a zoomed in version of the above plot. Probably need to adjust values.
if(draw_zoomed_plot){

    // Get the min magnitude of arrow 
    double min_mag = sqrt(min_x*min_x + min_y*min_y);

    // Factor to scale the min values by to try and make plot look sensible - can adjust this
    double N = 8; 

    TCanvas *Zoom = new TCanvas("Zoom","Zoom",1100,800);
    Zoom->SetRightMargin(0.25);
    Zoom->Draw();
    // Draw frame etc for canvas
    TH2F * hfZoom = (TH2F*) Zoom->DrawFrame(iparam->Value(px)+min_x*(-N), iparam->Value(py)+min_y*(-N), iparam->Value(px)+min_x*(N), iparam->Value(py)+min_y*(N));
    hfZoom->GetXaxis()->SetTitle(x_label);
    hfZoom->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
    hfZoom->GetYaxis()->SetTitleOffset(1.1);

    TLegend *leg_Zoom = new TLegend(0.75,0.16,1,0.95);
    leg_Zoom->SetHeader("Systematic","C"); 
    leg_Zoom->SetFillStyle(0);
    //leg_Zoom->SetBorderSize(0);
    leg_Zoom->SetTextSize(0.02);

    // Draw the arrows and fill the legend
    for(auto fit = 0; fit < ch.GetEntries(); fit++){
        ch.GetEntry(fit);

        double mag = sqrt((iparam->Value(px) - gbfparam->BestFitValue(px)) * (iparam->Value(px) - gbfparam->BestFitValue(px)) 
                        + (iparam->Value(py) - gbfparam->BestFitValue(py)) * (iparam->Value(py) - gbfparam->BestFitValue(py)));
        
        for(auto i = 0; i < varied_params.size(); i++){
            
            if(gbfparam->IsFixed(gbfparam->WhichParam(varied_params[i])) == true && mag < min_mag*(N-1)){

                arr[fit] = new TArrow(iparam->Value(px), iparam->Value(py), gbfparam->BestFitValue(px), gbfparam->BestFitValue(py),0.01,"|>");
                arr[fit]->SetFillColor(colors[i]);
                arr[fit]->SetLineColor(colors[i]);
                arr[fit]->SetLineWidth(2);
                arr[fit]->Draw();
           
                // draw the legend for the vaired params and make sure we're not double counting - might not be the most elegent method but works so going with it
                int param;
                if(iparam->Value(gbfparam->WhichParam(varied_params[i])) - gbfparam->InitValue(gbfparam->WhichParam(varied_params[i])) > 0){ 
                    leg_Zoom->AddEntry(arr[fit], gbfparam->Name(gbfparam->WhichParam(varied_params[i])).c_str(), "l");
                    param = gbfparam->WhichParam(varied_params[i]);
                }
                else if(iparam->Value(gbfparam->WhichParam(varied_params[i])) - gbfparam->InitValue(gbfparam->WhichParam(varied_params[i])) < 0 
                        && param != gbfparam->WhichParam(varied_params[i])){ 
                    leg_Zoom->AddEntry(arr[fit], gbfparam->Name(gbfparam->WhichParam(varied_params[i])).c_str(), "l");
                }
            }
        }
    }

    leg_Zoom->Draw();
}





}









