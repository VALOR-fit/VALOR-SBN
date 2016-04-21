//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "TString.h"

// fmwk
#include "Messenger/Messenger.h"
#include "Utilities/UtlSystem.h"
#include "Utilities/UtlXML.h"

// dune
#include "dune/Conventions/DuneBuild.h"
#include "dune/Conventions/ArrIdx.h"
#include "dune/SDFit/NDRFL.h"

#define USE_FLAT_SPLINE_FOR_MISSING

using std::endl;

using namespace valor;

//________________________________________________________________________________________
inline int SPLINE_INDEX(const int& ib, const int& is, const int& im, const int& ip, const int& ibin)
{
  return ib * conv::kNSamples*conv::kNReacModes*conv::kNFitParams*conv::kNMaxBinZones +
         is * conv::kNReacModes*conv::kNFitParams*conv::kNMaxBinZones +
         im * conv::kNFitParams*conv::kNMaxBinZones +
         ip * conv::kNMaxBinZones +
         ibin;
}
//________________________________________________________________________________________
// A key object used to index a function call to its spline.
namespace valor{
 class SplineKey: public TObject {
 
  private:
    conv::BeamConf_t    fBeam;
    conv::Sample_t    fSample;
    conv::ReacMode_t    fMode;
    conv::PhysParamId_t fParam;
    Double_t            fTruevar1;
    Double_t            fObsvar1;
    Double_t            fObsvar2;
    TSpline *           fSpline;
    
  public:
    SplineKey(conv::BeamConf_t b = conv::kbLBNF_FHC,
              conv::Sample_t s = conv::ksUndefined,
              conv::ReacMode_t m = conv::kmUndefined,
              conv::PhysParamId_t p = conv::kPhypUndefined,
              Double_t true1=-1, Double_t obs1=-1, Double_t obs2=-1) :
        fBeam(b), fSample(s), fMode(m), fParam(p),
        fTruevar1(true1), fObsvar1(obs1), fObsvar2(obs2),
        fSpline(0)
    {
      assert(sizeof(ULong_t)==sizeof(Double_t)); // We assume these two are the same length in hash computation
    }
    
    // Sets the hashed quantities
    void Update(conv::BeamConf_t b, conv::Sample_t s,
                conv::ReacMode_t m, conv::PhysParamId_t p,
                Double_t true1, Double_t obs1, Double_t obs2)
    {
      fBeam     = b;
      fSample   = s;
      fMode     = m;
      fParam    = p;
      fTruevar1 = true1;
      fObsvar1  = obs1;
      fObsvar2  = obs2;
    }
    
    // Sets the pointer to the spline
    void SetSpline(TSpline * spl)
    {
      fSpline = spl;
    }
    
    TSpline * GetSpline(void) const
    {
      return fSpline;
    }
    
