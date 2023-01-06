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
//TFile*fvalor_stat   = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_stat_fixed_params.root", "read");
TFile*fvalor_syst   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_numu_disapp_03d1.root","read");
TFile*fCAFAna       = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_numu_disapp_exclusion_2021.root","read");                                                
TFile*fSBNfit       = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/SBNfit_NumuDis_sensitivity.root","read"); 

TFile*fvalor_stat            = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_stat.root", "read");
TFile*fvalor_ccresvector     = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/single_param/output_contours_as_graphs_nue_app_ccresvector.root", "read");
TFile*fvalor_ccresaxial      = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/single_param/output_contours_as_graphs_nue_app_ccresaxial.root", "read");
TFile*fvalor_intranukencex   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/single_param/output_contours_as_graphs_nue_app_intranukencex.root", "read");
TFile*fvalor_pioninexsec     = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/single_param/output_contours_as_graphs_nue_app_pioninexsec.root", "read");


TFile*fvalor_flux            = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_flux.root", "read");
TFile*fvalor_proposal        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_proposal.root", "read");
TFile*fvalor_modern          = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_modern.root", "read");
TFile*fvalor_proposal_modern = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_proposal_modern.root", "read");
TFile*fvalor_detector        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d2_detector_5pct_0.5pct.root", "read");

//-----------------------------------------------------------------------------------------------

// get contours
TGraph *VALOR_stat   = (TGraph*) fvalor_stat->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_syst   = (TGraph*) fvalor_syst->Get("contour_5sigma_lin_0;1");

TGraph *CAFAna_stat   = (TGraph*) fCAFAna->Get("all_stat_5sig");
TGraph *CAFAna_syst   = (TGraph*) fCAFAna->Get("all_syst_5sig");

TGraph *SBNfit_stat   = (TGraph*) fSBNfit->Get("STATONLY_5sigma");
TGraph *SBNfit_syst   = (TGraph*) fSBNfit->Get("g5sigma");

TGraph *VALOR_ccresvector   = (TGraph*)fvalor_ccresvector->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_ccresaxial  = (TGraph*)fvalor_ccresaxial->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_intranukencex   = (TGraph*)fvalor_intranukencex->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_pioninexsec   = (TGraph*)fvalor_pioninexsec->Get("contour_5sigma_lin_0;1");


TGraph *VALOR_proposal        = (TGraph*) fvalor_proposal->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_modern          = (TGraph*) fvalor_modern->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_flux            = (TGraph*) fvalor_flux->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_proposal_modern = (TGraph*) fvalor_proposal_modern->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_detector        = (TGraph*) fvalor_detector->Get("contour_5sigma_lin_0;1");

//-----------------------------------------------------------------------------------------------

auto contour_ref = VALOR_stat;
auto contour_1   = VALOR_ccresvector;
auto contour_2   = VALOR_ccresaxial;
auto contour_3   = VALOR_intranukencex;
auto contour_4   = VALOR_pioninexsec;
//auto contour_5   = VALOR_detector;

// Get the min/max of our reference contour so we can draw the fram with the right height 
double max_y = contour_ref->GetHistogram()->GetMaximum();
double min_y = contour_ref->GetHistogram()->GetMinimum();
std::cout << max_y << "   " << min_y << std::endl;
TCanvas * c = new TCanvas("c","",20,20,900,900);
c->Draw();

TH2F * h = (TH2F*)c->DrawFrame(0.9,0.031,2,100);  //nue app
//TH2F * h = (TH2F*)c->DrawFrame(0.5,0.49,4,100);  //nue disapp
h->Draw();
//c->SetLogx();
c->SetLogy();
h->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}/sin^{2}2#theta_{#mue, REF}");
//h->GetXaxis()->SetTitle("sin^{2}2#theta_{ee}/sin^{2}2#theta_{ee, REF}");
h->GetXaxis()->SetTitleOffset(1.2);
h->GetXaxis()->SetTitleSize(0.03);
h->GetXaxis()->SetLabelSize(0.03);
h->GetYaxis()->SetTitle("#Deltam^{2}_{41} (eV^{2})");
h->GetYaxis()->SetTitleSize(0.03);
h->GetYaxis()->SetLabelSize(0.03);

int ref_points = contour_ref->GetN();

