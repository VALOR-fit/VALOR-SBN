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
#include "dune/Utilities/SingleSampleKineBinning.h"

#define USE_FLAT_SPLINE_FOR_MISSING

using std::endl;

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

// Initialise the flat spline
static Double_t flat_knots_y[5] = {  1,  1, 1, 1,  1};
const util::Interpolator * valor::util::DuneRFL::kFlatSpline =
  new util::Interpolator(TSpline3("flat_spline",-9E9,9E9,flat_knots_y,5));

// We'll never use this address to dereference - it can be passed as a flag indicating that no spline should exist.
const util::Interpolator* valor::util::DuneRFL::kNoSplineRequired = (util::Interpolator*)&conv::kBadResult;

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
fBinning       (NULL),
fSplines       (NULL),
fSplineBlockSize(0),
fBeam          (conv::kbUndefined),
fSample        (conv::ksUndefined),
fDetector      (conv::kdUndefined),
fNModes        (0),
fModes         (NULL),
fNParams       (0),
fParams        (NULL),
fNBinsTrue     (1),
fNBinsReco     (1),
fSplineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[ZONE]_[TRUE1]_[TRUE2]_[RECO1]_[RECO2]")
{
  
}
//________________________________________________________________________________________
valor::util::DuneRFL::DuneRFL(const SingleSampleKineBinning * binning, const std::vector<PhysParamId_t> & params)
 : DuneRFL(binning,params.size(),params.data()) {}
//________________________________________________________________________________________
valor::util::DuneRFL::DuneRFL(const SingleSampleKineBinning * binning, int n_params, const PhysParamId_t * param_ids)
 :
