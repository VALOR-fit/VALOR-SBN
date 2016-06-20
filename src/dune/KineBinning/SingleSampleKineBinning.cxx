//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <TSystem.h>

#include "valor/Utilities/UtlXML.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Env.h"
#include "valor/Messenger/Messenger.h"
#include "dune/Conventions/ArrIdx.h"
#include "dune/KineBinning/SingleSampleKineBinning.h"
#include "dune/KineBinning/KBCubHcmbMondrian.h"
#include "dune/KineBinning/KBCubHcmbEdge2Edge.h"

using namespace valor;

//________________________________________________________________________________________
SingleSampleKineBinning::SingleSampleKineBinning(conv::BeamConf_t b, conv::Sample_t s)
{
  this->Init();

  fBeamConf = b;
  fSample   = s;
}
//________________________________________________________________________________________
SingleSampleKineBinning::~SingleSampleKineBinning(void)
{
  this->CleanUp();
}
//________________________________________________________________________________________
bool SingleSampleKineBinning::Read(string file)
{
  if(fBeamConf == conv::kbUndefined) {
    LOG("SampleBinning", pERROR) << "Can not read binning for undefined beam";
    util::Die(1); 
    return false;
  }
  if(fSample == conv::ksUndefined) {
    LOG("SampleBinning", pERROR) << "Can not read binning for undefined sample";
    util::Die(1); 
    return false;
  }

  this->CleanUp();

  TString ts_file = file.c_str();
  gSystem->ExpandPathName(ts_file);

  // See if it works as a normal path
  FileStat_t dummy;
  if (gSystem->GetPathInfo(ts_file.Data(), dummy))
  {
    // If not, try the config folder
    ts_file = TString::Format("%s/%s",
       Env::Instance()->TopLevelConfDir().c_str(),ts_file.Data());
    if (gSystem->GetPathInfo(ts_file.Data(), dummy)) {
      LOG("SampleBinning", pERROR) << "Binning file not found: " << file;
      util::Die(1); 
      return false;
    }
  }

  // Parse the input binning configuration XML file
  TXMLEngine* xml = new TXMLEngine;
  XMLDocPointer_t xmldoc = xml->ParseFile(ts_file.Data());
  if (xmldoc==0) {
    LOG("SampleBinning",pERROR)
        << "Can not parse input XML file [" << ts_file << "]";
    delete xml;
    util::Die(1); 
    return false;
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);

  //
  // Reco/Optimized
  //

  if(! util::NodeExists(xml,root_node,"reco_optimized")) {
     LOG("SampleBinning", pERROR)
        << "<reco_optimized> node not found in file: " << file;
     return false;
  }
  string reco_opt_binning_file = util::XML2String(xml,root_node,"reco_optimized");
  LOG("SampleBinning", pINFO)
    << "Reading optimized reco binning from: " << reco_opt_binning_file;

  fRecoOptimizedBinning = new KBCubHcmbMondrian;
  bool read_ok = fRecoOptimizedBinning->Read(reco_opt_binning_file);
  if(!read_ok) {
     LOG("SampleBinning", pINFO)
       << "Could not read optimized reco binning from: " << reco_opt_binning_file;
     return false;
  }

  //
  // Reco/Simple
  //

  if(! util::NodeExists(xml,root_node,"reco_simple")) {
     LOG("SampleBinning", pERROR)
        << "<reco_simple> node not found in file: " << file;
     return false;
  }
  string reco_smp_binning_file = util::XML2String(xml,root_node,"reco_simple");
  LOG("SampleBinning", pINFO)
    << "Reading simple reco binning from: " << reco_smp_binning_file;

  fRecoSimpleBinning = new KBCubHcmbEdge2Edge;
  read_ok = fRecoSimpleBinning->Read(reco_smp_binning_file);
  if(!read_ok) {
     LOG("SampleBinning", pINFO)
       << "Could not read simple reco binning from: " << reco_smp_binning_file;
     return false;
  }


  //
  // True/Simple [default]
  //

  bool def_true_smp_exists = util::NodeExists(xml,root_node,"true_simple/default");
  if(! def_true_smp_exists) {
     LOG("SampleBinning", pWARN)
        << "<true_simple><default> node not found in file: " << file << "\n"
        << " ** Binning must be specified for every single reaction mode";
  }
  if(def_true_smp_exists) {
     string def_true_smp_binning_file = util::XML2String(xml,root_node,"true_simple/default");
     LOG("SampleBinning", pINFO)
        << "Reading default simple true binning from: " << def_true_smp_binning_file;

     KBCubHcmbEdge2Edge * def_true_smp_binning = new KBCubHcmbEdge2Edge;
     read_ok = def_true_smp_binning->Read(def_true_smp_binning_file);
     if(!read_ok) {
        LOG("SampleBinning", pINFO)
          << "Could not read default simple true binning from: " << def_true_smp_binning_file;
        return false;
     }
     fTrueSimpleBinningUnique.push_back(def_true_smp_binning);
     for(int im = 0; im < conv::kNReacModes; im++) {
        fTrueSimpleBinning [im] = def_true_smp_binning;
     }
  }

  //
  // True/Simple [per mode]
  //

  int is = util::ArrIdx::Instance()->SampleIdx(fBeamConf,fSample);
  for(int im = 0; im < conv::kNReacModes; im++) {
    conv::ReacMode_t m = conv::kReactionModes[is][im];
    if(m == conv::kmUndefined) continue;
    string node_path = "true_simple/" + util::AsString(m);
    bool mode_true_smp_exists = util::NodeExists(xml,root_node,node_path);
    if(mode_true_smp_exists) {
      string mode_true_smp_binning_file = util::XML2String(xml,root_node,node_path);
      LOG("SampleBinning", pINFO)
         << "Reading default simple true binning from: " << mode_true_smp_binning_file;

      KBCubHcmbEdge2Edge * mode_true_smp_binning = new KBCubHcmbEdge2Edge;
      read_ok = mode_true_smp_binning->Read(mode_true_smp_binning_file);
      if(!read_ok) {
         LOG("SampleBinning", pINFO)
            << "Could not read simple true binning from: " << mode_true_smp_binning_file;
         return false;
      }
      fTrueSimpleBinningUnique.push_back(mode_true_smp_binning);
      fTrueSimpleBinning [im] = mode_true_smp_binning;
    }    
  }


  return false;
}
//________________________________________________________________________________________
KBCubHcmbEdge2Edge * SingleSampleKineBinning::TrueSmpBinning(conv::ReacMode_t m) const
{
  if(m == conv::kmUndefined) return 0;
  int im = util::ArrIdx::Instance()->ReacModeIdx(fSample,m);
  return this->TrueSmpBinning(im);
}
//________________________________________________________________________________________
void SingleSampleKineBinning::Init(void)
{
  fBeamConf = conv::kbUndefined; 
  fSample   = conv::ksUndefined;

  fRecoOptimizedBinning = 0;
  fRecoSimpleBinning    = 0;
  for(int im = 0; im < conv::kNReacModes; im++) {
     fTrueSimpleBinning [im] = 0;
  }

  fTrueSimpleBinningUnique.clear();
}
//________________________________________________________________________________________
void SingleSampleKineBinning::CleanUp(void)
{
  if (fRecoOptimizedBinning) delete fRecoOptimizedBinning;
  if (fRecoSimpleBinning   ) delete fRecoSimpleBinning;

  vector<KBCubHcmbEdge2Edge *>::iterator it = fTrueSimpleBinningUnique.begin();
  for( ; it != fTrueSimpleBinningUnique.end(); ++it) {
    KBCubHcmbEdge2Edge * binning = *it;
    if(binning) { delete binning; }
  }

  this->Init();
}
//________________________________________________________________________________________



