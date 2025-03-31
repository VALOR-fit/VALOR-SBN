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
void plot_contours(
  const char *file_stat1,
  const char *file_stat2,
  const char *file_syst1,
  const char *file_syst2,
  const char *name_1,
  const char *name_2,
  const char *osc_channel
) {
/************************
 original prism files:
 numu:
  prism:
   03c1:
    /pnfs/sbnd/persistent/users/bslater/valor/prism/sbndonly03c1/output_contours_as_graphs.root
   stat:
    /pnfs/sbnd/persistent/users/bslater/valor/prism/sbndonlystat/output_contours_as_graphs.root 
  standard:
   03c1:
    /sbnd/app/users/bslater/valor/prism/contours/numu_disap/output_contours_as_graphs_sbnd_only_standard_03c1.root
   stat:
    /sbnd/app/users/bslater/valor/prism/contours/numu_disap/output_contours_as_graphs_sbnd_only_standard_stat.root
//  TFile *f_sbn03c1 = new TFile("/pnfs/sbnd/persistent/users/kroupa/valor_prism/prism_1_2020a1_03c1_1_standard_newDSTs/output_contours_as_graphs.root","read"); //sbn prism output tereza 03c1

  nue_app:
  TFile *f_sbndonly03c1 = new TFile("/sbnd/app/users/bslater/valor/prism/contours/nue_app/output_contours_as_graphs_prism_03c1_with_mec.root","read"); //sbnd only prism output 03c1
  TFile *f_sbndonlystandard03d1 = new TFile("/sbnd/app/users/bslater/valor/prism/contours/nue_app/output_contours_as_graphs_nue_app_03d1_sbnd.root","read"); //sbnd only prism output 03c1
  TFile *f_sbndonlystat = new TFile("/sbnd/app/users/bslater/valor/prism/contours/nue_app/output_contours_as_graphs_prism_stat_3.root","read"); //sbnd only prism output stat
  TFile *f_sbndonlystandardstat = new TFile("/sbnd/app/users/bslater/valor/prism/contours/nue_app/output_contours_as_graphs_nue_app_stat_sbnd.root","read"); //standard analysis sbnd only stat

  nue_disapp:
  TFile *f_sbndonly03c1 = new TFile("/sbnd/app/users/bslater/valor/prism/contours/nue_disapp/output_contours_as_graphs_prism_03c1.root","read"); //sbnd only prism output 03c1
  TFile *f_sbndonlystandard03d1 = new TFile("/sbnd/app/users/bslater/valor/prism/contours/nue_disapp/output_contours_as_graphs_standard_03d1.root","read"); //sbnd only prism output 03c1
  TFile *f_sbndonlystat = new TFile("/sbnd/app/users/bslater/valor/prism/contours/nue_disapp/output_contours_as_graphs_prism_stat.root","read"); //sbnd only prism output stat
  TFile *f_sbndonlystandardstat = new TFile("/sbnd/app/users/bslater/valor/prism/contours/nue_disapp/output_contours_as_graphs_standard_stat.root","read"); //standard analysis sbnd only stat

 ************************/  
//1 and 2 to allow for comparison (different prisms or prism vs standard etc)
  string stat1_exists = strstr(file_stat1, "blank");
  string stat2_exists = strstr(file_stat2, "blank");
  string syst1_exists = strstr(file_syst1, "blank");
  string syst2_exists = strstr(file_syst2, "blank");

  std::string n1; 
  std::string n2;
  if(name_1){
    n1=name_1;
  } 
  if(name_2){
    n2=name_2;
  }
 
  std::string osc = osc_channel;
  //get files and contours (5sigma)
  /* Check names in .root file
       contour_90pct_lin_0, contour_3sigma_lin_0, contour_5sigma_lin_0
  */
  TFile *f_stat1;
  TFile *f_stat2;
  TFile *f_syst1;
  TFile *f_syst2;
  TGraph *c5_stat1; 
  TGraph *c5_stat2; 
  TGraph *c5_syst1; 
  TGraph *c5_syst2; 
  if(stat1_exists != NULL){
    f_stat1 = new TFile(file_stat1,"read");
    //c5_stat1 = (TGraph*) f_stat1->Get("contour_5sigma_lin_0"); 
    c5_stat1 = (TGraph*) f_stat1->Get("stat_only_5sigma_lin_0"); 
  }
  if(stat2_exists != NULL){
    f_stat2 = new TFile(file_stat2,"read");
    c5_stat2 = (TGraph*) f_stat2->Get("contour_5sigma_lin_0"); 
  }
  if(syst1_exists != NULL){
    f_syst1 = new TFile(file_syst1,"read");
    //c5_syst1 = (TGraph*) f_syst1->Get("contour_5sigma_lin_0"); 
    c5_syst1 = (TGraph*) f_syst1->Get("stat_syst_5sigma_lin_0"); 
  }
  if(syst2_exists != NULL){
    f_syst2 = new TFile(file_syst2,"read");
    c5_syst2 = (TGraph*) f_syst2->Get("contour_5sigma_lin_0"); 
  }

  gStyle->SetOptLogz();
  if(stat1_exists != NULL){
    //statonly contour canvas
    TCanvas *c_stat = new TCanvas("c_stat","c_stat");
    c_stat->SetRightMargin(0.08);
    c_stat->SetLeftMargin(0.12);
    c_stat->SetTopMargin(0.08);
    c_stat->SetBottomMargin(0.12);
    c_stat->SetLogx();
    c_stat->SetLogy();
    
    // Add legend
    TLegend *l_stat = new TLegend(0.15,0.15,0.55,0.45);
    l_stat->SetTextSize(0.03);
    l_stat->SetTextFont(132);
    l_stat->SetTextColor(1);
    l_stat->SetFillStyle(0);
    l_stat->SetLineWidth(0);
    l_stat->AddEntry(c5_stat1,("5#sigma "+n1+" stat-only").c_str(),"L");
    if(stat2_exists != NULL){
      l_stat->AddEntry(c5_stat2,("5#sigma "+n2+" stat-only").c_str(),"L");
    }
      
    // Draw contours
    c5_stat1->Draw();
    //set x axis title and limits
    if(osc == "mumu"){ 
      c5_stat1->GetXaxis()->SetTitle("sin^{2}#theta_{#mu#mu}");
      c5_stat1->GetXaxis()->SetLimits(0.001,1);
    }else if(osc == "mue"){
      c5_stat1->GetXaxis()->SetTitle("(sin^{2}2#theta_{#mue})");
      c5_stat1->GetXaxis()->SetLimits(0.000015,1);
    }else if(osc == "ee"){
      c5_stat1->GetXaxis()->SetTitle("(sin^{2}2#theta_{ee})");
      c5_stat1->GetXaxis()->SetLimits(0.01,1);
    }else{
      std::cerr << "Did not recognise input sample. Stopping" << std::endl;
      exit(1);
    }

    c5_stat1->GetYaxis()->SetTitle("#Delta m^{2}_{41}");
    c5_stat1->GetXaxis()->SetTitleFont(132);
    c5_stat1->GetYaxis()->SetTitleFont(132);
    c5_stat1->GetXaxis()->SetTitleSize(0.05);
    c5_stat1->GetYaxis()->SetTitleSize(0.05);
    c5_stat1->GetXaxis()->SetTitleOffset(0.9);
    c5_stat1->GetYaxis()->SetTitleOffset(0.9);
    c5_stat1->GetXaxis()->SetLabelFont(132);
    c5_stat1->GetYaxis()->SetLabelFont(132);
    c5_stat1->GetYaxis()->SetRangeUser(0.01,100);
    
    c5_stat1->SetMarkerStyle(0);
    c5_stat1->SetLineWidth(2);
    c5_stat1->SetLineColor(kAzure-4);
    c5_stat1->Draw("same");
    
    if(stat2_exists != NULL){
      c5_stat2->SetMarkerStyle(0);
      c5_stat2->SetLineWidth(2);
      c5_stat2->SetLineStyle(7);
      c5_stat2->SetLineColor(kViolet-4);
      c5_stat2->Draw("same");
    }
  
    l_stat->Draw("same");

    if(stat2_exists != NULL){
      c_stat->SaveAs(("5sigma_"+n1+"_and_"+n2+"_stat_only.pdf").c_str());
    }else{
      c_stat->SaveAs(("5sigma_"+n1+"_stat_only.pdf").c_str());
    }
  }

  //syst
  if(file_syst1){
    TCanvas *c_syst = new TCanvas("c_syst","c_syst");
    c_syst->SetRightMargin(0.08);
    c_syst->SetLeftMargin(0.12);
    c_syst->SetTopMargin(0.08);
    c_syst->SetBottomMargin(0.12);
    c_syst->SetLogx();
    c_syst->SetLogy();

    // Add legend
    TLegend *l_syst = new TLegend(0.15,0.15,0.55,0.45);
    l_syst->SetTextSize(0.03);
    l_syst->SetTextFont(132);
    l_syst->SetTextColor(1);
    l_syst->SetFillStyle(0);
    l_syst->SetLineWidth(0);
    l_syst->AddEntry(c5_syst1,("5#sigma "+n1+" stat+syst").c_str(),"L");
    if(file_syst2){
      l_syst->AddEntry(c5_syst2,("5#sigma "+n2+" stat+syst").c_str(),"L");
    }
    
    // Draw contours
    c5_syst1->Draw();
    //set x axis title and limits
    if(osc == "mumu"){
      c5_syst1->GetXaxis()->SetTitle("sin^{2}#theta_{#mu#mu}");
      c5_syst1->GetXaxis()->SetLimits(0.001,1);
    }else if(osc == "mue"){
      c5_syst1->GetXaxis()->SetTitle("(sin^{2}2#theta_{#mue})");
      c5_syst1->GetXaxis()->SetLimits(0.000015,1);
    }else if(osc == "ee"){
      c5_syst1->GetXaxis()->SetTitle("(sin^{2}2#theta_{ee})");
      c5_syst1->GetXaxis()->SetLimits(0.01,1);
    }else{
      std::cerr << "Did not recognise input sample. Stopping" << std::endl;
      exit(1);
    }

    c5_syst1->GetYaxis()->SetTitle("#Delta m^{2}_{41}");
    c5_syst1->GetXaxis()->SetTitleFont(132);
    c5_syst1->GetYaxis()->SetTitleFont(132);
    c5_syst1->GetXaxis()->SetTitleSize(0.05);
    c5_syst1->GetYaxis()->SetTitleSize(0.05);
    c5_syst1->GetXaxis()->SetTitleOffset(0.9);
    c5_syst1->GetYaxis()->SetTitleOffset(0.9);
    c5_syst1->GetXaxis()->SetLabelFont(132);
    c5_syst1->GetYaxis()->SetLabelFont(132);
    c5_syst1->GetYaxis()->SetRangeUser(0.01,100);

    c5_syst1->SetMarkerStyle(0);
    c5_syst1->SetLineWidth(2);
    c5_syst1->SetLineColor(kAzure-4);
    c5_syst1->Draw("same");
    if(file_syst2){
      c5_syst2->SetMarkerStyle(0);
      c5_syst2->SetLineWidth(2);
      c5_syst2->SetLineColor(kViolet-4);
      c5_syst2->Draw("same");
    }

    l_syst->Draw("same");
    if(file_syst2){
      c_syst->SaveAs(("5sigma_"+n1+"_and_"+n2+"_statsyst_only.pdf").c_str());
    }else{
      c_syst->SaveAs(("5sigma_"+n1+"_statsyst_only.pdf").c_str());
    }

  }

//stat only and 03c1 5sigma
  if(file_stat1 && file_syst1){
    TCanvas *c_both = new TCanvas("c_both","c_both");
    c_both->SetRightMargin(0.08);
    c_both->SetLeftMargin(0.12);
    c_both->SetTopMargin(0.08);
    c_both->SetBottomMargin(0.12);
    c_both->SetLogx();
    c_both->SetLogy();
    
    // Add legend
    TLegend *l_both = new TLegend(0.15,0.15,0.55,0.45);
    l_both->SetTextSize(0.03);
    l_both->SetTextFont(132);
    l_both->SetTextColor(1);
    l_both->SetFillStyle(0);
    l_both->SetLineWidth(0);
    l_both->AddEntry(c5_stat1,("5#sigma "+n1+" stat-only").c_str(),"L");
    if(file_stat2){
      l_both->AddEntry(c5_stat2,("5#sigma "+n2+" stat-only").c_str(),"L");
    }
    l_both->AddEntry(c5_syst1,("5#sigma "+n1+" stat+syst").c_str(),"L");
    if(file_syst2){
      l_both->AddEntry(c5_syst2,("5#sigma "+n2+" stat+syst").c_str(),"L");
    }

    // Draw contours
    c5_syst1->Draw();
    //set x axis title and limits
    if(osc == "mumu"){
      c5_syst1->GetXaxis()->SetTitle("sin^{2}#theta_{#mu#mu}");
      c5_syst1->GetXaxis()->SetLimits(0.001,1);
    }else if(osc == "mue"){
      c5_syst1->GetXaxis()->SetTitle("(sin^{2}2#theta_{#mue})");
      c5_syst1->GetXaxis()->SetLimits(0.000015,1);
    }else if(osc == "ee"){
      c5_syst1->GetXaxis()->SetTitle("(sin^{2}2#theta_{ee})");
      c5_syst1->GetXaxis()->SetLimits(0.01,1);
    }else{
      std::cerr << "Did not recognise input sample. Stopping" << std::endl;
      exit(1);
    }

    c5_syst1->GetYaxis()->SetTitle("#Delta m^{2}_{41}");
    c5_syst1->GetXaxis()->SetTitleFont(132);
    c5_syst1->GetYaxis()->SetTitleFont(132);
    c5_syst1->GetXaxis()->SetTitleSize(0.05);
    c5_syst1->GetYaxis()->SetTitleSize(0.05);
    c5_syst1->GetXaxis()->SetTitleOffset(0.9);
    c5_syst1->GetYaxis()->SetTitleOffset(0.9);
    c5_syst1->GetXaxis()->SetLabelFont(132);
    c5_syst1->GetYaxis()->SetLabelFont(132);
    c5_syst1->GetYaxis()->SetRangeUser(0.01,100);

    c5_syst1->SetMarkerStyle(0);
    c5_syst1->SetLineWidth(2);
    c5_syst1->SetLineColor(kAzure-4);
    c5_syst1->Draw("same");
    if(file_syst2){
      c5_syst2->SetMarkerStyle(0);
      c5_syst2->SetLineWidth(2);
      c5_syst2->SetLineColor(kViolet-4);
      c5_syst2->Draw("same");
    }

    c5_stat1->SetMarkerStyle(0);
    c5_stat1->SetLineWidth(2);
    c5_stat1->SetLineStyle(7);
    c5_stat1->SetLineColor(kAzure-4);
    c5_stat1->Draw("same");

    if(file_stat2){
      c5_stat2->SetMarkerStyle(0);
      c5_stat2->SetLineWidth(2);
      c5_stat2->SetLineStyle(7);
      c5_stat2->SetLineColor(kViolet-4);
      c5_stat2->Draw("same");
    }

    l_both->Draw("same");
    if(file_stat2 && file_syst2){
      c_both->SaveAs(("5sigma_"+n1+"_and_"+n2+"_stat_statsyst.pdf").c_str());
    }else{
      c_both->SaveAs(("5sigma_"+n1+"_stat_statsyst.pdf").c_str());
    }

  }
}