fBinning       (binning),
fSplines       (NULL),
fSplineBlockSize(0),
fBeam          (fBinning->GetBeamConf()),
fSample        (fBinning->GetSample()),
fDetector      (fBinning->GetDetector()),
fNModes        (conv::kNReacModes),
fModes         (NULL),
fNParams       (n_params),
fParams        (NULL),
fNBinsTrue     (1),
fNBinsReco     (1),
fSplineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[TRUE]_[RECO]")
{
  fParams = new PhysParamId_t[fNParams];
  memcpy(fParams, param_ids, fNParams*sizeof(PhysParamId_t));
  fModes = new ReacMode_t[fNModes];
  memcpy(fModes,conv::kReactionModes[ArrIdx::Instance()->SampleIdx(fBeam,fSample)], fNModes*sizeof(ReacMode_t));
  
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
  
  const VALORBinning  * reco_ob = fBinning->XsecRecoBinning();

  fNBinsReco  = reco_ob->NBins();
  // Calculate max bin numbers
  for (int im = 0 ; im < fNModes ; im++) {
    conv::ReacMode_t m = fModes[im];
    const VALORBinning * true_sb = fBinning->XsecTrueBinning(m);
    fNBinsTrue = std::max(fNBinsTrue,true_sb->NBins());
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
  
  if (fModes        )  {delete[] fModes;        }
  if (fParams       )  {delete[] fParams;       }
}
//________________________________________________________________________________________
void valor::util::DuneRFL::Print(ostream & stream) const
{
  stream << "[response functions]" << endl;
}
//________________________________________________________________________________________
const util::Interpolator* valor::util::DuneRFL::GetSpline (
  conv::ReacMode_t m, conv::PhysParamId_t p,
  const int & itrue, const int & ireco) const
{
  static const util::ArrIdx * arr_idx = util::ArrIdx::Instance();
  
  const int im = arr_idx->ReacModeIdx(fSample,m);
  const int ip = this->Param2Idx(p);
  
  const int splidx = SplineIndex(im,ip,itrue,ireco);
  
  return fSplines[splidx];
}
//________________________________________________________________________________________
TString valor::util::DuneRFL::BuildSplineName (
  conv::ReacMode_t m, conv::PhysParamId_t p,
  const int& itrue, const int& ireco) const
{
  TString name = fSplineNamePattern;
  
  name = name.ReplaceAll("[BEAM]"   , util::AsString(fBeam  ).c_str());
  name = name.ReplaceAll("[SAMPLE]" , util::AsString(fSample).c_str());
  
  name = name.ReplaceAll("[MODE]"   , util::AsString(m).c_str());
  name = name.ReplaceAll("[PARAM]"  , util::AsString(p).c_str());
  
  name = name.ReplaceAll("[TRUE]" , TString::Format("%d", itrue ));
  name = name.ReplaceAll("[RECO]" , TString::Format("%d", ireco ));
  
  return name;
}
//________________________________________________________________________________________
bool valor::util::DuneRFL::Read(std::string config_file, Option_t * /*option*/)
{
  // Get binning details, allocate the spline block
  fSplineBlockSize = fNModes * fNParams * fNBinsTrue * fNBinsReco;
    
  LOG("DuneRFL",pDEBUG) << "Spline binning for sample "<<util::AsString(fBeam)<<" "<<util::AsString(fSample)<<"\n"
   <<std::setw(7)<<fNModes<<" modes.\n"
   <<std::setw(7)<<fNParams<<" parameters with splines.\n"
   <<std::setw(7)<<fNBinsTrue<<" true bins.\n"
   <<std::setw(7)<<fNBinsReco<<" reco bins \n"
   <<std::setw(7)<<fSplineBlockSize<<" maximum.";
    
  fSplines = new const util::Interpolator*[fSplineBlockSize]();

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
    filename = filename.ReplaceAll("[BEAM]"   , util::AsString(fBeam    ).c_str());
    filename = filename.ReplaceAll("[SAMPLE]" , util::AsString(fSample  ).c_str());
    filename = filename.ReplaceAll("[DET]"    , util::AsString(fDetector).c_str());
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
    
    const VALORBinning * true_sb = fBinning->XsecTrueBinning(m);
    const int n_bins_true = true_sb->NBins();
    const int n_bins_reco = fNBinsReco;
    
    for (int ip = 0 ; ip < fNParams ; ip++) {
      conv::PhysParamId_t p = fParams[ip];
      if(p == conv::kPhypUndefined) continue;
      
      bool param_applied_to_mode = util::ParamIsAppliedTo(fBeam,fSample,fDetector,m,p);
      
      for (int ireco = 0 ; ireco < n_bins_reco ; ireco++) {
        for (int itrue = 0 ; itrue < n_bins_true ; itrue++) {
          TString spl_name = this->BuildSplineName(m,p,itrue,ireco);
          
          const UInt_t spline_index = SplineIndex(imode,ip,itrue,ireco);
          if (spline_index >= fSplineBlockSize) {
            LOG("DuneRFL",pFATAL) << "Bad spline index "<<spline_index; 
            util::Die(-1); return false;
          }
          
          if (param_applied_to_mode) {
            TObject * spline_obj = NULL;
            // Read each file till we get one that contains our spline
            for (unsigned int ifile = 0; ifile < spline_files.size(); ifile++) {
              TFile * spline_file = spline_files[ifile];
              spline_obj = spline_file->Get(spl_name.Data());
              if (spline_obj) {break;}
            }
            TSpline* spline = dynamic_cast<TSpline*>(spline_obj);
            if (spline) {
              if (util::SplineIsFlat(spline)) {
                fSplines[spline_index] = kFlatSpline;
                n_splines_flat++;
                n_splines_read++;
                delete spline;
                continue;
              }
              util::Interpolator * gsl_spline = new util::Interpolator(spline,ROOT::Math::Interpolation::kAKIMA);
              delete spline;
              if (this->CheckForNegativeValues(gsl_spline,p)) {
                LOG("DuneRFL",pWARN)<<"Spline has negative values: "<<spl_name<<" - using flat spline instead.";
                delete gsl_spline;
                fSplines[spline_index] = kFlatSpline;
                n_splines_neg++;
                n_splines_read++;
              }
              else {
                fSplines[spline_index] = gsl_spline;
                n_splines_read++;
              }
            }
            else {
              LOG("DuneRFL",pWARN)<<"Spline not found: "<<spl_name;
#ifdef USE_FLAT_SPLINE_FOR_MISSING
              fSplines[spline_index] = kFlatSpline;
#else
              fSplines[spline_index] = NULL;
#endif
              n_splines_missing++;
            }
          }
          else {
            fSplines[spline_index] = kNoSplineRequired;
            n_splines_expected--;
          }
        } // itrue
      } //ireco
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
#ifdef USE_FLAT_SPLINE_FOR_MISSING
    LOG("DuneRFL",pERROR) << "Missing "<<n_splines_missing<<" splines of "<<n_splines_expected<<" expected. Continuing.";
#else
    LOG("DuneRFL",pFATAL) << "Missing "<<n_splines_missing<<" splines of "<<n_splines_expected<<" expected. Exiting.";
    util::Die(-1);return false;
#endif
  }
  
  xml->FreeDoc(xmldoc);
  delete xml;
  
  return true;
}
//________________________________________________________________________________________
std::pair<int,int> valor::util::DuneRFL::GetBin(const util::KinematicPoint & kp, conv::ReacMode_t m) const
{
  const VALORBinning * true_binning = fBinning->XsecTrueBinning(m);
  const VALORBinning * reco_binning = fBinning->XsecRecoBinning();
  
  int nrecodim = reco_binning->NDimensions();
  std::vector<double> recovec;
  if (nrecodim > 0) { recovec.push_back(kp.reco1); }
  if (nrecodim > 1) { recovec.push_back(kp.reco2); }
  if (nrecodim > 2) { recovec.push_back(kp.reco3); }
  
  int ntruedim = true_binning->NDimensions();
  std::vector<double> truevec;
  if (ntruedim > 0) { truevec.push_back(kp.true1); }
  if (ntruedim > 1) { truevec.push_back(kp.true2); }
  if (ntruedim > 2) { truevec.push_back(kp.true3); }
  
  const int itrue = true_binning->FindBin(truevec);
  const int ireco = reco_binning->FindBin(recovec);
  return std::pair<int,int>(itrue,ireco);
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
bool valor::util::DuneRFL::CheckForNegativeValues(const util::Interpolator * spl, conv::PhysParamId_t p) const
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
