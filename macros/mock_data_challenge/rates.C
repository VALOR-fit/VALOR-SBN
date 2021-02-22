#include "TFile.h"
#include "TH1.h"

#include <iostream>

std::string GetDetector(const std::string &det);

void rates(const std::string &md, 
           const std::string &pf, 
           const std::string &det, 
           const std::string &sample,
           const std::string &analysis,
           const std::string &model,
           const std::string &out="rates.txt"){

  TFile *md_file = new TFile(md.data(),"READ");
  TFile *pf_file = new TFile(pf.data(),"READ");

  TH1D *h_md   = static_cast<TH1D*>(md_file->Get(("toymc_data_sb_rf_"+det+"__BNB_FHC__"+sample).c_str()));
  TH1D *h_pre  = static_cast<TH1D*>(md_file->Get(("valor_pdfts_sb_rf_"+det+"__BNB_FHC__"+sample+"_Ereco").c_str()));
  TH1D *h_post = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
  TH1D *h_p1   = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_p1").c_str()));
  TH1D *h_m1   = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_m1").c_str()));

  double md_rate   = h_md->Integral();
  double pre_rate  = h_pre->Integral(); 
  double post_rate = h_post->Integral(); 
  double post_syst = (h_p1->Integral()-h_m1->Integral())*0.5;
  double post_stat = sqrt(post_rate);
  double post_err  = post_stat+post_syst;

  std::string det_print = GetDetector(det);
  
  ofstream of;
  of.open(out.c_str(), ios::app);
  of << "==========================================" << std::endl;
  of << " Detector       : " << det_print << std::endl;
  of << " Sample         : " << sample << std::endl;
  of << " Analysis       : " << analysis << std::endl;
  of << " Model          : " << model << std::endl;
  of << "------------------------------------------" << std::endl;
  of << " Rates            " << std::endl;
  of << " Mock Data      : " << std::setprecision(6) << md_rate << std::endl;
  of << " Prefit         : " << std::setprecision(6) << pre_rate << std::endl;
  of << " Postfit        : " << std::setprecision(6) << post_rate << std::endl;
  of << std::endl;       
  of << " (MD-Prefit)    : " << std::setprecision(6) << md_rate - pre_rate << std::endl;
  of << " (MD-Postfit)   : " << std::setprecision(6) << md_rate - post_rate << std::endl;
  of << "------------------------------------------" << std::endl;
  of << " Postift errors   " << std::endl;
  of << " Stat-only      : " << std::setprecision(6) << post_stat << std::endl; 
  of << " Syst-only      : " << std::setprecision(6) << post_syst << std::endl; 
  of << " Stat+syst      : " << std::setprecision(6) << post_err << std::endl; 
  of << "------------------------------------------" << std::endl;
  of << " Ratios           " << std::endl;
  of << " (MD-Pre)/MD    : " << std::setprecision(6) << ((md_rate - pre_rate)/md_rate)*100. << " %" << std::endl;
  of << " (MD-Post)/MD   : " << std::setprecision(6) << ((md_rate - post_rate)/md_rate)*100. << " %" << std::endl;
  of << " ErrPF/NPF      : " << std::setprecision(6) << (post_err/post_rate)*100. << " %" << std::endl;
  of << " (MD-Post)/ErrPF: " << std::setprecision(6) << ((md_rate - post_rate)/post_err) << std::endl;
  of << "==========================================" << std::endl;
  of.close();

}

std::string GetDetector(const std::string &det){
  if(det == "sbn_nd")
      return "SBND";
  else if(det == "sbn_uboone")
      return "MicroBooNE";
  else if(det == "sbn_icarus")
      return "ICARUS";
  else {
    std::cerr << "Invalid detector: " << det << std::endl;
    std::exit(1);
  }
}
