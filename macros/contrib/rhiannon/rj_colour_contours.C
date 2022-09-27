////////////////////////////////////////////////////////////
//														                            //
// Scrip to draw sensitivity contours onto a coloured     //
// background giving the chi-squared values.              //
//													                          	  //
// Use the output of the macro "fit_results_to_graphs.py" //
//														                            //
////////////////////////////////////////////////////////////

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

void rj_colour_contours(const std::string &file, const std::string &tag, const std::string &l="", const bool allowed=false, const std::string &contour_enum="0", const bool bkgd_only=false) {

  // Read in output file from fit_results_to_graphs.py
  TFile *f = new TFile(file.c_str(),"read");

  // Get contours from file
  // Check names in .root file
  TGraph *contour_90  = nullptr;
  if(allowed)
    contour_90 = (TGraph*) f->Get((tag+"_99pct_log_"+contour_enum).c_str());
  else
    contour_90 = (TGraph*) f->Get((tag+"_90pct_log_"+contour_enum).c_str());

  TGraph *contour_3_sigma      = (TGraph*) f->Get((tag+"_3sigma_log_"+contour_enum).c_str());
  TGraph *contour_5_sigma      = (TGraph*) f->Get((tag+"_5sigma_log_"+contour_enum).c_str());

  // Get background 
  TH2D *background = (TH2D*) f->Get((tag+"_log_hist").c_str());

  // Set colour palette for background
  //gStyle->SetPalette(kGreyScale);
  gStyle->SetPalette(51);
  // Set log colour scale 
  gStyle->SetOptLogz();
  // Get the number of different colours - pick a large number to get smooth transitions
  background->SetContour(1000);

  // Set title and axis (z axis is for the colour)
  //~background->SetTitle("#nu_{#mu} disappearance");
  // ~background->SetTitle("#nu_e appearance");

  // Range should probably be (-3,0) for numu and (-4,0) for nue
  background->GetXaxis()->SetRangeUser(-3,0);
  background->GetXaxis()->SetTitle("log_{10}(sin^{2}2#theta_{#mu#mu})");
  // ~background->GetXaxis()->SetRangeUser(-4,0);
  // ~background->GetXaxis()->SetTitle("log_{10}(sin^{2}2#theta_{#mue})");

  background->GetYaxis()->SetRangeUser(-2,2);
  background->GetYaxis()->SetTitle("log_{10}(#Deltam^{2}_{41})");
  background->GetYaxis()->SetTitleOffset(0.8);

  // Have to manually set range so that entire graph is filled
  if(allowed)
    background->GetZaxis()->SetRangeUser(1E-9,5e4);

  background->GetZaxis()->SetTitleOffset(0.8);
  background->GetZaxis()->SetTitleFont(132);

  // Edit canvas so axis titles etc. fit on properly
  TCanvas *c1 = new TCanvas("c1","c1",1000,800);
  c1->SetRightMargin(0.2);
  c1->SetLeftMargin(0.11);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.03);

  // Draw background 
  background->Draw("colz");

  if(!bkgd_only){
    // Draw contours
    contour_90->SetLineColor(kWhite);
    contour_90->SetLineWidth(1);
    contour_90->Draw("same");
    contour_3_sigma->SetLineStyle(2);
    contour_3_sigma->SetLineStyle(2);
    contour_3_sigma->SetLineColor(kWhite);
    contour_3_sigma->Draw("same");
    contour_5_sigma->SetLineColor(kWhite);
    contour_5_sigma->SetLineStyle(7);  
    contour_5_sigma->Draw("same");  

    // Add legend
    TLegend *leg = new TLegend(0.18,0.18,0.33,0.38);
    leg->SetTextSize(0.05);
    leg->SetTextFont(132);
    leg->SetTextColor(kWhite);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    if (allowed)
      leg->AddEntry(contour_90,"99%","L");
    else
      leg->AddEntry(contour_90,"90%","L");

    leg->AddEntry(contour_3_sigma,"3#sigma","l");
    leg->AddEntry(contour_5_sigma,"5#sigma","l");
    leg->Draw("same");
  }

  // Add label to colour legend
  TLatex *latex = new TLatex();
  latex->DrawLatexNDC(0.93,0.92,"#chi^{2}");
  if(l != ""){
    TLatex *latex1 = new TLatex();
    latex1->SetTextFont(132);
    latex1->SetTextColor(kWhite);
    latex1->DrawLatexNDC(0.15,0.90,l.c_str());
  }

  TString fOut(file);
  if(!bkgd_only){
    fOut.ReplaceAll(".root","_2Dcontour.png");
    c1->SaveAs(fOut);
    fOut.ReplaceAll(".png",".root");
    c1->SaveAs(fOut);
  }
  else{
    fOut.ReplaceAll(".root","_2Dcontour_noLines.png");
    c1->SaveAs(fOut);
    fOut.ReplaceAll(".png",".root");
    c1->SaveAs(fOut);
  }
}
