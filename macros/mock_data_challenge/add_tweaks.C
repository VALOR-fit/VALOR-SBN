#include "TFile.h"
#include "TH1.h"
#include "TMath.h"
#include <cmath>

void add_tweaks(const std::string ccExcFile, 
                std::string ccInclFile = "ccinclAddedFile.root")
{

  TFile *fExc = new TFile(ccExcFile.c_str(),"READ");

  std::vector<std::string> envs{"nom","p1","m1"};
  std::vector<TH1D*> cc0pi,ccoth,ccinc;

  for(const std::string e : envs){
    TH1D *h0pi  = static_cast<TH1D*>(fExc->Get(("env_sb_BNB_FHC_numuCC0piNtrk_"+e).c_str()));
    TH1D *hOth  = static_cast<TH1D*>(fExc->Get(("env_sb_BNB_FHC_numuCCoth_"+e).c_str()));
    cc0pi.push_back(h0pi);
    ccoth.push_back(hOth);
  }

  TH1D *hIncNom = static_cast<TH1D*>(cc0pi.at(0)->Clone("env_sb_BNB_FHC_numuCCincl_nom"));
  hIncNom->Add(ccoth.at(0));
  ccinc.push_back(hIncNom);
  
  // Add errors in quadrature
  TH1D *hIncP1 = static_cast<TH1D*>(ccinc.at(0)->Clone("env_sb_BNB_FHC_numuCCincl_p1"));
  TH1D *hIncM1 = static_cast<TH1D*>(ccinc.at(0)->Clone("env_sb_BNB_FHC_numuCCincl_m1"));
  
  for(int n = 1; n <= hIncP1->GetNbinsX(); ++n){
    double inc_nom     = ccinc.at(0)->GetBinContent(n);
    double nom_0pi     = cc0pi.at(0)->GetBinContent(n);
    double p1_0pi      = cc0pi.at(1)->GetBinContent(n);
    double m1_0pi      = cc0pi.at(2)->GetBinContent(n);
    double nom_oth     = ccoth.at(0)->GetBinContent(n);
    double p1_oth      = ccoth.at(1)->GetBinContent(n);
    double m1_oth      = ccoth.at(2)->GetBinContent(n);
    
    double diff_0pi_p1 = p1_0pi-nom_0pi;
    double diff_0pi_m1 = nom_0pi-m1_0pi;
    double diff_oth_p1 = p1_oth-nom_oth;
    double diff_oth_m1 = nom_oth-m1_oth;
    
    double diff_inc_p1 = sqrt(pow(diff_0pi_p1,2)+pow(diff_oth_p1,2));
    double diff_inc_m1 = sqrt(pow(diff_0pi_m1,2)+pow(diff_oth_m1,2));

    hIncP1->SetBinContent(n,inc_nom+diff_inc_p1);
    hIncM1->SetBinContent(n,inc_nom-diff_inc_m1);
  }
  ccinc.push_back(hIncP1);
  ccinc.push_back(hIncM1);
  
  /****** OLD AND WRONG ******
  for(unsigned int i = 0; i < envs.size(); ++i){
    TH1D *hInc = static_cast<TH1D*>(cc0pi.at(i)->Clone(("env_sb_BNB_FHC_numuCCincl_"+envs.at(i)).c_str()));
    hInc->Add(ccoth.at(i));
    ccinc.push_back(hInc);
  }*/

  TFile *fNew = new TFile(ccInclFile.c_str(),"RECREATE");
  for(const TH1D *h : ccinc){
    h->Write();
  }
  fNew->Close();

  std::cout << " Done adding spectra!" << std::endl;
}
