//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                      //
// Makes plots showing the change in oscillations parameters. It's the same info as a "star plot", but  //
// as a table for both the mixing angle and the mass splitting.                                         //
//                                                                                                      //
// Expects an even number of input fits with a + & - variation for each systematic of interest. When    //
// generating toy experiment, one parameters is varied whilst the others remain at nominal value        //
// (with some injected osc params). When running the fit on toy exp. the inititally varied param is     //
// fixed to the nominal value whilst all others are allowed to float.                                   //
//                                                                                                      //
// Example command to run;                                                                              //
// valor osc_param_pulls.cxx'("path/to/root/files/*.root")'                                             //
//                                                                                                      //
// Formatting goes a bit janky if running with just one fit but not worth my time to fix.               //
// Don't know why you'd want this anyway, but if you do, fix it yourself.                               // 
//                                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////                                                                              

#include <iostream>
#include "TString.h"
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

#include <string>
#include <experimental/filesystem>
#include <cmath>

using namespace valor;
using namespace valor::conv;
namespace vutil = valor::util;

void osc_param_pulls(
    const char *files
){

// Get the x-y params for the plot
auto px = util::NameRegistry::Instance()->PhysParamFromString("");
auto py = util::NameRegistry::Instance()->PhysParamFromString("dm41sq");

auto mumu = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuMu");
auto mue  = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuE");
auto ee   = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thEE");

auto x_label_p = "";
auto x_label_m = "";


// First build a FitElements so we can get information about the systematics
std::string config_path = vutil::CompleteConfigPath("/sbnd/app/users/tham/VALOR_master/VALOR-SBN/config/analysis/sbn_nue_2020a1_03d1_1.xml");
CompoundFitElements elems;
elems.Read(config_path.c_str(),"nomc nosplines");
FitModelABC * modelabc = elems.FitModel();
CompoundFitModel & model = *dynamic_cast<CompoundFitModel*>(modelabc);
CorrelatedSystematics * syst = model.GetSystematics();
const util::NameRegistry * nr = util::NameRegistry::Instance();


// vector to hold the params that were varied
std::vector<int> varied_params;

FitParamList    * gbfparam      = 0;   // global best-fit params
PhysParamList   * iparam        = 0;   // input params

// Read the files
TChain ch("valor_fit_ntp");
//TChain ch("valor_dune_nd_ntp");
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
    x_label_p = "#frac{+1#sigma}{nominal} [sin^{2}2#theta_{ee}]";
    x_label_m = "#frac{-1#sigma}{nominal} [sin^{2}2#theta_{ee}]";
}
else if(gbfparam->IsFixed(mumu) == true && gbfparam->IsFixed(ee) == true){
    std::cout << "Looking at a nue appearance sample." << std::endl;
    px = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuE");
    x_label_p = "#frac{+1#sigma}{nominal} [sin^{2}2#theta_{#mue}]";
    x_label_m = "#frac{-1#sigma}{nominal} [sin^{2}2#theta_{#mue}]";
}
else if(gbfparam->IsFixed(ee) == true && gbfparam->IsFixed(mue) == true){
    std::cout << "Looking at a numu disappearance sample." << std::endl;
    px = util::NameRegistry::Instance()->PhysParamFromString("sinsq2thMuMu");
    x_label_p = "#frac{+1#sigma}{nominal} [sin^{2}2#theta_{#mu#mu}]";
    x_label_m = "#frac{-1#sigma}{nominal} [sin^{2}2#theta_{#mu#mu}]";
}
else{
    std::cerr << "Not sure what sample we're looking at here. Was expecting only one of sinsq2thMuMu, sinsq2thMuE or sinsq2thEE to be allowed to float. Stopping" << std::endl;
    std::exit(-1);  
}

// Get max variation ratio 
double max_ratio_p = 1;
double max_ratio_m = 1;

// Get the number of + and - files. Would expect these to be the same but doesn't have to be.
int n_files_p = 0;
int n_files_m = 0;

