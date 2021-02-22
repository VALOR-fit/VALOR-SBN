#include "TFile.h"
#include "TH1.h"

void add_tweaks(const std::string cc0piFile, 
                const std::string ccOtherFile, 
                const std::string ccIncFile, 
                const std::string data    = "",
                const std::string dataExc = "",
                const int exp = 0, // 0 = nd, 1 = ub, 1 = fd
                std::string ccInclFile = "ccinclAddedFile.root")
{

  TFile *f0pi = new TFile(cc0piFile.c_str(),"READ");
  TFile *fOth = new TFile(ccOtherFile.c_str(),"READ");
  TFile *fInc = new TFile(ccIncFile.c_str(),"READ");

  std::vector<std::string> envs{"nom","p1","m1"};
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

  ccinc.at(0)->Draw();
  ccinc.at(0)->SetLineStyle(4);
  ccinc.at(0)->SetLineColor(kPink+5);
//  cc0pi.at(0)->Draw("same");
//  ccoth.at(0)->Draw("same");
  ccincGen.at(0)->Draw("same");
  ccincGen.at(0)->SetLineStyle(1);
  ccincGen.at(0)->SetLineColor(kPink+5);
  if(data != ""){
    TFile *fData = new TFile(data.c_str(),"READ");
    TFile *fDataExc = new TFile(dataExc.c_str(),"READ");
    if(exp == 0){
      TH1D *hData    = static_cast<TH1D*>(fData->Get("toymc_data_sb_rf_sbn_nd__BNB_FHC__numuCCincl"));
      TH1D *hDataExc = static_cast<TH1D*>(fDataExc->Get("toymc_data_sb_rf_sbn_nd__BNB_FHC__numuCC0piNtrk"));
      hDataExc->Add(static_cast<TH1D*>(fDataExc->Get("toymc_data_sb_rf_sbn_nd__BNB_FHC__numuCCoth")));
      hData->SetLineStyle(1);
      hData->SetLineColor(kAzure+7);
      hData->Draw("same");
      hDataExc->SetLineStyle(4);
      hDataExc->SetLineColor(kAzure+7);
      hDataExc->Draw("same");
    }
    else if(exp == 1){
      TH1D *hData  = static_cast<TH1D*>(fData->Get("toymc_data_sb_rf_sbn_uboone__BNB_FHC__numuCCincl"));
      hData->SetLineStyle(3);
      hData->SetLineColor(kAzure+7);
      hData->Draw("same");
    }
    else if(exp == 2){
      TH1D *hData    = static_cast<TH1D*>(fData->Get("toymc_data_sb_rf_sbn_icarus__BNB_FHC__numuCCincl"));
      TH1D *hDataExc = static_cast<TH1D*>(fDataExc->Get("toymc_data_sb_rf_sbn_icarus__BNB_FHC__numuCC0piNtrk"));
      hDataExc->Add(static_cast<TH1D*>(fDataExc->Get("toymc_data_sb_rf_sbn_icarus__BNB_FHC__numuCCoth")));
      hData->SetLineStyle(3);
      hData->SetLineColor(kAzure+7);
      hData->Draw("same");
      hDataExc->SetLineStyle(4);
      hDataExc->SetLineColor(kOrange+2);
      hDataExc->Draw("same");
    }
  
  }

  TFile *fNew = new TFile(ccInclFile.c_str(),"RECREATE");
  for(const TH1D *h : ccinc){
    h->Write();
  }
  fNew->Close();

}
