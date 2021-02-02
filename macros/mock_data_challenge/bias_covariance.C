/*  Macro to read in far detector mock data and prediction generated from ND or joint fit
 *  Calculate the difference between the two in each energy bin
 *
 *  Given the difference, define a binning scheme for a systematic parameter set by grouping 
 *  bins with 'similar' difference
 *
 *  Construct a covariance matrix from the bias in each of the parameter set bins
 *  Apply this to the analysis with a 1-sided (negative-only) range to account for the
 *  over-estimation of the prediction
 *  
 *  Author: R. S. Jones
 *  Email:  rjones@hep.ph.liv.ac.uk
 *
 *
 */

#include "TFile.h"
#include "TH1.h"
#include "TMatrix.h"
#include "TVector.h"
#include "TMath.h"
#include "TPrincipal.h"

std::vector<double> param_bin_edges = 
{
  0.0,
  0.3,
  0.4,
  0.45,
  0.5,
  0.55,
  0.6,
  0.65,
  0.7,
  0.75,
  0.8,
  0.85,
  0.9,
  0.95,
  1.0,
  1.25,
  1.5,
  3.0,
  10.0
};

using namespace valor;

void bias_covariance(const std::string &dataFiles, 
    const std::string &predFiles, 
    const std::string &sample, 
    const std::string &output,
    const std::string debug="",
    const bool &verbose=false)
{

  // Get the current data and prediction files and add to the covariance row
  ifstream dFiles(dataFiles.c_str());
  ifstream pFiles(predFiles.c_str());
  std::string dLine, pLine;
  std::vector<std::string> dLines, pLines;
  while(getline(dFiles,dLine)){
    dLines.push_back(dLine);
  }
  while(getline(pFiles,pLine)){
    pLines.push_back(pLine);
  }

  assert(dLines.size() == pLines.size());

  // Number of datasets we're assessing
  int nFiles = dLines.size();

  //The fractional bias matrix and test for maximum entires from models
  TMatrixD bias(param_bin_edges.size()-1,param_bin_edges.size()-1);
  TVectorD maxFracDiff(param_bin_edges.size()-1);
  TVectorD fracDiff(param_bin_edges.size()-1);
  
  // Access the largest bias values from all the mock data along with the mean of all the mock data in every bin
  for(unsigned int l = 0; l < dLines.size(); ++l){

    // Get the current data and MC histograms
    TFile *fData = new TFile(dLines.at(l).c_str(), "READ");
    TFile *fPred = new TFile(pLines.at(l).c_str(), "READ");

    TH1D *hData   = static_cast<TH1D*>(fData->Get(("toymc_data_ob_rf_sbn_icarus__BNB_FHC__"+sample).c_str()));
    TH1D *hPred   = static_cast<TH1D*>(fPred->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
    
    assert(hData->GetNbinsX() == hPred->GetNbinsX());

    std::vector<double> means(param_bin_edges.size()-1,0.);
    std::vector<double> cvs(means);

    assert(hData->GetNbinsX() == hPred->GetNbinsX());
    for(int b = 1; b <= hData->GetNbinsX(); ++b)
    {
      double curr_mean = hPred->GetBinContent(b);
      double curr_cv   = hData->GetBinContent(b);
      if(verbose){
        std::cout << " Mean in bin " << b 
          << ": " << curr_mean 
          << " CV in bin " << b
          << ": " << curr_cv
          << std::endl;
      }
      //Now loop over new binning and re-define the differences
      for(unsigned int p = 0; p < param_bin_edges.size()-1; ++p){
        if(hData->GetBinCenter(b) < param_bin_edges.at(p+1) && hData->GetBinCenter(b) >= param_bin_edges.at(p)){
          means.at(p) += curr_mean;
          cvs.at(p)   += curr_cv;
        }
      }
    }
    // Find the absolute maximum value to propagate to the bias matrix
    for(unsigned int i = 0; i < means.size(); ++i){
      double tempBias = (means.at(i)-cvs.at(i))/static_cast<double>(cvs.at(i));
      if(abs(tempBias) > maxFracDiff[i]){
        maxFracDiff[i]  = abs(tempBias);
        fracDiff[i]     = tempBias;
      }
    }
    // Now fill the current matrix
    for(unsigned int i = 0; i < means.size(); ++i){
      for(unsigned int j = 0; j < means.size(); ++j){
        bias[i][j] = fracDiff[i]*fracDiff[j];
      }
    }
  }
  
  if(verbose){
    for(unsigned int i = 0; i < bias.GetNrows(); ++i){
      for(unsigned int j = 0; j < bias.GetNrows(); ++j){
        std::cout << " Bias(i,j) : " << bias[i][j] << std::endl;
      }
    }
  }

  // Access and write the covariance matrix
  TMatrixD corr        = util::CovarianceMatrixToCorrelationMatrix(bias);
  TVectorD err         = util::CovarianceMatrixToErrorVector(bias);
  
  TFile *fOut = new TFile(output.c_str(),"RECREATE");
  bias.Write("frac_bias");
  corr.Write("corr");
  err.Write("frac_err");
  fOut->Close();

  // If we passed a file to use for debugging, calculate the difference 
  // between every entry in the matrices
  // These should be 0
  if(debug != ""){
    TFile fDebug(debug.c_str(),"READ");
    TMatrixD mDebug = *static_cast<TMatrixD*>(fDebug.Get("frac_bias"));
    assert(mDebug->GetNrows() == bias.GetNrows());

    std::cout << " Difference between every bin in the constructed and input matrices: " << std::endl;
    for(int i = 0; i < bias.GetNrows(); ++i){
      for(int j = 0; j < bias.GetNrows(); ++j){
        double dDebug = mDebug[i][j];
        if(std::abs(bias[i][j] - dDebug) > 0.01)
          std::cout << " In bin (" << i << ", " << j << ") = " << std::abs(bias[i][j] - dDebug) << std::endl;
      }
    }
  }
}
