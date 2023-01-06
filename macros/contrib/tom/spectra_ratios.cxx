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
 
void spectra_ratios(){
// get files
TFile*fspectra_nom   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/spectra/fixed_dirt_cosmic/nue_nominal.root","read");
TFile*fspectra_1   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/spectra/fixed_dirt_cosmic/nue_disapp_dmsq1_sinsq0.29.root","read");
TFile*fspectra_2   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/spectra/fixed_dirt_cosmic/nue_disapp_dmsq3_sinsq0.4.root","read");
TFile*fspectra_3   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/spectra/fixed_dirt_cosmic/nue_disapp_dmsq100_sinsq0.085.root","read");

//-----------------------------------------------------------------------------------------------

// SBND
TH1D *h_nom_sbnd   = (TH1D*) fspectra_nom->Get("valor_pdft_sb_rf_sbn_nd__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_1_sbnd     = (TH1D*) fspectra_1->Get("valor_pdft_sb_rf_sbn_nd__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_2_sbnd     = (TH1D*) fspectra_2->Get("valor_pdft_sb_rf_sbn_nd__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_3_sbnd     = (TH1D*) fspectra_3->Get("valor_pdft_sb_rf_sbn_nd__BNB_FHC__nuelikeCChigh_Ereco;1");

// ub 
TH1D *h_nom_ub     = (TH1D*) fspectra_nom->Get("valor_pdft_sb_rf_sbn_uboone__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_1_ub       = (TH1D*) fspectra_1->Get("valor_pdft_sb_rf_sbn_uboone__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_2_ub       = (TH1D*) fspectra_2->Get("valor_pdft_sb_rf_sbn_uboone__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_3_ub       = (TH1D*) fspectra_3->Get("valor_pdft_sb_rf_sbn_uboone__BNB_FHC__nuelikeCChigh_Ereco;1");

// ICARUS
TH1D *h_nom_icarus = (TH1D*) fspectra_nom->Get("valor_pdft_sb_rf_sbn_icarus__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_1_icarus   = (TH1D*) fspectra_1->Get("valor_pdft_sb_rf_sbn_icarus__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_2_icarus   = (TH1D*) fspectra_2->Get("valor_pdft_sb_rf_sbn_icarus__BNB_FHC__nuelikeCChigh_Ereco;1");
TH1D *h_3_icarus   = (TH1D*) fspectra_3->Get("valor_pdft_sb_rf_sbn_icarus__BNB_FHC__nuelikeCChigh_Ereco;1");

//-----------------------------------------------------------------------------------------------


TH1D *h_ref_sbnd = new TH1D(*h_nom_sbnd);
TH1D *h_ratio1_sbnd = new TH1D(*h_1_sbnd);
TH1D *h_ratio2_sbnd = new TH1D(*h_2_sbnd);
TH1D *h_ratio3_sbnd = new TH1D(*h_3_sbnd);
h_ref_sbnd->Divide(h_nom_sbnd);
h_ratio1_sbnd->Divide(h_nom_sbnd);
h_ratio2_sbnd->Divide(h_nom_sbnd);
h_ratio3_sbnd->Divide(h_nom_sbnd);

TH1D *h_ref_ub = new TH1D(*h_nom_ub);
TH1D *h_ratio1_ub = new TH1D(*h_1_ub);
TH1D *h_ratio2_ub = new TH1D(*h_2_ub);
TH1D *h_ratio3_ub = new TH1D(*h_3_ub);
h_ref_ub->Divide(h_nom_ub);
h_ratio1_ub->Divide(h_nom_ub);
h_ratio2_ub->Divide(h_nom_ub);
h_ratio3_ub->Divide(h_nom_ub);

TH1D *h_ref_icarus = new TH1D(*h_nom_icarus);
TH1D *h_ratio1_icarus = new TH1D(*h_1_icarus);
TH1D *h_ratio2_icarus = new TH1D(*h_2_icarus);
TH1D *h_ratio3_icarus = new TH1D(*h_3_icarus);
h_ref_icarus->Divide(h_nom_icarus);
h_ratio1_icarus->Divide(h_nom_icarus);
h_ratio2_icarus->Divide(h_nom_icarus);
h_ratio3_icarus->Divide(h_nom_icarus);

TCanvas * c_sbnd = new TCanvas("c_sbnd","",20,20,900,900);
c_sbnd->Draw();

//TH1D * h_sbnd = (TH1D*)c_sbnd->DrawFrame(0,0.9,2.999,1.6); //nue app
TH1D * h_sbnd = (TH1D*)c_sbnd->DrawFrame(0,0.4,2.999,1.1); // nue disapp
h_sbnd->GetXaxis()->SetTitle("E_{#nu} Reco [GeV]");
h_sbnd->GetXaxis()->SetTitleOffset(1.2);
h_sbnd->GetXaxis()->SetTitleSize(0.03);
h_sbnd->GetXaxis()->SetLabelSize(0.03);
h_sbnd->GetYaxis()->SetTitle("Osc spectrum / Nom spectrum");
h_sbnd->GetYaxis()->SetTitleSize(0.03);
h_sbnd->GetYaxis()->SetLabelSize(0.03);
h_sbnd->Draw();

h_ref_sbnd->SetLineWidth(4);
h_ref_sbnd->SetLineStyle(3);
h_ref_sbnd->SetLineColor(kBlack);

h_ratio1_sbnd->SetLineWidth(4);
h_ratio1_sbnd->SetLineColor(kAzure+1);

h_ratio2_sbnd->SetLineWidth(4);
h_ratio2_sbnd->SetLineColor(kGreen+1);

h_ratio3_sbnd->SetLineWidth(4);
h_ratio3_sbnd->SetLineColor(kMagenta);

h_ref_sbnd->Draw("same");
h_ratio1_sbnd->Draw("same");
h_ratio2_sbnd->Draw("same");
h_ratio3_sbnd->Draw("same");

//TLegend * l_sbnd = new TLegend(0.4,0.7,0.8,0.9); //nue app
TLegend * l_sbnd = new TLegend(0.4,0.15,0.8,0.35); //nue disapp
l_sbnd->SetFillStyle(0);
l_sbnd->SetBorderSize(0);
l_sbnd->SetTextFont(132);
l_sbnd->SetTextSize(0.025);
l_sbnd->SetHeader("SBND","C");
l_sbnd->AddEntry(h_ref_sbnd   , "#nu_{e} Nominal Spectrum","L");
//l_sbnd->AddEntry(h_ratio1_sbnd, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0014, #Deltam^{2}_{41} = 1 eV^{2}","L");
//l_sbnd->AddEntry(h_ratio2_sbnd, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0030, #Deltam^{2}_{41} = 1.32 eV^{2}","L");
//l_sbnd->AddEntry(h_ratio3_sbnd, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0005, #Deltam^{2}_{41} = 100 eV^{2}","L");
l_sbnd->AddEntry(h_ratio1_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.290, #Deltam^{2}_{41} = 1 eV^{2}","L");
l_sbnd->AddEntry(h_ratio2_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.400, #Deltam^{2}_{41} = 3 eV^{2}","L");
l_sbnd->AddEntry(h_ratio3_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.085, #Deltam^{2}_{41} = 100 eV^{2}","L");

l_sbnd->Draw();

TCanvas * c_ub = new TCanvas("c_ub","",20,20,900,900);
c_ub->Draw();

//TH1D * h_ub = (TH1D*)c_ub->DrawFrame(0,0.9,2.999,1.6);
TH1D * h_ub = (TH1D*)c_ub->DrawFrame(0,0.4,2.999,1.1); // nue disapp
h_ub->GetXaxis()->SetTitle("E_{#nu} Reco [GeV]");
h_ub->GetXaxis()->SetTitleOffset(1.2);
h_ub->GetXaxis()->SetTitleSize(0.03);
h_ub->GetXaxis()->SetLabelSize(0.03);
h_ub->GetYaxis()->SetTitle("Osc spectrum / Nom spectrum");
h_ub->GetYaxis()->SetTitleSize(0.03);
h_ub->GetYaxis()->SetLabelSize(0.03);
h_ub->Draw();

h_ref_ub->SetLineWidth(4);
h_ref_ub->SetLineStyle(3);
h_ref_ub->SetLineColor(kBlack);

h_ratio1_ub->SetLineWidth(4);
h_ratio1_ub->SetLineColor(kAzure+1);

h_ratio2_ub->SetLineWidth(4);
h_ratio2_ub->SetLineColor(kGreen+1);

h_ratio3_ub->SetLineWidth(4);
h_ratio3_ub->SetLineColor(kMagenta);

h_ref_ub->Draw("same");
h_ratio1_ub->Draw("same");
h_ratio2_ub->Draw("same");
h_ratio3_ub->Draw("same");

//TLegend * l_ub = new TLegend(0.4,0.7,0.8,0.9);
TLegend * l_ub = new TLegend(0.4,0.15,0.8,0.35); //nue disapp
l_ub->SetFillStyle(0);
l_ub->SetBorderSize(0);
l_ub->SetTextFont(132);
l_ub->SetTextSize(0.025);
l_ub->SetHeader("#muBooNE","C");
l_ub->AddEntry(h_ref_ub   , "#nu_{e} Nominal Spectrum","L");
//l_ub->AddEntry(h_ratio1_ub, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0014, #Deltam^{2}_{41} = 1 eV^{2}","L");
//l_ub->AddEntry(h_ratio2_ub, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0030, #Deltam^{2}_{41} = 1.32 eV^{2}","L");
//l_ub->AddEntry(h_ratio3_ub, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0005, #Deltam^{2}_{41} = 100 eV^{2}","L");
l_ub->AddEntry(h_ratio1_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.290, #Deltam^{2}_{41} = 1 eV^{2}","L");
l_ub->AddEntry(h_ratio2_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.400, #Deltam^{2}_{41} = 3 eV^{2}","L");
l_ub->AddEntry(h_ratio3_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.085, #Deltam^{2}_{41} = 100 eV^{2}","L");
l_ub->Draw();

TCanvas * c_icarus = new TCanvas("c_icarus","",20,20,900,900);
c_icarus->Draw();

//TH1D * h_icarus = (TH1D*)c_icarus->DrawFrame(0,0.9,2.999,1.6);
TH1D * h_icarus = (TH1D*)c_icarus->DrawFrame(0,0.4,2.999,1.1); // nue disapp
h_icarus->GetXaxis()->SetTitle("E_{#nu} Reco [GeV]");
h_icarus->GetXaxis()->SetTitleOffset(1.2);
h_icarus->GetXaxis()->SetTitleSize(0.03);
h_icarus->GetXaxis()->SetLabelSize(0.03);
h_icarus->GetYaxis()->SetTitle("Osc spectrum / Nom spectrum");
h_icarus->GetYaxis()->SetTitleSize(0.03);
h_icarus->GetYaxis()->SetLabelSize(0.03);
h_icarus->Draw();

h_ref_icarus->SetLineWidth(4);
h_ref_icarus->SetLineStyle(3);
h_ref_icarus->SetLineColor(kBlack);

h_ratio1_icarus->SetLineWidth(4);
h_ratio1_icarus->SetLineColor(kAzure+1);

h_ratio2_icarus->SetLineWidth(4);
h_ratio2_icarus->SetLineColor(kGreen+1);

h_ratio3_icarus->SetLineWidth(4);
h_ratio3_icarus->SetLineColor(kMagenta);

h_ref_icarus->Draw("same");
h_ratio1_icarus->Draw("same");
h_ratio2_icarus->Draw("same");
h_ratio3_icarus->Draw("same");

//TLegend * l_icarus = new TLegend(0.4,0.7,0.8,0.9);
TLegend * l_icarus = new TLegend(0.4,0.15,0.8,0.35); //nue disapp
l_icarus->SetFillStyle(0);
l_icarus->SetBorderSize(0);
l_icarus->SetTextFont(132);
l_icarus->SetTextSize(0.025);
l_icarus->SetHeader("ICARUS","C");
l_icarus->AddEntry(h_ref_icarus   , "#nu_{e} Nominal Spectrum","L");
//l_icarus->AddEntry(h_ratio1_icarus, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0014, #Deltam^{2}_{41} = 1 eV^{2}","L");
//l_icarus->AddEntry(h_ratio2_icarus, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0030, #Deltam^{2}_{41} = 1.32 eV^{2}","L");
//l_icarus->AddEntry(h_ratio3_icarus, "#nu_{e} app sin^{2}2#theta_{#mue} = 0.0005, #Deltam^{2}_{41} = 100 eV^{2}","L");
l_icarus->AddEntry(h_ratio1_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.290, #Deltam^{2}_{41} = 1 eV^{2}","L");
l_icarus->AddEntry(h_ratio2_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.400, #Deltam^{2}_{41} = 3 eV^{2}","L");
l_icarus->AddEntry(h_ratio3_sbnd, "#nu_{e} disapp sin^{2}2#theta_{#mue} = 0.085, #Deltam^{2}_{41} = 100 eV^{2}","L");
l_icarus->Draw();



}






