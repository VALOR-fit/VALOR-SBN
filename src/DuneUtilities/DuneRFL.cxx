//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "TString.h"

#include "Messenger/Messenger.h"
#include "Utilities/UtlSystem.h"
#include "Utilities/UtlXML.h"

#include "Conventions/DuneBuild.h"

#include "DuneUtilities/DuneRFL.h"
#include "DuneUtilities/KinematicBin.h"

#define USE_FLAT_SPLINE_FOR_MISSING

using std::endl;

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

// Initialise the flat spline
static Double_t flat_knots_x[5] = {-10, -5, 0, 5, 10};
static Double_t flat_knots_y[5] = {  1,  1, 1, 1,  1};
const TSpline * valor::util::DuneRFL::kFlatSpline = new TSpline3("flat_spline",flat_knots_x,flat_knots_y,5);

//________________________________________________________________________________________
inline int SPLINE_INDEX(const int& im, const int& ip, const util::KinematicBin & kb)
{
  using namespace valor::conv;
  return 0;
}
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
kNModes        (0),
kModes         (0),
kNParams       (0),
kParams        (0),
kNBinsTrue1    (0),
kBinEdgesTrue1 (0),
kNBinsTrue2    (0),
kBinEdgesTrue2 (0),
kNBinsTrue3    (0),
kBinEdgesTrue3 (0),
kNBinsReco1    (0),
kBinEdgesReco1 (0),
kNBinsReco2    (0),
kBinEdgesReco2 (0),
kNBinsReco3    (0),
kBinEdgesReco3 (0),
kNBinZones     (0),
kBinZones      (0)
{
  fSplineNamePattern = "spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[ZONE]_[TRUE1]_[TRUE2]_[OBS1]_[OBS2]";
  
  //~ //DEBUG - fill with flat splines with titles
  //~ int ibin = 0, iz=0;
  //~ for (int ib = 0 ; ib < conv::kNBeamConf ; ib++) {
    //~ for (int is = 0 ; is < conv::kNNDSamples; is++) {
      //~ for (int im = 0 ; im < conv::kNReacModes ; im++) {
        //~ for (int ip = 0 ; ip < conv::kNNDFitParams ; ip++) {
          //~ int i = SPLINE_INDEX(ib,is,im,ip,iz,ibin,ibin,ibin);
          //~ fSplines[i] = new TSpline3(*((TSpline3*)fFlatSpline));
          //~ fSplines[i]->SetTitle(Form("%d",i));
        //~ }
      //~ }
    //~ }
  //~ }
}
//________________________________________________________________________________________
//~ valor::util::DuneRFL::DuneRFL(const DuneRFL &) 
//~ {
//~ }
//________________________________________________________________________________________
valor::util::DuneRFL::~DuneRFL()
{
  for (int ispl = 0 ; ispl < fSplineBlockSize; ispl++) {
    if (fSplines[ispl]) {delete fSplines[ispl];}
    delete[] fSplines;
  }
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
  TSpline * spl = (TSpline*)-2;
  
  static const util::ArrIdx * arr_idx = util::ArrIdx::Instance();
  
  return spl;
}
//________________________________________________________________________________________
TString valor::util::DuneRFL::BuildSplineName (
  conv::BeamConf_t b, conv::Sample_t s,
  conv::ReacMode_t m, conv::PhysParamId_t p,
  const KinematicBin & kb) const
{
  TString name = fSplineNamePattern;
  
  //~ name = name.ReplaceAll("[TAG]" ,tag);
  name = name.ReplaceAll("[BEAM]"   , util::AsString(b).c_str());
  name = name.ReplaceAll("[SAMPLE]" , util::AsString(s).c_str());
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
  
  //~ for(int ibeam = 0; ibeam < conv::kNBeamConf; ibeam++) {
    //~ conv::BeamConf_t b = conv::kNDBeamConf[ibeam];
    //~ if(b == conv::kbUndefined) continue;
    //~ for(int isample = 0; isample < conv::kNNDSamples; isample++) {
      //~ conv::NDSample_t s = conv::kNDSample[ibeam][isample];
      //~ if(s == conv::ksNDUndefined) continue;
      //~ for(int imode = 0; imode < conv::kNReacModes; imode++) {
        //~ conv::ReacMode_t m = conv::kNDReactionModes[isample][imode];
        //~ if(m == conv::kmUndefined) continue;
        //~ for (int ip = 0 ; ip < conv::kNNDFitParams ; ip++) {
          //~ conv::PhysParamId_t p = conv::kNDFitParam[ip];
          //~ if(p == conv::kPhypUndefined) continue;
          //~ 
          //~ for (int izone = 0 ; izone < conv::kNMaxBinZones ; izone++ ) {
            //~ const int n_true1_bins = util::NumEtrueBins(s);
            //~ const int n_reco1_bins = util::NumErecoBins(s,izone);
            //~ const int n_reco2_bins = util::NumYrecoBins(s,izone);
            //~ for (int itrue1 = 0 ; itrue1 < n_true1_bins ; itrue1++) {
              //~ for (int ireco1 = 0 ; ireco1 < n_reco1_bins ; ireco1++) {
                //~ for (int ireco2 = 0 ; ireco2 < n_reco2_bins ; ireco2++) {
                //~ 
                //~ TString spl_name = this->BuildSplineName(b,s,m,p,izone,itrue1,ireco1,ireco2);
                //~ 
                //~ const int spline_index = SPLINE_INDEX(ibeam,isample,imode,ip,izone,itrue1,ireco1,ireco2);
                //~ TObject * spline_obj = spline_file->Get(spl_name.Data());
                //~ TSpline * spline = dynamic_cast<TSpline*>(spline_obj);
                //~ if (spline) {fSplines[spline_index] = spline;}
                //~ else {fSplines[spline_index] = 0;}
                //~ } //ireco2
              //~ } //ireco1
            //~ } //itrue1
          //~ } //iz
        //~ } //ip
      //~ } //imode
    //~ } //isample
  //~ } //ibeam
  
  spline_file->Close();
  
  return true;
}
//________________________________________________________________________________________