// Loops over all the fit files
for(auto fit = 0; fit < ch.GetEntries(); fit++){
    ch.GetEntry(fit);
   
    // Get filename
    std::string pathname = (ch.GetFile()->GetName());
    std::string filename = pathname.substr(pathname.find_last_of("/\\") + 1);

    //Find the +- file variants
    size_t found_p = filename.find("+");
    size_t found_m = filename.find("-");
  
    if(found_p != string::npos){
      n_files_p += 1;
      // Get max variation ratio
      if(gbfparam->BestFitValue(px) / iparam->Value(px) > max_ratio_p){
        max_ratio_p = gbfparam->BestFitValue(px) / iparam->Value(px);
      }
      else if(iparam->Value(px) / gbfparam->BestFitValue(px) > max_ratio_p){
        max_ratio_p = iparam->Value(px) / gbfparam->BestFitValue(px);
      }
      if(gbfparam->BestFitValue(py) / iparam->Value(py) > max_ratio_p){
        max_ratio_p = gbfparam->BestFitValue(py) / iparam->Value(py);
      }
      else if(iparam->Value(py) / gbfparam->BestFitValue(py) > max_ratio_p){
        max_ratio_p = iparam->Value(py) / gbfparam->BestFitValue(py);
      }
    }
    if(found_m != string::npos){
      n_files_m += 1;
      // Get max variation ratio  
      if(gbfparam->BestFitValue(px) / iparam->Value(px) > max_ratio_m){
          max_ratio_m = gbfparam->BestFitValue(px) / iparam->Value(px);
      }
      else if(iparam->Value(px) / gbfparam->BestFitValue(px) > max_ratio_m){
        max_ratio_m = iparam->Value(px) / gbfparam->BestFitValue(px);
      }
      if(gbfparam->BestFitValue(py) / iparam->Value(py) > max_ratio_m){
        max_ratio_m = gbfparam->BestFitValue(py) / iparam->Value(py);
      }
      else if(iparam->Value(py) / gbfparam->BestFitValue(py) > max_ratio_m){
        max_ratio_m = iparam->Value(py) / gbfparam->BestFitValue(py);
      }

    }

    // Loop over all the parameters and find the ones that were varied
    for(int i = 0; i < gbfparam->Size(); i++){
        if(gbfparam->InitValue(gbfparam->WhichParam(i)) != iparam->Value(gbfparam->WhichParam(i)) && gbfparam->IsNuisance(gbfparam->WhichParam(i)) == true){
          varied_params.push_back(i);
        }
    }
    // order vector and then get only unique entries otherwise we'll be double counting cos of the +-
    sort(varied_params.begin(), varied_params.end());
    varied_params.erase(unique(varied_params.begin(), varied_params.end()), varied_params.end());

}

auto pool = valor::ParameterPool::Instance();
// Prin the varied params
for(auto i : varied_params){
  //std::cout << "Varied param: " << gbfparam->Name(gbfparam->WhichParam(varied_params[i])).c_str() << std::endl;
  std::cout << "Varied param: " << gbfparam->Name(gbfparam->WhichParam(i)).c_str() << std::endl;
  //auto param = pool->GetParam(gbfparam->WhichParam(i));
  //std::cout << param.GetTeXName() << std::endl;
}

// Wanted to highlight systs based on syst groups but it's being a PIA so giving up for now..
/*
// Find the last param from each set so we can separate the syst sets
int last_int_prop = 0;
int last_int_mod  = 0;
int last_flux     = 0;

// We can do a binary search cos we ordered the vector earlier 
for(auto i : varied_params){
  //std::cout << i << std::endl;
  if(std::binary_search(util::GetParameterSet("flux_uncorr").begin(), util::GetParameterSet("flux_uncorr").end(), i)){
    last_flux += 1;
  }
  if(std::find(util::GetParameterSet("proposal").begin(), util::GetParameterSet("proposal").end(), i) != util::GetParameterSet("proposal").end()){
    last_int_prop += 1;
    std::cout << i << "  " << std::endl;
  }
  if(std::binary_search(util::GetParameterSet("modern").begin(), util::GetParameterSet("modern").end(), i)){
    last_int_mod += 1;
  }
}
std::cout << last_int_prop << std::endl;
*/

// Draw the canvas and sort out the pads
TCanvas *c = new TCanvas("c","",0,0,700,1400);

