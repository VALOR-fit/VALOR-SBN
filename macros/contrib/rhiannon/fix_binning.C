#include <iostream>
#include <vector> 

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

std::vector<double> ChangeBinning(TH1D* hist, double max_bins, double max_error);

void fix_binning(const char *file_name, const char *hist_name, double max_bins, double max_error = 0.1) {

  TFile *f = new TFile(file_name, "read");
  TH1D  *h = static_cast<TH1D*>(f->Get(hist_name));
  std::vector<double> bin_edges = ChangeBinning(h,max_bins,max_error);

  std::cout << "New bins for a maximum statistical error/bin of " << max_error << ": " << std::endl;
  for(const double &b : bin_edges){
    std::cout << b << std::endl;
  }
}

std::vector<double> ChangeBinning(TH1D* hist, double max_bins, double max_error){

  std::vector<double> bin_edges;
  for(size_t i = 0; i < hist->GetNbinsX(); i++){
    bin_edges.push_back(hist->GetBinLowEdge(i+1));
  }
  bin_edges.push_back(max_bins);

  for(size_t i = 0; i < hist->GetNbinsX(); i++){
    if(hist->GetBinError(i+1)/hist->GetBinContent(i+1) > max_error){

      if(i != hist->GetNbinsX()-1){
        bin_edges.erase(bin_edges.begin()+i+1);
        double edges_array[bin_edges.size()];
        std::copy(bin_edges.begin(), bin_edges.end(), edges_array);
        TH1D* new_hist = (TH1D*)hist->Rebin(bin_edges.size()-1, "new", edges_array);
        return ChangeBinning(new_hist, max_bins, max_error);
      }

      else{
        bin_edges.erase(bin_edges.begin()+(bin_edges.size()-2));
        return bin_edges;
      }

    }
  }
  return bin_edges;
}
