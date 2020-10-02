/**
 *  Estimating the uncertainty on Ereco, given Etrue.
 *  Beginning only with SBND.
 *
 *  Rhiannon Jones
 *  July 2020
 *
 **/
#include <iostream>
#include "TH1.h"
#include "TH2.h"
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

void SetStyle(TStyle *sty);

void ereco_error_estimation(const char *dst)
{

  // Get the DST file and tree
  TFile *f = new TFile(dst,"read");
  TTree *t = static_cast<TTree*>(f->Get("valor_sbncode_mini_dst"));

  // Get the true and reconstructed energies
  double enu_true, enu_reco;
  t->SetBranchAddress("enu_true", &enu_true);
  t->SetBranchAddress("enu_reco", &enu_reco);

  // Define histograms
  TH2D *h_true_reco   = new TH2D("h_true_reco",  "",180,0.25,3,240,0.25,5);
  TH2D *h_energy_diff = new TH2D("h_energy_diff","",100,0,3,100,-0.5,2);

  // Loop over the events
  int n_entries = t->GetEntries();
  for(int n = 0; n < n_entries; ++n){
    t->GetEntry(n);
    double diff = (enu_true-enu_reco)/enu_reco;
    h_true_reco->Fill(enu_reco,enu_true);
    h_energy_diff->Fill(enu_reco,diff);
  }
  
  // Format and draw
  TStyle *sty = new TStyle("sty","");
  SetStyle(sty);

  TCanvas *c = new TCanvas("c","",900,900);
  
  h_true_reco->GetXaxis()->SetTitle("Reco E_{#nu} [GeV]");
  h_true_reco->GetYaxis()->SetTitle("True E_{#nu} [GeV]");
  h_true_reco->Draw("colz");
  h_true_reco->SetContour(999);
  c->UseCurrentStyle();
  c->Update();

  c->SaveAs("true_reco_energy_2D.root");
  c->SaveAs("true_reco_energy_2D.png");
  c->Clear();

  h_energy_diff->GetXaxis()->SetTitle("E_{#nu, reco} [GeV]");
  h_energy_diff->GetYaxis()->SetTitle("(E_{#nu, true} - E_{#nu, reco})/E_{#nu, reco}");
  h_energy_diff->Draw("colz");
  h_energy_diff->SetContour(999);
  c->UseCurrentStyle();
  c->Update();

  c->SaveAs("energy_diff_2D.root");
  c->SaveAs("energy_diff_2D.png");
  c->Clear();


}
void SetStyle(TStyle *sty)
{
  sty->SetPalette(kBlueGreenYellow);
  sty->SetTitleFont(132,"XYZ");
  sty->SetLabelFont(132,"XYZ");
  sty->SetTitleSize(0.04,"XYZ");
  sty->SetLabelSize(0.035,"XYZ");
  sty->SetTitleOffset(1.2, "XYZ");
  sty->SetOptStat(0);
  sty->SetPadLeftMargin  (0.104585 );
  sty->SetPadRightMargin (0.10745);
  sty->SetPadBottomMargin(0.136827 );
  sty->SetPadTopMargin   (0.0509461);
  sty->SetCanvasBorderMode(0);
  sty->SetPadBorderMode(0);
  sty->SetPadColor(0);
  sty->SetCanvasColor(0);
  sty->cd();
}
