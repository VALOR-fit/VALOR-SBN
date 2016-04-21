//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "TString.h"
#include "TMath.h"

#include "Messenger/Messenger.h"
#include "Utilities/UtlSystem.h"
#include "Utilities/UtlXML.h"

#include "dune/Conventions/DuneBuild.h"
#include "dune/Utilities/DuneRFL.h"
#include "dune/Utilities/KinematicBin.h"

#define USE_FLAT_SPLINE_FOR_MISSING

using std::endl;

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

// Initialise the flat spline
static Double_t flat_knots_x[5] = {-10, -5, 0, 5, 10};
static Double_t flat_knots_y[5] = {  1,  1, 1, 1,  1};
const TSpline * valor::util::DuneRFL::kFlatSpline = new TSpline3("flat_spline",flat_knots_x,flat_knots_y,5);

// We'll never use this address to dereference - it can be passed as a flag indicating that no spline should exist.
const TSpline * valor::util::DuneRFL::kNoSplineRequired = (TSpline*)&conv::kBadResult;

//________________________________________________________________________________________
namespace valor {
namespace util {
  std::ostream & operator<<(std::ostream & stream, const DuneRFL & rfl)
  {
    rfl.Print(stream);
    return stream;
  }
}
}
//________________________________________________________________________________________
valor::util::DuneRFL::DuneRFL()
 :
fBeam          (conv::kbUndefined),
fSample        (conv::ksUndefined),
fNModes        (0),
fModes         (0),
fNParams       (0),
fParams        (0),
fNBinsTrue1    (1),
fNBinsTrue2    (1),
fNBinsTrue3    (1),
fNBinsReco1    (1),
fNBinsReco2    (1),
fNBinsReco3    (1),
fNBinZones     (1),
fSplineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[ZONE]_[TRUE1]_[TRUE2]_[OBS1]_[OBS2]")
{
  
}
//________________________________________________________________________________________
valor::util::DuneRFL::DuneRFL(BeamConf_t b, Sample_t s, int n_params, const PhysParamId_t * param_ids)
 :
