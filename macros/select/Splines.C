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
	     string outfhc     = "outfhc.root",
	     string outrhc     = "outrhc.root",
	     string datacard   = "lbne_ndfit-2014a-STT_baseline.xml",
	     string matrixfile = "LeptonEnergyScaleMatrix.root",
	     string splinefile = "LeptonEnergyScaleSplines.root",
	     double horncurrent= 2,
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
  const int nsamples = horncurrent*mkspl->GetNumberOfSamples(); // factor of two if doing both FHC and RHC
  const int nmodes   = mkspl->GetNumberOfReacModes();
  // Number of bin zones
  const int nzones   = mkspl->GetNumberOfBinZones();

  int erecobins[1] = {0};
  int etruebins[1] = {0};
  int yrecobins[1] = {0};

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
  
    // Datacards
    string m3sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM3S.xml";
    string m2sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM2S.xml";
    string m1sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM1S.xml";
    string m0sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM0S.xml";
    string p1sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP1S.xml";
    string p2sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP2S.xml";
    string p3sdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESMP3S.xml";

    // File to store the binning matrices
    TFile* EnergyScale = new TFile(matrixfile.c_str(), "RECREATE");
    // Get and store the binning matrices
    for(int i=0; i < nzones; i++){
      TString zonestr; zonestr.Form("z%i",i);
      TMatrixD tm3smatrix = mkspl->MakeGraphs(m3sdatacard,i);
      TMatrixD tm2smatrix = mkspl->MakeGraphs(m2sdatacard,i);
      TMatrixD tm1smatrix = mkspl->MakeGraphs(m1sdatacard,i);
      TMatrixD tm0smatrix = mkspl->MakeGraphs(m0sdatacard,i);
      TMatrixD tp1smatrix = mkspl->MakeGraphs(p1sdatacard,i);
      TMatrixD tp2smatrix = mkspl->MakeGraphs(p2sdatacard,i);
      TMatrixD tp3smatrix = mkspl->MakeGraphs(p3sdatacard,i);

      cout << "INFO::Rows = " << tm3smatrix.GetNrows() << " , Columns = " << tm3smatrix.GetNcols() << endl;
      erecobins[i] = mkspl->GetERecoBins();
      etruebins[i] = mkspl->GetETrueBins();
      yrecobins[i] = mkspl->GetYRecoBins();
      
      TString m3 = "m3smatrix_" + zonestr;
      TString m2 = "m2smatrix_" + zonestr;
      TString m1 = "m1smatrix_" + zonestr;
      TString m0 = "m0smatrix_" + zonestr;
      TString p1 = "p1smatrix_" + zonestr;
      TString p2 = "p2smatrix_" + zonestr;
      TString p3 = "p3smatrix_" + zonestr;
      EnergyScale->cd();
      tm3smatrix.Write(m3.Data());
      tm2smatrix.Write(m2.Data());
      tm1smatrix.Write(m1.Data());
      tm0smatrix.Write(m0.Data());
      tp1smatrix.Write(p1.Data());
      tp2smatrix.Write(p2.Data());
      tp3smatrix.Write(p3.Data());
      EnergyScale->Close();
    }
  }
  else{ // need to run once to get the binning. There is probably another way of doing this!
    string tdatacard = string(valor_dir) + "/config/lbne_ndfit-2014a-STT_baseline_ESM3S.xml";
    for(int i=0; i < nzones; i++){
      TMatrixD temp = mkspl->MakeGraphs(tdatacard,i);
      erecobins[i] = mkspl->GetERecoBins();
      etruebins[i] = mkspl->GetETrueBins();
      yrecobins[i] = mkspl->GetYRecoBins();
    }
  }

  // Open the files and access the trees
  TFile *File = new TFile(matrixfile.c_str(), "READ");

  const int n = 7;
  double xpoint[n] = {-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0};

  TString xaxistitle("E_reco_bins");
  TString yaxistitle("E_true_bins");
  TString zaxistitle("y_reco_bins");

  for(int m=0; m < nzones; m++){
    
    TString zonestr; zonestr.Form("z%i",m);
    TString m3 = "m3smatrix_" + zonestr;
    TString m2 = "m2smatrix_" + zonestr;
    TString m1 = "m1smatrix_" + zonestr;
    TString m0 = "m0smatrix_" + zonestr;
    TString p1 = "p1smatrix_" + zonestr;
    TString p2 = "p2smatrix_" + zonestr;
    TString p3 = "p3smatrix_" + zonestr;
    
    TMatrixD *m3smatrix = (TMatrixD*)File->Get(m3.Data());
    int ncolumns = m3smatrix->GetNcols();
    int nrows = m3smatrix->GetNrows();
    const int ndim = ncolumns*nrows;
    cout << "INFO::Rows = " << nrows << " , Columns = " << ncolumns << endl;
    if(nrows != nsamples*nmodes)
      cout << "WARNING:: Number of rows not equal to the samples*modes" << endl;
    
    TMatrixD *m2smatrix = (TMatrixD*)File->Get(m2.Data());
    TMatrixD *m1smatrix = (TMatrixD*)File->Get(m1.Data());
    TMatrixD *m0smatrix = (TMatrixD*)File->Get(m0.Data());
    TMatrixD *p1smatrix = (TMatrixD*)File->Get(p1.Data());
    TMatrixD *p2smatrix = (TMatrixD*)File->Get(p2.Data());
    TMatrixD *p3smatrix = (TMatrixD*)File->Get(p3.Data());

    // Object array to store all plots, graphs and splines
    TObjArray* NDModelArray = new TObjArray();
    
    for(int ii=0; ii < nsamples; ii++){
      
      TString canvasname; canvasname.Form("Sample_%i",ii);
      //TCanvas *c1 = new TCanvas(canvasname.Data(),canvasname.Data(),4800,800);
      //c1->Divide(51,5,0.004);
      for(int iii=0; iii < nmodes; iii++){
	int i = ii*nmodes + iii;
	TString histoname; histoname.Form("ERecoTrueHisto_%i_%i",ii,iii);
	TString histoname1; histoname1.Form("ERecoYRecoHisto_%i_%i",ii,iii);
	TH2D *histo   = new TH2D(histoname.Data(),histoname.Data(),erecobins[m],0,erecobins[m],etruebins[m],0,etruebins[m]);
	TH2D *histoEY = new TH2D(histoname1.Data(),histoname1.Data(),erecobins[m],0,erecobins[m],yrecobins[m],0,yrecobins[m]);
	
	for(int jj=0; jj < erecobins[m]; jj++){
	  for(int ss=0; ss < yrecobins[m]; ss++){
	    int etrueentries = 0;
	    for(int kk=0; kk < etruebins[m]; kk++){
	      int j = jj*etruebins[m] + ss*etruebins[m] + kk;

	      // Empty matrix elements
	      if(m0smatrix(i,j) == -10000){continue;}

	      etrueentries += m0smatrix(i,j);

	      histo->SetBinContent(jj+1,kk+1,m0smatrix(i,j));
	      histo->GetXaxis()->SetTitle(xaxistitle.Data());
	      histo->GetYaxis()->SetTitle(yaxistitle.Data());
	    
	      //for(int j=0; j < ncolumns; j++){
	      TString wname; wname.Form("Spline_%i_%i_%i_%i_%i_%i",m,ii,iii,jj,ss,kk);
	      TString gname; gname.Form("Graph_%i_%i_%i_%i_%i_%i",m,ii,iii,jj,ss,kk);
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
	      
	    }// etruebins
	    histoEY->SetBinContent(jj+1,ss+1,etrueentries);
	    histoEY->GetXaxis()->SetTitle(xaxistitle.Data());
	    histoEY->GetYaxis()->SetTitle(zaxistitle.Data());
	  } // yrecobins
	} // erecobins
	// Do not save empty histograms
	if(histo->GetMaximum() > 0)
	  NDModelArray->Add(histo);
	if(histoEY->GetMaximum() > 0)
	  NDModelArray->Add(histoEY);
      } // nmodes
      //NDModelArray->Add(c1);
    } // nsamples
  } // nzones

  TFile* splines = new TFile(splinefile.c_str(), "RECREATE");
  splines->cd();
  NDModelArray->Write();
  splines->Close();

  return;

}