TPad *pad_title    = new TPad("pad_title"  , "Pad with titles"              ,0.0,0.95,1.0,1.0);
TPad *pad_p_dmsq   = new TPad("pad_p_dmsq" , "Pad with +sigma var for dmsq" ,0.0,0.0,0.225,0.95);
TPad *pad_p_sinsq  = new TPad("pad_p_sinsq", "Pad with +sigma var for sinsq",0.225,0.0,0.45,0.95);
TPad *pad_label    = new TPad("pad_label"  , "Pad with the labels"          ,0.45,0.0,0.55,0.95);
TPad *pad_m_sinsq  = new TPad("pad_m_sinsq", "Pad with -sigma var for sinsq",0.55,0.0,0.775,0.95);
TPad *pad_m_dmsq   = new TPad("pad_m_dmsq" , "The with -sigma var for dmsq" ,0.775,0.0,1.0,0.95);
pad_title  ->Draw();
pad_p_dmsq ->Draw();
pad_p_sinsq->Draw();
pad_label  ->Draw();
pad_m_sinsq->Draw();
pad_m_dmsq ->Draw();

pad_title   ->SetBottomMargin(0);
pad_p_dmsq  ->SetTopMargin(0);
pad_p_sinsq ->SetTopMargin(0);
pad_label   ->SetTopMargin(0);
pad_m_sinsq ->SetTopMargin(0);
pad_m_dmsq  ->SetTopMargin(0);
pad_label   ->SetRightMargin(0);
pad_label   ->SetLeftMargin(0);
pad_p_dmsq  ->SetBottomMargin(0.1);
pad_p_sinsq ->SetBottomMargin(0.1);
pad_label   ->SetBottomMargin(0.1);
pad_m_sinsq ->SetBottomMargin(0.1);
pad_m_dmsq  ->SetBottomMargin(0.1);


pad_p_dmsq->cd();
pad_p_dmsq->SetRightMargin(0.03);
// I want the x-axis to count from xmax to xmin in the x-direction so the TArrows will be displayed back
// to back, but apparently root doesn't like this.
// For now we'll have it in the conventional manner (i.e. axis is increasing in x-direction)
// and we'll overwrite the axis later. Bear this in mind when drawing the TArrow's for this pad
// as it will have to be done as a "mirror" version.
TH2F * hc_p_dmsq = (TH2F*) c->DrawFrame(1,0,max_ratio_p,n_files_p);                         
hc_p_dmsq->GetXaxis()->SetTitle("#frac{+1#sigma}{nominal} [#Deltam^{2}_{41}]");
hc_p_dmsq->GetXaxis()->CenterTitle(true);
hc_p_dmsq->GetXaxis()->SetTitleSize(0.1);
hc_p_dmsq->GetXaxis()->SetTitleOffset(0.35);
hc_p_dmsq->GetXaxis()->SetNdivisions(505);
hc_p_dmsq->GetYaxis()->SetLabelOffset(999); // remove axis numbering
hc_p_dmsq->GetYaxis()->SetTickLength(0);    // remove axis ticks
hc_p_dmsq->Draw();                                                                                                                                                       

// Remove the current axis since we're manually creating a new one later
hc_p_dmsq->GetXaxis()->SetLabelOffset(999);
hc_p_dmsq->GetXaxis()->SetTickLength(0);

pad_p_sinsq->cd();
pad_p_sinsq->SetLeftMargin(0.03);
TH2F * hc_p_sinsq = (TH2F*) c->DrawFrame(1,0,max_ratio_p,n_files_p);                         
hc_p_sinsq->GetXaxis()->SetTitle(x_label_p);                                                                                                        
hc_p_sinsq->GetXaxis()->CenterTitle(true);
hc_p_sinsq->GetXaxis()->SetTitleSize(0.1);                                                                                                        
hc_p_sinsq->GetXaxis()->SetTitleOffset(0.35);                                                                                                        
hc_p_sinsq->GetXaxis()->SetLabelOffset(-0.055);                                                                                                        
hc_p_sinsq->GetXaxis()->SetLabelSize(0.1);                                                                                                        
hc_p_sinsq->GetXaxis()->SetNdivisions(505);
hc_p_sinsq->GetYaxis()->SetLabelOffset(999); // remove axis numbering
hc_p_sinsq->GetYaxis()->SetTickLength(0);    // remove axis ticks
hc_p_sinsq->Draw();                                                                                                                                                       

