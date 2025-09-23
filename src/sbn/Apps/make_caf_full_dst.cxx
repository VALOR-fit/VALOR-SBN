//____________________________________________________________________________
/*!

  \app       valor_sbn-make_caf_full_dst

  \brief     Converts sbncode CAFs (full CAFs) to VALOR DSTs.
             The DSTs contain additional variables that are not used for fitting.
	     If desired, an additional file containing systematic responses
	     will be generated, in an HDF5 format.

	     For these selections, I will use the slice reco branches. This may need to be changed.

  \syntax    valor_sbn-make_caf_full_dst
                --input  input_analysis_file.root
                --output output_file_containing_valor_dst.root
               [--write-systematics] optionally write out the systematic variations
	       [--systematics-output] output_systematics_file.h5

  \author    John Plows <kplows \at liverpool.ac.uk>
             University of Liverpool

  \created   September 2025

  \copyright Copyright (c) 2010-2025, The VALOR group. All rights reserved.

*/

#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-copy" // No custom copy operator in HDF5 so suppress this

// System
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>
#include <sstream>
// ROOT
#include "TFile.h"
#include "TH1D.h"
#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TSystem.h"
// GENIE
#include "Framework/GHEP/GHepRecord.h"
#include "Framework/GHEP/GHepParticle.h"
#include "Framework/GHEP/GHepStatus.h"
#include "Framework/Ntuple/NtpMCEventRecord.h"
#include "Framework/ParticleData/PDGCodes.h"
// VALOR/SDK
#include "valor/Conventions/Constants.h"
#include "valor/Conventions/BeamConf.h"
#include "valor/Conventions/ReacMode.h"
#include "valor/Conventions/Sample.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/Env.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Utilities/UtlNumStat.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Rnd.h"
#include "valor/GENIEUtilities/GENIEIncludes.h"
#include "valor/GENIEUtilities/GENIEIncludes.h"
#include "valor/GENIEUtilities/UtlEventRec.h"
// sbncode
#include "sbnanaobj/StandardRecord/StandardRecord.h"
#include "sbnanaobj/StandardRecord/SRSliceRecoBranch.h"
#include "sbnanaobj/StandardRecord/SRSlice.h"
#include "sbnanaobj/StandardRecord/SRVector3D.h"
#include "sbnanaobj/StandardRecord/SRPFP.h"
#include "sbnanaobj/StandardRecord/SRTrack.h"
#include "sbnanaobj/StandardRecord/SRTruthMatch.h"
// sbncode global tree
#include "sbnanaobj/StandardRecord/SRGlobal.h"
#include "sbnanaobj/StandardRecord/SRWeightParam.h"
#include "sbnanaobj/StandardRecord/SRWeightPSet.h"
#include "sbnanaobj/StandardRecord/SRWeightMapEntry.h"
// hdf5
#include "H5Cpp.h"
#include "H5File.h"

using std::string;
using std::ostringstream;
using namespace valor;

// -------------------------------------------------------------------------------------------
// Forward declarations
// -------------------------------------------------------------------------------------------

// Methods 
H5::Group create_group_recursive( H5::Group & in_group, std::string & full_path );
void add_string_attribute( H5::DataSet & dataset, const std::string & name, 
			   const std::string & value );
// This could be templated but w/e it's faster to have three methods
void add_vector_int_attribute( H5::DataSet & dataset, const std::string & name,
			       const std::vector<int> & value);
void add_vector_float_attribute( H5::DataSet & dataset, const std::string & name,
				 const std::vector<float> & value);
void add_vector_double_attribute( H5::DataSet & dataset, const std::string & name,
				  const std::vector<double> & value);
H5::DataSet create_or_open_dataset( H5::Group & group, const std::string & name,
				    const std::string & attr_name,
				    const std::vector<double> & attr_knots,
				    int D1, hsize_t chunk_size = 1000 );
void append_row( H5::DataSet & dataset, const std::vector<float> & row );

// Variables
H5::StrType strdatatype( H5::PredType::C_S1, H5T_VARIABLE ); // turn H5T_C_S1 to variable length
static const string analysis_tree = "recTree";
static const string global_tree = "globalTree"; // The tree containing responses for systematics
static const string genie_tree  = "GenieEvtRecTree"; // For matching to the EventRecord

// -------------------------------------------------------------------------------------------
// Implementation
// -------------------------------------------------------------------------------------------

// A really neat helper to print a progress bar in the main loop.
// See https://stackoverflow.com/questions/14539867/
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage) {
  int val = (int) (percentage * 100);
  int lpad = (int) (percentage * PBWIDTH);
  int rpad = PBWIDTH - lpad;
  printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
  fflush(stdout);
}

