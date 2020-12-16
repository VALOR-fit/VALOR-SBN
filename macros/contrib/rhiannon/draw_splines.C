#include "TSpline.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TStyle.h"
#include "TString.h"

#include <iostream>

void draw_splines(const std::string &spline_file, const std::string &param){

  TFile fSpline(spline_file.c_str(),"READ");

  TObjArray *oNuMuCCQE = static_cast<TObjArray*>(fSpline.Get(("spl_numuCCQE_"+param).c_str()));
  TSpline3 *sNuMuCCQE  = static_cast<TSpline3*>(oNuMuCCQE->FindObject(("spl_BNB_FHC_numuCCincl_numuCCQE_"+param+"_7_10").c_str()));


  // Setup the canvas
  TCanvas *c = new TCanvas("c","",700,900);
  c->SetLeftMargin  (0.130);
  c->SetRightMargin (0.018);
  c->SetBottomMargin(0.110);
  c->SetTopMargin   (0.020);
  
  // Setup a frame
  TH2F * hf = (TH2F*) c->DrawFrame(-3,0.9,3,1.1);
  hf->Draw();
  hf->GetYaxis()->SetTitleOffset(1.3);
  hf->GetXaxis()->SetTitle("Knot [#sigma]");
  hf->GetYaxis()->SetTitle("N_{m,b}^{v} / N_{m,b}^{n}");
  hf->GetXaxis()->SetTitleFont(132);
  hf->GetYaxis()->SetTitleFont(132);
  hf->GetXaxis()->SetLabelFont(132);
  hf->GetYaxis()->SetLabelFont(132);
  hf->GetXaxis()->SetTitleSize(0.045);
  hf->GetYaxis()->SetTitleSize(0.045);
  hf->GetXaxis()->SetLabelSize(0.035);
  hf->GetYaxis()->SetLabelSize(0.035);
  
  sNuMuCCQE->SetLineStyle(1);
  sNuMuCCQE->SetLineWidth(2);
  sNuMuCCQE->SetLineColor(kPink+4);

  sNuMuCCQE->Draw("same");

}