// Draw an invisible frame so we can better control where the latex labels go cos fuck root
pad_label->cd();
TH2F * hc_label = (TH2F*) c->DrawFrame(0,0,1,n_files_p);                         
hc_label->Draw("A");
TFrame *fr = (TFrame*)gPad->GetFrame();
fr->SetLineColor(0);
gPad->Modified();
fr->Draw();

pad_m_sinsq->cd();
pad_m_sinsq->SetRightMargin(0.03);
// I want the x-axis to count from xmax to xmin in the x-direction so the TArrows will be displayed back
// to back, but apparently root doesn't like this.
// For now we'll have it in the conventional manner (i.e. axis is increasing in x-direction)
// and we'll overwrite the axis later. Bear this in mind when drawing the TArrow's for this pad
// as it will have to be done as a "mirror" version.
TH2F * hc_m_sinsq = (TH2F*) c->DrawFrame(1,0,max_ratio_m,n_files_p);                         
hc_m_sinsq->GetXaxis()->SetTitle(x_label_m);
hc_m_sinsq->GetXaxis()->SetTitleSize(0.1);                                                                                                        
hc_m_sinsq->GetXaxis()->SetTitleOffset(0.35);                                                                                                        
hc_m_sinsq->GetXaxis()->CenterTitle(true);
hc_m_sinsq->GetXaxis()->SetNdivisions(505);
hc_m_sinsq->GetYaxis()->SetLabelOffset(999); // remove axis numbering
hc_m_sinsq->GetYaxis()->SetTickLength(0);    // remove axis ticks
hc_m_sinsq->Draw();                                                                                                                                                       

// Remove the current axis since we're manually creating a new one later
hc_m_sinsq->GetXaxis()->SetLabelOffset(999);
hc_m_sinsq->GetXaxis()->SetTickLength(0);

pad_m_dmsq->cd();
pad_m_dmsq->SetLeftMargin(0.03);
TH2F * hc_m_dmsq = (TH2F*) c->DrawFrame(1,0,max_ratio_m,n_files_p);                         
hc_m_dmsq->GetXaxis()->SetTitle("#frac{-1#sigma}{nominal} [#Deltam^{2}_{41}]");                                                                                                        
hc_m_dmsq->GetXaxis()->CenterTitle(true);
hc_m_dmsq->GetXaxis()->SetTitleSize(0.1);                                                                                                        
hc_m_dmsq->GetXaxis()->SetTitleOffset(0.35);                                                                                                        
hc_m_dmsq->GetXaxis()->SetLabelOffset(-0.055);
hc_m_dmsq->GetXaxis()->SetLabelSize(0.1);                                                                                                        
hc_m_dmsq->GetXaxis()->SetNdivisions(505);
hc_m_dmsq->GetYaxis()->SetLabelOffset(999); // remove axis numbering
hc_m_dmsq->GetYaxis()->SetTickLength(0);    // remove axis ticks
hc_m_dmsq->Draw();                                                                                                                                                       


TLine *intersect_line_sinsq_p[n_files_p]; 
TLine *intersect_line_dmsq_p[n_files_p]; 
TArrow *arr_sinsq_p[n_files_p];
TArrow *arr_dmsq_p[n_files_p];
TLine *intersect_line_sinsq_m[n_files_m]; 
TLine *intersect_line_dmsq_m[n_files_m]; 
TArrow *arr_sinsq_m[n_files_m];
TArrow *arr_dmsq_m[n_files_m];

TLatex latex;
latex.SetTextSize(0.20);
latex.SetTextAlign(22); // Horizontal and vertical centering

