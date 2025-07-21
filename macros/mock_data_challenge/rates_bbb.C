#include "TFile.h"
#include "TH1.h"

#include <iostream>

std::string GetDetector(const std::string &det);

void rates_bbb(const std::string &md, 
           const std::string &pf,
           const std::string &fit,
           const std::string &det, 
           const std::string &sample,
           const std::string &analysis,
           const std::string &model,
           const std::string &out="rates",
           const std::string &treename = "valor_fit_ntp"){

  using namespace valor;
  
  TFile *md_file  = new TFile(md.data(),"READ");
  TFile *pf_file  = new TFile(pf.data(),"READ");

  TH1D *h_md   = static_cast<TH1D*>(md_file->Get(("toymc_data_sb_rf_"+det+"__BNB_FHC__"+sample).c_str()));
  TH1D *h_pre  = static_cast<TH1D*>(md_file->Get(("valor_pdfts_sb_rf_"+det+"__BNB_FHC__"+sample+"_Ereco").c_str()));
  TH1D *h_post = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
  TH1D *h_p1   = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_p1").c_str()));
  TH1D *h_m1   = static_cast<TH1D*>(pf_file->Get(("env_sb_BNB_FHC_"+sample+"_m1").c_str()));

  TFile fit_file(fit.data(),"READ");
  FitParamList *  gbf = 0;
  TTree * t = static_cast<TTree*>(fit_file.Get(treename.c_str()));
  t->SetBranchAddress("best_fit_params", &gbf);
  t->GetEntry(0);
  
  double md_rate   = h_md->Integral();
  double pre_rate  = h_pre->Integral(); 
  double post_rate = h_post->Integral(); 
  double post_syst = (h_p1->Integral()-h_m1->Integral())*0.5;
  double post_stat = sqrt(post_rate);
  double post_err  = sqrt(pow(post_stat,2)+pow(post_syst,2));

  double diff_pre_md = 0;
  double diff_post_md = 0;
  double ratio_diff_pre_md = 0;
  double ratio_diff_post_md = 0;
  double ratio_diff_post_md_posterr = 0;
  double ratio_errpf_pf = 0;
  //double diff_w_pre_md = 0;
  //double diff_w_post_md = 0;
  double nbins = h_pre->GetNbinsX();
  double xrange = h_pre->GetXaxis()->GetBinUpEdge(nbins) - h_pre->GetXaxis()->GetBinLowEdge(0);
  for(int i = 1; i <= nbins; i++){ 
    double diff_pre = std::abs(h_pre->GetBinContent(i) - h_md->GetBinContent(i));
    //double weight_pre = h_pre->GetBinWidth(i) / xrange;
    //diff_w_pre_md += diff_pre * weight_pre;
    diff_pre_md += diff_pre;
    double diff_post = std::abs(h_post->GetBinContent(i) - h_md->GetBinContent(i));
    //double weight_post = h_post->GetBinWidth(i) / xrange;
    //diff_w_post_md += diff_post * weight_post;
    diff_post_md += diff_post;
    

    double ratio_diff_pre = diff_pre/h_md->GetBinContent(i);
    double ratio_diff_post = diff_post/h_md->GetBinContent(i);
    double post_err_i = sqrt(pow((h_p1->GetBinContent(i)-h_m1->GetBinContent(i))*0.5,2)+h_post->GetBinContent(i));
    double ratio_diff_post_posterr = diff_post/post_err_i;
    double ratio_errpf = post_err_i / h_post->GetBinContent(i);
    ratio_diff_pre_md += ratio_diff_pre;
    ratio_diff_post_md += ratio_diff_post;
    ratio_diff_post_md_posterr += ratio_diff_post_posterr;
    ratio_errpf_pf += ratio_errpf;
    //ratio_diff_pre = diff_pre/h_md->GetBinContent(i);
  }
  //unsigned int ndof = gbf->GetNumberFreeParameters();
  unsigned int ndof = 21; // (21 EReco Bins + X Syst) - (0 Osc + X constraints)
  double stat       = gbf->GetBestFitStatistic();
  
  std::string det_print = GetDetector(det);
  
  ofstream of;
  of.open((out).c_str(), ios::app);
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
  of << " (Prefit-MD)    : " << std::setprecision(6) << pre_rate  - md_rate << std::endl;
  of << " (Postfit-MD)   : " << std::setprecision(6) << post_rate - md_rate << std::endl;
  of << std::endl;       
  of << " SUM(Prefit_i-MD_i)    : " << std::setprecision(6) << diff_pre_md  << std::endl;
  of << " SUM(Postfit_i-MD_i)   : " << std::setprecision(6) << diff_post_md << std::endl;
  //of << std::endl;       
  //of << " Weighted SUM(Prefit_i-MD_i)    : " << std::setprecision(6) << diff_w_pre_md  << std::endl;
  //of << " Weighted SUM(Postfit_i-MD_i)   : " << std::setprecision(6) << diff_w_post_md << std::endl;
  of << "------------------------------------------" << std::endl;
  of << " Postfit errors   " << std::endl;
  of << " Stat-only      : " << std::setprecision(6) << post_stat << std::endl; 
  of << " Syst-only      : " << std::setprecision(6) << post_syst << std::endl; 
  of << " Stat+syst      : " << std::setprecision(6) << post_err << std::endl; 
  of << "------------------------------------------" << std::endl;
  of << " Ratios           " << std::endl;
  of << " (Pre-MD)/MD    : " << std::setprecision(6) << ((pre_rate - md_rate)/md_rate)*100. << " %" << std::endl;
  of << " (Post-MD)/MD   : " << std::setprecision(6) << ((post_rate - md_rate)/md_rate)*100. << " %" << std::endl;
  of << " ErrPF/NPF      : " << std::setprecision(6) << (post_err/post_rate)*100. << " %" << std::endl;
  of << " (Post-MD)/ErrPF: " << std::setprecision(6) << ((post_rate - md_rate)/post_err) << std::endl;
  of << std::endl;       
  of << " SUM((Pre_i-MD_i)/MD_i)    : " << std::setprecision(6) << ratio_diff_pre_md*100.     << " %" << std::endl;
  of << " SUM((Post_i-MD_i)/MD_i)   : " << std::setprecision(6) << ratio_diff_post_md*100.     << " %" << std::endl;
  of << " SUM(ErrPF_i/NPF_i)        : " << std::setprecision(6) << ratio_errpf_pf*100.        << " %" << std::endl;
  of << " SUM((Post_i-MD_i)/ErrPF_i): " << std::setprecision(6) << ratio_diff_post_md_posterr << std::endl;
  of << "------------------------------------------" << std::endl;
  of << "Global best fit contributions: " << endl;
  
  std::map<std::string,double>::const_iterator it;
  of << " Fit statistic  : " <<  std::setprecision(6) << stat << std::endl;
  of << " NDOF           : " <<  std::setprecision(6) << ndof << std::endl;
  for(it = gbf->GetBestFitStatisticContributions().begin(); it != gbf->GetBestFitStatisticContributions().end(); ++it){
      of << std::setprecision(6) << it->first;
      of << std::setprecision(6) << " = ";
      of << std::setprecision(6) << it->second;
      of << endl;
  }
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
