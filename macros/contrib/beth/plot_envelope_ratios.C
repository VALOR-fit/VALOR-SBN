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

std::vector<TH1D*> prismAverage(const char *file_name, const int n_bins) {

  std::vector<TH1D*> averaged_histograms;

  int nbins = n_bins;
  TFile *file = new TFile(file_name,"read");
  if (!file || file->IsZombie()) {
    std::cerr << "Error: Unable to open file " << file_name << std::endl;
    return averaged_histograms; // Return an empty vector
  }
  TH1D * nom_av= static_cast<TH1D*>(file->Get("env_sb_BNB_FHC_numuCCinclOA00_nom"));
  TH1D * p1_av  = static_cast<TH1D*>(file->Get("env_sb_BNB_FHC_numuCCinclOA00_p1"));
  TH1D * m1_av  = static_cast<TH1D*>(file->Get("env_sb_BNB_FHC_numuCCinclOA00_m1"));
  if (!nom_av || !p1_av || !m1_av) {
      std::cerr << "Error: Unable to retrieve reference histograms." << std::endl;
      delete file; // Close the file
      return averaged_histograms; // Return an empty vector
  }
  // make scale factor array (ER0X/ER_Tot)
  double er[nbins];
  //std::cout<<"nbins = "<<nbins<<std::endl;
  for(int i=0;i<nbins;i++){
    //std::cout<<"bin = "<<i<<std::endl;
    stringstream is;
    is << i;
    string bin = is.str();
    TH1D *nom = static_cast<TH1D*>(file->Get(("env_sb_BNB_FHC_numuCCinclOA0"+bin+"_nom").c_str()));
    for(int j=0; j<nom->GetXaxis()->GetNbins();j++){
      er[i] += nom->GetBinContent(j+1);
      //std::cout<<"er bin 0"<<i<<", hist bin "<<j<<" = "<<er[i]<<std::endl;
    }
  }
  double total_er = 0;
  for(int i = 0; i < nbins; i++){
    total_er += er[i];
  }
  //std::cout<<"total_er = " << total_er<<std::endl;
  double sf[nbins];
  for(int i = 0; i < nbins; i++){
    sf[i] = er[i]/total_er;
    //std::cout<<"sf "<<i<<" = "<<sf[i]<<std::endl;
  }
  //find frac histograms
  for(int i=0;i<nbins;i++){
    stringstream is;
    is << i;
    string bin = is.str();

    TH1D *nom = static_cast<TH1D*>(file->Get(("env_sb_BNB_FHC_numuCCinclOA0"+bin+"_nom").c_str()));
    TH1D *p1  = static_cast<TH1D*>(file->Get(("env_sb_BNB_FHC_numuCCinclOA0"+bin+"_p1").c_str()));
    TH1D *m1  = static_cast<TH1D*>(file->Get(("env_sb_BNB_FHC_numuCCinclOA0"+bin+"_m1").c_str()));
    if (!nom || !p1 || !m1) {
	std::cerr << "Error: Unable to retrieve histograms for bin " << i << std::endl;
	delete file; // Close the file
	return averaged_histograms; // Return an empty vector
    }
    std::cout << "Retrieved histograms for bin " << i << std::endl;
    //std::cout << "nom: " << nom->GetName() << ", p1: " << p1->GetName() << ", m1: " << m1->GetName() << std::endl;

    if (nom && p1 && m1){
      if(i==0){
	//p1_av->Add(nom,-1);
	//m1_av->Add(nom,-1);
	p1_av->Divide(nom);
	m1_av->Divide(nom);
	for(int j=0; j<nom->GetXaxis()->GetNbins();j++){
	  double nom_av_bin = nom_av->GetBinContent(j + 1) * sf[i];
	  nom_av->SetBinContent(j + 1, nom_av_bin);
	  double p1_av_bin = p1_av->GetBinContent(j + 1) * sf[i];
	  p1_av->SetBinContent(j + 1, p1_av_bin);
	  double m1_av_bin = m1_av->GetBinContent(j + 1) * sf[i];
	  m1_av->SetBinContent(j + 1, m1_av_bin);
	}
      } else {
	//p1->Add(nom,-1);
	//m1->Add(nom,-1);
	p1->Divide(nom);
	m1->Divide(nom);
	for(int j=0; j<nom->GetXaxis()->GetNbins();j++){
	  double nom_bin = nom->GetBinContent(j + 1) * sf[i];
	  nom->SetBinContent(j + 1, nom_bin);
	  double p1_bin = p1->GetBinContent(j + 1) * sf[i];
	  p1->SetBinContent(j + 1, p1_bin);
	  double m1_bin = m1->GetBinContent(j + 1) * sf[i];
	  m1->SetBinContent(j + 1, m1_bin);
	}
	nom_av->Add(nom);
	p1_av->Add(p1);
	m1_av->Add(m1);
      }
    } else std::cout << "nom , p1, or m2 not loaded properly"<<std::endl;
  }
  averaged_histograms.push_back(nom_av); //average nom
  averaged_histograms.push_back(p1_av); //average frac error p1
  averaged_histograms.push_back(m1_av); //average frac error m1

  return averaged_histograms;
}