// Loop over the files again and fill in the pulls on the canvas
for(auto fit = 0; fit < ch.GetEntries(); fit++){
  ch.GetEntry(fit);
 
  // Get filename
  std::string pathname = (ch.GetFile()->GetName());
  std::string filename = pathname.substr(pathname.find_last_of("/\\") + 1);

  //Find the +- file variants
  size_t found_p = filename.find("+");
  size_t found_m = filename.find("-");

  // Get all the +sigma files
  if(found_p != string::npos){
    for(auto i = 0; i < varied_params.size(); i++){
    
      // Get param name i.e. remove the trailing "_XXX" and the "genie_"
      //std::string param_name = gbfparam->Name(gbfparam->WhichParam(varied_params[i]));
      //size_t item_to_remove = param_name.find_last_of("_");
      //param_name = param_name.substr(0, item_to_remove);

      //std::regex target("(genie_)+");
      //std::string replacement = " ";
      //param_name = std::regex_replace(param_name, target, replacement);
      
      auto param = pool->GetParam(gbfparam->WhichParam(varied_params[i]));
      auto param_name = param.GetTeXName();
      std::cout << param_name << std::endl; 

      if(gbfparam->IsFixed(gbfparam->WhichParam(varied_params[i])) == true){
        
        // In anticipation of ovwerwriting the x-axis later we have to make all the TArrows in a mirror world 
        // so they'll be correct later 
        pad_p_dmsq->cd();
        bool invert_dmsq = false;
        // Get ratio of variation to nominal 
        if(iparam->Value(py) > gbfparam->BestFitValue(py)){
          invert_dmsq = true;
        }
        
        double var_ratio_dmsq = gbfparam->BestFitValue(py) / iparam->Value(py); 

        if(invert_dmsq == true){
          arr_dmsq_p[fit] = new TArrow(max_ratio_p, i+0.5, max_ratio_p-((1/var_ratio_dmsq)-1), i+0.5, 0.005, "|>");
          arr_dmsq_p[fit]->SetLineColor(kRed);
        }
        else{
          arr_dmsq_p[fit] = new TArrow(max_ratio_p, i+0.5, max_ratio_p-(var_ratio_dmsq-1), i+0.5, 0.005, "|>");
        }
        arr_dmsq_p[fit]->SetLineWidth(3);
        arr_dmsq_p[fit]->Draw();

        intersect_line_dmsq_p[fit] = new TLine(1, i, max_ratio_p, i);
        intersect_line_dmsq_p[fit]->SetLineStyle(2);
        intersect_line_dmsq_p[fit]->Draw();

        
        pad_p_sinsq->cd();

        bool invert_sinsq = false;
        // Get ratio of variation to nominal 
        if(iparam->Value(px) > gbfparam->BestFitValue(px)){
          invert_sinsq = true;
        }
        double var_ratio = gbfparam->BestFitValue(px) / iparam->Value(px); 

        if(invert_sinsq == true){
          arr_sinsq_p[fit] = new TArrow(1, i+0.5, 1/var_ratio, i+0.5, 0.005, "|>");
          arr_sinsq_p[fit]->SetLineColor(kRed);
        }
        else{
          arr_sinsq_p[fit] = new TArrow(1, i+0.5, var_ratio, i+0.5, 0.005, "|>");
        }
        arr_sinsq_p[fit]->SetLineWidth(3);
        arr_sinsq_p[fit]->Draw();

        intersect_line_sinsq_p[fit] = new TLine(1, i, max_ratio_p, i);
        intersect_line_sinsq_p[fit]->SetLineStyle(2);
        intersect_line_sinsq_p[fit]->Draw();

        // draw the param names in the middle pad
        pad_label->cd();
        //latex.DrawLatex(0.5,i+0.5,param_name.c_str());
        latex.DrawLatex(0.5,i+0.5,param_name.c_str());
        
      }
    }
  }
  // Get all the -sigma files
  if(found_m != string::npos){
    for(auto i = 0; i < varied_params.size(); i++){
      if(gbfparam->IsFixed(gbfparam->WhichParam(varied_params[i])) == true){
      
        // In anticipation of ovwerwriting the x-axis later we have to make all the TArrows in a mirror world 
        // so they'll be correct later 
        pad_m_sinsq->cd();
        bool invert_sinsq = false;
        // Get ratio of variation to nominal 
        if(iparam->Value(px) > gbfparam->BestFitValue(px)){
          invert_sinsq = true;
        }
        
        double var_ratio_sinsq = gbfparam->BestFitValue(px) / iparam->Value(px); 

        if(invert_sinsq == true){
          arr_sinsq_m[fit] = new TArrow(max_ratio_m, i+0.5, max_ratio_m-((1/var_ratio_sinsq)-1), i+0.5, 0.005, "|>");
          arr_sinsq_m[fit]->SetLineColor(kRed);
        }
        else{
          arr_sinsq_m[fit] = new TArrow(max_ratio_m, i+0.5, max_ratio_m-(var_ratio_sinsq-1), i+0.5, 0.005, "|>");
        }
        arr_sinsq_m[fit]->SetLineWidth(3);
        arr_sinsq_m[fit]->Draw();

        intersect_line_sinsq_m[fit] = new TLine(1, i, max_ratio_m, i);
        intersect_line_sinsq_m[fit]->SetLineStyle(2);
        intersect_line_sinsq_m[fit]->Draw();

        
        pad_m_dmsq->cd();

        bool invert_dmsq = false;
        // Get ratio of variation to nominal 
        if(iparam->Value(py) > gbfparam->BestFitValue(py)){
          invert_dmsq = true;
        }
        double var_ratio = gbfparam->BestFitValue(py) / iparam->Value(py); 

        if(invert_dmsq == true){
          arr_dmsq_m[fit] = new TArrow(1, i+0.5, 1/var_ratio, i+0.5, 0.005, "|>");
          arr_dmsq_m[fit]->SetLineColor(kRed);
        }
        else{
          arr_dmsq_m[fit] = new TArrow(1, i+0.5, var_ratio, i+0.5, 0.005, "|>");
        }
        arr_dmsq_m[fit]->SetLineWidth(3);
        arr_dmsq_m[fit]->Draw();

        intersect_line_dmsq_m[fit] = new TLine(1, i, max_ratio_m, i);
        intersect_line_dmsq_m[fit]->SetLineStyle(2);
        intersect_line_dmsq_m[fit]->Draw();
        }
      }
  }
}

