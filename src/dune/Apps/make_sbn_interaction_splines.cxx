//____________________________________________________________________________
/*!

  \app       valor_dune-make_sbn_interaction_splines

  \brief     

  \syntax    valor_dune-make_sbn_interaction_splines         
               --input  input_analysis_file.root
               --output output_sbn_interaction_splines_file.root
               --sample sample_name
               --systematic sbn_systematic_name

  \author    Rhiannon Jones <rjones@hep.ph.liv,ac,uk>
             University of Liverpool

  \created   March 15th, 2020

  \copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// c++
#include <string>
#include <iostream>
#include <fstream>

// ROOT
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TSpline.h>
#include <TString.h>
#include <TSystem.h>
#include <TMath.h>

// valor
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/NameRegistry.h"
#include "valor/VArray/VALORArray.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Conventions/BeamConf.h"
#include "valor/Conventions/Sample.h"
#include "valor/Conventions/Detector.h"
#include "valor/Conventions/ParameterPool.h"
#include "valor/Conventions/Parameter.h"
#include "valor/Conventions/ModeList.h"
#include "valor/KineBinning/VALORBinning.h"
#include "valor/Conventions/Parameter.h"
#include "valor/Conventions/ReacMode.h"
#include "valor/Conventions/ParameterPool.h"
#include "valor/GENIEUtilities/GENIEIncludes.h"
#include "valor/GENIEUtilities/UtlEventRec.h"
#include "valor/Utilities/SingleSampleKineBinning.h"
#include "valor/Utilities/RFL.h"
#include "valor/Utilities/KinematicBin.h"
#include "valor/FitCore/CompoundFitElements.h"
#include "valor/FitElements/GenericSingleSampleFitModel.h"
#include "valor/FitCore/UtlFitParamList.h"


using std::string;
using namespace valor;
using namespace valor::conv;

std::vector<std::string> interaction_systematics =
 { "genie_ccresAxial_Genie",
   "genie_ncresAxial_Genie",
   "genie_qema_Genie",
   "genie_NC_Genie",
   "genie_NonResRvbarp1pi_Genie",
   "genie_NonResRvbarp2pi_Genie",
   "genie_NonResRvp1pi_Genie",
   "genie_NonResRvp2pi_Genie",
 };
std::vector<std::string> flux_systematics =
 { "expskin_FluxUnisim",
   "horncurrent_FluxUnisim",
   "kminus_PrimaryHadronNormalization",
   "kplus_PrimaryHadronFeynmanScaling",
   "kzero_PrimaryHadronSanfordWang",
   "nucleoninexsec_FluxUnisim",
   "nucleonqexsec_FluxUnisim",
   "nucleontotxsec_FluxUnisim",
   "piminus_PrimaryHadronSWCentralSplineVariation",
   "pioninexsec_FluxUnisim",
   "pionqexsec_FluxUnisim",
   "piontotxsec_FluxUnisim",
   "piplus_PrimaryHadronSWCentralSplineVariation"
 };
 
void        GetVariations(std::vector<double> &vs, const std::string &in, const std::string &sy);
void        GetKnots(const std::vector<double> &vars, const std::vector<double> &knots, std::map<unsigned int, double> &vs, std::map<unsigned int, double> &kns);
std::string GetSystematic(const std::string &sy);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  
  // Read command line arguments
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_EXPT/config/apps/universes.arg:$VALOR_EXPT/config/apps/make_sbn_interaction_splines.arg");
  VLOG("valor_dune", pNOTICE) << arg;

  /*
  bool include_sb       = arg.GetBool("include-simple-binning");
  int  max_events       = arg.GetInt("max-events");
  size_t n_universes    = arg.GetInt("n-universes");
  */

  // Get arguments
  string arg_config_file = arg.GetString("config");
  string arg_output_file = arg.GetString("output");
  string arg_input_file  = arg.GetString("input");
  string arg_sample      = arg.GetString("sample");
  string arg_detector    = arg.GetString("detector");
  string arg_systematic  = arg.GetString("systematic");
  bool include_sb        = arg.GetBool("include-simple-binning");
  
  // From arguments
  Sample_t   sample      = util::SampleFromString   (arg_sample    );
  Detector_t detector    = util::DetectorFromString (arg_detector  );
  
  //
  // Get the systematic from the argument list and make sure it exists in the universes
  //
  std::string syst = GetSystematic(arg_systematic);
  if(syst.empty()){
    VLOG("valor_dune",pFATAL) << syst << "Systematic came back empty";
    util::Die(-1);
  }
  VLOG("valor_dune",pNOTICE) << syst << "Systematic parameter " << syst << " found";

  // 
  // Read in the universe-variation txt file and use it to determine the best universes to generate the 13 knots
  // for -3sigma -> +3sigma variations in steps of 0.5sigma
  //
  // 1) Read in the text file
  // 2) Find the row which starts with the name of the variation we want
  // 3) Pass the space-delimeted values to a vector
  //
  // Get the variations
  std::vector<double> variations;
  variations.clear();
  GetVariations(variations, arg_input_file, arg_systematic);
  // Check the variations
  if(!variations.size()){
    VLOG("valor_dune",pFATAL) << syst << "Variations came back empty";
    util::Die(-1);
  }
  VLOG("valor_dune",pNOTICE) << syst << "Variations in vector form of size " << variations.size();
  
  // 
  // 4) Find the entries which most closely match the knot positions
  // 5) Pass the universe entry (integer) and value (double) corresponding to these knots to a map
  //
  // Number of knots for the specified systematic parameter
  const std::vector<double> &knots = {-3.0,-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5,3.0};
  const int   n_knots              = knots.size();
  const int   inom                 = 5;
  const float knot_dial_min        = -3.0;
  const float knot_dial_max        =  3.0;
  const float knot_dial_step       = (knot_dial_max - knot_dial_min) / (n_knots-1);

  // Chosen universe specifications
  std::vector<unsigned int> ids;
  std::map<unsigned int, double> vars;
  std::map<unsigned int, double> kns;
  std::map<unsigned int, double>::iterator itr;
  ids.clear(); vars.clear(); kns.clear();

  GetKnots(variations,knots,vars,kns);
  VLOG("valor_dune",pNOTICE) << "Universe ID and variation value for knots : ";
  for(itr = vars.begin(); itr != vars.end(); ++itr) {
    VLOG("valor_dune",pNOTICE) << "ID: " << itr->first << ", variation: " << itr->second << " for knot: " << kns.at(itr->first);
    ids.push_back(itr->first);
  }

  // 
  // 6) Build the splines with the universe ID list passed to the tweaked GSSFM universe-based functions
  // 
  // Get model & configure
  // Make an elements without reading the MC
  std::string elem_readopt("nomc nosplines");
  CompoundFitElements * elements = new CompoundFitElements();
  std::string config_path = util::CompleteConfigPath(arg_config_file);
  elements->Read(config_path,elem_readopt.c_str());

  // Then tell it about the universes and read the MC
  FitModelABC * model = elements->FitModel();
  CompoundFitModel * cmodel = dynamic_cast<CompoundFitModel*>(model);
  assert(cmodel);
  GenericSingleSampleFitModel * gmodel = 0;
  bool got_appropriate_model = false;
  for (unsigned int ism = 0 ; ism < cmodel->GetNSubModels() ; ism++) {
    gmodel = dynamic_cast<GenericSingleSampleFitModel*>(cmodel->GetSubModel(ism));
    if  (gmodel->GetDetector() == detector && 
         gmodel->GetSample()   == sample) 
      { got_appropriate_model = true; break; }
  }
  if (!got_appropriate_model) {
    VLOG("valor_dune", pFATAL) << "Failed to identify appropriate fit model to get binning.";
  }
 
  // For spline generation
  const util::RFL & rfl                   = *(gmodel->GetRFL());
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());
  
  // Binning choice needs to be made carefully, likely that stats will be very low in
  // some bins in the standard 2D ereco-etrue param space so will need to redefine
  //
  // Redefinition needs to be along the edges of existing bins in the analysis so as to
  // not cause leakage 
  //
  const VALORBinning * reco_ob = (binning.RecoOptBinning());
  const VALORBinning * reco_sb = (binning.RecoSmpBinning());
  const int n_reco_bins_ob  = reco_ob->NBins();
  const int n_reco_bins_sb  = reco_sb->NBins();

  const ModeList *ml = gmodel->GetModeList();
  const std::vector<conv::ReacMode_t> & read_modes = ml->Modes();

  // Arrays to store the number of events in each MC template bin
  // for each systematic parameter tweak
  VALORArray * mc_templ_sb [n_knots] [read_modes.size()];
  VALORArray * mc_templ_ob [n_knots] [read_modes.size()];

  for(int iknot = 0; iknot < n_knots; iknot++) {
    unsigned int imode = 0;
    for(ReacMode_t m : read_modes) {
      const VALORBinning * true_sb = binning.TrueSmpBinning(m);
      const int n_true_bins_sb  = true_sb->NBins();
      if (include_sb) {
        mc_templ_sb [iknot][imode] = 
          new VALORArray(n_reco_bins_sb, n_true_bins_sb);
        mc_templ_sb [iknot][imode] -> SetAll(0.);
      }
      mc_templ_ob [iknot][imode] = 
        new VALORArray(n_reco_bins_ob, n_true_bins_sb);
      mc_templ_ob [iknot][imode] -> SetAll(0.);
      imode++;
    }
  }
  /*
   * After dtermining the universes to save for the given parameter, mode, and bin
   * Then can define a function like SetUniversesToRead(std::vector<int>) where the vector of ints is the
   * list of universe entries to read and save 
   * Then add/change all the analogous functions to those associated with SetUniverseRangeToRead(0,n_universes)
   * This is how to create the templates for the spline knots.
   */
  gmodel->SetUniversesToRead(ids);
  gmodel->SetUniverseParameterToRead(syst);

  // And finally read the MC properly
  std::string model_readopt("forcedst nosplines");
  gmodel->Read(gmodel->GetLastConfigFileRead().c_str(),model_readopt.c_str());

  return 0;
}
//___________________________________________________________________

