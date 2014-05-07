//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <ostream>

#include <TFile.h>
#include <TObjArray.h>
#include <TH1D.h>

//fmwk
#include "Conventions/PhysHypothesisId.h"
#include "Conventions/PhysParamId.h"
#include "Conventions/NuOscMixParam.h"
#include "Conventions/NuOscDmsqScheme.h"
#include "Conventions/Opt.h"
#include "Conventions/PDG.h"
#include "Utilities/UtlStyle.h"
#include "Utilities/UtlXML.h"
#include "Messenger/Messenger.h"
//lbnx
#include "Conventions/ReacMode.h"
#include "NDFit/NDModel.h"
#include "NDFit/NDSample.h"
#include "NDFit/NDSystDef.h"

using std::endl;

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
NDModel::NDModel() :
FitModelABC()
{
  //...
}
//________________________________________________________________________________________
NDModel::~NDModel() 
{
  //...
}
//________________________________________________________________________________________
string NDModel::Name(void)
{
  return "LBNxND";
}
//________________________________________________________________________________________
bool NDModel::Read(string file, Option_t * /*opt*/)
{
  // Parse the input XML configuration file
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(file.c_str());
  if (xmldoc==0) {
    LOG("NDModel",pERROR) << "Can not parse input: " << file;
    delete xml;
    return false;  
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);

  //
  fMCTree = util::XML2TTree (xml,root_node,"nd/mc/dstfile");
  assert(fMCTree);

  fPOTFHC = util::XML2Dbl(xml,root_node,"nd/data/pot/fhc");
  fPOTRHC = util::XML2Dbl(xml,root_node,"nd/data/pot/rhc");

  // Release memory
  xml->FreeDoc(xmldoc);
  delete xml;

  LOG("NDModel",pNOTICE) << "Done configuring LBNx/ND model... \n\n";

  return true;
}
//________________________________________________________________________________________
bool NDModel::Generate(const PhysHypothesis & ph)
{
  fPhysHypothesis.Copy(ph);
  PhysHypothesis_t hyp = fPhysHypothesis.Hypothesis();

  LOG("NDModel",pINFO)  
     << "Generating model predictions for the input hypothesis: " 
     << fPhysHypothesis;



  //
  //
  // ...
  //
  //



  LOG("NDModel",pDEBUG) << "Done generating predictions";

  return true;
}
//________________________________________________________________________________________
void NDModel::RandomizeSystematics(void)
{
  //...
}
//________________________________________________________________________________________
void NDModel::TweakSystematic(
  string /*syst_name*/, double /*twkdial*/, Option_t * /*opt*/)
{
  //...
}
//________________________________________________________________________________________
void NDModel::TweakSystematic(
  PhysParamId_t /*syst*/, double /*twkdial*/, Option_t * /*opt*/)
{
  //...
}
//________________________________________________________________________________________
PhysParamList NDModel::Tweaks(void)
{
  PhysParamList list;
  //...
  return list;
}
//________________________________________________________________________________________
void NDModel::ResetSystematics(void)
{
  //...
}
//________________________________________________________________________________________
void NDModel::PrintSystematics(ostream & stream) const
{
  stream << endl;
}
//________________________________________________________________________________________
bool NDModel::Generate (const FitParamList & fp)
{
  // extract the values of params driving the oscillation, decoherence or decay model
  PhysHypothesis ph(fp);

  // call the main Generate() method
  return this->Generate(ph);
}
//________________________________________________________________________________________
bool NDModel::Write(TObjArray * array, const char * tag, Option_t * /*write_opt*/)
{
  if(!array) return false;

  valor::util::SetDefaultStyle();

  //...

  return true;
}
//________________________________________________________________________________________
bool NDModel::Write(
  const char * filename, const char * tag, Option_t * write_opt, Option_t * file_opt)
{
  TObjArray * array = new TObjArray();
  this->Write(array,tag,write_opt);

  Option_t * used_file_opt = (file_opt == 0) ? "recreate" : file_opt;
  TFile f(filename, used_file_opt);
  array->Write();
  f.Close();

  return true;
}
//________________________________________________________________________________________
void NDModel::Init(void)
{
  for(int isample = 0; isample < kNNDSamples; isample++) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         fNullMCTempl[isample][imode][izone] = true;
         fMCTemplNom [isample][imode][izone] = 0;
         fMCTemplTun [isample][imode][izone] = 0;
         fMCTemplSys [isample][imode][izone] = 0;
         fMCTemplFin [isample][imode][izone] = 0;
      }//izone
    }//imode
  }//isample

  fMCTree = 0;

  fPOTFHC = 0;
  fPOTRHC = 0;
}
//________________________________________________________________________________________
void NDModel::Book(void)
{
  for(int isample = 0; isample < kNNDSamples; isample++) {
    NDSample_t s = kNDSample[isample];
    if(s == ksNDUndefined) continue;
    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kNDReactionModes[isample][imode];
      if(m == kmUndefined) continue;
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         const int n_etrue_bins = util::NumEtrueBins(s,izone);
         const int n_ereco_bins = util::NumErecoBins(s,izone);
         const int n_yreco_bins = util::NumYrecoBins(s,izone);
         if(n_ereco_bins <= 0 || n_yreco_bins <= 0) continue;
         fNullMCTempl[isample][imode][izone] = false;
         fMCTemplNom [isample][imode][izone] = 
            new VALORArray(n_etrue_bins,n_ereco_bins,n_yreco_bins);
         fMCTemplTun [isample][imode][izone] = 
            new VALORArray(n_etrue_bins,n_ereco_bins,n_yreco_bins);
         fMCTemplSys [isample][imode][izone] = 
            new VALORArray(n_etrue_bins,n_ereco_bins,n_yreco_bins);
         fMCTemplFin [isample][imode][izone] = 
            new VALORArray(n_etrue_bins,n_ereco_bins,n_yreco_bins);
      }//izone
    }//imode
  }//isample
}
//________________________________________________________________________________________
void NDModel::Clean(void)
{
  for(int isample = 0; isample < kNNDSamples; isample++) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        fNullMCTempl[isample][imode][izone] = true;
        if(fMCTemplNom[isample][imode][izone]) delete fMCTemplNom[isample][imode][izone];
        fMCTemplNom[isample][imode][izone] = 0;
        if(fMCTemplTun[isample][imode][izone]) delete fMCTemplTun[isample][imode][izone];
        fMCTemplTun[isample][imode][izone] = 0;
        if(fMCTemplSys[isample][imode][izone]) delete fMCTemplSys[isample][imode][izone];
        fMCTemplSys[isample][imode][izone] = 0;
        if(fMCTemplFin[isample][imode][izone]) delete fMCTemplFin[isample][imode][izone];
        fMCTemplFin[isample][imode][izone] = 0;
      }//izone
    }//imode
  }//isample

  //if (fMCTree) delete fMCTree;
}
//________________________________________________________________________________________
void NDModel::ZeroTemplates(void)
{
  for(int isample = 0; isample < kNNDSamples; isample++) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         bool is_null = fNullMCTempl[isample][imode][izone];
         if(!is_null) {
             fMCTemplNom[isample][imode][izone]->SetAll(0.);
             fMCTemplTun[isample][imode][izone]->SetAll(0.);
             fMCTemplSys[isample][imode][izone]->SetAll(0.);
             fMCTemplFin[isample][imode][izone]->SetAll(0.);
         }
      }//izone
    }//imode
  }//isample

}
//________________________________________________________________________________________
void NDModel::FillTemplates(TTree * t)
{
  if(!t) return;

  this->ZeroTemplates();

  TBranch * bSample   = t->GetBranch("sample");         // selected ND sample
  TBranch * bReacMode = t->GetBranch("reac_mode");      // reaction mode
  TBranch * bEnuTrue  = t->GetBranch("enu_true");       // true energy (GeV)
  TBranch * bEnuReco  = t->GetBranch("enu_reco");       // reco energy (GeV)
  TBranch * byReco    = t->GetBranch("y_reco");         // reco inelasticity y
  TBranch * bWghtPOT  = t->GetBranch("wgt_to1e20pot");  // weight for 1E+20 POT exposure

  int    sample    = 0;
  int    reac_mode = 0;
  double enu_true  = 0;
  double enu_reco  = 0;
  double y_reco    = 0;
  double wght_pot  = 0;

  bSample   -> SetAddress(&sample    );
  bReacMode -> SetAddress(&reac_mode );
  bEnuTrue  -> SetAddress(&enu_true  );
  bEnuReco  -> SetAddress(&enu_reco  );
  byReco    -> SetAddress(&y_reco    );
  bWghtPOT  -> SetAddress(&wght_pot  );

  t->SetBranchStatus("*",0);
  t->SetBranchStatus("sample",        1); 
  t->SetBranchStatus("reac_mode",     1);    
  t->SetBranchStatus("enu_true",      1);  
  t->SetBranchStatus("enu_reco",      1);  
  t->SetBranchStatus("y_reco",        1);    
  t->SetBranchStatus("wgt_to1e20pot", 1);

  for(int iev = 0; iev < t->GetEntries(); iev++) 
  {
     t->GetEntry(iev);

     int isample   = 0;
     int imode     = 1;
     int izone     = 2;

     bool is_null = fNullMCTempl[isample][imode][izone];
     if(is_null) continue;

     int ienu_true = 3;
     int ienu_reco = 4;
     int iy_reco   = 5;

     double data_pot = fPOTFHC;
     double mc_pot   = wght_pot * 1E+20;

     double wght = data_pot/mc_pot;

     fMCTemplNom[isample][imode][izone]->SetEntry(wght, ienu_true, ienu_reco, iy_reco);
     fMCTemplTun[isample][imode][izone]->SetEntry(wght, ienu_true, ienu_reco, iy_reco);
     fMCTemplSys[isample][imode][izone]->SetEntry(wght, ienu_true, ienu_reco, iy_reco);
     fMCTemplFin[isample][imode][izone]->SetEntry(wght, ienu_true, ienu_reco, iy_reco);

  }//iev 

}
//________________________________________________________________________________________

