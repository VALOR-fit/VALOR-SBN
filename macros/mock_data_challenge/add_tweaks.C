#include "TFile.h"
#include "TH1.h"

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

  for(unsigned int i = 0; i < envs.size(); ++i){
    TH1D *hInc = static_cast<TH1D*>(cc0pi.at(i)->Clone(("env_sb_BNB_FHC_numuCCincl_"+envs.at(i)).c_str()));
    hInc->Add(ccoth.at(i));
    ccinc.push_back(hInc);
  }

  TFile *fNew = new TFile(ccInclFile.c_str(),"RECREATE");
  for(const TH1D *h : ccinc){
    h->Write();
  }
  fNew->Close();
}