// Give some sort of title
pad_title->cd();
TLatex Title;
Title.SetTextSize(0.7);
Title.SetTextAlign(22); // Horizontal and vertical centering
Title.DrawLatex(0.2,0.5,"+1#sigma variation");
Title.DrawLatex(0.8,0.5,"-1#sigma variation");


// Redraw the new axes (need to do top and bottom..)
pad_p_dmsq->cd();
pad_p_dmsq->Update();
TGaxis *newaxis_p_dmsq = new TGaxis(pad_p_dmsq->GetUxmax(),
                                pad_p_dmsq->GetUymin(),
                                pad_p_dmsq->GetUxmin(),
                                pad_p_dmsq->GetUymin(),
                                hc_p_dmsq->GetXaxis()->GetXmin(),
                                hc_p_dmsq->GetXaxis()->GetXmax(),
                                505,"-");
newaxis_p_dmsq->SetLabelOffset(-0.13);
newaxis_p_dmsq->SetLabelSize(0.1);
newaxis_p_dmsq->SetLabelFont(132);
newaxis_p_dmsq->Draw("same");

TGaxis *newaxis_p_dmsq2 = new TGaxis(pad_p_dmsq->GetUxmax(),
                                pad_p_dmsq->GetUymax(),
                                pad_p_dmsq->GetUxmin(),
                                pad_p_dmsq->GetUymax(),
                                hc_p_dmsq->GetXaxis()->GetXmin(),
                                hc_p_dmsq->GetXaxis()->GetXmax(),
                                505,"+");
newaxis_p_dmsq2->SetLabelOffset(999);
newaxis_p_dmsq2->Draw("same");

pad_m_sinsq->cd();
pad_m_sinsq->Update();
TGaxis *newaxis_m_sinsq = new TGaxis(pad_m_sinsq->GetUxmax(),
                                pad_m_sinsq->GetUymin(),
                                pad_m_sinsq->GetUxmin(),
                                pad_m_sinsq->GetUymin(),
                                hc_m_sinsq->GetXaxis()->GetXmin(),
                                hc_m_sinsq->GetXaxis()->GetXmax(),
                                510,"-");
newaxis_m_sinsq->SetNdivisions(505);
newaxis_m_sinsq->SetLabelOffset(-0.13);
newaxis_m_sinsq->SetLabelSize(0.1);
newaxis_m_sinsq->SetLabelFont(132);
newaxis_m_sinsq->Draw("same");

TGaxis *newaxis_m_sinsq2 = new TGaxis(pad_m_sinsq->GetUxmax(),
                                pad_m_sinsq->GetUymax(),
                                pad_m_sinsq->GetUxmin(),
                                pad_m_sinsq->GetUymax(),
                                hc_m_sinsq->GetXaxis()->GetXmin(),
                                hc_m_sinsq->GetXaxis()->GetXmax(),
                                505,"+");
newaxis_m_sinsq2->SetLabelOffset(999);
newaxis_m_sinsq2->Draw("same");




}















