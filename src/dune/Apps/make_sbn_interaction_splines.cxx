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
 
TString splineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[TRUE]_[RECO]");

std::string GetSystematic(const std::string &sy);
void        GetVariations(std::vector<double> &vs, 
                          const std::string &in, 
                          const std::string &sy);
void        GetKnots(const std::vector<double> &vars, 
                     const std::vector<double> &knots, 
                     std::map<unsigned int, double> &vs, 
                     std::map<unsigned int, double> &kns,
                     std::map<double, unsigned int> &kn_uns);
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
  string hypname           = arg.GetString("physics-hypothesis");
  string fplopt            = arg.GetString("fit-param-opt");
  string arg_config_file   = arg.GetString("config");
  string arg_analysis_file = arg.GetString("input");
  string arg_output_file   = arg.GetString("output");
  string arg_var_file      = arg.GetString("variations");
  string arg_modelist_file = arg.GetString("modes");
  string arg_sample        = arg.GetString("sample");
  string arg_beam          = arg.GetString("beam");
  string arg_detector      = arg.GetString("detector");
  string arg_systematic    = arg.GetString("systematic");
  
  // From arguments
  BeamConf_t beam     = util::BeamConfFromString (arg_beam    );
  Sample_t   sample   = util::SampleFromString   (arg_sample  );
  Detector_t detector = util::DetectorFromString (arg_detector);
  
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
  std::vector<double> variations;
  variations.clear();
  GetVariations(variations, arg_var_file, arg_systematic);
  // Check the variations
  if(!variations.size()){
    VLOG("valor_dune",pFATAL) << syst << " variations came back empty";
    util::Die(-1);
  }
  VLOG("valor_dune",pNOTICE) << "Variations in vector form of size " << variations.size();
  
  // 
  // 4) Find the entries which most closely match the knot positions
  // 5) Pass the universe entry (integer) and value (double) corresponding to these knots to a map
  //
  // Number of knots for the specified systematic parameter
  const std::vector<double> &knots = {-3.0,-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5,3.0};
  const int   n_knots              = knots.size();
  const int   inom                 = 7; // Nominal template ID, 0-sigma variation

  // Chosen universe specifications
  std::vector<unsigned int> ids;
  std::map<double, unsigned int> kn_uns; // Knot to universe ID
  std::map<unsigned int, double> vars; // Universe ID to universe variation
  std::map<unsigned int, double> kns; // Universe ID to knot
  std::map<unsigned int, double>::iterator itr;
  ids.clear(); vars.clear(); kns.clear();

  GetKnots(variations,knots,vars,kns,kn_uns);
  VLOG("valor_dune",pNOTICE) << "Universe ID and variation value for knots : ";
  for(itr = vars.begin(); itr != vars.end(); ++itr) {
    VLOG("valor_dune",pNOTICE) << "ID: " << itr->first << ", variation: " << itr->second << " for knot: " << kns.at(itr->first);
    ids.push_back(itr->first);
  }

  // Get model & configure
  // Make an elements without reading the MC
  std::string elem_readopt("nomc");
  CompoundFitElements * elements = new CompoundFitElements();
  std::string config_file        = util::CompleteConfigPath(arg_config_file);
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
         gmodel->GetSample()   == sample) 
      { got_appropriate_model = true; break; }
  }
  if (!got_appropriate_model) {
    VLOG("valor_dune", pFATAL) << "Failed to identify appropriate fit model to get binning.";
  }
  assert(gmodel);

  gmodel->SetUniversesToRead(ids);
  gmodel->SetUniverseParameterToRead(syst);

  // And finally read the MC properly
  std::string model_readopt("forcedst");
  gmodel->Read(gmodel->GetLastConfigFileRead().c_str(),model_readopt.c_str());  

  // 
  // 6) Build the splines with the universe ID list passed to the tweaked GSSFM universe-based functions
  // 
  // Get model & configure
  // Make an elements without reading the MC
  // For spline generation
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());
  
  // Binning choice needs to be made carefully, likely that stats will be very low in
  // some bins in the standard 2D ereco-etrue param space so will need to redefine
  //
  // Redefinition needs to be along the edges of existing bins in the analysis so as to
  // not cause leakage 
  //
  const VALORBinning * reco_ob = (binning.RecoOptBinning());
  const int n_reco_bins_ob  = reco_ob->NBins();

  const ModeList ml                                = valor::ModeList(util::CompleteConfigPath(arg_modelist_file));
  const std::vector<conv::ReacMode_t> & reac_modes = ml.Modes();

  // 
  // Loop over knots, Generate and access the universe templates for the systematic
  //
  // Using the pre-defined etrue and ereco binning, fill each bin with
  // event rates weighted for each universe knot for each relevant  mode
  // This will produce 13 values per bin definition (13xnModes histograms)

  // Define VALORArrays
  VALORArray *mc_templ_ob [knots.size()] [reac_modes.size()];
  TString var_name = "mctfin";
  
  for (unsigned int iknot = 0; iknot < knots.size(); ++iknot) {
    std::vector<ReacMode_t> temp_modes;
    double kn         = knots[iknot];
    unsigned int univ = kn_uns[kn];
    
    LOG("valor_dune",pINFO) << "Iterator: " << iknot << ", knot : " << kn << ", universe ID: " << univ;
    gmodel->SetSystematicVariationIDToApply(syst, univ);
    
    PhysHypothesis ph(conv::kHypVoid);
    Option_t * generate_opt = ""; // also generate non-default (for fitting) predictions in extra binning schemes
    model->Generate(ph,generate_opt);

    TObjArray *mct_var_ob = new TObjArray();
    std::string tag = "mct_var_"+std::to_string(iknot);
    model->Write(mct_var_ob,tag.c_str(),"mct_vf");
    unsigned int n_mcts = mct_var_ob->GetEntries();
    LOG("valor_dune",pINFO) << " Number of entries in the TObjArray: " << n_mcts;

    // Loop over the object, define every entry containing 'Fin' and the reaction mode name as the VALORArray
    // Now access the entries from the templates in each mode and fill histograms for making splines
    for(unsigned int n = 0; n < n_mcts; ++n){
      TObject * mct_var = (*mct_var_ob)[n];
      TString mct_name = mct_var->GetName();
      //LOG("valor_dune",pDEBUG) << " Looking at template named: " << mct_name;
      for(unsigned int imode = 0; imode < reac_modes.size(); ++imode) {
        const ReacMode_t &m = reac_modes.at(imode);
        TString m_name = util::AsString(m);
        mc_templ_ob[iknot][imode] = nullptr;
        
        // Check if the current mct name contains the current mode
        // Check if the current mct name contains the string 'mctfin' as this is the template we need
        if(!(mct_name.Contains(m_name) && mct_name.Contains(var_name))) {
          LOG("valor_dune",pDEBUG) << " No match: Found template for mode " << m_name << " in template named: " << mct_name;
          continue;
        }
        LOG("valor_dune",pDEBUG) << " Match: Found template for mode " << m_name << " in template named: " << mct_name;

        // Define the current template
        mc_templ_ob[iknot][imode] = static_cast<VALORArray*>(mct_var);
        LOG("valor_dune",pDEBUG) << " Cast the written templates onto VALORArrays, number of entries in the VALORArray: " << mc_templ_ob[iknot][imode]->GetSize();
        
        const VALORBinning * true_sb = binning.TrueSmpBinning(m);
        const int n_true_bins_sb = true_sb->NBins();

        for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
          for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
            double nevents  = mc_templ_ob [iknot][imode] -> GetEntry(ireco, itrue);
            LOG("valor_dune",pDEBUG) << "Mode : " << util::AsString(m) << ", bin (ireco,itrue): " << ireco << ", " << itrue << ", nevents: " << nevents;
          }
        }
      } // Modes
    } // MCTs
  } // Knots

  // Output file - first make the substitutions for sample/parameter
  TString ts_outfile = arg_output_file.c_str();
  ts_outfile = ts_outfile.ReplaceAll("[BEAM]"   , util::AsString(beam).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[SAMPLE]" , util::AsString(sample).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[PARAM]"  , syst.c_str());
  VLOG("valor_dune", pNOTICE) << "Saving VALOR response functions to: "<<ts_outfile;
  TFile fout(ts_outfile.Data(),"recreate");
  
  int n_splines_written = 0;

  for(unsigned int imode = 0; imode < reac_modes.size(); ++imode) {
    const ReacMode_t &m = reac_modes.at(imode);
    const VALORBinning * true_sb = binning.TrueSmpBinning(m);
    const int n_true_bins_sb = true_sb->NBins();
    
    for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
      for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
        double y[n_knots] = { 0 };
        double x[n_knots] = { 0 };    
        for(int iknot = 0; iknot < n_knots; iknot++) {
          if(!mc_templ_ob [iknot][imode]) continue;
          double knot = knots[iknot];
          LOG("valor_dune",pDEBUG) << "Mode : " << util::AsString(m) << ", bin (ireco,itrue): " << ireco << ", " << itrue;
          double nevents  = mc_templ_ob [iknot][imode] -> GetEntry(ireco, itrue);
          LOG("valor_dune",pDEBUG) << " Got nevents, about to construct nevents0";
          double nevents0 = mc_templ_ob [inom][imode] -> GetEntry(ireco, itrue);
          LOG("valor_dune",pDEBUG) << " nevents0: " << nevents0 << ", nevents: " << nevents;
          y[iknot] = (nevents0 > 0) ? nevents/double(nevents0) : 1; // Ratio of the variation rate to the nominal rate
          x[iknot] = vars[kn_uns[knot]]; //NSigma from the universe found for the current knot
          LOG("valor_dune",pDEBUG) << " Current knot : " << knot << ", closest universe variation : " << vars[kn_uns[knot]] << ", with " << y[iknot] << " entries";
        }//iknot
        TString name  = BuildSplineName(sample, beam, m, syst, itrue, ireco);
        LOG("valor_dune",pDEBUG) << " Building spline with name: " << name;
        
        TString title = name; // Make this contain real kinematic ranges
        LOG("valor_dune",pDEBUG) << "                 and title: " << title;
        
        TSpline3 spl(title.Data(), x[0],x[n_knots-1], y, n_knots, "0"); // Define only first and last knots - faster interpolation.
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

  VLOG("valor_dune", pNOTICE)  << "Done! Wrote "<<n_splines_written<<" splines.";

  return 0;
}
//___________________________________________________________________

