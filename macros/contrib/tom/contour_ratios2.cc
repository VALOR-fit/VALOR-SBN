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
 
void contour_ratios2(){
// get files
TFile*fvalor_stat    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_stat_fixed_params.root", "read");
TFile*fvalor_syst   = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_nue_app_21july.root","read");
TFile*fCAFAna       = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_nue_app_exclusion_2021.root","read");                                                
TFile*fSBNfit       = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/SBNfit_NueAppear_sensitivity_2021.root","read"); 


//-----------------------------------------------------------------------------------------------

// get contours
TGraph *VALOR_stat   = (TGraph*) fvalor_stat->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_syst   = (TGraph*) fvalor_syst->Get("contour_5sigma_lin_0;1");

TGraph *CAFAna_stat   = (TGraph*) fCAFAna->Get("all_stat_5sig");
TGraph *CAFAna_syst   = (TGraph*) fCAFAna->Get("all_syst_5sig");

TGraph *SBNfit_stat   = (TGraph*) fSBNfit->Get("STATONLY_5sigma");
TGraph *SBNfit_syst   = (TGraph*) fSBNfit->Get("g5sigma");

//-----------------------------------------------------------------------------------------------

// nue stat

auto VALOR_contour  = VALOR_syst;
auto CAFANA_contour = CAFAna_syst;
auto SBNFIT_contour = SBNfit_syst;

TCanvas * nue_stat = new TCanvas("nue","",20,20,900,900);
nue_stat->Draw();

TH2F * hnue_stat = (TH2F*)nue_stat->DrawFrame(0.5,1E-2,3,1E+2);
hnue_stat->Draw();
//nue_stat->SetLogx();
nue_stat->SetLogy();
hnue_stat->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue_X}/sin^{2}2#theta_{#mue_reference_value}");
hnue_stat->GetXaxis()->SetTitleSize(0.03);
hnue_stat->GetXaxis()->SetLabelSize(0.03);
hnue_stat->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_stat->GetYaxis()->SetTitleSize(0.03);
hnue_stat->GetYaxis()->SetLabelSize(0.03);

int ref_points = VALOR_contour->GetN();

double Xvalue_VALOR                [ref_points];
double Xvalue_VALOR_ratio          [ref_points];
double Yvalue_VALOR                [ref_points];
double Xvalue_CAFANA               [ref_points];
double Xvalue_CAFANA_ratio         [ref_points];
double Xvalue_SBNFIT               [ref_points];
double Xvalue_SBNFIT_ratio         [ref_points];

TGraph inv_CAFANA(CAFANA_contour->GetN(), CAFANA_contour->GetY(), CAFANA_contour->GetX());
TGraph inv_SBNFIT(SBNFIT_contour->GetN(), SBNFIT_contour->GetY(), SBNFIT_contour->GetX());

for(int i = 0; i < ref_points; i++){
    Xvalue_VALOR[i] = VALOR_contour->GetX()[i];
    Yvalue_VALOR[i] = VALOR_contour->GetY()[i];

    Xvalue_CAFANA[i] = inv_CAFANA.Eval(VALOR_contour->GetY()[i]);
    Xvalue_SBNFIT[i] = inv_SBNFIT.Eval(VALOR_contour->GetY()[i]);

    Xvalue_VALOR_ratio[i] = Xvalue_VALOR[i] / Xvalue_VALOR[i];
    Xvalue_CAFANA_ratio[i] = Xvalue_CAFANA[i] / Xvalue_VALOR[i];
    Xvalue_SBNFIT_ratio[i] = Xvalue_SBNFIT[i] / Xvalue_VALOR[i];
    //std::cout << i << "  " <<  Yvalue_VALOR[i] << "   " << Xvalue_VALOR[i] << "  " << Xvalue_CAFANA[i] << "  " << Xvalue_SBNFIT[i] << std::endl;
}


TGraph *gref = new TGraph(ref_points, Xvalue_VALOR_ratio, Yvalue_VALOR);
TGraph *gCAFANA = new TGraph(ref_points, Xvalue_CAFANA_ratio, Yvalue_VALOR);
TGraph *gSBNFIT = new TGraph(ref_points, Xvalue_SBNFIT_ratio, Yvalue_VALOR);

gref->SetLineColor(kBlack);
gref->SetLineWidth(4);
gref->Draw("l");

gCAFANA->SetLineColor(kOrange);
gCAFANA->SetLineWidth(4);
gCAFANA->Draw("l");

gSBNFIT->SetLineColor(kBlue);
gSBNFIT->SetLineWidth(4);
gSBNFIT->Draw("l");

TLegend * lnue_ratio = new TLegend(0.5,0.7,0.8,0.9);
lnue_ratio->SetFillStyle(0);
lnue_ratio->SetBorderSize(0);
lnue_ratio->SetTextFont(132);
lnue_ratio->SetTextSize(0.025);
lnue_ratio->AddEntry(gref, "Reference Value VALOR","L");
lnue_ratio->AddEntry(gCAFANA , "CAFANA/VALOR","L");
lnue_ratio->AddEntry(gSBNFIT , "SBNFIT/VALOR","L");
lnue_ratio->Draw();

}














