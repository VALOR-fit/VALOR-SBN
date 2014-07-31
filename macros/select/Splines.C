#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

#include <string>
#include <sstream>

#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"

#ifndef __CINT__
#include "MakeSplines.h"
#endif

using namespace std;
using namespace valor;

void Splines(string infhc      = "FHC_LBNE_ND_Tree_v25.root",
	     string inrhc      = "FHC_LBNE_ND_Tree_v25.root",
	     string inTree     = "LBNETree",
	     string outfhc     = "hadronicoutfhc.root",
	     string outrhc     = "hadronicoutrhc.root",
	     string datacard   = "lbne_ndfit-2014a-STT_baseline.xml",
	     string matrixfile = "HadronEnergyScale.root",
	     bool   leptonic   = false)
{
  // Define the paths
  const char* valor_dir = getenv("VALOR_LBNX");
  string fdatacard = string(valor_dir) + "/config/" + datacard;

  string inFilefhc = string(valor_dir) + "/data/" + infhc;
  string inFilerhc = string(valor_dir) + "/data/" + inrhc;

  string outFilefhc = string(valor_dir) + "/data/" + outfhc;
  string outFilerhc = string(valor_dir) + "/data/" + outrhc;
  // Main constructor
  MakeSplines *mkspl = new MakeSplines();
  // Read the datacard
  mkspl->ReadXMLDatacard(fdatacard);
  // Save the trees and files
  TObjArray *fhc = mkspl->CreateArray(inFilefhc,inTree,leptonic);
  TObjArray *rhc = mkspl->CreateArray(inFilerhc,inTree,leptonic);
  
  TFile* outfilefhc = new TFile(outFilefhc.c_str(), "RECREATE");
  outfilefhc->cd();
  fhc->Write();
  outfilefhc->Close();

  TFile* outfilerhc = new TFile(outFilerhc.c_str(), "RECREATE");
  outfilerhc->cd();
  rhc->Write();
  outfilerhc->Close();
  
  // Make the matrices 
  string m3sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM3S.xml";
  TMatrixD m3smatrix = mkspl->MakeGraphs(m3sdatacard);
  int ncolumns = m3smatrix.GetNcols();
  int nrows = m3smatrix.GetNrows();
  cout << "Rows = " << nrows << " , Columns = " << ncolumns << endl;
  string m2sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM2S.xml";
  TMatrixD m2smatrix = mkspl->MakeGraphs(m2sdatacard);
  string m1sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM1S.xml";
  TMatrixD m1smatrix = mkspl->MakeGraphs(m1sdatacard);
  string m0sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM0S.xml";
  TMatrixD m0smatrix = mkspl->MakeGraphs(m0sdatacard);
  string p1sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP1S.xml";
  TMatrixD p1smatrix = mkspl->MakeGraphs(p1sdatacard);
  string p2sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP2S.xml";
  TMatrixD p2smatrix = mkspl->MakeGraphs(p2sdatacard);
  string p3sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP3S.xml";
  TMatrixD p3smatrix = mkspl->MakeGraphs(p3sdatacard);
  
  TFile* EnergyScale = new TFile("HadronEnergyScale.root", "RECREATE");
  EnergyScale->cd();
  m3smatrix.Write("m3smatrix");
  m2smatrix.Write("m2smatrix");
  m1smatrix.Write("m1smatrix");
  m0smatrix.Write("m0smatrix");
  p1smatrix.Write("p1smatrix");
  p2smatrix.Write("p2smatrix");
  p3smatrix.Write("p3smatrix");
  EnergyScale->Close();

  // Open the files and access the trees
  TObjArray* NDModelArray = new TObjArray();
  const int n = 7;
  //TFile *File = new TFile(matrixfile.c_str(), "READ");
  //TMatrixD *m3smatrix = (TMatrixD*)File->Get("m3smatrix");
  //int ncolumns = m3smatrix->GetNcols();
  //int nrows = m3smatrix->GetNrows();
  int ncolumns = m3smatrix.GetNcols();
  int nrows = m3smatrix.GetNrows();
  const int ndim = ncolumns*nrows;
  cout << "Rows = " << nrows << " , Columns = " << ncolumns << endl;
  //TMatrixD *m2smatrix = (TMatrixD*)File->Get("m2smatrix");
  //TMatrixD *m1smatrix = (TMatrixD*)File->Get("m1smatrix");
  //TMatrixD *m0smatrix = (TMatrixD*)File->Get("m0smatrix");
  //TMatrixD *p1smatrix = (TMatrixD*)File->Get("p1smatrix");
  //TMatrixD *p2smatrix = (TMatrixD*)File->Get("p2smatrix");
  //TMatrixD *p3smatrix = (TMatrixD*)File->Get("p3smatrix");

  double xpoint[n] = {-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0};

  for(int i=0; i < nrows; i++){
    for(int j=0; j < ncolumns; j++){
      TString wname; wname.Form("Spline_%d_%d",i,j);
      TString gname; gname.Form("Graph_%d_%d",i,j);
      double m3signum = m3smatrix(i,j);
      double m2signum = m2smatrix(i,j);
      double m1signum = m1smatrix(i,j);
      double m0signum = m0smatrix(i,j);
      double p1signum = p1smatrix(i,j);
      double p2signum = p2smatrix(i,j);
      double p3signum = p3smatrix(i,j);
      double signum[n] = {m3signum,m2signum,m1signum,m0signum,p1signum,p2signum,p3signum};
      double num[n] = {1.0};
      for(int k = 0; k < n; k++){
	if(m0signum == 0.0)
	  num[k] = 1.0;
	else{
	  num[k] = signum[k]/m0signum;
	  if(num[k] == 0.0)
	    num[k] = 1.0;
	}
      }

      // How many point fluctuated
      int count = 0;
      for(int k = 0; k < 7; k++)
	if(num[k] == 1.0)
	  count++;
      // At least 3 points for the spline contrustion
      if(count < 4)
	continue;

      TGraph *Graph    = new TGraph(n,xpoint,num);
      TSpline3 *Spline = new TSpline3(wname.Data(),Graph);
      Graph->SetName(gname.Data());
      NDModelArray->Add(Graph);
      NDModelArray->Add(Spline);

    }
  }
    
  TFile* splines = new TFile("HadronEnergyScaleGraphs.root", "RECREATE");
  splines->cd();
  NDModelArray->Write();
  splines->Close();

  return;

}