void GetVariations(std::vector<double> &vs, const std::string &in, const std::string &sy){

  std::ifstream uFile;
  uFile.open(in);
  if(!uFile){
    VLOG("valor_dune",pFATAL) << "Unable to open universe file: " << in;
    exit(1);
  }
  if(vs.size()){
    VLOG("valor_dune",pFATAL) << "Vector to hold variations is not empty";
    return;
  }

  while(!uFile.eof()){
    std::string line = "";
    std::getline(uFile,line);
    size_t found_v = line.find(sy);
    if(found_v != std::string::npos){
      // Clean up the line to pass the variations to the vector
      VLOG("valor_dune",pDEBUG) << "Found line containing " << sy << " parameters: \n" << line;
      VLOG("valor_dune",pDEBUG) << "Removing systematic name from line";
      line.erase(0, found_v+sy.length());
      VLOG("valor_dune",pDEBUG) << "Line now contains: \n" << line;

      // Pass the remaining contents of the line to a vector of doubles
      double value;
      std::stringstream lineValue(line);
      while(lineValue >> value){
        VLOG("valor_dune",pDEBUG) << "Variation: " << value;
        vs.push_back(value);
      }
      break;
    }  
  } // variations text file
} // GetVariations
//___________________________________________________________________

std::string GetSystematic(const std::string &sy){

  std::string syst = "";
  bool found_syst = false;
  for(const std::string &s : interaction_systematics){
    size_t found_s = s.find(sy);
    if(found_s != std::string::npos){
      syst = s;
      VLOG("valor_dune", pNOTICE) << "Found the chosen interaction systematic: " << syst;
      found_syst = true;
      break;
    }
  }

  if(!found_syst){
    for(const std::string &s : flux_systematics){
      size_t found_s = s.find(sy);
      if(found_s != std::string::npos){
        syst = s;
        VLOG("valor_dune", pNOTICE) << "Found the chosen flux systematic: " << syst;
        found_syst = true;
        break;
      }
    }
  }

  if(!found_syst){
    VLOG("valor_dune", pFATAL) << "Couldn't find the chosen systematic parameter: " << sy;
    util::Die(-1);
  }
  return syst;
}
//___________________________________________________________________

