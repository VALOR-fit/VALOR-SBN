#include <vector>
#include <string>
#include <map>
#include <unordered_map>
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

// Global variables
std::vector<std::string> fileNames, sinsqVals, dmsqVals;

std::vector<int> pal = {
  kAzure+5,
  kViolet-5,
  kTeal-5,
  kPink+5,
  kSpring-5,
  kOrange-2
};

// Global functions
void GetFilesVals(const std::string &f);
void FormatLatex(const double &x, const double &y, const char *s);

// Main
void spectral_comparisons(const std::string &fileList, const std::string &tag="ratio", const std::string &type="total", const bool &ratio=true) {
    
  // -------------------------------------------------------------------------
  //        Loop over fileList and get the oscillated spectra at each point
  // -------------------------------------------------------------------------

  GetFilesVals(fileList);

  // Get the histogram name based on the type
  std::string name_sbnd   = "sbn_nd_"+type;
  std::string name_uboone = "sbn_uboone_"+type;
  std::string name_icarus = "sbn_icarus_"+type;
  
  std::vector<TFile*> osc_files;
  for(const std::string &f : fileNames){
    TFile *f_osc = new TFile(f.c_str(),"read");
    osc_files.push_back(f_osc);
  }
  TFile *f_unosc = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/2021TN/VALOR_unosc_spectra.root","read");

  // Get a vector of each detector's histograms, unosc last
  std::vector<TH1D*> sbnd, uboone, icarus;
  
  // Get the relevant histograms
  for(TFile *f: osc_files){
    TH1D *sbnd_osc     = static_cast<TH1D*>(f->Get(name_sbnd.c_str()));
    TH1D *uboone_osc   = static_cast<TH1D*>(f->Get(name_uboone.c_str()));
    TH1D *icarus_osc   = static_cast<TH1D*>(f->Get(name_icarus.c_str()));
    sbnd.push_back(sbnd_osc);
    uboone.push_back(uboone_osc);
    icarus.push_back(icarus_osc);
  }
  
  // Unosc
  TH1D *sbnd_unosc   = static_cast<TH1D*>(f_unosc->Get(name_sbnd.c_str()));
  TH1D *uboone_unosc = static_cast<TH1D*>(f_unosc->Get(name_uboone.c_str()));
  TH1D *icarus_unosc = static_cast<TH1D*>(f_unosc->Get(name_icarus.c_str()));

  sbnd.push_back(sbnd_unosc);
  uboone.push_back(uboone_unosc);
  icarus.push_back(icarus_unosc);

  std::unordered_map< std::string, std::vector<TH1D*> > detector_hists;
  detector_hists.emplace("sbnd",sbnd);
  detector_hists.emplace("uboone",uboone);
  detector_hists.emplace("icarus",icarus);

  for (const auto& it: detector_hists) {
    std::string det          = it.first;
    std::vector<TH1D*> hists = it.second;

    // Get the unoscillated histogram from the end of the vector
    TH1D *unosc = hists.at(hists.size()-1);

    // Sort out the plotting ranges while we're at it
    double max = 1;
    double min = 1;

    // Y location of the latex
    double yLoc = max;

    // Setup the canvas and the legend
    TCanvas *c = new TCanvas("c","c",20,20,900,900);
    c->SetRightMargin(0.02);
    c->SetLeftMargin(0.15);
    c->SetTopMargin(0.05);
    c->SetBottomMargin(0.15);

    // Add legend
    TLegend *leg = nullptr;
    
    if(ratio)
      leg = new TLegend(0.372, 0.199, 0.885, 0.457);
    else
      leg = new TLegend(0.472,0.7,0.95,0.92);

    leg->SetEntrySeparation(0.01);
    leg->SetTextFont(132);
    leg->SetTextColor(1);
    leg->SetFillStyle(0);
    leg->SetLineWidth(0);

    // Name for latex later on
    std::string name = det;
    
    // Now plot, get the ratios if necessary
    for(unsigned int h = 0; h < hists.size(); ++h){
      TH1D *osc = hists.at(h);

      // 
      // OSCILLATED/UNOSCILLATED
      //
      TH1D *osc_unosc = static_cast<TH1D*>(osc->Clone("osc_unosc"));
      if(ratio)
        osc_unosc->Divide(unosc);

      // Update the range values
      if(osc_unosc->GetMinimum() < min)
        min = osc_unosc->GetMinimum();
      if(osc_unosc->GetMaximum() > max)
        max = osc_unosc->GetMaximum();

      //
      // OSCILLATED RATE DIFFERENCES
      //
      TH1D *diff = static_cast<TH1D*>(unosc->Clone("diff"));
      diff->Add(osc, -1);

      osc_unosc->SetLineColor(pal.at(h));
      osc_unosc->SetLineWidth(2);
      osc_unosc->SetLineStyle(1);

      // If we are at the last entry, this corresponds to nominal/nominal
      if(h == hists.size()-1){
        osc_unosc->SetLineWidth(3);
        osc_unosc->SetLineStyle(2);
        osc_unosc->SetLineColor(kGray+2);
      }

      osc_unosc->SetStats(0);
      osc_unosc->SetTitle("");
      osc_unosc->GetXaxis()->SetTitle("E_{Reco} [GeV]");
      osc_unosc->GetYaxis()->SetTitle("Oscillated/Unoscillated Rate");
      osc_unosc->GetXaxis()->SetTitleFont(132);
      osc_unosc->GetYaxis()->SetTitleFont(132);
      osc_unosc->GetXaxis()->SetLabelFont(132);
      osc_unosc->GetYaxis()->SetLabelFont(132);
      osc_unosc->GetXaxis()->SetTitleSize(0.055);
      osc_unosc->GetYaxis()->SetTitleSize(0.055);
      osc_unosc->GetXaxis()->SetLabelSize(0.045);
      osc_unosc->GetYaxis()->SetLabelSize(0.045);
      osc_unosc->GetXaxis()->SetTitleOffset(1);
      osc_unosc->GetYaxis()->SetTitleOffset(1.35);
      osc_unosc->GetXaxis()->SetMaxDigits(3);
      osc_unosc->GetYaxis()->SetMaxDigits(3);
      
      std::string leg_entry = "Nominal";

      if(h < hists.size()-1){
        leg_entry = "sin^{2}2#theta_{#mu#mu} = "+sinsqVals.at(h)+", #Delta m^{2}_{41} = "+dmsqVals.at(h);
      }
      leg->AddEntry(osc_unosc, leg_entry.c_str(), "l");

      // Update axes
      osc_unosc->GetXaxis()->SetRangeUser(0.2,3);
      if(det == "sbnd"){
        if(ratio){
          osc_unosc->GetYaxis()->SetRangeUser(min*0.998,max*1.001);
          yLoc = (max*1.001)+((max*1.001-min*0.998)/80.);
        }
        else{
          osc_unosc->GetYaxis()->SetRangeUser(0.,max*1.1);
          yLoc = max*1.11;
        }
        name = "SBND";
      }
      else if(det == "uboone"){
        if(ratio){
          osc_unosc->GetYaxis()->SetRangeUser(min*0.994,max*1.004);
          yLoc = (max*1.004)+((max*1.004-min*0.994)/100.);
        }
        else{
          osc_unosc->GetYaxis()->SetRangeUser(0.,max*1.1);
          yLoc = max*1.08;
        }
        name = "MicroBooNE";
      }
      else if(det == "icarus"){
        if(ratio){
          osc_unosc->GetYaxis()->SetRangeUser(min*0.994,max*1.004);
          yLoc = (max*1.004)+((max*1.004-min*0.994)/100.);
        }
        else{
          osc_unosc->GetYaxis()->SetRangeUser(0.,max*1.1);
          yLoc = max*1.06;
        }
        name = "ICARUS";
      }
     
      // Draw
      if(h == 0){
        osc_unosc->Draw("hist");       
      }
      else{
        osc_unosc->Draw("hist same");
      }
      leg->Draw("same");
    } // Histograms

    std::cout << " Drawing LATEX with name: " << name << " at yLoc: " << yLoc << " with max: " << max << std::endl;
    // Add the detector label
    FormatLatex(2,yLoc,("#color[855]{"+name+"}").c_str());

    // Add label to colour legend
    c->SaveAs(("valor_osc_unosc_"+tag+"_"+det+".root").c_str());
    c->SaveAs(("valor_osc_unosc_"+tag+"_"+det+".png").c_str());
    c->Clear();
    leg->Clear();

  } // Detector map
}
void GetFilesVals(const std::string &f){

  //Construct the list of model and file names from the input
  ifstream files(f.c_str());
  std::string line;
  std::vector<std::string> lines;
  while(getline(files,line)){
    lines.push_back(line);
  }

  // Now extract the model and file names from the list
  for(const std::string &l : lines){
    int pos0=0, pos1, pos2;
    std::string fileName="", sinsqVal="", dmsqVal="";
    while(l[pos0] != ' '){
      fileName += l[pos0];
      pos0++;
    }
    for(pos1 = pos0; l[pos1] == ' '; ++pos1);
    while(l[pos1] != ' '){
      sinsqVal += l[pos1];
      pos1++;
    }
    for(pos2 = pos1; l[pos2] == ' '; ++pos2);
    while(l[pos2] != ' '){
      dmsqVal += l[pos2];
      pos2++;
    }
    fileNames.push_back(fileName);
    sinsqVals.push_back(sinsqVal);
    dmsqVals.push_back(dmsqVal);
  }
  assert(sinsqVals.size() == fileNames.size() && dmsqVals.size() == fileNames.size());
}
void FormatLatex(const double &x, const double &y, const char *s){
  // Setup the Latex object
  TLatex l(0,0,s);
  l.SetTextAlign(11);
  l.SetTextSize(0.04);
  l.SetTextFont(132);

  // Asthetics
  l.DrawLatex(x,y,s);
}
