/*  Macro to read in far detector mock data and prediction generated from ND or joint fit
 *  Calculate the difference between the two in each energy bin
 *
 *  Given the difference, define a binning scheme for a systematic parameter set by grouping 
 *  bins with 'similar' difference
 *
 *  Construct a covariance matrix from the bias in each of the parameter set bins
 *  Apply this to the analysis with a 1-sided (negative-only) range to account for the
 *  over-estimation of the prediction
 *  
 *  Author: R. S. Jones
 *  Email:  rjones@hep.ph.liv.ac.uk
 *
 *
 */

#include "TFile.h"
#include "TH1.h"
#include "TMatrix.h"
#include "TVector.h"
#include "TMath.h"
#include "TPrincipal.h"

using namespace valor;

// Setup the styling lists
std::vector<int> cols{
  kAzure-5, 
  kAzure-5,
  kPink+5,
  kPink+5,
  kTeal-5,
  kTeal-5,
  kOrange+2,
  kViolet+6,
  kSpring-5
};
std::vector<int> styles{
  1,
  3,
  1,
  2,
  1,
  2,
  1,
  1,
  1
};
std::vector<int> widths{
  2,
  3,
  2,
  3,
  2,
  3,
  2,
  2,
  2
};

void StyleHist(TH1D *h, const unsigned int i);

void bias_overlay(const std::string &dataFiles, 
    const std::string &predFiles, 
    const std::string &sample, 
    const std::string &output,
    const std::string debug="",
    const bool &verbose=false)
{

  // Now extract the model and file names from the list
  ifstream dStrings(dataFiles.c_str());
  ifstream pFiles(predFiles.c_str());
  std::string dLine, pLine;
  std::vector<std::string> dLines, pLines, lEntries, dFiles;
  while(getline(dStrings,dLine)){
    dLines.push_back(dLine);
  }
  while(getline(pFiles,pLine)){
    pLines.push_back(pLine);
  }

  assert(dLines.size() == pLines.size());

  // Setup the histogram and integral vectors
  std::vector<TH1D*> diffHists;
  
  // Access the largest bias values from all the mock data along with the mean of all the mock data in every bin
  int nFiles = dLines.size();
  for(const std::string &l : dLines){
    int pos0=0, pos1;
    std::string dataName="", legendEntry="";
    while(l[pos0] != ' '){
      legendEntry += l[pos0];
      pos0++;
    }
    for(pos1 = pos0; l[pos1] == ' '; ++pos1);
    while(l[pos1] != ' '){
      dataName += l[pos1];
      pos1++;
    }
    dFiles.push_back(dataName);
    lEntries.push_back(legendEntry);
  }
  for(int l = 0; l < nFiles; ++l){

    // Get the current data and MC histograms
    TFile *fData = new TFile(dFiles.at(l).c_str(), "READ");
    TFile *fPred = new TFile(pLines.at(l).c_str(), "READ");
    std::cout << " Read: " << pLines.at(l) << " prediction" << std::endl;
    std::cout << " Read: " << dLines.at(l) << " data" << std::endl;

    TH1D *hData   = static_cast<TH1D*>(fData->Get(("toymc_data_ob_rf_sbn_icarus__BNB_FHC__"+sample).c_str()));
    TH1D *hPred   = static_cast<TH1D*>(fPred->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
    
    assert(hData->GetNbinsX() == hPred->GetNbinsX());

    TH1D *hDiff = static_cast<TH1D*>(hPred->Clone("hDiff"));
    hDiff->Add(hData,-1);
    
    // Now scale by the mock data rate in every bin
    for (int ibin = 1 ; ibin <= hData->GetXaxis()->GetNbins(); ibin++) {
      double orig_content   = hDiff->GetBinContent(ibin);
      double to_scale_by    = hData->GetBinContent(ibin);
      double scaled_content = orig_content/to_scale_by;
      hDiff->SetBinContent(ibin,scaled_content);
    }

    diffHists.push_back(hDiff);
  }

  TCanvas *c = new TCanvas("c","",900,900);
  c->SetLeftMargin  (0.16);
  c->SetBottomMargin(0.13);
  c->SetRightMargin (0.02);
  c->SetTopMargin   (0.02);

  TLegend *l = new TLegend(0.68,0.55,0.97,0.94);
  l->SetTextFont(132);
  l->SetBorderSize(0);
  l->SetFillStyle(0);

  double max_y = -999.;
  double min_y =  999.;
  for(unsigned int i = 0; i < diffHists.size(); ++i){
    StyleHist(diffHists.at(i),i);
    if(diffHists.at(i)->GetMaximum() > max_y)
      max_y = diffHists.at(i)->GetMaximum();
    if(diffHists.at(i)->GetMinimum() < min_y)
      min_y = diffHists.at(i)->GetMinimum();
  }
  diffHists.at(0)->Draw("hist");
  if(min_y < 0)
    min_y *= 1.1;
  else
    min_y *= 0.9;

  if(max_y > 0)
    max_y *= 1.1;
  else
    max_y *= 0.9;

  diffHists.at(0)->GetYaxis()->SetRangeUser(min_y,max_y);
  l->AddEntry(diffHists.at(0), lEntries.at(0).c_str(),"L");
  for(unsigned int i = 1; i < diffHists.size(); ++i){
    diffHists.at(i)->Draw("hist same");
    l->AddEntry(diffHists.at(i), lEntries.at(i).c_str(),"L");
  }
  l->Draw();

  c->SaveAs(output.c_str());
}
void StyleHist(TH1D *h, const unsigned int i){
  h->GetXaxis()->SetLabelFont(132);
  h->GetYaxis()->SetLabelFont(132);
  h->GetXaxis()->SetTitleFont(132);
  h->GetYaxis()->SetTitleFont(132);
  h->GetXaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetLabelSize(0.05);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetRangeUser(0.,3.);
  h->GetYaxis()->SetTitleOffset(1.3);
  h->GetXaxis()->SetTitle("Reconstructed Neutrino Energy [GeV]");
  h->GetYaxis()->SetTitle("N_{Postfit}-N_{MockData}/N_{MockData}");
  h->SetStats(0);
  h->SetTitle("");

  h->SetLineColor(cols.at(i));
  h->SetLineStyle(styles.at(i));
  h->SetLineWidth(widths.at(i));

}