// Some helpers for HDF5

// Helper method to create HDF5 group hierarchy
H5::Group create_group_recursive( H5::Group & in_group, std::string & full_path ) {
  H5::Group group;
  size_t pos = 0;

  while( (pos = full_path.find('/', pos)) != std::string::npos ) { // subgroups exist
    std::string sub = full_path.substr(0, pos);
    pos++;
    if( !sub.empty() ) {
      try { group = in_group.openGroup(sub); }
      catch (...) { group = in_group.createGroup(sub); }
    } 
  } // subgroups

  // and another loop in case of no subgroups
  try { group = in_group.openGroup(full_path); }
  catch (...) { group = in_group.createGroup(full_path); }

  return group;
}

// Attribute helpers
void add_string_attribute(H5::DataSet & dataset, const std::string & name, const std::string & value) {
  H5::DataSpace attr_dataspace( H5S_SCALAR );
  H5::Attribute attribute = dataset.createAttribute( name, strdatatype, attr_dataspace );
  attribute.write(strdatatype, value);
}

void add_vector_int_attribute(H5::DataSet & dataset, const std::string & name, 
			      const std::vector<int> & values ) {
  hsize_t dims[1] = { values.size() };
  H5::DataSpace attr_dataspace(1, dims);
  H5::Attribute attribute = dataset.createAttribute( name, H5::PredType::NATIVE_INT, attr_dataspace );
  attribute.write(H5::PredType::NATIVE_INT, values.data());
}

void add_vector_float_attribute(H5::DataSet & dataset, const std::string & name, 
			      const std::vector<float> & values ) {
  hsize_t dims[1] = { values.size() };
  H5::DataSpace attr_dataspace(1, dims);
  H5::Attribute attribute = dataset.createAttribute( name, H5::PredType::NATIVE_FLOAT, attr_dataspace );
  attribute.write(H5::PredType::NATIVE_FLOAT, values.data());
}

void add_vector_double_attribute(H5::DataSet & dataset, const std::string & name, 
				 const std::vector<double> & values ) {
  hsize_t dims[1] = { values.size() };
  H5::DataSpace attr_dataspace(1, dims);
  H5::Attribute attribute = dataset.createAttribute( name, H5::PredType::NATIVE_DOUBLE, attr_dataspace );
  attribute.write(H5::PredType::NATIVE_DOUBLE, values.data());
}

// Helper to create or open an *extendable* dataset of floats. 
// Good for adding chunks and keeping mem happy
// D1 is the number of knots you want your splines to have + 2 (Ereco and Etrue)
// D0 (dims[0]) is the number of rows in this dataset. Controlled in active mem by chunk_size
H5::DataSet create_or_open_dataset( H5::Group & group, const std::string & name, 
				    const std::string & attr_name,
				    const std::vector<double> & attr_knots,
				    int D1, hsize_t chunk_size )
{
  if( H5Lexists( group.getId(), name.c_str(), H5P_DEFAULT ) ) 
    return group.openDataSet(name);

  hsize_t init_dims[2] = {0, static_cast<hsize_t>(D1)};
  hsize_t max_dims[2] = {H5S_UNLIMITED, static_cast<hsize_t>(D1)};
  hsize_t chunk_dims[2] = {chunk_size, static_cast<hsize_t>(D1)};

  H5::DataSpace dataspace(2, init_dims, max_dims);

  // Sorcery to do compression for efficiency in disk size
  H5::DSetCreatPropList plist;
  plist.setChunk(2, chunk_dims);
  plist.setDeflate(6); // 1 to 9, 1 is speed, 9 is size. 6 is balanced

  H5::DataSet dset = group.createDataSet( name, H5::PredType::NATIVE_FLOAT, dataspace, plist );
  // Add some attributes for metadata
  add_string_attribute( dset, "Full name", attr_name );
  //add_vector_float_attribute( dset, "Tweaks", attr_knots );
  add_vector_double_attribute( dset, "Tweaks", attr_knots );

  return dset;
}