void GetVariations(std::vector<double> &vs, const std::string &in, const std::string &sy){

  std::ifstream uFile;
  uFile.open(in);
  if(!uFile){
    VLOG("valor_dune",pFATAL) << "Unable to open universe file: " << in;
    util::Die(-1);
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
void GetKnots(const std::vector<double> &vars, 
              const std::vector<double> &knots, 
              std::map<unsigned int, double> &vs, 
              std::map<unsigned int, double> &kns,
              std::map<double, unsigned int> &kn_uns){

  for(const double &kn : knots){
    double min_diff       = 999.;
    double best_var       = -999.;
    unsigned int min_id   = 999;
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
    kn_uns.insert({kn, min_id});
  }
  if(vs.size() != kns.size()){
    VLOG("valor_dune",pFATAL) << "Number of entries in knots and variation lists don't match";
    VLOG("valor_dune",pFATAL) << "NKnots: " << kns.size() << ", NVariations: " << vs.size();
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
  /*
  // Open input analysis file and get the DST
  TFile fin(arg_analysis_file.c_str(),"READ");
  if (!fin.IsOpen()) {
    VLOG("valor_dune", pFATAL) 
      << "Failed to open file "<<arg_analysis_file.c_str();
    util::Die(-1);
  }
  string tree_name = "valor_sbncode_mini_dst";
  TTree * analysis_tree = dynamic_cast <TTree *> (fin.Get(tree_name.c_str()));
  if(!analysis_tree) {
    VLOG("valor_dune", pFATAL) 
      << "No event tree " << tree_name 
      << " in " << " input analysis file: "
      << arg_analysis_file;
    util::Die(-1);
  }
  
  // Get the branches we're interested in
  //
  // Universes
  const size_t max_n_universes = 10000;
  std::map<std::string,int> branch_n_universes;
  std::map<std::string,std::vector<float>> branch_universes;
  
  // For now, processing a single systematic at a time so each map will only have 1 entry
  branch_universes.emplace(syst,std::vector<float>(max_n_universes));
  std::string branch_name   = Form("variation_%s",syst.c_str());
  std::string branch_name_n = Form("variation_n_%s",syst.c_str());
  analysis_tree->SetBranchStatus (branch_name_n.c_str(),1);
  analysis_tree->SetBranchStatus (branch_name  .c_str(),1);
  bool bstat_univ_n = analysis_tree->SetBranchAddress(branch_name_n.c_str(),&branch_n_universes[syst]);
  bool bstat_univ   = analysis_tree->SetBranchAddress(branch_name.c_str(),branch_universes[syst].data());
  if (bstat_univ_n || bstat_univ) {
    LOG("valor_dune",pFATAL) << " Failed to load needed universe branch.";
    util::Die(-1);
  }
  VLOG("universe_variation_tweaks", pINFO) << " Successfully loaded universe branches";

  // Only apply simple binning for now
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());
  const VALORBinning * reco_sb            = (binning.RecoSmpBinning());
  const int n_reco_bins                   = reco_sb->NBins();
  // Setup arrays to be used for constructing the histograms
  VALORArray *pdfuni[n_knots];
  VALORArray *pdfnom  = new VALORArray(n_reco_bins);
  pdfnom->SetAll(0.);
  for(int i = 0; i < n_knots; ++i){
    pdfuni[i] = new VALORArray(n_reco_bins);
    pdfuni[i]->SetAll(0.);
  }
  VLOG("universe_variation_tweaks", pINFO) << " Successfully setup PDFs";

  // Ereco
  double enu_reco   = -999.;
  double weight     = -999.;
  double pot_weight = -999.;
  analysis_tree->SetBranchAddress("enu_reco", &enu_reco);
  analysis_tree->SetBranchAddress("wght",     &weight);
  analysis_tree->SetBranchAddress("wght_pot", &pot_weight);
*/
