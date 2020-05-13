//____________________________________________________________________________
/*!

  \app       valor_dune-make_sbn_interaction_splines

  \brief     

  \syntax    valor_dune-make_sbn_interaction_splines         
  
  \options     --output              : Where to save splines to. [def: valor_splines_[SAMPLE]_[PARAM]_[BEAM].root]
               --config              : Analysis configuration file [required]
               --variations          : Location of the text file which holds the sigma variations
               --systematic          : Parameter to generate spline for
               --sample              : Topology [def: numulikeCChigh]
               --detector            : Detector [def: sbn_nd]
               --beam                : Beam [def: BNB_FHC]
               --spectra-write-opt   : Write options for spectra [def: pdfts_rf]
               --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]
               --store-spectra 
               || --discard-spectra  : Store param spectra for knots? [def: --discard-spectra]

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
 
TString splineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[TRUE]_[RECO]");

std::string GetSystematic(const std::string &sy);
void        GetVariations(std::vector<double> &variations, 
                          const std::string &input, 
                          const std::string &sy);
void        GetKnots(const std::vector<double> &variations, 
                     const std::vector<double> &knots, 
                     std::map<unsigned int, double> &universes_variations, 
                     std::map<unsigned int, double> &universes_knots,
                     std::map<double, unsigned int> &knots_universes);
TString     BuildSplineName(const Sample_t    &s, 
                            const BeamConf_t  &b,
                            const ReacMode_t  &m, 
                            const std::string &p,
                            const int         &itrue, 
                            const int         &ireco);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  
  // Read command line arguments
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_EXPT/config/apps/universes.arg:$VALOR_EXPT/config/apps/make_sbn_interaction_splines.arg");
  VLOG("valor_dune", pNOTICE) << arg;

  // Get arguments
  string arg_config_file   = arg.GetString("config");
  string arg_output_file   = arg.GetString("output");
  string arg_var_file      = arg.GetString("variations");
  string arg_sample        = arg.GetString("sample");
  string arg_beam          = arg.GetString("beam");
  string arg_detector      = arg.GetString("detector");
  string arg_systematic    = arg.GetString("systematic");
  string arg_write_opt     = arg.GetString("spectra-write-opt");
  bool   arg_store_spectra = arg.GetBool("store-spectra");
  bool   arg_save_modelist = arg.GetBool("save-modelist");
  
  // From arguments
  string mesg_thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  string config_file     = util::CompleteConfigPath(arg_config_file);
  BeamConf_t beam        = util::BeamConfFromString (arg_beam    );
  Sample_t   sample      = util::SampleFromString   (arg_sample  );
  Detector_t detector    = util::DetectorFromString (arg_detector);
  
  // Message thresholds
  Messenger::Instance()->Configure(mesg_thresholds);

  // If the write options for the spectra are empty, fill with pdfts_rf
  if(arg_write_opt == "")
    arg_write_opt = "pdfts_rf";
  //
  // Get the systematic from the argument list and make sure it exists in the universes
  //
  std::string syst = GetSystematic(arg_systematic);
  if(syst.empty()){
    VLOG("valor_dune",pFATAL) << syst << " systematic came back empty";
    util::Die(-1);
  }
  VLOG("valor_dune",pNOTICE) <<  "Systematic parameter " << syst << " found";
  
  // 
  // Read in the universe-variation txt file and use it to determine the best universes to generate the 13 knots
  // for -3sigma -> +3sigma variations in steps of 0.5sigma
  //
  // 1) Read in the text file
  // 2) Find the row which starts with the name of the variation we want
  // 3) Pass the space-delimeted values to a vector
  //
  // Get the variations
  std::vector<double> all_variations;
  GetVariations(all_variations, arg_var_file, arg_systematic);
  // Check the variations
  if(!all_variations.size()){
    VLOG("valor_dune",pFATAL) << syst << " variations came back empty";
    util::Die(-1);
  }
  VLOG("valor_dune",pNOTICE) << "Variations in vector form of size " << all_variations.size();
  
  // 
  // 4) Find the entries which most closely match the knot positions
  // 5) Pass the universe entry (integer) and value (double) corresponding to these knots to a map
  //
  // Number of knots for the specified systematic parameter
  const std::vector<double> &knots = {-3.0,-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5,3.0};
  const int   n_knots              = knots.size();
  const int   inom                 = 6; // Nominal template ID, 0-sigma variation

  // Chosen universe specifications
  std::vector<unsigned int> ids;
  std::vector<double> variations; // Variations attributed to chosen knot values
  std::map<double, unsigned int> knots_universes; // Knot to universe ID
  std::map<unsigned int, double> universes_variations; // Universe ID to universe variation
  std::map<unsigned int, double> universes_knots; // Universe ID to knot
  std::map<unsigned int, double>::iterator itr;

  GetKnots(all_variations,knots,universes_variations,universes_knots,knots_universes);
  VLOG("valor_dune",pNOTICE) << "Universe ID and variation value for knots : ";
  for(itr = universes_variations.begin(); itr != universes_variations.end(); ++itr) {
    VLOG("valor_dune",pNOTICE) << "ID: " << itr->first << ", variation: " << itr->second << " for knot: " << universes_knots.at(itr->first);
    ids.push_back(itr->first);
    variations.push_back(itr->second);
  }
  // Variations only to pass to the output file for generating tweaks when validating
  TVectorD t_variations(variations.size(),variations.data());

  // Get model & configure
  // Make an elements without reading the MC
  std::string elem_readopt("nomc nosplines");
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(util::CompleteConfigPath(config_file),elem_readopt.c_str());
  
  // Then tell it about the universes and read the MC
  FitModelABC * model = elements->FitModel();
  CompoundFitModel * cmodel = dynamic_cast<CompoundFitModel*>(model);
  assert(cmodel);
  GenericSingleSampleFitModel * gmodel = 0;
  bool got_appropriate_model = false;
  for (unsigned int ism = 0 ; ism < cmodel->GetNSubModels() ; ism++) {
    gmodel = dynamic_cast<GenericSingleSampleFitModel*>(cmodel->GetSubModel(ism));
    if  (gmodel->GetDetector() == detector && 
         gmodel->GetSample()   == sample   &&
         gmodel->GetBeam()     == beam) 
      { got_appropriate_model = true; break; }
  }
  if (!got_appropriate_model) {
    VLOG("valor_dune", pFATAL) << "Failed to identify appropriate fit model to get binning.";
  }
  assert(gmodel);

  gmodel->SetUniversesToRead(ids);
  gmodel->SetUniverseParameterToRead(syst);

  // And finally read the MC properly
  std::string model_readopt("forcedst nosplines");
  gmodel->Read(gmodel->GetLastConfigFileRead().c_str(),model_readopt.c_str());  

  // 
  // 6) Build the splines with the universe ID list passed to the tweaked GSSFM universe-based functions
  // 
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());
  
  // Get the modelist from the model configuration
  const std::vector<conv::ReacMode_t> & reac_modes = gmodel->GetReactionModes();
  
  // Binning choice needs to be made carefully, likely that stats will be very low in
  // some bins in the standard 2D ereco-etrue param space so will need to redefine
  //
  // Redefinition needs to be along the edges of existing bins in the analysis so as to
  // not cause leakage 
  //
  const VALORBinning * reco_ob = (binning.RecoOptBinning());
  const int n_reco_bins_ob  = reco_ob->NBins();

  // 
  // Loop over knots, Generate and access the universe templates for the systematic
  //
  // Using the pre-defined etrue and ereco binning, fill each bin with
  // event rates weighted for each universe knot for each relevant  mode
  // This will produce 13 values per bin definition (13xnModes histograms)
 
  // Filename for is we choose to store the spectra
  TString hist_outfile = arg_output_file.c_str();
  hist_outfile = hist_outfile.ReplaceAll("[BEAM]"   , util::AsString(beam).c_str());
  hist_outfile = hist_outfile.ReplaceAll("[SAMPLE]" , util::AsString(sample).c_str());
  hist_outfile = hist_outfile.ReplaceAll("[PARAM]"  , syst.c_str());
  hist_outfile = hist_outfile.ReplaceAll(".root","_spectra.root");
  VLOG("valor_dune", pNOTICE) << "Saving spectra to: "<<hist_outfile;
  TFile histout(hist_outfile.Data(),"RECREATE");
  t_variations.Write("actual_knot_values");

  // Name to search VALORArrays for 
  const TString fin_name = "mctfin";
  
  std::vector< std::map< ReacMode_t, VALORArray> > mct_knots_modes;
  for (unsigned int iknot = 0; iknot < knots.size(); ++iknot) {
    const double kn         = knots.at(iknot);
    const unsigned int univ = knots_universes.at(kn);
    
    LOG("valor_dune",pINFO) << "Iterator: " << iknot << ", knot : " << kn << ", universe ID: " << univ;
    gmodel->SetSystematicVariationIDToApply(syst, univ);
    
    const PhysHypothesis ph(conv::kHypVoid);
    const Option_t * generate_opt = ""; // also generate non-default (for fitting) predictions in extra binning schemes
    model->Generate(ph,generate_opt);

    const std::string tag = "mct_var_"+std::to_string(iknot);
    TObjArray *mct_modes_varray = new TObjArray();
    model->Write(mct_modes_varray,tag.c_str(),"mct_vf");
    const unsigned int n_mcts = mct_modes_varray->GetEntries();
    LOG("valor_dune",pDEBUG) << " Number of entries in the TObjArray: " << n_mcts;

    // If we are storing the spectra (for validation) do so here
    // Only do this for integer values of sigma (+/- 3, 2, 1)
    // This can be done by only accessing the even integers in the iknot iterator
    if(arg_store_spectra && iknot % 2 == 0){
      TString hist_tag = "spectra_var_";
      const int nsigma = static_cast<int>(round(kn));
      std::string s_nsigma = std::to_string(nsigma);
      hist_tag.Append(s_nsigma.c_str());
      hist_tag.ReplaceAll("-","m");
//      const std::string hist_tag  = "spectra_var_"+std::to_string(static_cast<int>(knots.at(iknot)));
      LOG("valor_dune",pINFO) << " Saving spectra for knot: " << kn << " with options: " << arg_write_opt << " to file with name: " << hist_tag;
      TObjArray hist_modes_varray;
      hist_modes_varray.SetOwner(true);
      model->Write(&hist_modes_varray,hist_tag.Data(),arg_write_opt.c_str());

      for (int ihist = 0 ; ihist < hist_modes_varray.GetEntries() ; ihist++) {
        const TH1* hist = dynamic_cast<TH1*>(hist_modes_varray[ihist]);
        assert(hist);
        const TString hist_name = hist->GetName();
        histout.cd();
        hist->Write();

        if (hist_name.Contains("pdfts")) {
          LOG("valor_dune", pNOTICE) << "Wrote histogram "<<hist->GetName()<<" with "<<hist->Integral()<<" events.";
        }
      }
    }
        
    std::map<ReacMode_t, VALORArray> mct_modes;
    for(unsigned int imct = 0; imct < n_mcts; ++imct){
      const VALORArray mct = *static_cast<VALORArray*>((*mct_modes_varray)[imct]);
      const std::string mct_name = mct.GetName();
      const TString t_mct_name = mct_name;
      const size_t underscore_index = mct_name.find_last_of("_");
      if(underscore_index == string::npos){
        LOG("valor_dune",pERROR) << " No '_' found in mct_name: " << mct_name;
        util::Die(-1);
      }
      const std::string mct_mode_name = mct_name.substr(underscore_index+1);
      LOG("valor_dune",pINFO) << " MCT name " << mct_name << ", mct_mode_name: " << mct_mode_name;
      if(!(t_mct_name.Contains(fin_name))) continue;
      for(const ReacMode_t &mode : reac_modes) {
        const TString mode_name = util::AsString(mode);
        if(mct_mode_name == mode_name){
          if(!mct_modes.emplace(mode,mct).second) {
            LOG("valor_dune",pERROR) << " Couldn't place the template in the map entry due to repeated entry for mode " << util::AsString(mode);
            util::Die(-1);
          }
          break;
        }
      }
    }
    mct_knots_modes.push_back(mct_modes);
  }
  // Close histogram file
  histout.Close();

  for (unsigned int iknot = 0; iknot < mct_knots_modes.size(); ++iknot) {
    const std::map<ReacMode_t, VALORArray> mct_modes = mct_knots_modes.at(iknot);
    for(const ReacMode_t &mode : reac_modes){
      std::map<ReacMode_t, VALORArray>::const_iterator it;
      it = mct_modes.find(mode);
      if(it == mct_modes.end()) continue;
      const VALORArray &mct = it->second; 
      LOG("valor_dune",pDEBUG) << " At knot = " << iknot << " & mode = " << util::AsString(mode) << ", entry(8,8) = " << mct.GetEntry(8, 8);
    }
  } // Knots 
  //// DREAMS

  // Output file - first make the substitutions for sample/parameter
  // Modelist to save any modes which result in non-zero splines
  std::vector<std::string> applied_to_modes;

  TString ts_outfile = arg_output_file.c_str();
  ts_outfile = ts_outfile.ReplaceAll("[BEAM]"   , util::AsString(beam).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[SAMPLE]" , util::AsString(sample).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[PARAM]"  , syst.c_str());
  VLOG("valor_dune", pNOTICE) << "Saving VALOR response functions to: "<<ts_outfile;
  TFile fout(ts_outfile.Data(),"RECREATE");

  int n_splines_written = 0;

  // Get the name of the reaction modes for the nominal knot
  const std::map<ReacMode_t, VALORArray> mct_mode_nom = mct_knots_modes.at(inom); 

  for(const ReacMode_t &mode : reac_modes){
    // Iterator for the nominal knot map
    std::map<ReacMode_t, VALORArray>::const_iterator it_mct_mode_nom = mct_mode_nom.find(mode);

    // Make sure the current mode exists for the nominal knot
    if(it_mct_mode_nom == mct_knots_modes.at(inom).end()) continue;

    // Access the VALOR array for the nominal mct in this mode
    const VALORArray &mct_nom = it_mct_mode_nom->second; 
    
    // Get the true, standard binning for this mode
    const VALORBinning * true_sb = binning.TrueSmpBinning(mode);
    const int n_true_bins_sb = true_sb->NBins();
   
    // Boolean to check if the current mode ever results in a spline entry != 1
    bool mode_used = false;
    // Loop over the reco and true bins
    for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
      for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
        // Get the nominal event rate in this bin
        double nevents0 = mct_nom.GetEntry(ireco, itrue);
        std::vector<double> x,y;
        for (unsigned int iknot = 0; iknot < knots.size(); ++iknot) {
          // Get the mct-mode map for the current knot and its corresponding iterator
          const std::map<ReacMode_t, VALORArray> mct_mode_knot = mct_knots_modes.at(iknot); 
          std::map<ReacMode_t, VALORArray>::const_iterator it_mct_mode_knot = mct_mode_knot.find(mode);

          // Make sure the current mode exists for the current knot
          if(it_mct_mode_knot == mct_knots_modes.at(iknot).end()) {
            LOG("valor_dune", pERROR) << " Couldn't find an entry for the current knot " << iknot << " in mct_knots_modes";
            util::Die(-1);
          }
          // Access the VALOR array for the nominal mct in this mode
          const VALORArray &mct_knot = it_mct_mode_knot->second; 

          // Get the value of the current knot for debugging purposes
          double knot = knots.at(iknot);

          // Get the event rate for this knot and mode in this bin
          double nevents = mct_knot.GetEntry(ireco, itrue);

          // Set the y axis entry to be the current rate/nominal rate
          // Set the x axis to be the exact sigma of the current knot from the relevant universe
          double event_ratio = (nevents0 > 0) ? nevents/double(nevents0) : 1; // Ratio of the variation rate to the nominal rate
          if(iknot == inom)
            event_ratio = 1; // For the nominal variation set nsigma = 0 and ratio = 1 explicitly
          y.push_back(event_ratio);

          double universe_variation = universes_variations.at(knots_universes.at(knot));
          if(iknot == inom)
            universe_variation = 0; // For the nominal variation set nsigma = 0 and ratio = 1 explicitly

          x.push_back(universe_variation); //NSigma from the universe found for the current knot

          // Print statements for validation
          LOG("valor_dune",pDEBUG ) << " Knot :                   " << iknot << ", " << knot << "\n"
                                   << " Universe variation:      " << universe_variation << " \n"
                                   << " Mode :                   " << util::AsString(mode) << "\n"
                                   << " Nominal event rate:      " << nevents0 << "\n"
                                   << " Current knot event rate: " << nevents << "\n"
                                   << " Bin (ireco,itrue):       " << ireco << ", " << itrue << "\n"
                                   << " x-axis entry (universe variation): " << x.at(iknot) << "\n"
                                   << " y-axis entry (event rate ratio):   " << y.at(iknot);
          
          // Now if we are saving the modelist, check if the current mode affects the spline
          if(arg_save_modelist && iknot != inom){
            // Check if a variation for this mode has already been found
            if(!mode_used){
              // Check if the event ratio is extremely close to 1
              if(event_ratio > 1.0 || event_ratio < 1.0){
                LOG("valor_dune",pDEBUG) << "Event ratio for mode " << util::AsString(mode) << " isn't 1: " << event_ratio  << " therefore saving the mode to the list";
                applied_to_modes.push_back(util::AsString(mode));
                mode_used = true;
              }
            }
          }//save_modelist
        }//iknot
        assert((x.size() == y.size()) && (x.size() == knots.size()));
        TString name  = BuildSplineName(sample, beam, mode, syst, itrue, ireco);
        TString title = name; // Make this contain real kinematic ranges
        TSpline3 spl(title.Data(), x.data(), y.data(), n_knots);
        spl.SetName(name.Data());
        spl.Write();
        n_splines_written++;
        if (n_splines_written%1000==0) {
          VLOG("valor_dune",pNOTICE)<<"Written "<<n_splines_written<<" splines so far.";
        }

      }//itrue
    }//ireco
  }//imode

  fout.Close();

  // Now construct the file to save the modelist to
  if(arg_save_modelist){
    // If we want to save but the modelist has no entries, cry.
    if(!applied_to_modes.size()){
      LOG("valor_dune",pERROR) << " Error: Modelist is empty, can't save.";
    }
    else{ 
      TString mode_outfile = ts_outfile;
      mode_outfile = mode_outfile.ReplaceAll(".root","_modelist.root");
      LOG("valor_dune",pNOTICE) << "Saving modelist to: " << mode_outfile.Data();
      TFile *fmode = TFile::Open(mode_outfile.Data(),"RECREATE");
      TTree *tree = new TTree("ModeList","List of modes impacted by each systematic parameter");
      tree->Branch(syst.c_str(),&applied_to_modes);
      tree->Fill();
      fmode->Write();
      fmode->Close();
    }
  }
  
  VLOG("valor_dune", pNOTICE)  << "Done! Wrote "<<n_splines_written<<" splines.";
  
  return 0;
}
//___________________________________________________________________

void GetVariations(std::vector<double> &variations, const std::string &input, const std::string &sy){

  std::ifstream uFile;
  uFile.open(input);
  if(!uFile){
    LOG("valor_dune",pFATAL) << "Unable to open universe file: " << input;
    util::Die(-1);
  }
  if(variations.size()){
    LOG("valor_dune",pERROR) << "Vector to hold variations is not empty";
    return;
  }

  int count_lines = 0;
  while(!uFile.eof()){

    std::string line = "";
    std::getline(uFile,line);
    TString tline(line);
    TString tsyst(sy);
    tsyst.ToLower();
    tline.ToLower();
    std::string lline = static_cast<std::string>(tline);
    // Add a space to the end of the parameter name to avoid getting the wrong one 
    size_t found_v = lline.find(tsyst+" ");
    if(found_v != std::string::npos){
      // Clean up the line to pass the variations to the vector
      LOG("valor_dune",pDEBUG) << "On textfile line: " << count_lines;
      LOG("valor_dune",pDEBUG) << "Found line containing " << sy << " parameters: \n" << line;
      LOG("valor_dune",pDEBUG) << "Removing systematic name from line";
      line.erase(0, found_v+sy.length());
      LOG("valor_dune",pDEBUG) << "Line now contains: \n" << line;

      // Pass the remaining contents of the line to a vector of doubles
      double value;
      std::stringstream lineValue(line);
      while(lineValue >> value){
        LOG("valor_dune",pDEBUG) << "Variation: " << value;
        variations.push_back(value);
      }
     //break; // Don't break: there are two lines per parameter in the text file!
    }  
    count_lines++;
  } // variations text file
} // GetVariations
//___________________________________________________________________

std::string GetSystematic(const std::string &sy){

  std::string syst = "";
  bool found_syst = false;
  for(const std::string &s : interaction_systematics){
    LOG("valor_dune",pDEBUG) << "Checking interaction systematic: " << s << " for " << sy;
    // Add a space to the end of the parameter name to avoid getting the wrong one 
    size_t found_s = s.find(sy+"_");
    if(found_s != std::string::npos){
      syst = s;
      LOG("valor_dune",pINFO) << "Found the chosen interaction systematic: " << syst;
      found_syst = true;
      break;
    }
  }

  if(!found_syst){
    for(const std::string &s : flux_systematics){
      LOG("valor_dune",pDEBUG) << "Checking flux systematic: " << s << " for " << sy;
    // Add a space to the end of the parameter name to avoid getting the wrong one 
      size_t found_s = s.find(sy+"_");
      if(found_s != std::string::npos){
        syst = s;
        LOG("valor_dune",pINFO) << "Found the chosen flux systematic: " << syst;
        found_syst = true;
        break;
      }
    }
  }

  if(!found_syst){
    LOG("valor_dune",pFATAL) << "Couldn't find the chosen systematic parameter: " << sy;
    util::Die(-1);
  }
  return syst;
}
//___________________________________________________________________
void GetKnots(const std::vector<double> &variations, 
              const std::vector<double> &knots, 
              std::map<unsigned int, double> &universes_variations, 
              std::map<unsigned int, double> &universes_knots,
              std::map<double, unsigned int> &knots_universes){

  for(const double &kn : knots){
    double min_diff       = 999.;
    double best_var       = -999.;
    unsigned int min_id   = 999;
    for(unsigned int v = 0; v < variations.size(); ++v){
      //Check if the current variation is closest to the current knot
      //At the end of the loop, push back the closest variation and it's location in the vector
      double var = variations[v];
      if(abs(kn-var) < abs(min_diff)){
        min_diff  = abs(kn-var);
        best_var  = var;
        min_id    = v;
      }
    }
    universes_variations.emplace(min_id,best_var);
    universes_knots.emplace(min_id,kn);
    knots_universes.emplace(kn, min_id);
  }
  if(universes_variations.size() != universes_knots.size()){
    LOG("valor_dune",pFATAL) << "Number of entries in knots and variation lists don't match";
    LOG("valor_dune",pFATAL) << "NKnots: " << universes_knots.size() << ", NVariations: ";
    util::Die(-1);
  }
}
//___________________________________________________________________
TString BuildSplineName(const Sample_t    &s, 
                        const BeamConf_t  &b,
                        const ReacMode_t  &m, 
                        const std::string &p,
                        const int         &itrue, 
                        const int         &ireco){

  TString name = splineNamePattern;
  
  name = name.ReplaceAll("[BEAM]"   , util::AsString(b).c_str());
  name = name.ReplaceAll("[SAMPLE]" , util::AsString(s).c_str());
  
  name = name.ReplaceAll("[MODE]"   , util::AsString(m).c_str());
  name = name.ReplaceAll("[PARAM]"  , p.c_str());
  
  name = name.ReplaceAll("[TRUE]" , TString::Format("%d", itrue ));
  name = name.ReplaceAll("[RECO]" , TString::Format("%d", ireco ));
  
  return name;

}
//___________________________________________________________________