void plot_envelope_ratios(
  const char *tweak_file_1,
  const char *tweak_file_2,
  const char *sample1,
  const char *sample2,
  const char *tag1,
  const char *tag2
){


  TCanvas * c = new TCanvas("c","",20,20,700,900);
  c->SetTopMargin(0.044);
  c->SetBottomMargin(0.1);
  c->SetLeftMargin(0.1);
  c->SetRightMargin(0.044);
  c->Draw();

  gStyle->SetTitleSize(0.04,"X");
  gStyle->SetTitleSize(0.04,"Y");
  gStyle->SetLabelSize(0.03,"X");
  gStyle->SetLabelSize(0.03,"Y");
  gStyle->SetOptStat(0);
  
  std::vector<TH1D*> hists1,hists2;
  /*if(std::string(tweak_file_1).find("prism3") != std::string::npos) hists1 = prismAverage(tweak_file_1,3);
  else if(std::string(tweak_file_1).find("prism5") != std::string::npos) hists1 = prismAverage(tweak_file_1,5);
  else if(std::string(tweak_file_1).find("prism8") != std::string::npos) hists1 = prismAverage(tweak_file_1,8);
  else{*/
    TFile *tweak1 = new TFile(tweak_file_1,"read");
    hists1.push_back(static_cast<TH1D*>(tweak1->Get(("env_sb_BNB_FHC_"+std::string(sample1)+"_nom").c_str())));
    //hists1.push_back(static_cast<TH1D*>(tweak1->Get(("env_sb_BNB_FHC_"+std::string(sample1)+"_p1").c_str())));
    //hists1.push_back(static_cast<TH1D*>(tweak1->Get(("env_sb_BNB_FHC_"+std::string(sample1)+"_m1").c_str())));
    TH1D* h_p1 = static_cast<TH1D*>(tweak1->Get(("env_sb_BNB_FHC_"+std::string(sample1)+"_p1").c_str()));
    TH1D* h_m1 = static_cast<TH1D*>(tweak1->Get(("env_sb_BNB_FHC_"+std::string(sample1)+"_m1").c_str()));
    //h_p1->Add(hists1[0],-1);
    h_p1->Divide(hists1[0]);
    //h_m1->Add(hists1[0],-1);
    h_m1->Divide(hists1[0]);
    hists1.push_back(h_p1);
    hists1.push_back(h_m1);
//  }
  if (hists1.size() == 3) std::cout << " Got histograms from file 1" << std::endl;
  else {
    std::cout << "Histograms not loaded correctly from tweak_file_1" << std::endl;
    return;
  }
 
  /*if(std::string(tweak_file_2).find("prism3") != std::string::npos) hists2 = prismAverage(tweak_file_2,3);
  else if(std::string(tweak_file_2).find("prism5") != std::string::npos) hists2 = prismAverage(tweak_file_2,5);
  else if(std::string(tweak_file_2).find("prism8") != std::string::npos) hists2 = prismAverage(tweak_file_2,8);
  else{*/
    TFile *tweak2 = new TFile(tweak_file_2, "read");
    hists2.push_back(static_cast<TH1D*>(tweak2->Get(("env_sb_BNB_FHC_"+std::string(sample2)+"_nom").c_str())));
    //TH1D* 
    h_p1 = static_cast<TH1D*>(tweak2->Get(("env_sb_BNB_FHC_"+std::string(sample2)+"_p1").c_str()));
    //TH1D* 
    h_m1 = static_cast<TH1D*>(tweak2->Get(("env_sb_BNB_FHC_"+std::string(sample2)+"_m1").c_str()));
    //h_p1->Add(hists2[0],-1);
    h_p1->Divide(hists2[0]);
    //h_m1->Add(hists2[0],-1);
    h_m1->Divide(hists2[0]);
    hists2.push_back(h_p1);
    hists2.push_back(h_m1);
//  }
  if (hists2.size() == 3) std::cout << " Got histograms from file 2" << std::endl;
  else {
    std::cout << "Histograms not loaded correctly from tweak_file_2" << std::endl;
    return;
  }

  
  if((std::string(tweak_file_1).find("pre") != std::string::npos && std::string(tweak_file_2).find("post") != std::string::npos) || (std::string(tweak_file_2).find("pre") != std::string::npos &&  std::string(tweak_file_1).find("post") != std::string::npos)){

    std::cout << "Given a prefit and a postfit tweaks file, will plot fractional 1 sigma errors using sample1 and tag1" << std::endl;

    std::string curr_tag = tag1;
    size_t pos = curr_tag.find("sbnd");
    while (pos != std::string::npos) {
	curr_tag.replace(pos, 4, "SBND");
	pos = curr_tag.find("sbnd", pos + 4); // Move to next occurrence
    }
    // Replace "_reduced_modes"
    pos = curr_tag.find("_reducedmodes");
    while (pos != std::string::npos) {
	curr_tag.replace(pos, 13, " reduced modes");
	pos = curr_tag.find("_reducedmodes", pos + 13); // Move to next occurrence
    }
    // Replace "_" with a space
    pos = curr_tag.find("_0");
    while (pos != std::string::npos) {
	curr_tag.replace(pos, 2, " 0");
	pos = curr_tag.find("_0", pos + 2); // Move to next occurrence
    }
    // Replace "_" with a space
    pos = curr_tag.find("_s");
    while (pos != std::string::npos) {
	curr_tag.replace(pos, 2, " s");
	pos = curr_tag.find("_s", pos + 2); // Move to next occurrence
    }
    // Replace "prism" with "PRISM"
    pos = curr_tag.find("prism");
    while (pos != std::string::npos) {
	curr_tag.replace(pos, 5, "PRISM");
	pos = curr_tag.find("prism", pos + 5); // Move to next occurrence
    }
    std::string sample = sample1;
    std::string tag = tag1;
    TH1D * h_pre_nom, *h_pre_p1, *h_pre_m1, *h_post_nom, *h_post_p1, *h_post_m1;
    if(std::string(tweak_file_1).find("pre") != std::string::npos){
      h_pre_nom = static_cast<TH1D*>(hists1[0]->Clone("h_pre_nom"));
      h_pre_p1 = static_cast<TH1D*>(hists1[1]->Clone("h_pre_p1"));
      h_pre_m1 = static_cast<TH1D*>(hists1[2]->Clone("h_pre_m1"));
      h_post_nom = static_cast<TH1D*>(hists2[0]->Clone("h_post_nom"));
      h_post_p1 = static_cast<TH1D*>(hists2[1]->Clone("h_post_p1"));
      h_post_m1 = static_cast<TH1D*>(hists2[2]->Clone("h_post_m1"));
    } else {
      h_pre_nom = static_cast<TH1D*>(hists2[0]->Clone("h_pre_nom"));
      h_pre_p1 = static_cast<TH1D*>(hists2[1]->Clone("h_pre_p1"));
      h_pre_m1 = static_cast<TH1D*>(hists2[2]->Clone("h_pre_m1"));
      h_post_nom = static_cast<TH1D*>(hists1[0]->Clone("h_post_nom"));
      h_post_p1 = static_cast<TH1D*>(hists1[1]->Clone("h_post_p1"));
      h_post_m1 = static_cast<TH1D*>(hists1[2]->Clone("h_post_m1"));
    }

    TH1D *h_frac_p1_post = static_cast<TH1D*>(h_post_p1->Clone("h_frac_p1_post"));
    TH1D *h_frac_p1_pre = static_cast<TH1D*>(h_pre_p1->Clone("h_frac_p1_pre"));
    TH1D *h_frac_m1_post = static_cast<TH1D*>(h_post_m1->Clone("h_frac_m1_post"));
    TH1D *h_frac_m1_pre = static_cast<TH1D*>(h_pre_m1->Clone("h_frac_m1_pre"));
    // Formatting
    h_frac_p1_post -> SetLineColor(kPink+5);
    h_frac_p1_post -> SetLineStyle(1);
    h_frac_p1_post -> SetLineWidth(2);
    h_frac_p1_post -> SetMarkerStyle(0);

    h_frac_m1_post -> SetLineColor(kPink+5);
    h_frac_m1_post -> SetLineStyle(1);
    h_frac_m1_post -> SetLineWidth(2);
    h_frac_m1_post -> SetMarkerStyle(0);

    h_frac_p1_pre -> SetLineColor(kOrange+1);
    h_frac_p1_pre -> SetLineStyle(7);
    h_frac_p1_pre -> SetLineWidth(2);
    h_frac_p1_pre -> SetMarkerStyle(0);

    h_frac_m1_pre -> SetLineColor(kOrange+1);
    h_frac_m1_pre -> SetLineStyle(7);
    h_frac_m1_pre -> SetLineWidth(2);
    h_frac_m1_pre -> SetMarkerStyle(0);

    // 
    // No stat all external all fitters 
    //

    TLatex *latex = new TLatex();
    latex->SetTextSize(0.04);
    latex->SetTextAlign(23);

    // Nominal ratio
    //h_frac_p1_post>SetStats(0);
    h_frac_p1_post->GetYaxis()->SetTitleOffset(1.3);
    h_frac_p1_post->GetXaxis()->SetRangeUser(0.2,3);
    h_frac_p1_post->GetYaxis()->SetRangeUser(0.4,1.4);
    //h_frac_p1_post->GetYaxis()->SetRangeUser(0.65,1.25);
    h_frac_p1_post->SetTitle("");
    h_frac_p1_post->GetXaxis()->SetTitle("E_{#nu, Reco}");
    //h_frac_p1_post->GetYaxis()->SetTitle("Ratio #pm1#sigma/nominal");
    h_frac_p1_post->GetYaxis()->SetTitle("Event Rate Ratio");
    h_frac_p1_post->GetXaxis()->SetTitleFont(132);
    h_frac_p1_post->GetYaxis()->SetTitleFont(132);
    h_frac_p1_post->GetXaxis()->SetLabelFont(132);
    h_frac_p1_post->GetYaxis()->SetLabelFont(132);
    h_frac_p1_post->GetYaxis()->SetMaxDigits(3);
    h_frac_p1_post->Draw("same");
    h_frac_m1_post->Draw("same");
    h_frac_p1_pre->Draw("same");
    h_frac_m1_pre->Draw("same");  

    TLegend * l = new TLegend(0.13,0.13,0.8,0.3);
    l->SetBorderSize(0);
    l->SetTextFont(132);
//    l->SetHeader(tag.c_str(),"C");
    l->AddEntry(h_frac_p1_pre, "Prefit", "L");// +1#sigma/nominal", "L");
    l->AddEntry(h_frac_p1_post, "Postfit", "L");// +1#sigma/nominal", "L");
   // l->AddEntry(h_frac_m1_post, "postfit -1#sigma/nominal", "L");
   // l->AddEntry(h_frac_m1_pre, "prefit -1#sigma/nominal", "L");
    l->Draw();

    //latex->DrawLatex(1.05, 0.818, curr_tag.c_str());
    latex->DrawLatex(1.05, 0.68, curr_tag.c_str()); //start x at 0.75 for short syst label
    latex->SetTextSize(0.06);
    //latex->DrawLatex(2.25, 0.78, "#frac{nom#pm1#sigma}{nom}");
    latex->DrawLatex(2.25, 0.6167, "#frac{nom#pm1#sigma}{nom}");

    const char* filename1 = "postfit_frac_error_hists.root";
    // Check if the file exists
    TFile *input_root_file1 = TFile::Open(filename1);
    if (input_root_file1 && !input_root_file1->IsZombie()) {
        std::cout << "File exists. Opening in UPDATE mode." << std::endl;
        // File exists, open in UPDATE mode
        input_root_file1->Close();
        input_root_file1 = TFile::Open(filename1, "UPDATE");
    } else {
        std::cout << "File does not exist. Creating a new one." << std::endl;
        // File does not exist, create a new one
        input_root_file1 = TFile::Open(filename1, "RECREATE");
    }

    if (!input_root_file1 || input_root_file1->IsZombie()) {
        std::cerr << "Error: Could not open or create input ROOT file." << std::endl;
    }else{
      h_frac_p1_post->SetName(("h_frac_postfit_p1_"+tag).c_str());
      h_frac_m1_post->SetName(("h_frac_postfit_m1_"+tag).c_str());
      h_frac_p1_post->Write();
      h_frac_m1_post->Write();
      input_root_file1->Close();
    }

    c->SaveAs(("frac_1sigma_pre_postfit_"+tag+"_"+sample+".pdf").c_str());
    c->SaveAs(("frac_1sigma_pre_postfit_"+tag+"_"+sample+".png").c_str());
    //c->SaveAs(("frac_1sigma_pre_postfit_"+tag+"_"+sample+"_zoom.pdf").c_str());
    //c->SaveAs(("frac_1sigma_pre_postfit_"+tag+"_"+sample+"_zoom.png").c_str());
    c->Clear();
    l->Clear();
    latex->Clear();


    TH1D * h_p1_ratio = static_cast<TH1D*>(h_frac_p1_post->Clone("h_p1_ratio"));
    h_p1_ratio->Divide(h_frac_p1_pre);
    TH1D * h_m1_ratio = static_cast<TH1D*>(h_frac_m1_post->Clone("h_m1_ratio"));
    h_m1_ratio->Divide(h_frac_m1_pre);

    h_p1_ratio -> SetLineColor(kPink+5);
    h_p1_ratio -> SetLineStyle(7);
    h_p1_ratio -> SetLineWidth(2);
    h_p1_ratio -> SetMarkerStyle(0);

    h_m1_ratio -> SetLineColor(kOrange+1);
    h_m1_ratio -> SetLineStyle(7);
    h_m1_ratio -> SetLineWidth(2);
    h_m1_ratio -> SetMarkerStyle(0);

    h_m1_ratio->SetStats(0);
    h_p1_ratio->GetYaxis()->SetTitleOffset(1.3);
    h_p1_ratio->GetXaxis()->SetRangeUser(0.2,3);
    h_p1_ratio->GetYaxis()->SetRangeUser(0.4,1.4);
    //h_p1_ratio->GetYaxis()->SetRangeUser(-0.95,0.75);
    h_p1_ratio->SetTitle("");
    h_p1_ratio->GetXaxis()->SetTitle("E_{#nu, Reco}");
    h_p1_ratio->GetYaxis()->SetTitle("Event Rate Ratio");
    h_p1_ratio->GetXaxis()->SetTitleFont(132);
    h_p1_ratio->GetYaxis()->SetTitleFont(132);
    h_p1_ratio->GetXaxis()->SetLabelFont(132);
    h_p1_ratio->GetYaxis()->SetLabelFont(132);
    h_p1_ratio->GetYaxis()->SetMaxDigits(3);

    h_p1_ratio -> Draw();
    h_m1_ratio -> Draw("same");

    TLegend * l2 = new TLegend(0.13,0.13,0.8,0.3);
    l2->SetTextSize(0.04);
    l2->SetBorderSize(0);
    l2->SetTextFont(132);
//    l2->SetHeader(tag.c_str(),"C");
    l2->AddEntry(h_p1_ratio, "+1#sigma", "L");
    l2->AddEntry(h_m1_ratio, "-1#sigma", "L");
    //l2->AddEntry(h_p1_ratio, "(postfit/prefit)_{+1#sigma/nominal}", "L");
    //l2->AddEntry(h_m1_ratio, "(postfit/prefit)_{-1#sigma/nominal}", "L");
    l2->Draw();
    latex->SetTextSize(0.04);
    latex->DrawLatex(0.75, 0.68, curr_tag.c_str());
    latex->SetTextSize(0.05);
    latex->DrawLatex(2.25, 0.65, "#frac{#frac{nom#pm1#sigma}{nom}#cbar_{postfit}}{#frac{nom#pm1#sigma}{nom}#cbar_{prefit}}");

    c->SaveAs(("double_ratios_postfit_prefit_"+tag+".pdf").c_str());
    c->SaveAs(("double_ratios_postfit_prefit_"+tag+".png").c_str());

    const char* filename = "postfit_prefit_histograms.root";
    // Check if the file exists
    TFile *input_root_file = TFile::Open(filename);
    if (input_root_file && !input_root_file->IsZombie()) {
        std::cout << "File exists. Opening in UPDATE mode." << std::endl;
        // File exists, open in UPDATE mode
        input_root_file->Close();
        input_root_file = TFile::Open(filename, "UPDATE");
    } else {
        std::cout << "File does not exist. Creating a new one." << std::endl;
        // File does not exist, create a new one
        input_root_file = TFile::Open(filename, "RECREATE");
    }

    if (!input_root_file || input_root_file->IsZombie()) {
        std::cerr << "Error: Could not open or create input ROOT file." << std::endl;
    }else{
      h_p1_ratio->SetName(("h_ratio_postfit_prefit_p1_"+tag).c_str());
      h_m1_ratio->SetName(("h_ratio_postfit_prefit_m1_"+tag).c_str());
      h_p1_ratio->Write();
      h_m1_ratio->Write();
      input_root_file->Close();
    }

  }/*else if(std::string(tweak_file_1).find("post") != std::string::npos && std::string(tweak_file_2).find("post") != std::string::npos){

    std::cout << "Given 2 postfit tweaks files, will plot double ratio" << std::endl;

  //  TFile *f_1 = new TFile(tweak_file_1,"read");
   // TFile *f_2 = new TFile(tweak_file_2,"read");
    
    std::string sample_1 = sample1;
    std::string sample_2 = sample2;
    std::string tag_1 = tag1;
    std::string tag_2 = tag2;

    TH1D * h_p1_ratio = static_cast<TH1D*>(hists1[1]->Clone("h_p1_ratio")); //p1 frac error (p1-nom/nom)
    //TH1D * h_p1_ratio = static_cast<TH1D*>(h_1_p1->Clone("h_p1_ratio"));
    //h_p1_ratio->Divide(h_2_p1);
    h_p1_ratio->Divide(hists2[1]); //(p1 frac error 1/ p1 frac error 2
    TH1D * h_m1_ratio = static_cast<TH1D*>(hists1[2]->Clone("h_m1_ratio"));
    //TH1D * h_m1_ratio = static_cast<TH1D*>(h_1_m1->Clone("h_m1_ratio"));
    //h_m1_ratio->Divide(h_2_m1);
    h_m1_ratio->Divide(hists2[2]);

    //std::cout<< "h_1_p1 bin 1 = "<<h_1_p1->GetBinContent(1)<< ", h_2_p1 bin 1 = "<<h_2_p1->GetBinContent(1)<< ", h_p1_ratio bin 1 = "<<h_p1_ratio->GetBinContent(1)<<std::endl;
    std::cout<< "hists1[1] bin 1 = "<<hists1[1]->GetBinContent(1)<< ", hists2[1] bin 1 = "<<hists2[1]->GetBinContent(1)<< ", h_p1_ratio bin 1 = "<<h_p1_ratio->GetBinContent(1)<<std::endl;
    h_p1_ratio -> SetLineColor(kPink+5);
    h_p1_ratio -> SetLineStyle(7);
    h_p1_ratio -> SetLineWidth(2);
    h_p1_ratio -> SetMarkerStyle(0);

    h_m1_ratio -> SetLineColor(kOrange+1);
    h_m1_ratio -> SetLineStyle(7);
    h_m1_ratio -> SetLineWidth(2);
    h_m1_ratio -> SetMarkerStyle(0);

    h_m1_ratio->SetStats(0);
    h_p1_ratio->GetYaxis()->SetTitleOffset(1.3);
    h_p1_ratio->GetXaxis()->SetRangeUser(0.2,3);
    h_p1_ratio->GetYaxis()->SetRangeUser(0.98,1.02);
    //h_p1_ratio->GetYaxis()->SetRangeUser(-0.95,0.75);
    h_p1_ratio->SetTitle("");
    h_p1_ratio->GetXaxis()->SetTitle("E_{#nu, Reco}");
    h_p1_ratio->GetYaxis()->SetTitle("Event Rate Ratio");
    h_p1_ratio->GetXaxis()->SetTitleFont(132);
    h_p1_ratio->GetYaxis()->SetTitleFont(132);
    h_p1_ratio->GetXaxis()->SetLabelFont(132);
    h_p1_ratio->GetYaxis()->SetLabelFont(132);
    h_p1_ratio->GetYaxis()->SetMaxDigits(3);

    h_p1_ratio -> Draw();
    h_m1_ratio -> Draw("same");

    TLegend * l2 = new TLegend(0.132,0.137,0.878,0.213);
    l2->SetTextSize(0.04);
    l2->SetBorderSize(0);
    l2->SetTextFont(132);
    l2->AddEntry(h_p1_ratio, ("("+tag_1+"/"+tag_2+")_{+1#sigma/nominal}").c_str(), "L");
    l2->AddEntry(h_m1_ratio, ("("+tag_1+"/"+tag_2+")_{-1#sigma/nominal}").c_str(), "L");
    l2->Draw();

    c->SaveAs(("double_ratios_"+tag_1+"_"+tag_2+".pdf").c_str());
    c->SaveAs(("double_ratios_"+tag_1+"_"+tag_2+".png").c_str());

    c->Clear();
    l2->Clear();
  }*/
}
