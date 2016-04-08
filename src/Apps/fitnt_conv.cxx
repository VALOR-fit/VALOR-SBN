//____________________________________________________________________________
/*!

\app       valor_dune-fitnt_conv

\brief     Picks some info out ofan input VALOR fit n-tuple and converts it 
           to a bare ROOT format (for comparison with other fitters or for
           interfacing the VALOR ND-fit with non-VALOR FD fits)

\syntax    valor_dune-fitnt_conv
              --input /path/input_file.root
             [--output /path/output_file.root]
              --format output_format

           --format options:
               * ndfit_extracts_bare_root

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   March 27, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// system
#include <string>
#include <sstream>
// root
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TVector.h>
#include <TMatrixDSym.h>
// fmwk
#include "FitCore/PhysParamList.h"
#include "FitCore/FitParamList.h"
#include "FitCore/FitInputs.h"
#include "Messenger/Messenger.h"
#include "CmdLine/CmdLnArgParser.h"
// dune
#include "Conventions/FitParam.h"

using std::string;
using std::ostringstream;
using namespace valor;

void GetCommandLineArgs (int argc, char ** argv);

string gOptInpFileName;
string gOptOutFileName;
string gOptOutFormat;

int NDFitExtractsBareRoot(void);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  GetCommandLineArgs (argc, argv);

  if(gOptOutFormat == "ndfit_extracts_bare_root") {
    return NDFitExtractsBareRoot();
  }

  return 0;
}
//___________________________________________________________________
int NDFitExtractsBareRoot(void)
{
// Extract selected VALOR/DUNE ND fit info and copy in bare ROOT format
//

  const int buffer_size = 100;

  //
  // Create the output n-tuple and output meta-data
  //

  TTree * out_metadata = new TTree (
     "valor_dune_ndfit_metadata", 
     "Selected metadata for VALOR/DUNE ND-fit");

  int    brPId   = 0;
  char   brPName [buffer_size] = {};
  double brPEmin = 0;
  double brPEmax = 0;

  out_metadata -> Branch("parameter_id",   &brPId,   "parameter_id/I");
  out_metadata -> Branch("parameter_name", (void*)brPName, "parameter_name/C", buffer_size);
  out_metadata -> Branch("enu_true_min",   &brPEmin, "enu_true_min/D");
  out_metadata -> Branch("enu_true_max",   &brPEmax, "enu_true_max/D");

  for(int ip=0; ip < conv::kNFitParams; ip++) {
    conv::PhysParamId_t p = conv::kFitParam[ip];
    brPId = ip;
    strcpy(brPName, util::AsString(p).c_str());
    brPEmin = conv::kFitParamEtrueRange[ip][0];
    brPEmin = conv::kFitParamEtrueRange[ip][1];
    out_metadata->Fill();
  }

  TTree * out_fitnt = new TTree(
     "valor_dune_ndfit_ntuple_extracts",
      "Selected info extracted from the VALOR/DUNE ND-fit n-tuple and converted to bare ROOT format");

  int           brItoy      = 0; 
  TMatrixDSym * brCovMtrx  = 0;
  TVectorD *    brBestFitP = 0;

  out_fitnt->Branch("itoymc",   &brItoy,      "itoymc/I");
  out_fitnt->Branch("covmtrx",  "TMatrixDSym", &brCovMtrx,   1280000,0);
  out_fitnt->Branch("bestfitp", "TVectorD",    &brBestFitP,  1280000,0);

  //
  // Open the input file, get the VALOR fit n-tuple and prepare to read it
  //

  TFile fin(gOptInpFileName.c_str(),"READ");

  TTree * fitnt = (TTree*) fin.Get("valor_dune_nd_ntp");

  PhysParamList * true_param_array     = 0; // input true params
  FitParamList *  best_fit_param_array = 0; // best-fit params
  TObjArray *     best_fit_model_array = 0; // an array of various best-fit model predictions for the current toy-MC experiment 
  TObjArray *     data_array           = 0; // an array of all fitted data distributions for the current toy-MC experiment

  fitnt->SetBranchAddress("true_params",        &true_param_array);
  fitnt->SetBranchAddress("best_fit_params",    &best_fit_param_array);
  fitnt->SetBranchAddress("best_fit_model",     &best_fit_model_array);
  fitnt->SetBranchAddress("data",               &data_array);

  //
  // Loop over toy-MC fits and extract info
  //

  Long_t ntoymc = fitnt->GetEntries();

  for(Long_t itoymc = 0; itoymc < ntoymc; itoymc++) {

    fitnt->GetEntry(itoymc);

    LOG("fitnt_conv", pNOTICE) 
       << "******************************************************* \n" 
       << "Toy-MC experiment: # " << itoymc << "\n"
       << "******************************************************* \n";

    LOG("fitnt_conv", pNOTICE) 
      << "\n >> Input parameter list: \n "
      << *true_param_array;

    LOG("fitnt_conv", pNOTICE) 
      << "\n >> Best-fit parameter list: \n " 
      << *best_fit_param_array;


    brItoy = itoymc;
    brCovMtrx = new TMatrixDSym(*best_fit_param_array->GetCovMatrix());

    int np = best_fit_param_array->GetNumberParameters();
    brBestFitP = new TVectorD(np);
    for(int ip = 0; ip < np; ip++) {
      (*brBestFitP)(ip) = best_fit_param_array->BestFitValueByIndex(ip);
    }

    out_fitnt->Fill();
  }

  fin.Close();

  LOG("fitnt_conv", pNOTICE) 
      << "*** Saving VALOR/DUNE fit n-tuple extracts to: " 
      << gOptOutFileName;

  TFile fout(gOptOutFileName.c_str(),"recreate");
  out_fitnt->Write();
  out_metadata->Write();
  fout.Close();

  LOG("fitnt_conv", pNOTICE)  << "Done!";
  return 0;
}
//___________________________________________________________________
void GetCommandLineArgs(int argc, char ** argv)
{
  LOG("fitnt_conv", pINFO) << "*** Parsing command line arguments";

  // Parse run options for this app
  CmdLnArgParser parser(argc,argv);

  // get output format
  if ( parser.OptionExists("input") ) {
    LOG("fitnt_conv", pINFO) << "Reading output format";
    gOptOutFormat = parser.ArgAsString("format");
  } else {
    LOG("fitnt_conv", pFATAL) 
       << "Unspecified output format - Exiting";
    exit(1);
  }

  // get input VALOR fit file name
  if ( parser.OptionExists("input") ) {
    LOG("fitnt_conv", pINFO) << "Reading input file";
    gOptInpFileName = parser.ArgAsString("input");
  } else {
    LOG("fitnt_conv", pFATAL) 
       << "Unspecified input filename - Exiting";
    exit(1);
  }

  // get output file name (or set default)
  if ( parser.OptionExists("output") ) {
    LOG("fitnt_conv", pINFO) << "Reading output file";
    gOptOutFileName = parser.ArgAsString("output");
  } else {

    // set default
    string inpname = gOptInpFileName;
    unsigned int L = inpname.length();
    // if the last 4 characters are "root" (file extension) then remove them
    if(inpname.substr(L-4, L).find("root") != string::npos) {
        inpname.erase(L-4, L);
    }
/*
    // remove vfnt.
    size_t pos = inpname.find(".");
    if(pos != string::npos) {
         inpname.erase(pos, pos+4);
    }
*/
    ostringstream name;
    name << inpname << "vfnt_extracts.root";

    gOptOutFileName = gSystem->BaseName(name.str().c_str());
  }

}
//_________________________________________________________________________________
