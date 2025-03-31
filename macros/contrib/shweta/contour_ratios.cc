#include <iostream>
#include <algorithm>
#include <iterator>

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"
#include "TFrame.h"
#include "TF1.h"

#include "TGraph.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TColor.h"
 
void contour_ratios(std::string inFile1, std::string inFile2, const char* tag){
  // get files
  //TFile*fvalor_incl    = new TFile("/exp/sbnd/app/users/yadav/valor_recent/valor_package/run_scripts/output_contours/output_contours_as_graphs_inc.root", "read");
  //TFile*fvalor_excl   = new TFile("/exp/sbnd/app/users/yadav/valor_recent/valor_package/run_scripts/output_contours/output_contours_as_graphs_0p0pi.root","read");
  
  TFile *fvalor_incl    = TFile::Open(inFile1.c_str());
  TFile *fvalor_excl    = TFile::Open(inFile2.c_str());
  
  
  //-----------------------------------------------------------------------------------------------
  
  // get contours
  TGraph *VALOR_incl   = (TGraph*) fvalor_incl->Get("contour_5sigma_lin_0;1");
  TGraph *VALOR_excl   = (TGraph*) fvalor_excl->Get("contour_5sigma_lin_0;1");
  
  //-----------------------------------------------------------------------------------------------
  
  // nue stat
  
  auto VALOR_contour_incl  = VALOR_incl;
  auto VALOR_contour_excl  = VALOR_excl;
  
  
  TCanvas * n_stat = new TCanvas("nstat","",20,20,900,900);
  n_stat->Draw();
  
  TH2F * hn_stat = (TH2F*)n_stat->DrawFrame(0.9,1E-2,1.4,1E+2);
  hn_stat->Draw();
  //n_stat->SetLogx();
  n_stat->SetLogy();
  hn_stat->GetXaxis()->SetTitle("Relative sin^{2}2#theta_{#mu#mu}");
  hn_stat->GetXaxis()->SetTitleSize(0.03);
  hn_stat->GetXaxis()->SetLabelSize(0.03);
  hn_stat->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
  hn_stat->GetYaxis()->SetTitleSize(0.03);
  hn_stat->GetYaxis()->SetLabelSize(0.03);
  
  int ref_points = VALOR_contour_incl->GetN();
  
  double Xvalue_VALOR_incl                [ref_points];
  double Xvalue_VALOR_incl_ratio          [ref_points];
  double Yvalue_VALOR_incl                [ref_points];
  double Xvalue_VALOR_excl                [ref_points];
  double Xvalue_VALOR_excl_ratio          [ref_points];
  
  
  TGraph inv_VALOR_excl(VALOR_contour_excl->GetN(), VALOR_contour_excl->GetY(), VALOR_contour_excl->GetX());
  //TGraph inv_SBNFIT(SBNFIT_contour->GetN(), SBNFIT_contour->GetY(), SBNFIT_contour->GetX());
  
  for(int i = 0; i < ref_points; i++){
    Xvalue_VALOR_incl[i] = VALOR_contour_incl->GetX()[i];
    Yvalue_VALOR_incl[i] = VALOR_contour_incl->GetY()[i];
    
    Xvalue_VALOR_excl[i] = inv_VALOR_excl.Eval(VALOR_contour_incl->GetY()[i]);
    
    Xvalue_VALOR_incl_ratio[i] = Xvalue_VALOR_incl[i] / Xvalue_VALOR_incl[i];
    Xvalue_VALOR_excl_ratio[i] = Xvalue_VALOR_excl[i] / Xvalue_VALOR_incl[i];
    //std::cout << i << "  " <<  Yvalue_VALOR_incl[i] << "   " << Xvalue_VALOR_incl[i] << "  " << Xvalue_VALOR_excl[i] << std::endl;
  }
  
  
  TGraph *gref_incl = new TGraph(ref_points, Xvalue_VALOR_incl_ratio, Yvalue_VALOR_incl);
  TGraph *gref_excl = new TGraph(ref_points, Xvalue_VALOR_excl_ratio, Yvalue_VALOR_incl);
  
  gref_incl->SetLineColor(kBlack);
  gref_incl->SetLineWidth(4);
  gref_incl->Draw("l");
  
  gref_excl->SetLineColor(kOrange);
  gref_excl->SetLineWidth(4);
  gref_excl->Draw("l");
  
  TLegend * l_ratio = new TLegend(0.5,0.7,0.8,0.9);
  l_ratio->SetFillStyle(0);
  l_ratio->SetBorderSize(0);
  l_ratio->SetTextFont(132);
  l_ratio->SetTextSize(0.025);
  //l_ratio->AddEntry(gref_incl, "Inclusive/Inclusive","L");
  //l_ratio->AddEntry(gref_excl , Form("Exclusive (%s)/Inclusive", tag),"L");
  l_ratio->AddEntry(gref_incl, "1p0pi/1p0pi","L");
  l_ratio->AddEntry(gref_excl , Form("1p0pi (%s)/1p0pi", tag),"L");
  l_ratio->Draw();
  
}