void GetKnots(const std::vector<double> & vars, const std::vector<double> &knots, std::map<unsigned int, double> &vs, std::map<unsigned int, double> &kns){
  for(const double &kn : knots){
    double min_diff     = 999.;
    double best_var     = -999.;
    unsigned int min_id = 999; 
    for(unsigned int v = 0; v < vars.size(); ++v){
      //Check if the current variation is closest to the current knot
      //At the end of the loop, push back the closest variation and it's location in the vector
      double var = vars[v];
      if(abs(kn-var) < abs(min_diff)){
        min_diff  = abs(kn-var);
        best_var  = var;
        min_id    = v;
      }
    }
    vs.insert({min_id,best_var});
    kns.insert({min_id,kn});
  }
  if(vs.size() != kns.size()){
    VLOG("valor_dune",pFATAL) << "Number of entries in knots and variation lists don't match";
    VLOG("valor_dune",pFATAL) << "NKnots: " << kns.size() << ", NVariations: " << vs.size();
    util::Die(-1);
  }
}
  /*
  Parameter p = ParameterPool::Instance()->ParamFromString(arg_systematic);
  PhysParamId_t fit_param = p.GetID();
  
  if (sample == ksUndefined || fit_param == kPhypUndefined) {
    std::cerr<<"Bad configuration."<<std::endl;
    std::cerr<<"Sample:     "<<arg_sample     <<"\t => "<< util::AsString(sample)  <<std::endl;
    std::cerr<<"Detector:   "<<arg_detector   <<"\t => "<< util::AsString(detector)<<std::endl;
    std::cerr<<"Syst:       "<<arg_systematic << std::endl;
    std::cerr<<" to VALOR   "<< "\t => "<<util::NameRegistry::Instance()->AsString(fit_param)<<std::endl;
  }
  assert(sample    != ksUndefined   );
  assert(detector  != kdUndefined   );
  assert(fit_param != kPhypUndefined);

  CompoundFitModel * compound_model = dynamic_cast<CompoundFitModel*>(elements->FitModel());
  assert(compound_model);
  GenericSingleSampleFitModel * fit_model = 0;
  bool got_appropriate_model = false;
  for (unsigned int ism = 0 ; ism < compound_model->GetNSubModels() ; ism++) {
    fit_model = dynamic_cast<GenericSingleSampleFitModel*>(compound_model->GetSubModel(ism));
    if  (fit_model->GetDetector() == detector && 
         fit_model->GetSample()   == sample ) 
      { got_appropriate_model = true; break; }
  }
  if (!got_appropriate_model) {
    VLOG("make_sbn_interaction_splines", pFATAL) << "Failed to identify appropriate fit model to get binning.";
  }
  
  const util::RFL & rfl                   = *(fit_model->GetRFL());
  const SingleSampleKineBinning & binning = *(fit_model->GetBinning());
  
  // Make it an option here to use the Xsec binning instead
  const VALORBinning * reco_ob = (binning.RecoOptBinning());
  const VALORBinning * reco_sb = (binning.RecoSmpBinning());
  const int n_reco_bins_ob  = reco_ob->NBins();
  const int n_reco_bins_sb  = reco_sb->NBins();
  
  */

  /*
  ModeList ml = fit_model->GetModeList();
  const std::vector<conv::ReacMode_t> & read_modes = ml.Modes();

  // Arrays to store the number of events in each MC template bin
  // for each systematic parameter tweak
  VALORArray * mc_templ_sb [n_twks] [read_modes.size()];
  VALORArray * mc_templ_ob [n_twks] [read_modes.size()];

  for(int itwk = 0; itwk < n_twks; itwk++) {
    unsigned int imode = 0;
    for(ReacMode_t m : read_modes) {
      const VALORBinning * true_sb = binning.TrueSmpBinning(m);
      const int n_true_bins_sb  = true_sb->NBins();
      if (include_sb) {
        mc_templ_sb [itwk][imode] = 
          new VALORArray(n_reco_bins_sb, n_true_bins_sb);
        mc_templ_sb [itwk][imode] -> SetAll(0.);
      }
      mc_templ_ob [itwk][imode] = 
        new VALORArray(n_reco_bins_ob, n_true_bins_sb);
      mc_templ_ob [itwk][imode] -> SetAll(0.);
      imode++;
    }
  }

  // Open input file and get tree

  // Output file - first make the substitutions for sample/parameter
  TString ts_outfile = arg_out_file.c_str();
  ts_outfile = ts_outfile.ReplaceAll("[SAMPLE]" , util::                          AsString(sample   ).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[PARAM]"  , util::NameRegistry::Instance()->AsString(fit_param).c_str());
  VLOG("make_sbn_interaction_splines", pNOTICE) 
    << "Saving VALOR response functions to: "<<ts_outfile;
  TFile fout(ts_outfile.Data(),"recreate");
  
  int n_splines_written = 0;

  unsigned int imode = 0;
  for(ReacMode_t m : read_modes) {
    const VALORBinning * true_sb = binning.TrueSmpBinning(m);
    const int n_true_bins_sb = true_sb->NBins();
    
    if (include_sb) {
      for(int ireco = 0; ireco < n_reco_bins_sb; ireco++) {
        for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
          double y[n_twks] = { 0 };
          double x[n_twks] = { 0 };    
          for(int itwk = 0; itwk < n_twks; itwk++) {
            double twk_dial = twk_dial_min + itwk * twk_dial_step;  
            double nevents  = mc_templ_sb [itwk][imode] -> GetEntry(ireco,itrue);
            double nevents0 = mc_templ_sb [inom][imode] -> GetEntry(ireco,itrue);
            y[itwk] = (nevents0 > 0) ? nevents/nevents0 : 1;
            x[itwk] = 1+(twk_dial * GSystUncertainty::Instance()->OneSigmaErr(syst));                   
          }//itwk
          TString name  = rfl.BuildSplineName(m,fit_param,itrue,ireco);
          TString title = name; // Make this contain real kinematic ranges
          //~ TSpline3 spl(title.Data(), x, y, n_twks, "0"); // Define each x knot individually
          TSpline3 spl(title.Data(), x[0], x[n_twks-1], y, n_twks, "0"); // Define only first and last knots - faster interpolation.
          spl.SetName(name.Data());
          spl.Write();
          n_splines_written++;
          if (n_splines_written%1000==0) {
            VLOG("make_sbn_interaction_splines",pNOTICE)<<"Written "<<n_splines_written<<" splines so far.";
          }
        }//itrue
      }//ireco
    }//if include sb
    for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
      for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
        double y[n_twks] = { 0 };
        double x[n_twks] = { 0 };    
        for(int itwk = 0; itwk < n_twks; itwk++) {
          double twk_dial = twk_dial_min + itwk * twk_dial_step;  
          double nevents  = mc_templ_ob [itwk][imode] -> GetEntry(ireco, itrue);
          double nevents0 = mc_templ_ob [inom][imode] -> GetEntry(ireco, itrue);
          y[itwk] = (nevents0 > 0) ? nevents/nevents0 : 1;
          x[itwk] = 1+(twk_dial * GSystUncertainty::Instance()->OneSigmaErr(syst));                   
        }//itwk
        TString name  = rfl.BuildSplineName(m,fit_param,itrue,ireco);
        TString title = name; // Make this contain real kinematic ranges
        //~ TSpline3 spl(title.Data(), x, y, n_twks, "0"); // Define each x knot individually
        TSpline3 spl(title.Data(), x[0],x[n_twks-1], y, n_twks, "0"); // Define only first and last knots - faster interpolation.
        spl.SetName(name.Data());
        spl.Write();
        n_splines_written++;
        if (n_splines_written%1000==0) {
          VLOG("make_sbn_interaction_splines",pNOTICE)<<"Written "<<n_splines_written<<" splines so far.";
        }
      }//itrue
    }//ireco
    imode++;
  }//imode

  fout.Close();

  VLOG("make_sbn_interaction_splines", pNOTICE)  << "Done! Wrote "<<n_splines_written<<" splines.";
*/
//___________________________________________________________________
