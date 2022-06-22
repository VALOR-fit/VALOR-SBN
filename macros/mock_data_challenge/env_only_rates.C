#include "TFile.h"
#include "TH1.h"

#include <iostream>

std::string GetDetector(const std::string &det);

void env_only_rates(const std::string &pf, 
                    const std::string &det, 
                    const std::string &sample,
                    const std::string &analysis,
                    const std::string &out="rates.txt"){

  using namespace valor;
  
  TFile *pf_file  = new TFile(pf.data(),"READ");

  TH1D *h_post = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
  TH1D *h_p1   = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_p1").c_str()));
  TH1D *h_m1   = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_m1").c_str()));

  double post_rate = h_post->Integral(); 
  double post_syst = (h_p1->Integral()-h_m1->Integral())*0.5;
  double post_stat = sqrt(post_rate);
  double post_err  = sqrt(pow(post_stat,2)+pow(post_syst,2));
  
  std::string det_print = GetDetector(det);
  
  ofstream of;
  of.open(out.c_str(), ios::app);
  of << "==========================================" << std::endl;
  of << " Detector       : " << det_print << std::endl;
  of << " Sample         : " << sample << std::endl;
  of << " Analysis       : " << analysis << std::endl;
  of << "------------------------------------------" << std::endl;
  of << " Rate           : " << std::setprecision(6) << post_rate << std::endl;
  of << " Stat-only      : " << std::setprecision(6) << post_stat << std::endl; 
  of << " Syst-only      : " << std::setprecision(6) << post_syst << std::endl; 
  of << " Stat+syst      : " << std::setprecision(6) << post_err << std::endl; 
  of << " Stat-only %    : " << std::setprecision(6) << (post_stat/post_rate)*100. << " %" << std::endl; 
  of << " Syst-only %    : " << std::setprecision(6) << (post_syst/post_rate)*100. << " %" << std::endl; 
  of << " Stat+syst %    : " << std::setprecision(6) << (post_err/post_rate)*100. << " %" << std::endl;
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