double Xvalue_ref       [ref_points];
double Xvalue_ref_ratio [ref_points];
double Yvalue_ref       [ref_points];
double Xvalue_1         [ref_points];
double Xvalue_1_ratio   [ref_points];
double Xvalue_2         [ref_points];
double Xvalue_2_ratio   [ref_points];
double Xvalue_3         [ref_points];
double Xvalue_3_ratio   [ref_points];
double Xvalue_4         [ref_points];
double Xvalue_4_ratio   [ref_points];
double Xvalue_5         [ref_points];
double Xvalue_5_ratio   [ref_points];

TGraph inv_1(contour_1->GetN(), contour_1->GetY(), contour_1->GetX());
TGraph inv_2(contour_2->GetN(), contour_2->GetY(), contour_2->GetX());
TGraph inv_3(contour_3->GetN(), contour_3->GetY(), contour_3->GetX());
TGraph inv_4(contour_4->GetN(), contour_4->GetY(), contour_4->GetX());
//TGraph inv_5(contour_5->GetN(), contour_5->GetY(), contour_5->GetX());

for(int i = 0; i < ref_points; i++){
    std::cout << contour_ref->GetX()[i] << "   " << contour_ref->GetY()[i] << std::endl;
    Xvalue_ref[i] = contour_ref->GetX()[i];
    Yvalue_ref[i] = contour_ref->GetY()[i];

    Xvalue_1[i] = inv_1.Eval(contour_ref->GetY()[i]);
    Xvalue_2[i] = inv_2.Eval(contour_ref->GetY()[i]);
    Xvalue_3[i] = inv_3.Eval(contour_ref->GetY()[i]);
    Xvalue_4[i] = inv_4.Eval(contour_ref->GetY()[i]);
    //Xvalue_5[i] = inv_5.Eval(contour_ref->GetY()[i]);

    Xvalue_ref_ratio[i] = Xvalue_ref[i] / Xvalue_ref[i];
    Xvalue_1_ratio[i] = Xvalue_1[i] / Xvalue_ref[i];
    Xvalue_2_ratio[i] = Xvalue_2[i] / Xvalue_ref[i];
    Xvalue_3_ratio[i] = Xvalue_3[i] / Xvalue_ref[i];
    Xvalue_4_ratio[i] = Xvalue_4[i] / Xvalue_ref[i];
    //Xvalue_5_ratio[i] = Xvalue_5[i] / Xvalue_ref[i];
}

TGraph *gref = new TGraph(ref_points, Xvalue_ref_ratio, Yvalue_ref);
TGraph *g1 = new TGraph(ref_points, Xvalue_1_ratio, Yvalue_ref);
TGraph *g2 = new TGraph(ref_points, Xvalue_2_ratio, Yvalue_ref);
TGraph *g3 = new TGraph(ref_points, Xvalue_3_ratio, Yvalue_ref);
TGraph *g4 = new TGraph(ref_points, Xvalue_4_ratio, Yvalue_ref);
//TGraph *g5 = new TGraph(ref_points, Xvalue_5_ratio, Yvalue_ref);

gref->SetLineColor(kBlack);
gref->SetLineWidth(4);
gref->Draw("l");

g1->SetLineColor(kAzure+1);
g1->SetLineWidth(4);
g1->Draw("l");

g2->SetLineColor(kRed+1);
g2->SetLineWidth(4);
g2->Draw("l");

g3->SetLineColor(kOrange+1);
g3->SetLineWidth(4);
g3->Draw("l");

g4->SetLineColor(kGreen+1);
g4->SetLineWidth(4);
g4->Draw("l");

//g5->SetLineColor(kMagenta);
//g5->SetLineWidth(4);
//g5->Draw("l");


TLegend * lnue_ratio = new TLegend(0.47,0.2,0.6,0.4);
lnue_ratio->SetFillStyle(0);
lnue_ratio->SetBorderSize(0);
lnue_ratio->SetTextFont(132);
lnue_ratio->SetTextSize(0.025);
lnue_ratio->AddEntry(gref, "Reference Value 5#sigma stat-only","L");
lnue_ratio->AddEntry(g1 , "5#sigma f_{M_{V}^{CCRes}}","L");
lnue_ratio->AddEntry(g2 , "5#sigma f_{M_{A}^{CCRes}}","L");
lnue_ratio->AddEntry(g3 , "5#sigma f_{R_{#pi}^{CEx}}","L");
lnue_ratio->AddEntry(g4 , "5#sigma f_{expskin}","L");
//lnue_ratio->AddEntry(g5 , "5#sigma detector syst","L");
lnue_ratio->Draw();

}














