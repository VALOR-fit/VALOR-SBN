//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <iostream>
#include <iomanip>

#include "TMath.h"
#include "TString.h"
#include "TSystem.h"

#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/UtlNumStat.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/UtlXML.h"

#include "dune/Conventions/DuneBuild.h"
#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Utilities/DuneRFL.h"
#include "dune/Utilities/KinematicBin.h"

#define USE_FLAT_SPLINE_FOR_MISSING

using std::endl;

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

// Initialise the flat spline
static Double_t flat_knots_y[5] = {  1,  1, 1, 1,  1};
const ROOT::Math::Interpolator* valor::util::DuneRFL::kFlatSpline = util::ConvertTSplineToGSL(TSpline3("flat_spline",-100,100,flat_knots_y,5));

// We'll never use this address to dereference - it can be passed as a flag indicating that no spline should exist.
const ROOT::Math::Interpolator* valor::util::DuneRFL::kNoSplineRequired = (ROOT::Math::Interpolator*)&conv::kBadResult;

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
valor::util::DuneRFL::DuneRFL(void)
 :
fSplines       (NULL),
fSplineBlockSize(0),
fBeam          (conv::kbUndefined),
fSample        (conv::ksUndefined),
fNModes        (0),
fModes         (NULL),
fNParams       (0),
fParams        (NULL),
fNBinsTrue1    (1),
fNBinsTrue2    (1),
fNBinsTrue3    (1),
fNBinsReco1    (1),
fNBinsReco2    (1),
fNBinsReco3    (1),
fNBinZones     (1),
fSplineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[ZONE]_[TRUE1]_[TRUE2]_[RECO1]_[RECO2]")
{
  
}
//________________________________________________________________________________________
valor::util::DuneRFL::DuneRFL(conv::BeamConf_t b, conv::Sample_t s, int n_params, const PhysParamId_t * param_ids)
 :