fBeam          (b),
fSample        (s),
fNModes        (0),
fModes         (0),
fNParams       (n_params),
fParams        (NULL),
fNBinsTrue1    (1),
fNBinsTrue2    (1),
fNBinsTrue3    (1),
fNBinsReco1    (1),
fNBinsReco2    (1),
fNBinsReco3    (1),
fNBinZones     (1),
fSplineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[ZONE]_[TRUE1]_[TRUE2]_[OBS1]_[OBS2]")
{
  fParams = new PhysParamId_t[fNParams];
  memcpy(fParams, param_ids, n_params*sizeof(PhysParamId_t));
  
  // Fill parameter to index
  for (int ip = 0 ; ip < conv::knppmax ; ip++ ) {
    conv::PhysParamId_t p = (conv::PhysParamId_t)ip;
    fParam2Idx[p] = -1;
    for (int idx = 0 ; idx < fNParams; idx++) {
      if (fParams[idx]==p) {
        fParam2Idx[p] = idx;
      }
    }
  }
}
//________________________________________________________________________________________
//~ valor::util::DuneRFL::DuneRFL(const DuneRFL &) 
//~ {
//~ }
//________________________________________________________________________________________
valor::util::DuneRFL::~DuneRFL()
{
  for (unsigned int ispl = 0 ; ispl < fSplineBlockSize; ispl++) {
    if (fSplines[ispl]) {delete fSplines[ispl];}
    delete[] fSplines;
  }
  
  if (fModes        )  {delete fModes;        }
  if (fParams       )  {delete fParams;       }
  
}
//________________________________________________________________________________________
void valor::util::DuneRFL::Print(ostream & stream) const
{
  stream << "[response functions]" << endl;
}
//________________________________________________________________________________________
const TSpline * valor::util::DuneRFL::GetSpline (
  conv::ReacMode_t m, conv::PhysParamId_t p,
  const KinematicBin & kb) const
{
  static const util::ArrIdx * arr_idx = util::ArrIdx::Instance();
  
  const int im = arr_idx->ReacModeIdx(fSample,m);
  const int ip = this->Param2Idx(p);
  
  const int splidx = SplineIndex(im,ip,kb);
  
  return fSplines[splidx];
}
//________________________________________________________________________________________
TString valor::util::DuneRFL::BuildSplineName (
  conv::ReacMode_t m, conv::PhysParamId_t p,
  const KinematicBin & kb) const
{
  TString name = fSplineNamePattern;
  
  name = name.ReplaceAll("[BEAM]"   , util::AsString(fBeam  ).c_str());
  name = name.ReplaceAll("[SAMPLE]" , util::AsString(fSample).c_str());
  
  name = name.ReplaceAll("[MODE]"   , util::AsString(m).c_str());
  name = name.ReplaceAll("[PARAM]"  , util::AsString(p).c_str());
  
  name = name.ReplaceAll("[ZONE]"  , TString::Format("%d", kb.zone  ));
  name = name.ReplaceAll("[TRUE1]" , TString::Format("%d", kb.true1 ));
  name = name.ReplaceAll("[TRUE2]" , TString::Format("%d", kb.true2 ));
  name = name.ReplaceAll("[TRUE3]" , TString::Format("%d", kb.true3 ));
  name = name.ReplaceAll("[RECO1]" , TString::Format("%d", kb.reco1 ));
  name = name.ReplaceAll("[RECO2]" , TString::Format("%d", kb.reco2 ));
  name = name.ReplaceAll("[RECO3]" , TString::Format("%d", kb.reco3 ));
                         
  return name;
}
//________________________________________________________________________________________
bool valor::util::DuneRFL::Read(std::string config_file,Option_t * /*option*/)
{
  // Get binning details, allocate the spline block
  fNBinsTrue1 = util::NumEtrueBinsXsec (fSample);
  fNBinsReco1 = util::NumErecoBinsXsec (fSample, 0);
  fNBinsReco2 = util::NumYrecoBinsXsec (fSample, 0);
  for (int im = 0 ; im < fNModes ; im++) {
    conv::ReacMode_t m = fModes[im];
    fNBinsTrue2 = TMath::Max(fNBinsTrue2,util::NumQ2trueBinsXsec (fSample,m));
  }
  fSplineBlockSize = fNBinZones *
    fNBinsTrue1*fNBinsTrue2*fNBinsTrue3*
    fNBinsReco1*fNBinsReco2*fNBinsReco3;
    
  fSplines = new TSpline*[fSplineBlockSize]();

  // Parse the input XML configuration file
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(config_file.c_str());
  if (xmldoc==0) {
    LOG("DuneRFL",pERROR) << "Can not parse input XML file [" << config_file << "]";
    delete xml;
    util::Die(1); return false;
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);
  
  TFile * spline_file = util::XML2TFile(xml,root_node,"splines/file");
  
  int isample = ArrIdx::Instance()->SampleIdx(fBeam, fSample);
  
  for(int imode = 0; imode < conv::kNReacModes; imode++) {
    conv::ReacMode_t m = conv::kReactionModes[isample][imode];
    if(m == conv::kmUndefined) continue;
    for (int ip = 0 ; ip < fNParams ; ip++) {
      conv::PhysParamId_t p = fParams[ip];
      if(p == conv::kPhypUndefined) continue;
      
      KinematicBin kb;
      
      for (int izone = 0 ; izone < conv::kNMaxBinZones ; izone++ ) {
        kb.zone = izone;
        for (int itrue1 = 0 ; itrue1 < fNBinsTrue1 ; itrue1++) {
          kb.true1 = itrue1;
          for (int itrue2 = 0 ; itrue2 < fNBinsTrue2 ; itrue2++) {
            kb.true2 = itrue2;
            for (int itrue3 = 0 ; itrue3 < fNBinsTrue3 ; itrue3++) {
              kb.true3 = itrue3;
              for (int ireco1 = 0 ; ireco1 < fNBinsReco1 ; ireco1++) {
                kb.reco1 = ireco1;
                for (int ireco2 = 0 ; ireco2 < fNBinsReco2 ; ireco2++) {
                  kb.reco2 = ireco2;
                  for (int ireco3 = 0 ; ireco3 < fNBinsReco3 ; ireco3++) {
                    kb.reco2 = ireco2;
                    
                    TString spl_name = this->BuildSplineName(m,p,kb);
                    
                    const int spline_index = SplineIndex(imode,ip,kb);
                    TObject * spline_obj = spline_file->Get(spl_name.Data());
                    TSpline * spline = dynamic_cast<TSpline*>(spline_obj);
                    if (spline) {
                      fSplines[spline_index] = spline;
                    }
                    else {
                      LOG("DuneRFL",pWARN)<<"Spline not found: "<<spl_name;
                      fSplines[spline_index] = 0;
                    }
                  } //ireco2
                } //ireco1
              } //itrue1
            } //itrue3
          } //itrue2
        } //itrue1
      } //iz
    } //ip
  } //imode
  
  spline_file->Close();
  
  return true;
}
//________________________________________________________________________________________
util::KinematicBin valor::util::DuneRFL::GetBin(const util::KinematicPoint & kp, conv::ReacMode_t m) const
{
  static const int zone = 0;//SHOULD BE FIXED
  util::KinematicBin kb_out;
  if (fNBinsTrue1 > 1) {
    const Long_t n_bins = fNBinsTrue1;
    const double * bin_edges = util::EtrueBinEdgesXsec(fSample);
    kb_out.true1 = TMath::BinarySearch(n_bins+1, bin_edges, kp.true1);
  }
  if (fNBinsTrue2 > 1) {
    const Long_t n_bins = util::NumQ2trueBinsXsec(fSample,m);
    const double * bin_edges = util::Q2trueBinEdgesXsec(fSample,m);
    kb_out.true2 = TMath::BinarySearch(n_bins+1, bin_edges, kp.true2);
  }
  if (fNBinsTrue3 > 1) {
    const Long_t n_bins    = 1;
    const double * bin_edges = 0;
    assert(!"Not supported");
    kb_out.true3 = TMath::BinarySearch(n_bins+1, bin_edges, kp.true3);
  }
  if (fNBinsReco1 > 1) {
    const Long_t n_bins    = fNBinsReco1;
    const double * bin_edges = util::ErecoBinEdgesXsec(fSample, zone);
    kb_out.reco1 = TMath::BinarySearch(n_bins+1, bin_edges, kp.reco1);
  }
  if (fNBinsReco2 > 1) {
    const Long_t n_bins    = fNBinsReco2;
    const double * bin_edges = util::YrecoBinEdgesXsec(fSample, zone);
    kb_out.reco2 = TMath::BinarySearch(n_bins+1, bin_edges, kp.reco2);
  }
  if (fNBinsReco3 > 1) {
    const Long_t n_bins    = 1;
    const double * bin_edges = 0;
    assert(!"Not supported");
    kb_out.reco3 = TMath::BinarySearch(n_bins+1, bin_edges, kp.reco3);
  }
  
  return kb_out;
}
//________________________________________________________________________________________
int valor::util::DuneRFL::Param2Idx(conv::PhysParamId_t p) const
{
  if (p < 0 || p > conv::knppmax) {
    LOG("DuneRFL",pFATAL) << "Parameter out of range "<<p<<"\t"<<util::AsString(p);
  }
  return fParam2Idx[p];
}
//________________________________________________________________________________________
