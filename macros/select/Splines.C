//____________________________________________________________________________
/*!

\brief    Macro to create the splines for the energy scale uncertainty
          Run the macro twice for the leptonic and hadronic energy scale
          uncertainties 

          George Christodoulou <georgios \at hep.ph.liv.ac.uk>
          University of Liverpool

\created   August, 2014

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

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
#include "TCanvas.h"
#include "TSpline.h"
#include "TGraph.h"
#include "TMatrixD.h"
#include "TCanvas.h"
#include "TString.h"

#ifndef __CINT__
#include "MakeSplines.h"
#endif

using namespace std;
using namespace valor;

void Splines(string infhc      = "FHC_LBNE_ND_Tree_v25.root",
	     string inrhc      = "RHC_LBNE_ND_Tree_v25.root",
	     string inTree     = "LBNETree",
	     string outfhc     = "Loutfhc.root",
	     string outrhc     = "Loutrhc.root",
	     string datacard   = "lbne_ndfit-2014a-STT_baseline.xml",
	     string matrixfile = "LeptonEnergyScale.root",
	     bool   createfile = true,
	     bool   leptonic   = true)
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
  // Get the samples, modes and binning
  const int nsamples = 2*mkspl->GetNumberOfSamples(); // factor of two if doing both FHC and RHC
  const int nmodes   = mkspl->GetNumberOfReacModes();

  int erecobins = 0;
  int etruebins = 0;

  if(createfile){
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
    TMatrixD tm3smatrix = mkspl->MakeGraphs(m3sdatacard);

    cout << "Rows = " << tm3smatrix.GetNrows() << " , Columns = " << tm3smatrix.GetNcols() << endl;
    erecobins = mkspl->GetERecoBins();
    etruebins = mkspl->GetETrueBins();

    string m2sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM2S.xml";
    TMatrixD tm2smatrix = mkspl->MakeGraphs(m2sdatacard);
    string m1sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM1S.xml";
    TMatrixD tm1smatrix = mkspl->MakeGraphs(m1sdatacard);
    string m0sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM0S.xml";
    TMatrixD tm0smatrix = mkspl->MakeGraphs(m0sdatacard);
    string p1sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP1S.xml";
    TMatrixD tp1smatrix = mkspl->MakeGraphs(p1sdatacard);
    string p2sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP2S.xml";
    TMatrixD tp2smatrix = mkspl->MakeGraphs(p2sdatacard);
    string p3sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP3S.xml";
    TMatrixD tp3smatrix = mkspl->MakeGraphs(p3sdatacard);
    
    TFile* EnergyScale = new TFile(matrixfile.c_str(), "RECREATE");
    EnergyScale->cd();
    tm3smatrix.Write("m3smatrix");
    tm2smatrix.Write("m2smatrix");
    tm1smatrix.Write("m1smatrix");
    tm0smatrix.Write("m0smatrix");
    tp1smatrix.Write("p1smatrix");
    tp2smatrix.Write("p2smatrix");
    tp3smatrix.Write("p3smatrix");
    EnergyScale->Close();
  }
  else{ // need to run once to get the binning. There is probably another way of doing this!
    string tdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM3S.xml";
    TMatrixD temp = mkspl->MakeGraphs(tdatacard);
    erecobins = mkspl->GetERecoBins();
    etruebins = mkspl->GetETrueBins();
  }
  
  // Open the files and access the trees
  TObjArray* NDModelArray = new TObjArray();

  TFile *File = new TFile(matrixfile.c_str(), "READ");
  TMatrixD *m3smatrix = (TMatrixD*)File->Get("m3smatrix");
  int ncolumns = m3smatrix->GetNcols();
  int nrows = m3smatrix->GetNrows();
  const int ndim = ncolumns*nrows;
  cout << "Rows = " << nrows << " , Columns = " << ncolumns << endl;
  if(nrows != nsamples*nmodes)
    cout << "WARNING:: Number of rows not equal to the samples*modes" << endl;
  
  TMatrixD *m2smatrix = (TMatrixD*)File->Get("m2smatrix");
  TMatrixD *m1smatrix = (TMatrixD*)File->Get("m1smatrix");
  TMatrixD *m0smatrix = (TMatrixD*)File->Get("m0smatrix");
  TMatrixD *p1smatrix = (TMatrixD*)File->Get("p1smatrix");
  TMatrixD *p2smatrix = (TMatrixD*)File->Get("p2smatrix");
  TMatrixD *p3smatrix = (TMatrixD*)File->Get("p3smatrix");
  
  const int n = 7;
  double xpoint[n] = {-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0};

  TString xaxistitle("E_reco_bins");
  TString yaxistitle("E_true_bins");
 
  // Object array to store all plots, graphs and splines
  TObjArray* NDModelArray = new TObjArray();

  for(int ii=0; ii < nsamples; ii++){

    TString canvasname; canvasname.Form("Sample_%d",ii);
    //TCanvas *c1 = new TCanvas(canvasname.Data(),canvasname.Data(),4800,800);
    //c1->Divide(51,5,0.004);
     for(int iii=0; iii < nmodes; iii++){
      int i = ii*nmodes + iii;
      TString histoname; histoname.Form("Histo_%d_%d",ii,iii);
      TH2D *histo = new TH2D(histoname.Data(),histoname.Data(),erecobins,0,erecobins,etruebins,0,etruebins);

      for(int jj=0; jj < erecobins; jj++){
	for(int kk=0; kk < etruebins; kk++){
	  int j = jj*etruebins + kk;
	  histo->SetBinContent(jj+1,kk+1,m0smatrix(i,j));
	  histo->GetXaxis()->SetTitle(xaxistitle.Data());
	  histo->GetYaxis()->SetTitle(yaxistitle.Data());

	  //for(int j=0; j < ncolumns; j++){
	  TString wname; wname.Form("Spline_%d_%d_%d",ii,iii,j);
	  TString gname; gname.Form("Graph_%d_%d_%d",ii,iii,j);
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
	  
	  // How many points fluctuated
	  int count = 0;
	  for(int k = 0; k < 7; k++)
	    if(num[k] == 1.0)
	      count++;
	  // At least 4 points for the spline contrustion
	  if(count > 3)
	    continue;
	  
	  TGraph *Graph    = new TGraph(n,xpoint,num);
	  TSpline3 *Spline = new TSpline3(wname.Data(),Graph);
	  Graph->SetName(gname.Data());
	  Spline->SetName(wname.Data());
	  NDModelArray->Add(Graph);
	  NDModelArray->Add(Spline);
	  
	  //c1->cd(j);
	  //Graph->Draw();
	  //Spline->Draw();

	}// columns
      }
      // Do not save empty histograms
      if(histo->GetMaximum() > 0)
	NDModelArray->Add(histo);
     }
     //NDModelArray->Add(c1);
  }

  TFile* splines = new TFile("LeptonEnergyScaleGraphs.root", "RECREATE");
  splines->cd();
  NDModelArray->Write();
  splines->Close();

  return;

}