// Helper to append a row to an extendable dataset
void append_row( H5::DataSet & dataset, const std::vector<float> & row ) {
  H5::DataSpace filespace = dataset.getSpace();
  hsize_t curr_dims[2];
  filespace.getSimpleExtentDims(curr_dims);

  if( row.size() != curr_dims[1] ) {
    std::cerr << "Error! Row size (" << row.size() << ") does not match dataset dimension 1: "
	      << curr_dims[1] << " - returning nothing" << std::endl;
    return;
  }

  hsize_t new_dims[2] = {curr_dims[0]+1, curr_dims[1]};
  dataset.extend(new_dims);

  filespace = dataset.getSpace();
  hsize_t offset[2] = {curr_dims[0], 0}; // add to end of dataset
  hsize_t count[2] = {1, curr_dims[1]}; // size of new bit
  filespace.selectHyperslab(H5S_SELECT_SET, count, offset);

  // And now load the memory in place and write to it!
  H5::DataSpace memspace(2, count);
  dataset.write(row.data(), H5::PredType::NATIVE_FLOAT, memspace, filespace);
  return;
}

// -------------------------------------------------------------------------------------------
// Main method
// -------------------------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  time_t scriptstartrawtime;
  struct tm * scriptstarttimeinfo;
  time (&scriptstartrawtime);
  scriptstarttimeinfo = localtime (&scriptstartrawtime);
  VLOG("valor_sbn", pNOTICE) << "-----------------------------------------------------------";
  VLOG("valor_sbn", pNOTICE) << " Script start local time and date:  " << asctime(scriptstarttimeinfo);
  VLOG("valor_sbn", pNOTICE) << "-----------------------------------------------------------";

  // Set GENIE print level
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());

  // Get arguments from command line
  CmdLnArgList arg;
  arg.Read(argc,argv, "$VALOR_EXPT/config/apps/make_caf_full_dst.arg");
  VLOG("valor_sbn", pNOTICE) << arg;

  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  valor::Messenger::Instance()->Configure(thresholds);

  string opt_input_name     = arg.GetString("input");
  bool   opt_input_is_list  = arg.GetBool("use-file-list");
  string opt_output_name    = arg.GetString("output");
  string opt_beam_name      = arg.GetString("beam");
  string opt_sample_name    = arg.GetString("sample");
  string opt_oscillation    = arg.GetString("oscillation");
  bool   is_data            = arg.GetBool("is-data");
  bool   write_systematics  = arg.GetBool("write-systematics");
  string systematics_output = arg.GetString("systematics-output");
  int    max_n_events       = arg.GetInt("max-n-events");

  // Switch off systematics for data if passed by accident
  if( is_data && write_systematics ) {
    VLOG("valor_sbn", pWARN) << "You asked for systematics, but have also asked for data. I am going to set systematics to false.";
    write_systematics = false;
  }

  // Get the sample and beam configuration
  conv::Sample_t sample = util::SampleFromString(opt_sample_name);
  // We'll explicitly allow this to be Undefined for now, pending reorganisation of the samples
  
  conv::BeamConf_t beam = util::BeamConfFromString(opt_beam_name);
  assert(beam != conv::kbUndefined);

  // Get the trees. Only the recTree will be available for data
  TChain * recTree    = new TChain(analysis_tree.c_str());
  TChain * globalTree = ( ! is_data ) ? new TChain(global_tree.c_str()) : 0;
  TChain * genieTree  = ( ! is_data ) ? new TChain(genie_tree.c_str()) : 0;

  if( is_data ) VLOG("valor_sbn", pNOTICE) << "You are processing DATA. Ignoring global tree and GENIE";

  // Add files to the chain. Check files exist, check all inputs OK
  // Also, get the number of POT processed
  double NPOT = 0.0;
  if( ! opt_input_is_list ) {
    try {
      recTree->Add(opt_input_name.c_str());
      if( globalTree != 0 ) globalTree->Add(opt_input_name.c_str());
      if( genieTree != 0 ) genieTree->Add(opt_input_name.c_str());

      // open the file and get the POT now. Uses xroot's nominated access pattern
      // unique_ptr releases mem when out of scope! yay for good memory mgmt :)
      auto fin = std::unique_ptr<TFile>( TFile::Open(opt_input_name.c_str()) );
      NPOT += (dynamic_cast<TH1D *>( fin->Get("TotalPOT") ))->Integral();
      fin->Close();
    } catch (const std::exception & e) {
      VLOG("valor_sbn", pFATAL) << "Caught exception when processing input file: " << e.what();
    } // catch exception
  } else { // For each file in the list, add the input
    try {
      std::ifstream input_stream(opt_input_name.c_str());
      std::string line; std::string count_line;
      int iFile = 0; int nFiles = 0;
      while( std::getline(input_stream, count_line) ) {
	nFiles++;
      }
      input_stream.clear();
      input_stream.seekg(0, std::ios::beg);

      while( std::getline(input_stream, line) ) {
	try {
	  recTree->Add(line.c_str());
	  if( globalTree != 0 ) globalTree->Add(line.c_str());
	  if( genieTree != 0 ) genieTree->Add(line.c_str());
	  printProgress(static_cast<double>(iFile+1)/static_cast<double>(nFiles));
	  auto fin = std::unique_ptr<TFile>( TFile::Open(line.c_str()) );
	  NPOT += (dynamic_cast<TH1D *>( fin->Get("TotalPOT") ))->Integral();
	  fin->Close();
	} catch (const std::exception & ex) {
	  VLOG("valor_sbn", pFATAL) << "Caught exception when processing single input file " << line.c_str() << " in list: " << ex.what();
	} // catch exception in line of input list

	iFile++;
      } // loop over lines
      std::cout << "" << std::endl;
      input_stream.close();
    } catch (const std::exception & e) {
      VLOG("valor_sbn", pFATAL) << "Caught exception when processing input file list: " << e.what();
    } // catch input list exception
    
  } // input is list of files?

  std::ostringstream asts;
  asts << "I successfully opened " << recTree->GetNtrees() 
       << " caf files, with " << NPOT << " POT.";
  asts << "\nThere are " << recTree->GetEntries() << " events";
  if( genieTree != 0 ) asts << "\nThese correspond to " << genieTree->GetEntries() << " interactions";

  VLOG("valor_sbn", pNOTICE) << asts.str();

  // Start setting out the structure
  int    valor_dst_sample       = sample;
  int    valor_dst_beam         = -1;   // see Conventions/BeamConf.h
  int    valor_dst_reac_mode    = -1;   // see Conventions/ReacMode.h
  int    valor_dst_reac_type    = -1;   // see Conventions/ReacMode.h
  int    valor_dst_target       = -1;   // nuclear target -  GENIE PDG convention
  double valor_dst_baseline     = -1.0; // true baseline of the event
  int    valor_dst_init_nupdg   = -1;   // Initial PDG
  int    valor_dst_final_nupdg  = -1;   // Final PDG
  double valor_dst_enu_true     = -1.0; // true neutrino energy, in GeV
  double valor_dst_enu_reco     = -1.0; // reco neutrino energy, in GeV
  double valor_dst_wght_pot     = 1.0 / NPOT; // POT weight

  TFile fout(opt_output_name.c_str(),"recreate");
  fout.cd();

  TTree * valor_dst =
    new TTree("valor_sbn_dst","DST input for VALOR/SBN fit");

  Long64_t nev = recTree->GetEntries();
  if( max_n_events > 0 ) nev = std::min( nev, static_cast<Long64_t>(max_n_events) );
  Long64_t nev_accept = 0;
  std::vector<Long64_t> nev_accept_by_mode;
  for (int im = 0 ; im < valor::conv::kNReacModes; im++) {
    nev_accept_by_mode.push_back(0);
  }

  valor_dst->Branch("beam"      , &valor_dst_beam        ,"beam/I"       );
  valor_dst->Branch("sample"    , &valor_dst_sample      ,"sample/I"     );
  valor_dst->Branch("reac_mode" , &valor_dst_reac_mode   ,"reac_mode/I"  );
  valor_dst->Branch("reac_type" , &valor_dst_reac_type   ,"reac_type/I"  );
  valor_dst->Branch("init_pdg"  , &valor_dst_init_nupdg  ,"init_pdg/I"   );
  valor_dst->Branch("final_pdg" , &valor_dst_final_nupdg ,"final_pdg/I"  );
  valor_dst->Branch("baseline"  , &valor_dst_baseline    ,"baseline/D"   );
  valor_dst->Branch("target"    , &valor_dst_target      ,"target/I"     );
  valor_dst->Branch("enu_true"  , &valor_dst_enu_true    ,"enu_true/D"   );
  valor_dst->Branch("enu_reco"  , &valor_dst_enu_reco    ,"enu_reco/D"   );
  valor_dst->Branch("wght_pot"  , &valor_dst_wght_pot    ,"wght_pot/D"   );

  // To get the reconstructed energy, we'll need a few components. We'll use Pandora reconstruction
  /*
   * Rationale: In each slice, Pandora assigns PFPs (which I think stands for Particle Flow Particles)
   * a track score. If score >= 0.5, assume the particle is track-like, else it's shower-like.
   *
   *
   * For now, we'll only deal with track-like (SRTrack) particles.
   * These are either contained, or not. (see the fiducial volume in cafpyana/util/makedf.py, I use
   * Sungbin's definition of the FV).
   * If the track's start and end vertices are within the FV, we use momentum-by-range (SRTrkRange) -
   * if not, by multiple Coulomb scattering (MCS).
   * 
   * Each track-like PFP gets a particle hypothesis (since we can only see the energy deposited along
   * the track, so we have to assume the dE/dx profile of each possible particle and fit it to the
   * depositions we see).
   *
   * To make matters worse, each plane (2 inductions and a collection) has its own chi2 and N_hits.
   * That is to say, each plane does its own fit.
   * For each particle hypothesis, average the three fits using the chi2/ndof, X, as a metric:
   * If planes 0, 1, 2 have hits N0, N1, N2 and metrics X0, X1, X2, then the average metric is
   *
   *        w0 * X0 + w1 * X1 + w2 * X2                    Ni
   * <X> = -----------------------------, where wi = --------------
   *            (w0 + w1 + w2) == 1                   N0 + N1 + N2
   *
   * We'll save the lepton track score, and the minimum \sum_{particle hypotheses}(<X>).
   * 
   * From each of these components, we get the momentum, and from that + mass the energy.
   *
   */

  // The FV limits are a pair (first: SBND, second.ICARUS) of vectors of (low, high) limits on (x, y, z)
  // units: cm, detector coordinates
  const std::pair< std::vector<std::pair<double, double>>,
		   std::vector<std::pair<double, double>> > FV_limits = {
    { { -190.0, 190.0 }, { -190.0, 190.0 }, { 10.0, 450.0 } },
    { { -358.49, -61.94 }, { -181.86, 134.96 }, { -894.95, 894.95 } }
  };

  Float_t valor_dst_vertex_x = -9999.99;
  Float_t valor_dst_vertex_y = -9999.99;
  Float_t valor_dst_vertex_z = -9999.99;

  Float_t valor_dst_lep_track_score = -1.0;
  Float_t valor_dst_min_chi2_ndof   = -1.0;
  Int_t   valor_dst_contained_event = -1;

  valor_dst->Branch("reco_vertex_x",        &valor_dst_vertex_x,        "reco_vertex_x/F"       );
  valor_dst->Branch("reco_vertex_y",        &valor_dst_vertex_y,        "reco_vertex_y/F"       );
  valor_dst->Branch("reco_vertex_z",        &valor_dst_vertex_z,        "reco_vertex_z/F"       );
  valor_dst->Branch("reco_lep_track_score", &valor_dst_lep_track_score, "reco_lep_track_score/F");
  valor_dst->Branch("reco_min_chi2_ndof",   &valor_dst_min_chi2_ndof,   "reco_min_chi2_ndof/F"  );
  valor_dst->Branch("reco_contained_event", &valor_dst_contained_event, "reco_contained_event/I");

  caf::StandardRecord * rec = 0; 
  recTree->SetBranchAddress("rec", &rec);

  Long64_t slices_considered = 0;
  for( Long64_t iev = 0; iev < nev; iev++ ) {
    //printProgress(static_cast<double>(iev+1)/static_cast<double>(nev));

    recTree->GetEntry(iev);
    std::vector<caf::SRSlice> slices = rec->slc;

    for( std::vector<caf::SRSlice>::iterator it_slc = slices.begin();
	 it_slc != slices.end(); ++it_slc ) {

      if( (*it_slc).is_clear_cosmic ) continue; // No need to consider these!

      caf::SRVector3D vtx = (*it_slc).vertex;
      valor_dst_vertex_x = vtx.X();
      valor_dst_vertex_y = vtx.Y();
      valor_dst_vertex_z = vtx.Z();

      slices_considered++;
      valor_dst->Fill();

    } // loop over slices in entry
  } // loop over entries in chain

  std::cout << "" << std::endl;
  std::cout << "considered " << slices_considered << " slices" << std::endl;

  // Saving VALOR DST to output file
  VLOG("valor_sbn", pNOTICE)
    << "Saving VALOR/SBN DST to: " << opt_output_name;
  valor_dst->Write();
  fout.Close();

  VLOG("valor_sbn", pNOTICE)  << "Done!";

  time_t endrawtime;
  struct tm * endtimeinfo;
  time (&endrawtime);
  endtimeinfo = localtime (&endrawtime);
  time_t total_time = endrawtime-scriptstartrawtime;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " End local time and date  :  " << asctime(endtimeinfo);
  std::cout << " Total time taken         :  " << total_time/static_cast<double>(60) << " minutes" << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;

  return 0;
}

#pragma diagnostic pop
