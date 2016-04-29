//____________________________________________________________________________
/*!

  \app       valor_dune-make_response_functions

  \brief     

  \syntax    valor_dune-make_response_functions         
               --input  input_analysis_file.root
               --output output_response_function_file.root
               --format format_of_the_input_file <hpgartpc, lartpc, fgt>
               --beam   beam_name
               --sample sample_name
               --systematic genie_systematic_name

  \author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
             University of Liverpool & STFC Rutherford Appleton Laboratory

  \created   April 20, 2016

  \copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#include <string>

//
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TSpline.h>
#include <TString.h>
#include <TSystem.h>
#include <TMath.h>

// genie
#include "Conventions/GBuild.h"
#include "EVGCore/EventRecord.h"
#include "GHEP/GHepParticle.h"
#include "Ntuple/NtpMCFormat.h"
#include "Ntuple/NtpMCTreeHeader.h"
#include "Ntuple/NtpMCEventRecord.h"
#include "PDG/PDGCodes.h"
#include "PDG/PDGUtils.h"
#include "PDG/PDGLibrary.h"
#include "Utils/CmdLnArgParser.h"
#include "Utils/RunOpt.h"
#include "ReWeight/GReWeightI.h"
#include "ReWeight/GSystSet.h"
#include "ReWeight/GSyst.h"
#include "ReWeight/GReWeight.h"
#include "ReWeight/GReWeightINuke.h"

// valor
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/VArray/VALORArray.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "dune/Conventions/Detector.h"
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/Sample.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/KineVar.h"
#include "dune/Conventions/SampleKineBinning.h"
#include "dune/Conventions/SampleReacMode.h"
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/ArrIdx.h"

#include "dune/GENIEUtilities/UtlEventRec.h"

using std::string;
using genie::EventRecord;
using namespace valor;
using namespace valor::conv;

//___________________________________________________________________
int main(int argc, char ** argv)
{
  Env::Instance()->AutoSet("dune");
  
  // Read command line arguments
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/make_response_functions.arg");
  VLOG("valor_dune", pNOTICE) << arg;

  string arg_beam       = arg.GetString("beam");
  string arg_sample     = arg.GetString("sample");
  string arg_systematic = arg.GetString("systematic");
  string arg_format     = arg.GetString("format");  
  string arg_inp_file   = arg.GetString("input");
  string arg_out_file   = arg.GetString("output");
  
  bool include_sb       = arg.GetBool("include-simple-binning");

  BeamConf_t beam      = util::BeamConfFromString (arg_beam      );
  Sample_t   sample    = util::SampleFromString   (arg_sample    );
  GSyst_t    syst      = GSyst::FromString        (arg_systematic);  

  PhysParamId_t fit_param = kPhypUndefined;
  if      (syst == kINukeTwkDial_MFP_pi     ) fit_param = kNuisIntPiMeanFreePath; 
  else if (syst == kINukeTwkDial_MFP_N      ) fit_param = kNuisIntNucMeanFreePath;
  else if (syst == kINukeTwkDial_FrCEx_pi   ) fit_param = kNuisIntFracPiChargeExchange; 
  else if (syst == kINukeTwkDial_FrInel_pi  ) fit_param = kNuisIntFracPiInelastic; 
  else if (syst == kINukeTwkDial_FrAbs_pi   ) fit_param = kNuisIntFracPiAbsorb; 
  else if (syst == kINukeTwkDial_FrPiProd_pi) fit_param = kNuisIntFracPiProduction; 
  else if (syst == kINukeTwkDial_FrCEx_N    ) fit_param = kNuisIntFracNucChargeExchange; 
  else if (syst == kINukeTwkDial_FrInel_N   ) fit_param = kNuisIntFracNucInelastic; 
  else if (syst == kINukeTwkDial_FrAbs_N    ) fit_param = kNuisIntFracNucAbsorb; 
  else if (syst == kINukeTwkDial_FrPiProd_N ) fit_param = kNuisIntFracNucProduction; 
  
  if (beam==kbUndefined || sample == ksUndefined || fit_param == kPhypUndefined) {
    std::cerr<<"Bad configuration."<<std::endl;
    std::cerr<<"Beam:       "<<arg_beam       <<"\t => "<< util::AsString(beam)  <<std::endl;
    std::cerr<<"Sample:     "<<arg_sample     <<"\t => "<< util::AsString(sample)<<std::endl;
    std::cerr<<"GENIE Syst: "<<arg_systematic <<"\t => "<<GSyst::AsString(syst)  <<std::endl;
    std::cerr<<" to VALOR   "<< "\t => "<<util::AsString(fit_param)<<std::endl;
  }
  assert(beam      != kbUndefined   );
  assert(sample    != ksUndefined   );
  assert(fit_param != kPhypUndefined);

  // Number of tweaks for the specified systematic parameter
  const int   inom          = 5;
  const int   n_twks        = 11;
  const float twk_dial_min  = -5.0;
  const float twk_dial_max  =  5.0;
  const float twk_dial_step = (twk_dial_max - twk_dial_min) / (n_twks-1);

  // Arrays to store the number of events in each MC template bin
  // for each systematic parameter tweak
  VALORArray * mc_templ_sb [n_twks] [kNReacModes]; 
  VALORArray * mc_templ_ob [n_twks] [kNReacModes][kNMaxBinZones]; 

  const util::ArrIdx * arridx = util::ArrIdx::Instance();  
  int isample = arridx->SampleIdx(beam,sample);

  for(int itwk = 0; itwk < n_twks; itwk++) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kReactionModes[isample][imode];
      if(m == kmUndefined) continue;
      const int n_y_reco_bins_sb  = util::NumYrecoBinsSb(sample);
      const int n_enu_true_bins   = util::NumEtrueBinsXsec(sample);
      const int n_q2_true_bins    = util::NumQ2trueBinsXsec(sample,m);
      if (include_sb) {
        mc_templ_sb [itwk][imode] = 
          new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb, n_enu_true_bins, n_q2_true_bins);
        mc_templ_sb [itwk][imode] -> SetAll(0.);
      }
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        const int n_enu_reco_bins = util::NumErecoBinsXsec(sample,izone);
        const int n_y_reco_bins   = util::NumYrecoBinsXsec(sample,izone);
        if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
        mc_templ_ob [itwk][imode][izone] = 
          new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins, n_q2_true_bins);
        mc_templ_ob [itwk][imode][izone] -> SetAll(0.);
      }
    }
  }

  // Open input file and get the HPGArTPC, LArTPC or FGT event tree
  TFile fin(arg_inp_file.c_str(),"READ");
  if (!fin.IsOpen()) {
    VLOG("make_response_func", pFATAL) 
      << "Failed to open file "<<arg_inp_file.c_str();
    exit(1);
  }
  string tree_name = "";
  if(arg_format == "hpgartpc") {
    tree_name = "GasTPCTree";
  } 
  else
    if(arg_format == "lartpc" || arg_format == "fgt") {
      tree_name = "dune_dst";
    }
    else {
      VLOG("make_response_func", pFATAL) 
        << "Unknown input file format. Please specify one of hpgartpc, lartpc or fgt";
      exit(1);
    }
  TTree * analysis_tree = dynamic_cast <TTree *> (fin.Get(tree_name.c_str()));
  if(!analysis_tree) {
    VLOG("make_response_func", pFATAL) 
      << "No event tree " << tree_name 
      << " in " << arg_format << "-format input file: "
      << arg.GetString("input");
    exit(1);
  }
  NtpMCEventRecord * curr_mcrec = 0;
  Sample_t curr_sample          = ksUndefined;
  int      curr_sample_int      = -1;
  double   curr_enu_reco        =  -999;
  double   curr_y_reco          =  -999;
  float    curr_enu_reco_float  =  -999;
  float    curr_y_reco_float    =  -999;
  if(arg_format == "hpgartpc") {
    analysis_tree->SetBranchAddress("gmcrec",          &curr_mcrec);
    analysis_tree->SetBranchAddress("sample",          &curr_sample_int);
    analysis_tree->SetBranchAddress("Ev_reco",         &curr_enu_reco);
    analysis_tree->SetBranchAddress("y_reco",          &curr_y_reco);
  }
  else if(arg_format == "lartpc" || arg_format == "fgt") {
    analysis_tree->SetBranchAddress("genie_mc_truth",  &curr_mcrec);
    analysis_tree->SetBranchAddress("sample",          &curr_sample_int);
    analysis_tree->SetBranchAddress("Ev_reco",         &curr_enu_reco_float);
    analysis_tree->SetBranchAddress("y_reco",          &curr_y_reco_float);
  }
  else {
    VLOG("make_response_func",pFATAL)
      << "No recognised tree format.";
    util::Die(-1); return(-1);
  }
  
  // GENIE event reweighting interface
  GReWeight rw;
  rw.AdoptWghtCalc( "hadro_intranuke", new GReWeightINuke );
  GSystSet & syst_list = rw.Systematics();

  // I think we need to add all fates except the ones we want to act as cushion terms
  // So I add all mfp terms and all fates (except elastic) with nominal value
  // Only the input one will be tweaked later on.
  //syst_list.Init(syst);
  syst_list.Init(kINukeTwkDial_MFP_pi,      0., twk_dial_min, twk_dial_max);
  syst_list.Init(kINukeTwkDial_MFP_N,       0., twk_dial_min, twk_dial_max);
  syst_list.Init(kINukeTwkDial_FrCEx_pi,    0., twk_dial_min, twk_dial_max); 
  syst_list.Init(kINukeTwkDial_FrInel_pi,   0., twk_dial_min, twk_dial_max);
  syst_list.Init(kINukeTwkDial_FrAbs_pi,    0., twk_dial_min, twk_dial_max);
  syst_list.Init(kINukeTwkDial_FrPiProd_pi, 0., twk_dial_min, twk_dial_max);
  syst_list.Init(kINukeTwkDial_FrCEx_N,     0., twk_dial_min, twk_dial_max); 
  syst_list.Init(kINukeTwkDial_FrInel_N,    0., twk_dial_min, twk_dial_max);
  syst_list.Init(kINukeTwkDial_FrAbs_N,     0., twk_dial_min, twk_dial_max);
  syst_list.Init(kINukeTwkDial_FrPiProd_N,  0., twk_dial_min, twk_dial_max);

  // Systematic tweaks
  for(int itwk = 0; itwk < n_twks; itwk++) {

    double twk_dial = twk_dial_min + itwk * twk_dial_step;  
    syst_list.Set(syst, twk_dial);
    rw.Reconfigure();

    // Event loop
    Long64_t nev = analysis_tree->GetEntries();
    for(Long64_t iev = 0; iev < nev; iev++) {
      VLOG("make_response_func", pNOTICE) << "** Reading event: " << iev;
      analysis_tree->GetEntry(iev);
      
      // Consider only input sample
      curr_sample = util::SampleFromInt(curr_sample_int);
      if(curr_sample != sample) {
        curr_mcrec->Clear();
        continue;
      }
      
      // Retrieve GHEP event record and print it out.
      NtpMCRecHeader rec_header = curr_mcrec->hdr;
      EventRecord &  event = *(curr_mcrec->event);
      VLOG("make_response_func", pINFO) 
        << "GENIE MC truth info: " << event;

      // hpgartpc output in MeV, convert to GeV as in lartpc and fgt outputs
      if(arg_format == "hpgartpc") {
        curr_enu_reco = curr_enu_reco/1000.;
      } // and the other two detectors are floats, not doubles
      else if (arg_format == "lartpc" || arg_format == "fgt") {
        curr_enu_reco = curr_enu_reco_float;
        curr_y_reco = curr_y_reco_float;
      }
      
      if(curr_enu_reco <= 0) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [Ev (reco) <= 0]";
        curr_mcrec->Clear();
        continue;
      }
      if(curr_y_reco < 0) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [y (reco) < 0]";
        curr_mcrec->Clear();
        continue;
      }
      
      // Get reaction mode
      ReacMode_t curr_mode = valor::util::DetermineReactionMode(&event, false);
      if(curr_mode == kmUndefined) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [Undefined mode]";
        curr_mcrec->Clear();
        continue;
      }
      int imode = arridx->ReacModeIdx(curr_sample, curr_mode);       

      // Get required true kinematical variables
      double curr_enu_true = event.Particle(0)->E();
      double curr_q2_true  = event.Summary()->KinePtr()->Q2(true);

      // Calculate event weight
      double wght = rw.CalcWeight(event);
      //if(wght <    0) wght = 1; // needed?
      //if(wght > 9999) wght = 1; // needed?

      // Get enu_true, enu_reco, y_reco array indices
      const int izone = util::BinZone(curr_sample, curr_enu_reco, curr_y_reco);
      if(izone < 0) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [Negative zone!]";
        curr_mcrec->Clear();
        continue;
      }
      const int      n_enu_true_bins       = util::NumEtrueBinsXsec  (curr_sample);
      const double * enu_true_bin_edges    = util::EtrueBinEdgesXsec (curr_sample);
      const int      n_q2_true_bins        = util::NumQ2trueBinsXsec (curr_sample,curr_mode);
      const double * q2_true_bin_edges     = util::Q2trueBinEdgesXsec(curr_sample,curr_mode);
      
      const int      n_enu_reco_bins_ob    = util::NumErecoBinsXsec  (curr_sample,izone);
      const double * enu_reco_bin_edges_ob = util::ErecoBinEdgesXsec (curr_sample,izone);
      const int      n_y_reco_bins_sb      = util::NumYrecoBinsSb    (curr_sample);
      const double * y_reco_bin_edges_sb   = util::YrecoBinEdgesSb   (curr_sample);
      const int      n_y_reco_bins_ob      = util::NumYrecoBinsXsec  (curr_sample,izone);
      const double * y_reco_bin_edges_ob   = util::YrecoBinEdgesXsec (curr_sample,izone);

      // Protect against vars at upper limit (eg y_reco = 1, set by hand for NC events) as
      // the binary search below will give an index out of limits
      const double epsilon = 1E-10;
      if(curr_enu_reco >= kErecoMax) { curr_enu_reco = curr_enu_reco - epsilon; }
      if(curr_y_reco   >= kYrecoMax) { curr_y_reco   = curr_y_reco   - epsilon; } 

      // Repeat, finding the indices for the template versions using a simple binning scheme
      int ienu_reco_sb = TMath::BinarySearch(1+(Long_t)kNErecoBinsSb,      kErecoBinEdgesSb,      curr_enu_reco);
      int iy_reco_sb   = TMath::BinarySearch(1+(Long_t)n_y_reco_bins_sb,   y_reco_bin_edges_sb,   curr_y_reco  );
      // Work-out the index using the bin-edge array defining the variable-size binning scheme
      int ienu_true    = TMath::BinarySearch(1+(Long_t)n_enu_true_bins,    enu_true_bin_edges,    curr_enu_true);
      int iq2_true     = TMath::BinarySearch(1+(Long_t)n_q2_true_bins ,    q2_true_bin_edges ,    curr_q2_true);
      int ienu_reco_ob = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins_ob, enu_reco_bin_edges_ob, curr_enu_reco);
      int iy_reco_ob   = TMath::BinarySearch(1+(Long_t)n_y_reco_bins_ob,   y_reco_bin_edges_ob,   curr_y_reco  );

      if (include_sb) {
        mc_templ_sb [itwk] [imode]      -> AddToEntry(wght, ienu_reco_sb, iy_reco_sb, ienu_true, iq2_true); 
      }
      mc_templ_ob [itwk] [imode][izone] -> AddToEntry(wght, ienu_reco_ob, iy_reco_ob, ienu_true, iq2_true);
      curr_mcrec->Clear();
    }// event loop
  }//tweaks

  VLOG("make_response_func", pNOTICE) << "Closing input file";

  fin.Close();

  // Output file - first make the substitutions for sample/parameter
  TString ts_outfile = arg_out_file.c_str();
  ts_outfile = ts_outfile.ReplaceAll("[BEAM]"   , util::AsString(beam     ).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[SAMPLE]" , util::AsString(sample   ).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[PARAM]"  , util::AsString(fit_param).c_str());
  VLOG("make_response_func", pNOTICE) 
    << "Saving VALOR response functions to: "<<ts_outfile;
  TFile fout(ts_outfile.Data(),"recreate");
  
  int n_splines_written = 0;

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    const int n_enu_reco_bins_sb = kNErecoBinsSb;    
    const int n_y_reco_bins_sb   = util::NumYrecoBinsSb(sample);
    const int n_enu_true_bins    = util::NumEtrueBinsXsec(sample);
    const int n_q2_true_bins     = util::NumQ2trueBinsXsec(sample, m);
    if (include_sb) {
      for(int ienu_reco = 0; ienu_reco < n_enu_reco_bins_sb; ienu_reco++) {
        for(int iy_reco = 0;  iy_reco <  n_y_reco_bins_sb; iy_reco++) {
          for(int ienu_true = 0; ienu_true < n_enu_true_bins; ienu_true++) {
            for(int iq2_true = 0; iq2_true < n_q2_true_bins; iq2_true++) {
              double y[n_twks] = { 0 };
              double x[n_twks] = { 0 };    
              for(int itwk = 0; itwk < n_twks; itwk++) {
                double twk_dial = twk_dial_min + itwk * twk_dial_step;  
                double nevents  = mc_templ_sb [itwk][imode] -> GetEntry(ienu_reco, iy_reco, ienu_true, iq2_true);
                double nevents0 = mc_templ_sb [inom][imode] -> GetEntry(ienu_reco, iy_reco, ienu_true, iq2_true);
                y[itwk] = (nevents0 > 0) ? nevents/nevents0 : 1;
                x[itwk] = twk_dial;                   
              }//itwk
              const char * ccb   = arg_beam.c_str();
              const char * ccs   = arg_sample.c_str();
              const char * ccm   = util::ModeAsString(m).c_str();
              const char * ccp   = util::ParamAsString(fit_param).c_str();
              TString name = TString::Format("spl_sb_%s_%s_%s_%s_%d_%d_%d_%d",ccb,ccs,ccm,ccp,ienu_true,iq2_true,ienu_reco,iy_reco);
              TString title = name; // Make this contain real kinematic ranges
              TSpline3 spl(title.Data(), x, y, n_twks, "0");
              spl.SetName(name.Data());
              spl.Write();
              n_splines_written++;
              if (n_splines_written%1000==0) {
                VLOG("make_response_func",pNOTICE)<<"Written "<<n_splines_written<<" splines so far.";
              }
            }//iq2_true
          }//ienu_true
        }//iy_reco
      }//ienu_reco
    }//if include sb
    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      const int n_enu_reco_bins_ob = util::NumErecoBinsXsec(sample,izone);
      const int n_y_reco_bins_ob   = util::NumYrecoBinsXsec(sample,izone);
      for(int ienu_reco = 0; ienu_reco < n_enu_reco_bins_ob; ienu_reco++) {
        for(int iy_reco = 0;  iy_reco <  n_y_reco_bins_ob; iy_reco++) {
          for(int ienu_true = 0; ienu_true < n_enu_true_bins; ienu_true++) {
            for(int iq2_true = 0; iq2_true < n_q2_true_bins; iq2_true++) {
              double y[n_twks] = { 0 };
              double x[n_twks] = { 0 };    
              for(int itwk = 0; itwk < n_twks; itwk++) {
                double twk_dial = twk_dial_min + itwk * twk_dial_step;  
                double nevents  = mc_templ_ob [itwk][imode][izone] -> GetEntry(ienu_reco, iy_reco, ienu_true, iq2_true);
                double nevents0 = mc_templ_ob [inom][imode][izone] -> GetEntry(ienu_reco, iy_reco, ienu_true, iq2_true);
                y[itwk] = (nevents0 > 0) ? nevents/nevents0 : 1;
                x[itwk] = twk_dial;                   
              }//itwk
              const char * ccb   = arg_beam.c_str();
              const char * ccs   = arg_sample.c_str();
              const char * ccm   = util::ModeAsString(m).c_str();
              const char * ccp   = util::ParamAsString(fit_param).c_str();
              TString name  = TString::Format("spl_%s_%s_%s_%s_%d_%d_%d_%d_%d",ccb,ccs,ccm,ccp,izone,ienu_true,iq2_true,ienu_reco, iy_reco);
              TString title = name; // Make this contain real kinematic ranges
              TSpline3 spl(title.Data(), x, y, n_twks, "0");
              spl.SetName(name.Data());
              spl.Write();
              n_splines_written++;
              if (n_splines_written%1000==0) {
                VLOG("make_response_func",pNOTICE)<<"Written "<<n_splines_written<<" splines so far.";
              }
            }//iq2_true
          }//ienu_true
        }//iy_reco
      }//ienu_reco    
    }//izone
  }//imode

  fout.Close();

  VLOG("make_response_func", pNOTICE)  << "Done! Wrote "<<n_splines_written<<" splines.";

  return 0;
}
//___________________________________________________________________
