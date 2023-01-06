#include "TSpline.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TStyle.h"
#include "TString.h"

#include <iostream>

void draw_splines(const std::string &spline_file, const std::string &param, const std::string &output = ""){

  TFile fSpline(spline_file.c_str(),"READ");

  TObjArray *oNuMuCCQE  = static_cast<TObjArray*>(fSpline.Get(("spl_nueCCQE_"+param).c_str()));
  TSpline3 *sNuMuCCQE   = static_cast<TSpline3*>(oNuMuCCQE->FindObject(("spl_BNB_FHC_nuelikeCChigh_nueCCQE_"+param+"_6_7").c_str()));
//  TObjArray *oNuMuCC1pi = static_cast<TObjArray*>(fSpline.Get(("spl_numuCC1piC_"+param).c_str()));
//  TSpline3 *sNuMuCC1pi  = static_cast<TSpline3*>(oNuMuCC1pi->FindObject(("spl_BNB_FHC_numuCCincl_numuCC1piC_"+param+"_13_11").c_str()));
//  TObjArray *oNuMuNC2pi = static_cast<TObjArray*>(fSpline.Get(("spl_numuNC2piC_"+param).c_str()));
//  TSpline3 *sNuMuNC2pi  = static_cast<TSpline3*>(oNuMuNC2pi->FindObject(("spl_BNB_FHC_numuCCincl_numuNC2piC_"+param+"_17_16").c_str()));

  // Setup the canvas
  TCanvas *c = new TCanvas("c","",700,1200);
  c->SetLeftMargin  (0.128);
  c->SetRightMargin (0.018);
  c->SetBottomMargin(0.111);
  c->SetTopMargin   (0.148);
  c->SetGridx();
  c->SetGridy();

  // Setup a frame
  TH2F * hf = (TH2F*) c->DrawFrame(-3,0.4,3,1.6);
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
//  sNuMuCC1pi->SetLineStyle(2);
//  sNuMuCC1pi->SetLineWidth(3);
//  sNuMuCC1pi->SetLineColor(kAzure-7);
//  sNuMuNC2pi->SetLineStyle(4);
//  sNuMuNC2pi->SetLineWidth(3);
//  sNuMuNC2pi->SetLineColor(kOrange+1);

  sNuMuCCQE->Draw("same");
//  sNuMuCC1pi->Draw("same");
//  sNuMuNC2pi->Draw("same");

  TLegend *l = new TLegend(0.126,0.865,0.98,0.98);
  l->SetTextFont(132);
  l->SetTextSize(0.025);
  l->SetBorderSize(0);
  l->SetFillStyle(0);

  l->AddEntry(sNuMuCCQE,  "Mode: #nu_{#mu} CC QE, Bin: 0.55 < E_{Reco} < 0.6 GeV, 0.65 < E_{True} < 0.7 GeV", "l");
//  l->AddEntry(sNuMuCC1pi, "Mode: #nu_{#mu} CC 1#pi^{#pm}, Bin: 0.75 < E_{Reco} < 0.8 GeV, 1 < E_{True} < 1.05 GeV", "l");
//  l->AddEntry(sNuMuNC2pi, "Mode: #nu_{#mu} NC 2#pi^{#pm}, Bin: 1 < E_{Reco} < 1.25 GeV, 1.2 < E_{True} < 1.5 GeV", "l");
  l->Draw();

  std::string name = "";
  if(output == ""){
    name = (param+"_splines").c_str();
  }
  else 
    name = output;

  c->SaveAs((name+".png").c_str());
  c->SaveAs((name+".pdf").c_str());
  c->SaveAs((name+".root").c_str());

}
