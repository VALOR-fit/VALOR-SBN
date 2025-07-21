#include "TFile.h"
#include "TH1.h"

#include <iostream>

std::string GetDetector(const std::string &det);

void rates(const std::string &md, 
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

  unsigned int ndof = gbf->GetNumberFreeParameters();
  double stat       = gbf->GetBestFitStatistic();
  
  std::string det_print = GetDetector(det);
  
  ofstream of;
  of.open((out+".txt").c_str(), ios::app);
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
  of << "------------------------------------------" << std::endl;
  of << " Postift errors   " << std::endl;
  of << " Stat-only      : " << std::setprecision(6) << post_stat << std::endl; 
  of << " Syst-only      : " << std::setprecision(6) << post_syst << std::endl; 
  of << " Stat+syst      : " << std::setprecision(6) << post_err << std::endl; 
  of << "------------------------------------------" << std::endl;
  of << " Ratios           " << std::endl;
  of << " (Pre-MD)/MD    : " << std::setprecision(6) << ((pre_rate - md_rate)/md_rate)*100. << " %" << std::endl;
  of << " (Post-MD)/MD   : " << std::setprecision(6) << ((post_rate - md_rate)/md_rate)*100. << " %" << std::endl;
  of << " ErrPF/NPF      : " << std::setprecision(6) << (post_err/post_rate)*100. << " %" << std::endl;
  of << " (Post-MD)/ErrPF: " << std::setprecision(6) << ((post_rate - md_rate)/post_err) << std::endl;
  of << "------------------------------------------" << std::endl;
  of << "Global best fit contributions: " << endl;
  
  std::map<std::string,double>::const_iterator it;
  of << " Fit statistic  : " <<  std::setprecision(6) << stat << std::endl;
  of << " NDOF           : " <<  std::setprecision(6) << ndof << std::endl;
  double syst;
  int i =0;
  for(it = gbf->GetBestFitStatisticContributions().begin(); it != gbf->GetBestFitStatisticContributions().end(); ++it){
      of << std::setprecision(6) << it->first;
      of << std::setprecision(6) << " = ";
      of << std::setprecision(6) << it->second;
      of << endl;
      if(i==1) syst = it->second;
      i++;
  }
  of << "==========================================" << std::endl;
  of.close();
  ofstream tex;
  tex.open((out+".tex").c_str(), ios::app);
  tex <<  "\\documentclass{article} " << std::endl;
  tex <<  "\\usepackage[utf8]{inputenc} " << std::endl;
  tex <<  "\\usepackage{multirow} " << std::endl;
  tex <<  "\\usepackage{makecell} % For bold hline " << std::endl;
  tex <<  "\\usepackage{amsmath} % For math symbols" << std::endl;
  tex <<  "\\usepackage{booktabs} " << std::endl;
  tex <<  "\\usepackage{arydshln} " << std::endl;
  tex <<  std::endl;
  tex <<  "\\setlength\\dashlinedash{1.2pt} " << std::endl;
  tex <<  "\\setlength\\dashlinegap{1.2pt} " << std::endl;
  tex <<  "\\setlength\\arrayrulewidth{0.3pt}" << std::endl;
  tex <<  std::endl;
  tex <<  "\\begin{document} " << std::endl;
  tex <<  std::endl;
  tex <<  "\\begin{table} " << std::endl;
  tex <<  "	\\renewcommand{\\arraystretch}{1.5} " << std::endl;
  tex <<  "	\\centering " << std::endl;
  tex <<  "	\\caption{Table showing a numerical sumamry of results from the mock data analyses for each of the SBND and PRISM3 fits. $N_{Post, MD}$ is the integrated event rate for the postfit and mock data cases respectively. $\\Delta N_{Post-MD}$ is the difference in integrated event rates between the postfit and MD cases.} " << std::endl;
  tex <<  "	\\begin{tabular}{p{1.5cm} p{1.5cm} p{1.5cm} p{2cm} p{2cm} p{2cm}} \\toprule " << std::endl;
  tex <<  "	Analysis & $\\chi^2$ $ \\chi^2_{syst}$ & $\\frac{\\sigma_{Postfit}}{N_{Postfit}}$ & $\\frac{\\Delta N_{Post-MD}}{N_{Mockdata}}$   & $\\frac{\\Delta N_{Post-MD}}{\\sigma_{Postfit}}$ \\\\ " << std::endl;
  tex <<  "	\\midrule " << std::endl;
  tex << "	\\multicolumn{5}{c}{\\textit{"<<analysis<<"}} \\\\ \\hdashline" << std::endl; 
  tex << "	" << std::setprecision(6) << model<<" & "<<stat<<" & " << syst << " & "<<(post_err/post_rate)*100.<<"\\% & "<<((post_rate - md_rate)/md_rate)*100<<" \\% & "<<((post_rate - md_rate)/post_err)<<" \\\\ " << std::endl;
  tex <<  "	\\bottomrule " << std::endl;
  tex << "	\\end{tabular}" << std::endl;
  tex << "	\\label{tab:my_label} " << std::endl;
  tex << "\\end{table}  " << std::endl;
  tex <<  std::endl;
  tex << "\\end{document}" <<std::endl;
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
