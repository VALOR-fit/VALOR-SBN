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

using namespace valor;

void thesis_ereco_etrue_plots(const char *dst)
{

  // Get the DST file and tree
  TFile *f = new TFile(dst,"read");
  TTree *t = static_cast<TTree*>(f->Get("valor_sbn_minidst"));

  // Get the true and reconstructed energies
  double enu_true, enu_reco;
  t->SetBranchAddress("enu_true", &enu_true);
  t->SetBranchAddress("enu_reco", &enu_reco);
  int n_entries = t->GetEntries();

  /*
   * -------------------------------------------------------------------------------
   *
   *                Plot the information in various ways
   *
   * -------------------------------------------------------------------------------
   */
  // Define histograms
  TH2D *h_true_reco   = new TH2D("h_true_reco",  "",100,0,5,80,0,5);
  TH2D *h_diff_true   = new TH2D("h_diff_true","",100,-5,5,80,0,5); // ereco-etrue vs etrue

  TH1D *h_ereco       = new TH1D("h_ereco","",80,0,5);
  TH1D *h_etrue       = new TH1D("h_etrue","",80,0,5);
  TH1D *h_energy_diff = new TH1D("h_energy_diff","",80,-5,5); // ereco-etrue

  // Loop over the events
  for(int n = 0; n < n_entries; ++n){
    t->GetEntry(n);
    double diff = (enu_reco-enu_true);
    h_true_reco->Fill(enu_true,enu_reco);
    h_diff_true->Fill(diff,enu_true);
    h_ereco->Fill(enu_reco);
    h_etrue->Fill(enu_true);
    h_energy_diff->Fill(diff);
  }
  
  // Format and draw
  TStyle *sty = new TStyle("sty","");
  SetStyle(sty);

  TCanvas *c = new TCanvas("c","",900,900);
  c->SetRightMargin(0.156);
  c->SetLeftMargin(0.14);
  c->SetBottomMargin(0.14);
  c->SetTopMargin(0.022);
  
  h_true_reco->GetXaxis()->SetTitle("True E_{#nu} [GeV]");
  h_true_reco->GetYaxis()->SetTitle("Reco E_{#nu} [GeV]");
  h_true_reco->Draw("colz");
  h_true_reco->SetContour(99);
  h_true_reco->GetXaxis()->SetTitleSize(0.065);
  h_true_reco->GetXaxis()->SetLabelSize(0.055);
  h_true_reco->GetYaxis()->SetTitleSize(0.065);
  h_true_reco->GetYaxis()->SetLabelSize(0.055);
  h_true_reco->GetYaxis()->SetTitleOffset(1);
  h_true_reco->GetZaxis()->SetMaxDigits(3);

  c->SaveAs("true_reco_energy_2D.root");
  c->SaveAs("true_reco_energy_2D.png");
  c->SaveAs("true_reco_energy_2D.pdf");
  c->Clear();

  h_diff_true->Draw("colz");
  h_diff_true->SetContour(99);
  h_diff_true->GetXaxis()->SetTitle("(E_{#nu, reco} - E_{#nu, true}) [GeV]");
  h_diff_true->GetYaxis()->SetTitle("E_{#nu, true} [GeV]");
  h_diff_true->GetXaxis()->SetTitleSize(0.065);
  h_diff_true->GetXaxis()->SetLabelSize(0.055);
  h_diff_true->GetYaxis()->SetTitleSize(0.065);
  h_diff_true->GetYaxis()->SetLabelSize(0.055);
  h_diff_true->GetYaxis()->SetTitleOffset(1);
  //c->UseCurrentStyle();
  //c->Update();

  c->SaveAs("energy_diff_2D.root");
  c->SaveAs("energy_diff_2D.png");
  c->SaveAs("energy_diff_2D.pdf");
  c->Clear();

  /*****************************************************************************
   *
   *      1D Plots
   *
   *****************************************************************************/
  TCanvas *c1 = new TCanvas("c1","",900,900);
  c1->SetLeftMargin  (0.14);
  c1->SetRightMargin (0.02);
  c1->SetBottomMargin(0.16);
  c1->SetTopMargin   (0.068);

  TLegend *l = new TLegend(0.48,0.70,0.92,0.90);
  l->SetTextFont(132);
  l->SetTextSize(0.045);
  l->SetFillStyle(0);
  l->SetBorderSize(0);

  l->AddEntry(h_ereco,"Reco. neutrino energy","FL");
  l->AddEntry(h_etrue,"True neutrino energy","FL");

  // Get shape-only true and reconstructed plots
  h_ereco->Scale(1/static_cast<double>(h_ereco->Integral()));
  h_etrue->Scale(1/static_cast<double>(h_etrue->Integral()));

  h_ereco->GetXaxis()->SetTitle("E_{#nu} [GeV]");
  h_ereco->GetYaxis()->SetTitle("Area-normalised event rate");
  h_ereco->GetXaxis()->SetTitleSize(0.065);
  h_ereco->GetXaxis()->SetLabelSize(0.055);
  h_ereco->GetYaxis()->SetTitleSize(0.065);
  h_ereco->GetYaxis()->SetLabelSize(0.055);
  h_ereco->GetYaxis()->SetTitleOffset(1);
  h_ereco->GetXaxis()->SetMaxDigits(3);
  h_ereco->GetYaxis()->SetMaxDigits(3);
  h_ereco->SetLineWidth(2);
  h_ereco->SetLineColor(kTeal-5);
  h_ereco->SetFillStyle(3017);
  h_ereco->SetFillColor(kTeal-5);
  h_etrue->SetLineWidth(2);
  h_etrue->SetLineColor(kViolet-5);
  h_etrue->SetFillStyle(3018);
  h_etrue->SetFillColor(kViolet-5);

  h_ereco->Draw("hist");
  h_etrue->Draw("same hist");
  l->Draw();
  c1->SaveAs("etrue_ereco_overlay.root");
  c1->SaveAs("etrue_ereco_overlay.png");
  c1->SaveAs("etrue_ereco_overlay.pdf");

  c1->Clear();

  h_energy_diff->GetXaxis()->SetTitle("(E_{#nu, reco} - E_{#nu, true}) GeV");
  h_energy_diff->GetYaxis()->SetTitle("Event rate");
  h_energy_diff->GetXaxis()->SetTitleSize(0.065);
  h_energy_diff->GetXaxis()->SetLabelSize(0.055);
  h_energy_diff->GetYaxis()->SetTitleSize(0.065);
  h_energy_diff->GetYaxis()->SetLabelSize(0.055);
  h_energy_diff->GetYaxis()->SetTitleOffset(1);
  h_energy_diff->GetXaxis()->SetMaxDigits(3);
  h_energy_diff->GetYaxis()->SetMaxDigits(3);
  h_energy_diff->SetLineWidth(2);
  h_energy_diff->SetLineColor(kAzure-5);
  h_energy_diff->SetFillStyle(3017);
  h_energy_diff->SetFillColor(kAzure-5);

  h_energy_diff->Draw("hist");
  c1->SaveAs("energy_diff_1D.root");
  c1->SaveAs("energy_diff_1D.png");
  c1->SaveAs("energy_diff_1D.pdf");

}
void SetStyle(TStyle *sty)
{
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