fSplines       (NULL),
fSplineBlockSize(0),
fBeam          (b),
fSample        (s),
fNModes        (conv::kNReacModes),
fModes         (NULL),
fNParams       (n_params),
fParams        (NULL),
fNBinsTrue1    (1),
fNBinsTrue2    (1),
fNBinsTrue3    (1),
fNBinsReco1    (1),
fNBinsReco2    (1),
fNBinsReco3    (1),
fNBinZones     (1),
fSplineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[ZONE]_[TRUE1]_[TRUE2]_[RECO1]_[RECO2]")
{
  fParams = new PhysParamId_t[fNParams];
  memcpy(fParams, param_ids, fNParams*sizeof(PhysParamId_t));
  fModes = new ReacMode_t[fNModes];
  memcpy(fModes,conv::kReactionModes[ArrIdx::Instance()->SampleIdx(b,s)], fNParams*sizeof(ReacMode_t));
  
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
    if (fSplines[ispl] && fSplines[ispl]!=kFlatSpline && fSplines[ispl]!=kNoSplineRequired) {
       delete fSplines[ispl];
    }
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
const ROOT::Math::Interpolator* valor::util::DuneRFL::GetSpline (
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
bool valor::util::DuneRFL::Read(std::string config_file, Option_t * /*option*/)
{
  // Get binning details, allocate the spline block
  fNBinsTrue1 = util::NumEtrueBinsXsec (fSample);
  fNBinsReco1 = util::NumErecoBinsXsec (fSample, 0);
  fNBinsReco2 = util::NumYrecoBinsXsec (fSample, 0);
  for (int im = 0 ; im < fNModes ; im++) {
    conv::ReacMode_t m = fModes[im];
    fNBinsTrue2 = TMath::Max(fNBinsTrue2,util::NumQ2trueBinsXsec (fSample,m));
  }
  fSplineBlockSize = fNModes * fNParams * fNBinZones *
    fNBinsTrue1*fNBinsTrue2*fNBinsTrue3*
    fNBinsReco1*fNBinsReco2*fNBinsReco3;
    
  LOG("DuneRFL",pDEBUG) << "Spline binning for sample "<<util::AsString(fBeam)<<" "<<util::AsString(fSample)<<"\n"
   <<std::setw(7)<<fNModes<<" modes.\n"
   <<std::setw(7)<<fNParams<<" parameters with splines.\n"
   <<std::setw(7)<<fNBinZones<<" bin zones.\n"
   <<std::setw(7)<<fNBinsTrue1<<" Etrue bins.\n"
   <<std::setw(7)<<fNBinsTrue2<<" Q^2 bins.\n"
   <<std::setw(7)<<fNBinsTrue3<<" other truevar bins.\n"
   <<std::setw(7)<<fNBinsReco1<<" Ereco bins.\n"
   <<std::setw(7)<<fNBinsReco2<<" Yreco bins.\n"
   <<std::setw(7)<<fNBinsReco2<<" other recovar bins.\n"
   <<std::setw(7)<<fSplineBlockSize<<" maximum.";
    
  fSplines = new const ROOT::Math::Interpolator*[fSplineBlockSize]();

  TString ts_file = config_file.c_str();
  gSystem->ExpandPathName(ts_file);

  // Check for config file.
  // See if it works as a normal path
  FileStat_t dummy;
  if (gSystem->GetPathInfo(ts_file.Data(), dummy)) 
  {
    // If not, try the config folder
    ts_file = TString::Format("%s/%s",Env::Instance()->TopLevelConfDir().c_str(),ts_file.Data());
    if (gSystem->GetPathInfo(ts_file.Data(), dummy)) {
      LOG("DuneRFL",pERROR) << "Config file not found: "<<ts_file;
      util::Die(1); return false;
    }
  }
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(ts_file.Data());
  if (xmldoc==0) {
    LOG("DuneRFL",pERROR) << "Can not parse input XML file [" << ts_file << "]";
    delete xml;
    util::Die(1); return false;
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);
  
  string folder = util::XML2String(xml,root_node,"splines/folder");
  if (!folder.size()) {
    LOG("DuneRFL",pFATAL) << "Failed to read spline folder from XML.";
    util::Die(-1); return false;
  }
  
  string spl_file_pattern = util::XML2String(xml,root_node,"splines/pattern");

  if (!spl_file_pattern.size()) {
    LOG("DuneRFL",pFATAL) << "Failed to open spline filename pattern from XML.";
    util::Die(-1); return false;
  }
  
  vector<TFile*> spline_files;
  for (int ip = 0 ; ip < fNParams ; ip++) {
    conv::PhysParamId_t p = fParams[ip];
    if(p == conv::kPhypUndefined) continue;
    TString filename = spl_file_pattern.c_str();
    filename = filename.ReplaceAll("[BEAM]"   , util::AsString(fBeam  ).c_str());
    filename = filename.ReplaceAll("[SAMPLE]" , util::AsString(fSample).c_str());
    filename = filename.ReplaceAll("[PARAM]"  , util::AsString(p).c_str());
    
    TString base_dir = Env::Instance()->TopLevelDataDir().c_str();
    
    TFile * spline_file = new TFile((base_dir+"/"+folder.c_str()+"/"+filename).Data());
    LOG("DuneRFL",pINFO) << "Will read splines from file "<<spline_file->GetName();
    spline_files.push_back(spline_file);
  }
  
  int isample = ArrIdx::Instance()->SampleIdx(fBeam, fSample);
  
  int n_splines_read = 0;
  int n_splines_missing = 0;
  int n_splines_expected = fSplineBlockSize;
  int n_splines_flat = 0;
  int n_splines_neg = 0;
  
  for(int imode = 0; imode < conv::kNReacModes; imode++) {
    conv::ReacMode_t m = conv::kReactionModes[isample][imode];
    if(m == conv::kmUndefined) continue;
    
    const int true1_bins = util::NumEtrueBinsXsec (fSample);
    const int true2_bins = util::NumQ2trueBinsXsec (fSample,m);
    
    for (int ip = 0 ; ip < fNParams ; ip++) {
      conv::PhysParamId_t p = fParams[ip];
      if(p == conv::kPhypUndefined) continue;
      
      bool param_applied_to_mode = util::ParamIsAppliedTo(fBeam,fSample,m,p);
      
      KinematicBin kb;
      
      for (int izone = 0 ; izone < fNBinZones ; izone++ ) {
        kb.zone = izone;
        const int reco1_bins = util::NumErecoBinsXsec (fSample, izone);
        const int reco2_bins = util::NumYrecoBinsXsec (fSample, izone);
        for (int itrue1 = 0 ; itrue1 < true1_bins ; itrue1++) {
          kb.true1 = itrue1;
          for (int itrue2 = 0 ; itrue2 < true2_bins ; itrue2++) {
            kb.true2 = itrue2;
            for (int itrue3 = 0 ; itrue3 < fNBinsTrue3 ; itrue3++) {
              kb.true3 = itrue3;
              for (int ireco1 = 0 ; ireco1 < reco1_bins ; ireco1++) {
                kb.reco1 = ireco1;
                for (int ireco2 = 0 ; ireco2 < reco2_bins ; ireco2++) {
                  kb.reco2 = ireco2;
                  for (int ireco3 = 0 ; ireco3 < fNBinsReco3 ; ireco3++) {
                    kb.reco3 = ireco3;
                    
                    TString spl_name = this->BuildSplineName(m,p,kb);
                    
                    const UInt_t spline_index = SplineIndex(imode,ip,kb);
                    if (spline_index >= fSplineBlockSize) {
                      LOG("DuneRFL",pFATAL) << "Bad spline index "<<spline_index; 
                      util::Die(-1); return false;
                    }
                    
                    if (param_applied_to_mode) {
                      TObject * spline_obj = NULL;
                      for (unsigned int ifile = 0; ifile < spline_files.size(); ifile++) {
                        TFile * spline_file = spline_files[ifile];
                        spline_obj = spline_file->Get(spl_name.Data());
                        if (spline_obj) {break;}
                      }
                      TSpline* spline = dynamic_cast<TSpline*>(spline_obj);
                      if (spline) {
                        if (util::SplineIsFlat(spline)) {
                          delete spline;
                          fSplines[spline_index] = kFlatSpline;
                          n_splines_flat++;
                          n_splines_read++;
                        }
                        else if (this->CheckForNegativeValues(spline,p)) {
                          delete spline;
                          fSplines[spline_index] = kFlatSpline;
                          n_splines_neg++;
                          n_splines_read++;
                        }
                        else {
                          fSplines[spline_index] = util::ConvertTSplineToGSL(*spline);
                          delete spline;
                          n_splines_read++;
                        }
                      }
                      else {
                        LOG("DuneRFL",pWARN)<<"Spline not found: "<<spl_name;
                        fSplines[spline_index] = NULL;
                        n_splines_missing++;
                      }
                    }
                    else {
                      fSplines[spline_index] = kNoSplineRequired;
                      n_splines_expected--;
                    }
                  } //ireco3
                } //ireco2
              } //ireco1
            } //itrue3
          } //itrue2
        } //itrue1
      } //iz
    } //ip
  } //imode
  
  for (unsigned int ifile = 0; ifile < spline_files.size(); ifile++) {
    TFile * spline_file = spline_files[ifile];
    spline_file->Close();
    delete spline_file;
  }
  
  LOG("DuneRFL",pINFO)<<"Read "<<n_splines_read<<" splines, of which "<<n_splines_flat<<" were flat.";
  if (n_splines_neg) {
    LOG("DuneRFL",pWARN) << "Skipped "<<n_splines_neg<<" splines due to negative values. Fix this!";
  }
  if (n_splines_missing) {
    LOG("DuneRFL",pFATAL) << "Missing "<<n_splines_missing<<" splines. Exiting.";
    util::Die(-1);return false;
  }
  
  xml->FreeDoc(xmldoc);
  delete xml;
  
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
void valor::util::DuneRFL::SetSplineNamePattern(std::string pattern) {
  fSplineNamePattern = pattern.c_str();
}
//________________________________________________________________________________________
bool valor::util::DuneRFL::CheckForNegativeValues(const TSpline * spl, conv::PhysParamId_t p) const
{
  double min_val = PhysicalParameterLimits::Instance()->MinValue(p);
  double max_val = PhysicalParameterLimits::Instance()->MaxValue(p);
  static const int evaluations = 30;
  for (int i = 0 ; i < evaluations; i++) {
    double x = min_val + (i+0.5)*(max_val-min_val)/evaluations;
    if (spl->Eval(x) < 0) {return true;}
  }
  return false;
}
//________________________________________________________________________________________
