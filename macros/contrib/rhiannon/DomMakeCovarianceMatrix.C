#include "TPrincipal.h"

void  MakeMatrix(){

  //using namespace valor;
  //  using namespace valor::conv;

  TPrincipal tp(66);

  TFile *f1 = TFile::Open("modern_reco_nue_int-flux-0-to-1000.root");
  TIter next(f1->GetListOfKeys());
  TKey *key;

  std::map<int,std::vector<double> > arrays;
 
  while ((key = (TKey*)next())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    TH1 *h = (TH1*)key->ReadObj();

    TString name = h->GetName();
    size_t last_ = name.Last('_');
    int universe = (name.Remove(0,last_+1)).Atoi();

    if(arrays.find(universe) == arrays.end()){
      arrays[universe].resize(66,-999);
    }
    
    name = h->GetName();
    if(name.Contains("nd")){
      for(unsigned j=0; j<11;++j){
	std::cout << "sbnd bin content: " << h->GetBinContent(1+j) << std::endl;
	arrays[universe][j] = h->GetBinContent(1+j);  
      }
    }
    else if(name.Contains("uboone")){
      for(unsigned j=0; j<11;++j){
	std::cout << "uboone bin content: " << h->GetBinContent(1+j) << std::endl;
	arrays[universe][11+j] = h->GetBinContent(1+j);  
      }
    }
    else if(name.Contains("icarus")){
      for(unsigned j=0; j<11;++j){
	std::cout << "icaurs bin content: " << h->GetBinContent(1+j) << std::endl;
	arrays[universe][22+j] = h->GetBinContent(1+j);  
      }
    }
  }

  TFile *f2 = TFile::Open("modern_reco_nue_int-flux-0-to-1000.root");
  TIter next1(f2->GetListOfKeys());
  TKey *key1;

  while ((key = (TKey*)next1())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    TH1 *h = (TH1*)key->ReadObj();

    TString name = h->GetName();
    size_t last_ = name.Last('_');
    int universe = (name.Remove(0,last_+1)).Atoi();

    if(arrays.find(universe) == arrays.end()){
      arrays[universe].resize(66,-999);
    }
    
    name = h->GetName();
    if(name.Contains("nd")){
      for(unsigned j=0; j<11;++j){
	std::cout << "sbnd bin content: " << h->GetBinContent(1+j) << std::endl;
	arrays[universe][j+33] = h->GetBinContent(1+j);  
      }
    }
    else if(name.Contains("uboone")){
      for(unsigned j=0; j<11;++j){
	std::cout << "uboone bin content: " << h->GetBinContent(1+j) << std::endl;
	arrays[universe][44+j] = h->GetBinContent(1+j);  
      }
    }
    else if(name.Contains("icarus")){
      for(unsigned j=0; j<11;++j){
	std::cout << "icaurs bin content: " << h->GetBinContent(1+j) << std::endl;
	arrays[universe][55+j] = h->GetBinContent(1+j);  
      }
    }
  }


  for(auto const& vec: arrays){
    double array[66];

    //Only add rows wit contributions from all three detectors
    if(std::find(vec.second.begin(), vec.second.end(), -999) != vec.second.end()){
      std::cout << "Not fully formed binning" << std::endl;
      continue;
    }

    if(vec.second.size() != 66){
      std::cout << "something has gone wrong" << std::endl;
      return;
    }

    for(int i=0; i<vec.second.size(); ++i){
      array[i] = vec.second.at(i);
    } 
    tp.AddRow(array);
  }

  
  TMatrixD cov = valor::util::LowerTriangularMatrixToSymMatrix(*tp.GetCovarianceMatrix());
  
  TVectorD mean_vec = *tp.GetMeanValues();

  TMatrixD frac_cov = cov;
  for(int i=0; i<cov.GetNrows(); ++i){
    for(int j=0; j<cov.GetNcols(); ++j){
      frac_cov[i][j] = frac_cov[i][j] / (mean_vec[i]*mean_vec[j]);
    }
  }

  TVectorD vec = TVectorD(cov.GetNrows());
  for(int i=0; i<cov.GetNrows(); ++i){
    vec[i] = TMath::Sqrt(frac_cov[i][i]);
  }
  vec.Draw();

  TFile* outputfile = new TFile("covarience_matrix.root","RECREATE");
  frac_cov.Write("frac_cov");

}
