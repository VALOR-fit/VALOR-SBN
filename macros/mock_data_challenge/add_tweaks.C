#include "TFile.h"
#include "TH1.h"

void add_tweaks(const std::string cc0piFile, const std::string ccOtherFile, const std::string ccIncFile, std::string ccInclFile = "ccinclAddedFile.root")
{

  TFile *f0pi = new TFile(cc0piFile.c_str(),"READ");
  TFile *fOth = new TFile(ccOtherFile.c_str(),"READ");
  TFile *fInc = new TFile(ccIncFile.c_str(),"READ");

  std::vector<std::string> envs{"p1","m1","nom"};
  std::vector<TH1D*> cc0pi,ccoth,ccinc,ccincGen;

  for(const std::string e : envs){
    TH1D *h0pi  = static_cast<TH1D*>(f0pi->Get(("env_sb_BNB_FHC_numuCC0piNtrk_"+e).c_str()));
    TH1D *hOth  = static_cast<TH1D*>(fOth->Get(("env_sb_BNB_FHC_numuCCoth_"+e).c_str()));
    TH1D *hInc  = static_cast<TH1D*>(fInc->Get(("env_sb_BNB_FHC_numuCCincl_"+e).c_str()));
    cc0pi.push_back(h0pi);
    ccoth.push_back(hOth);
    ccincGen.push_back(hInc);
  }

  for(unsigned int i = 0; i < envs.size(); ++i){
    TH1D *hInc = static_cast<TH1D*>(cc0pi.at(i)->Clone(("env_sb_BNB_FHC_numuCCincl_"+envs.at(i)).c_str()));
    hInc->Add(ccoth.at(i));
    ccinc.push_back(hInc);
  }

  ccinc.at(2)->Draw();
  cc0pi.at(2)->Draw("same");
  ccoth.at(2)->Draw("same");
  ccincGen.at(2)->Draw("same");
  ccincGen.at(2)->SetLineStyle(2);

  TFile *fNew = new TFile(ccInclFile.c_str(),"RECREATE");
  for(const TH1D *h : ccinc){
    h->Write();
  }
  fNew->Close();

}
