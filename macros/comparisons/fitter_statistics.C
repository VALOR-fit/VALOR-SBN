#include <iostream>
#include <fstream>
#include <unordered_map>
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

void fitter_statistics(const std::string &dmsq="1e2", const std::string &sinsq="2e-3") {

  TFile *f_val_osc   = new TFile(("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/VALOR_dmsq_"+dmsq+"_sinsq2thmumu_"+sinsq+"_osc_breakdown_hists.root").c_str(),"read");
  TFile *f_val_unosc = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/VALOR_unosc_breakdown_hists.root","read");
  TFile *f_sbn_osc   = new TFile(("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/SBNfit_sinsq_"+sinsq+"_dmsq_"+dmsq+".SBNspec.root").c_str(),"read");
  TFile *f_sbn_unosc = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/SBNfit_CV.SBNspec.root","read");
  TFile *f_caf       = new TFile(("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/CAFAna_dmsq_"+dmsq+"_ss2thmm_"+sinsq+".root").c_str(),"read");

  // -------------------------------------------
  
  enum Fitter 
  {
    VALOR,
    CAFANA,
    SBNFIT
  };

  std::unordered_map<Fitter, std::string> fitterToString;
  fitterToString[VALOR]  = "VALOR";
  fitterToString[CAFANA] = "CAFAna";
  fitterToString[SBNFIT] = "SBNFit";

  // -------------------------------------------

  enum Mode
  {
    NUMUCC,
    NUMUNC,
    NUE,
    TOTAL
  };

  std::unordered_map<Mode, std::string> modeToString;
  modeToString[NUMUCC] = "NuMu-CC";
  modeToString[NUMUNC] = "NC";
  modeToString[NUE]    = "NuE";
  modeToString[TOTAL]  = "Total";
  
  // -------------------------------------------
  
  enum Detector
  {
    SBND,
    UBOONE,
    ICARUS
  };
  
  std::unordered_map<Detector, std::string> detectorToString;
  detectorToString[SBND]   = "SBND";
  detectorToString[UBOONE] = "MicroBooNE";
  detectorToString[ICARUS] = "ICARUS";

  // -------------------------------------------

  // Map with indices of fitter and bool (is oscillated) to the corresponding TFile
  std::unordered_map<Fitter, std::unordered_map<bool, TFile*> > fileMap;

  // Populate the input file map
  fileMap[VALOR][false]  = f_val_unosc;
  fileMap[VALOR][true]   = f_val_osc;
  fileMap[SBNFIT][false] = f_sbn_unosc;
  fileMap[SBNFIT][true]  = f_sbn_osc;
  fileMap[CAFANA][false] = f_caf;
  fileMap[CAFANA][true]  = f_caf;
 
  // -------------------------------------------
  
  // Map with indices of fitter to the option to use when finding the integral
  std::unordered_map<Fitter, std::string > integralOptionMap;
  integralOptionMap[VALOR]  = "width";
  integralOptionMap[SBNFIT] = "";
  integralOptionMap[CAFANA] = "width";
 
  // -------------------------------------------
  
  // Map with indicies of fitter, and detector to the prefix of the histogram names
  std::unordered_map<Fitter, std::unordered_map<Detector, std::string> > histNamePrefixMap;
  histNamePrefixMap[VALOR][SBND]   = "sbn_nd_";
  histNamePrefixMap[VALOR][UBOONE] = "sbn_uboone_";
  histNamePrefixMap[VALOR][ICARUS] = "sbn_icarus_";

  histNamePrefixMap[CAFANA][SBND]   = "nd_";
  histNamePrefixMap[CAFANA][UBOONE] = "ub_";
  histNamePrefixMap[CAFANA][ICARUS] = "fd_";
  
  histNamePrefixMap[SBNFIT][SBND]   = "nu_SBND_";
  histNamePrefixMap[SBNFIT][UBOONE] = "nu_uBooNE_";
  histNamePrefixMap[SBNFIT][ICARUS] = "nu_ICARUS_";
 
  // -------------------------------------------

  // Map with indicies of fitter, bool (is oscillated), mode to the suffix name of the histogram
  std::unordered_map<Fitter, std::unordered_map<bool, std::unordered_map<Mode, std::string> > > histNameSuffixMap;

  // Populate the histogram name map
  histNameSuffixMap[VALOR][false][NUMUCC] = "numu_cc";
  histNameSuffixMap[VALOR][true][NUMUCC]  = "numu_cc";
  histNameSuffixMap[VALOR][false][NUMUNC] = "numu_nc";
  histNameSuffixMap[VALOR][true][NUMUNC]  = "numu_nc";
  histNameSuffixMap[VALOR][false][NUE]    = "nue";
  histNameSuffixMap[VALOR][true][NUE]     = "nue";

  histNameSuffixMap[CAFANA][false][NUMUCC] = "numucc_unosc";
  histNameSuffixMap[CAFANA][true][NUMUCC]  = "numucc_osc";
  histNameSuffixMap[CAFANA][false][NUMUNC] = "nc_unosc";
  histNameSuffixMap[CAFANA][true][NUMUNC]  = "nc_osc";
  histNameSuffixMap[CAFANA][false][NUE]    = "nuecc_unosc";
  histNameSuffixMap[CAFANA][true][NUE]     = "nuecc_osc";

  histNameSuffixMap[SBNFIT][false][NUMUCC] = "numu_cc";
  histNameSuffixMap[SBNFIT][true][NUMUCC]  = "numu_cc";
  histNameSuffixMap[SBNFIT][false][NUMUNC] = "numu_nc";
  histNameSuffixMap[SBNFIT][true][NUMUNC]  = "numu_nc";
  histNameSuffixMap[SBNFIT][false][NUE]    = "numu_nue";
  histNameSuffixMap[SBNFIT][true][NUE]     = "numu_nue";
 
  // -------------------------------------------

  // Get the histograms
  std::unordered_map<Detector, std::unordered_map<Fitter, std::unordered_map<bool, std::unordered_map<Mode, TH1D*> > > > histMap;

  for (const Detector &detector : {SBND, UBOONE, ICARUS})
  {
    for (const Fitter &fitter : {VALOR, CAFANA, SBNFIT})
    {
      const std::string &histNamePrefix = histNamePrefixMap.at(fitter).at(detector);

      for (const bool isOscillated : {false, true})
      {
        TFile *pFile = fileMap.at(fitter).at(isOscillated);
        
        for (const Mode &mode : {NUMUCC, NUMUNC, NUE})
        {
          // Get the full histogram name
          const std::string &histNameSuffix = histNameSuffixMap.at(fitter).at(isOscillated).at(mode);
          const std::string histName = histNamePrefix + histNameSuffix;

          // Access the histogram from the file and store it in the map
          histMap[detector][fitter][isOscillated][mode] = static_cast<TH1D*>(pFile->Get(histName.c_str()));
          TH1D *pHist = histMap.at(detector).at(fitter).at(isOscillated).at(mode);

          // Now make the total histograms
          if (histMap.at(detector).at(fitter).at(isOscillated).find(TOTAL) == histMap.at(detector).at(fitter).at(isOscillated).end()) 
          {
            histMap[detector][fitter][isOscillated][TOTAL] = static_cast<TH1D*>(pHist->Clone((fitterToString[fitter]+"total").c_str()));
          }
          else
          {
            histMap.at(detector).at(fitter).at(isOscillated).at(TOTAL)->Add(pHist);
          }
        }
      }
    }
  }

  // -------------------------------------------

  // Open the file for writing
  ofstream file;
  file.open(("event_rates_at_dmsq-"+dmsq+"_sinsq-"+sinsq+".txt").c_str());

  const unsigned int colWidth  = 15;
  const unsigned int precision = 4;

  file << std::endl;
  file << std::setw(colWidth) << "Mode";
  file << " || ";
  file << std::setw(colWidth) << "CAFAna";
  file << " || ";
  file << std::setw(colWidth) << "SBNFit";
  file << " || "; 
  file << std::setw(colWidth) << "VALOR";
  file << " || "; 
  file << std::setw(colWidth) << "VALOR-CAFAna";
  file << " || "; 
  file << std::setw(colWidth) << "VALOR-SBNFit";
  file << " || "; 
  file << std::setw(colWidth) << "CAFAna-SBNFit";
  file << std::endl;
  file << std::endl;

  auto printRow = [&](const std::string &str, const double &cafana, const double &sbnfit, const double &valor) {
    file << std::setw(colWidth) << str;
    file << " || ";
    file << std::setw(colWidth) << std::setprecision(precision) << std::fixed << cafana;
    file << " || ";
    file << std::setw(colWidth) << std::setprecision(precision) << std::fixed << sbnfit;
    file << " || ";
    file << std::setw(colWidth) << std::setprecision(precision) << std::fixed << valor;
    file << " || ";
    file << std::setw(colWidth) << std::setprecision(precision) << std::fixed << valor-cafana;
    file << " || ";
    file << std::setw(colWidth) << std::setprecision(precision) << std::fixed << valor-sbnfit;
    file << " || ";
    file << std::setw(colWidth) << std::setprecision(precision) << std::fixed << cafana-sbnfit;
    file << std::endl;
  };

  // Make the table
  for (const Detector &detector : {SBND, UBOONE, ICARUS})
  {
    file << " --- " << detectorToString.at(detector) << " --- " << std::endl;

    for (const bool isOscillated : {false, true})
    {
      file << " --- " << (isOscillated ? "Oscillated, dmsq = "+dmsq+", sinsq = "+sinsq : "Unoscillated") << " --- " << std::endl;

      // Loop over the modes individually
      for (const Mode &mode : {NUMUCC, NUMUNC, NUE, TOTAL})
      {

        std::unordered_map<Fitter, double> fitterToIntegralMap;
        std::unordered_map<Fitter, double> fitterToOscillatedIntegralMap;
        std::unordered_map<Fitter, double> fitterToUnOscillatedIntegralMap;
        for (const Fitter &fitter : {VALOR, CAFANA, SBNFIT})
        {
          // Get the histogram
          const TH1D *pHist = histMap.at(detector).at(fitter).at(isOscillated).at(mode);

          // Get integral of the histogram
          fitterToIntegralMap[fitter] = pHist->Integral(integralOptionMap.at(fitter).c_str());
          isOscillated ? 
            fitterToOscillatedIntegralMap[fitter]   = pHist->Integral(integralOptionMap.at(fitter).c_str()) :
            fitterToUnOscillatedIntegralMap[fitter] = pHist->Integral(integralOptionMap.at(fitter).c_str());

        }
        // Print the row
        printRow(modeToString[mode], fitterToIntegralMap.at(CAFANA), fitterToIntegralMap.at(SBNFIT), fitterToIntegralMap.at(VALOR)); 
      }
    }
    // Now calculate the chisq values
    // Chi2 value calculated using 3 different likelihood ratio definitions
    //
    //    A [Normal definition]: chisq = 2. * (ndata * std::log(ndata / nmc) + nmc - ndata)
    //    B [Used by VALOR]    : chisq = 2. *  ndata * (nmc / ndata + std::log(ndata / nmc) - 1.0)
    //    C [Used by CAFAna]   : chisq = 2. *  ndata * ((nmc - ndata) / ndata + std::log1p((ndata - nmc) / nmc))
    std::unordered_map<Fitter, double> fitterToChi2AMap;
    std::unordered_map<Fitter, double> fitterToChi2BMap;
    std::unordered_map<Fitter, double> fitterToChi2CMap;
    for (const Fitter &fitter : {VALOR, CAFANA, SBNFIT})
    {
      double chi2A = 0;
      double chi2B = 0;
      double chi2C = 0;

      TH1D *oscHist   = histMap.at(detector).at(fitter).at(true).at(TOTAL);
      TH1D *unOscHist = histMap.at(detector).at(fitter).at(false).at(TOTAL);
      
      for (int i = 0; i < oscHist->GetNbinsX(); ++i){
        double ndata = oscHist->GetBinContent(i);
        double nmc   = unOscHist->GetBinContent(i);
        if(fitter == SBNFIT) 
        {
          ndata = oscHist->GetBinContent(i)/static_cast<double>(oscHist->GetBinWidth(i));
          nmc   = unOscHist->GetBinContent(i)/static_cast<double>(unOscHist->GetBinWidth(i));
        }

        if((ndata < 1e-10 || nmc < 1e-10) && !(ndata < 1e-10 && nmc < 1e-10))
        {
          chi2A += 0;
          chi2B += 0;
          chi2C += 0;
        }
        else if(ndata < 1e-10 && nmc < 1e-10)
        {
          chi2A += 2.*(nmc-ndata);
          chi2B += 2.*(nmc-ndata);
          chi2C += 2.*(nmc-ndata);
        }
        else
        {
          // Calculate each chi2 and increment total
          chi2A += 2. * (ndata * std::log(ndata / nmc) + nmc - ndata);
          chi2B += 2. *  ndata * (nmc / ndata + std::log(ndata / nmc) - 1.0);
          chi2C += 2. *  ndata * ((nmc - ndata) / ndata + std::log1p((ndata - nmc) / nmc));
        }
      }
      fitterToChi2AMap[fitter] = std::max(0.,chi2A);
      fitterToChi2BMap[fitter] = std::max(0.,chi2B);
      fitterToChi2CMap[fitter] = std::max(0.,chi2C);
    }
    file << " --- Fit statistics --- " << std::endl;
    printRow("Chi2A", fitterToChi2AMap.at(CAFANA), fitterToChi2AMap.at(SBNFIT), fitterToChi2AMap.at(VALOR)); 
    printRow("Chi2B", fitterToChi2BMap.at(CAFANA), fitterToChi2BMap.at(SBNFIT), fitterToChi2BMap.at(VALOR)); 
    printRow("Chi2C", fitterToChi2CMap.at(CAFANA), fitterToChi2CMap.at(SBNFIT), fitterToChi2CMap.at(VALOR)); 
    file << endl;
  }

  file.close();

}