    // Hashing function, based off https://en.wikipedia.org/wiki/Fowler-Noll-Vo_hash_function
    // Hashes the members of the class but NOT the spline address
    ULong_t Hash() const
    {
      static const ULong_t seed = 0xcbf29ce484222325; //FNV offset
      ULong_t myhash = seed;
      // FNV-1 hash https://en.wikipedia.org/wiki/Fowler-Noll-Vo_hash_function
      static const ULong_t prime = 0x100000001b3;
      // First do Enums, 4 bytes at a time, converting properly to 8-byte uints
      myhash *= prime;
      myhash ^= (ULong_t)fBeam;
      myhash *= prime;
      myhash ^= (ULong_t)fSample;
      myhash *= prime;
      myhash ^= (ULong_t)fMode;
      myhash *= prime;
      myhash ^= (ULong_t)fParam;
      // Then do doubles, 8 bytes at time, stuffing into 8-byte uints without conversion
      myhash *= prime;
      myhash ^= *(ULong_t*)&(fTruevar1);
      myhash *= prime;
      myhash ^= *(ULong_t*)&(fObsvar1);
      myhash *= prime;
      myhash ^= *(ULong_t*)&(fObsvar2);
      return myhash;
    };
 };
}
//________________________________________________________________________________________
namespace valor {
  ostream & operator<<(ostream & stream, const NDRFL & rfl)
  {
    rfl.Print(stream);
    return stream;
  }
}
//________________________________________________________________________________________
NDRFL * NDRFL::fInstance = 0;
//________________________________________________________________________________________
NDRFL::NDRFL() 
{
  fInstance = 0;
  fSplineMapIsEnabled  = true;
  fSplineMapIsComplete = false;
  
  fTag = "spl";
  
  static Double_t flat_knots_x[5] = {-10, -5, 0, 5, 10};
  static Double_t flat_knots_y[5] = {  1,  1, 1, 1,  1};
  fFlatSpline = new TSpline3("flat_spline",flat_knots_x,flat_knots_y,5);
  
  fSplines = new TSpline*[conv::kNFitParams*conv::kNBeamConf*conv::kNSamples*conv::kNReacModes*conv::kNMaxBinZones];
  
  //DEBUG - fill with flat splines with titles
  int ibin = 0;
  for (int ib = 0 ; ib < conv::kNBeamConf ; ib++) {
    for (int is = 0 ; is < conv::kNSamples; is++) {
      for (int im = 0 ; im < conv::kNReacModes ; im++) {
        for (int ip = 0 ; ip < conv::kNFitParams ; ip++) {
          int i = SPLINE_INDEX(ib,is,im,ip,ibin);
          fSplines[i] = new TSpline3(*((TSpline3*)fFlatSpline));
          fSplines[i]->SetTitle(Form("%d",i));
        }
      }
    }
  }
  
  fSplineMap = new THashTable;
  fSplineMap->SetOwner(true); // We'll be sticking splinekeys in here and then otherwise throwing away the pointer
}
//________________________________________________________________________________________
NDRFL::NDRFL(const NDRFL &) 
{

}
//________________________________________________________________________________________
NDRFL::~NDRFL()
{
  delete   fFlatSpline;
  delete[] fSplines;
}
//________________________________________________________________________________________
NDRFL * NDRFL::Instance()
{
  if(fInstance == 0) {
    static NDRFL::Cleaner cleaner;
    cleaner.DummyMethodAndSilentCompiler();
    fInstance = new NDRFL;
  }
  return fInstance;
}
//________________________________________________________________________________________
void NDRFL::Print(ostream & stream) const
{
  stream << "[response functions]" << endl;

}
//________________________________________________________________________________________
TSpline * NDRFL::GetSpline(conv::BeamConf_t b, conv::Sample_t s, conv::ReacMode_t m,
                           conv::PhysParamId_t p, double true1, double obs1, double obs2) const
{
  TSpline * spl = (TSpline*)-2;
  static SplineKey key;
  static const util::ArrIdx * arr_idx = util::ArrIdx::Instance();
  
  // If we're using the map, check it for our call
  if (fSplineMapIsEnabled) {
    // Define the relevant parts of the key
    key.Update(b,s,m,p,true1,obs1,obs2);
    // Retrieve (possibly) a key with a spline attached
    TObject * spl_obj = fSplineMap->FindObject(&key);
    std::cerr<<"NDRFL/GetSpline > Retrieved "<<spl_obj<<endl;
    
    // If that worked, we're home free. Return our spline.
    if (spl_obj) {
      SplineKey * retrieved_key = (SplineKey*)(spl_obj);
      spl=retrieved_key->GetSpline();
    }
  }
  
  // If that didn't work, get the spline manually
  if (!spl) {
    int ib = arr_idx->BeamConfIdx(b)  ;
    int is = arr_idx->SampleIdx  (b,s);
    int im = arr_idx->ReacModeIdx(s,m);
    int ip = arr_idx->FitParamIdx(p)  ;
    int ibin = 0; //ZONED_BINNING_INPLEMENTATION_NEEDED
    
    int spl_idx = SPLINE_INDEX(ib,is,im,ip,ibin);
                  
    spl = fSplines[spl_idx];
    
    if (fSplineMapIsEnabled) {
      SplineKey * newkey = new SplineKey(b,s,m,p,true1,obs1,obs2);
      newkey->SetSpline(spl);
      fSplineMap->Add(newkey);
    } // We've added our spline to the map
  }
  
  return spl;
}
//________________________________________________________________________________________
void NDRFL::SetSplineMapIsComplete(bool is_complete)
{
  fSplineMapIsComplete = is_complete;
}
//________________________________________________________________________________________
void NDRFL::SetSplineMapIsEnabled(bool is_enabled)
{
  fSplineMapIsEnabled = is_enabled;
}
//________________________________________________________________________________________
TString NDRFL::BuildSplineName(conv::BeamConf_t b, conv::Sample_t s, conv::ReacMode_t m,
                        conv::PhysParamId_t p, int true_bin, int obs1_bin, int obs2_bin) const
{
  TString name;
  if (obs2_bin < 0) {
    name.Format("%s_%s_%s_%s_%s_%d_%d",
                           fTag.c_str(),
                           util::AsString(b).c_str(),
                           util::AsString(s).c_str(),
                           util::AsString(m).c_str(),
                           util::AsString(p).c_str(),
                           true_bin, obs1_bin);
  }
  else {
    name.Format("%s_%s_%s_%s_%s_%d_%d_%d",
                           fTag.c_str(),
                           util::AsString(b).c_str(),
                           util::AsString(s).c_str(),
                           util::AsString(m).c_str(),
                           util::AsString(p).c_str(),
                           true_bin, obs1_bin, obs2_bin);
  }
                         
  return name;
}
//________________________________________________________________________________________
bool valor::NDRFL::Read(std::string config_file,Option_t * /*option*/)
{
  // Parse the input XML configuration file
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(config_file.c_str());
  if (xmldoc==0) {
    LOG("NDRFL",pERROR) << "Can not parse input XML file [" << config_file << "]";
    delete xml;
    util::Die(1); return false;
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);
  
  fTag = util::XML2String(xml,root_node,"splines/tag");
  
  TFile * spline_file = util::XML2TFile(xml,root_node,"splines/file");
  
  for(int ibeam = 0; ibeam < conv::kNBeamConf; ibeam++) {
    conv::BeamConf_t b = conv::kBeamConf[ibeam];
    if(b == conv::kbUndefined) continue;
    for(int isample = 0; isample < conv::kNSamples; isample++) {
      conv::Sample_t s = conv::kSample[ibeam][isample];
      if(s == conv::ksUndefined) continue;
      for(int imode = 0; imode < conv::kNReacModes; imode++) {
        conv::ReacMode_t m = conv::kReactionModes[isample][imode];
        if(m == conv::kmUndefined) continue;
        for (int ip = 0 ; ip < conv::kNFitParams ; ip++) {
          conv::PhysParamId_t p = conv::kFitParam[ip];
          if(p == conv::kPhypUndefined) continue;
          
          const int n_true1_bins = 1;//DEBUG
          for (int itrue1 = 0 ; itrue1 < n_true1_bins ; itrue1++) {
            const int n_reco1_bins = 1;//DEBUG
            for (int ireco1 = 0 ; ireco1 < n_reco1_bins ; ireco1++) {
              const int n_reco2_bins = 1;//DEBUG
              for (int ireco2 = 0 ; ireco2 < n_reco2_bins ; ireco2++) {
                
                TString spl_name = this->BuildSplineName(b,s,m,p,itrue1,ireco1,ireco2);
                
                const int spline_index = SPLINE_INDEX(ibeam,isample,imode,ip,itrue1);
                TObject * spline_obj = spline_file->Get(spl_name.Data());
                TSpline * spline = dynamic_cast<TSpline*>(spline_obj);
                if (spline) {fSplines[spline_index] = spline;}
                else {fSplines[spline_index] = 0;}
              } //ireco2
            } //ireco1
          } //itrue1
        } //ip
      } //imode
    } //isample
  } //ibeam
  
  spline_file->Close();
  
  return true;
}
//________________________________________________________________________________________
