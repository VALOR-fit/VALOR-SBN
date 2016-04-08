//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

//fmwk
#include "Utilities/UtlStr.h"
#include "Messenger/Messenger.h"
//dune
#include "Conventions/KineSpace.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return "<Etrue>";                  break;
    case (kspEreco)            : return "<Ereco>";                  break;
    case (kspEvis )            : return "<Evis>";                   break;
    case (kspYreco)            : return "<yreco>";                  break;
    case (kspErecoYreco)       : return "<Ereco,yreco>";            break;
    default : 
     LOG("KineSpace",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTeX(KineSpace_t ks, bool root)
{
  string name = "";

  switch(ks) {
    case (kspEtrue)            : name = "<E_{true}>";                     break;
    case (kspEreco)            : name = "<E_{reco}>";                     break;
    case (kspEvis )            : name = "<E_{vis}>";                      break;
    case (kspYreco)            : name = "<y_{reco}>";                     break;
    case (kspErecoYreco)       : name = ">E_{reco},y_{reco}>";            break;
    default : 
     LOG("KineSpace",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }

  if(root) return name;

  // change # with \ -- later

  return name;
}
//________________________________________________________________________________________
bool util::IsPureReco(KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return false;
    case (kspEreco)            : return true;
    case (kspEvis )            : return true;
    case (kspYreco)            : return true;
    case (kspErecoYreco)       : return true;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return false;
}
//________________________________________________________________________________________
bool util::IsPureTrue(KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return true;
    case (kspEreco)            : return false;
    case (kspEvis )            : return false;
    case (kspYreco)            : return false;
    case (kspErecoYreco)       : return false;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return false;
}
//________________________________________________________________________________________
bool util::IsMixedRecoTrue(KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return false;
    case (kspEreco)            : return false;
    case (kspEvis )            : return false;
    case (kspYreco)            : return false;
    case (kspErecoYreco)       : return false;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return false;
}
//________________________________________________________________________________________
int util::NDim(KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return 1;
    case (kspEreco)            : return 1;
    case (kspEvis )            : return 1;
    case (kspYreco)            : return 1;
    case (kspErecoYreco)       : return 2;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return 0;
}
//________________________________________________________________________________________
int util::NDimReco(KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return 0;
    case (kspEreco)            : return 1;
    case (kspEvis )            : return 1;
    case (kspYreco)            : return 1;
    case (kspErecoYreco)       : return 2;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return 0;
}
//________________________________________________________________________________________
int util::NDimTrue(KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return 1;
    case (kspEreco)            : return 0;
    case (kspEvis )            : return 0;
    case (kspYreco)            : return 0;
    case (kspErecoYreco)       : return 0;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return 0;
}
//________________________________________________________________________________________
conv::KineSpace_t util::SubSpaceReco(conv::KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return kspUndefined;
    case (kspEreco)            : return kspEreco;
    case (kspEvis )            : return kspEvis;
    case (kspYreco)            : return kspYreco;
    case (kspErecoYreco)       : return kspErecoYreco;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return kspUndefined;
}
//________________________________________________________________________________________
conv::KineSpace_t util::SubSpaceTrue(conv::KineSpace_t ks)
{
  switch(ks) {
    case (kspEtrue)            : return kspEtrue;
    case (kspEreco)            : return kspUndefined;
    case (kspEvis )            : return kspUndefined;
    case (kspYreco)            : return kspUndefined;
    case (kspErecoYreco)       : return kspUndefined;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }
  return kspUndefined;
}
//________________________________________________________________________________________
vector<KineVar_t> util::KineVar(conv::KineSpace_t ks)
{
  vector<KineVar_t> vv;

  switch(ks) {
    case (kspEtrue) : 
      vv.push_back(kvEtrue);
      break;
    case (kspEreco) : 
      vv.push_back(kvEreco);
      break;
    case (kspEvis) : 
      vv.push_back(kvEvis);
      break;
    case (kspYreco) : 
      vv.push_back(kvYreco);
      break;
    case (kspErecoYreco) : 
      vv.push_back(kvEreco);
      vv.push_back(kvYreco);
      break;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }

  return vv;
}
//________________________________________________________________________________________
vector<KineVar_t> util::KineVarReco(conv::KineSpace_t ks)
{
  vector<KineVar_t> vv;

  switch(ks) {
    case (kspEtrue) : 
      break;
    case (kspEreco) : 
      vv.push_back(kvEreco);
      break;
    case (kspEvis) : 
      vv.push_back(kvEvis);
      break;
    case (kspYreco) : 
      vv.push_back(kvYreco);
      break;
    case (kspErecoYreco) : 
      vv.push_back(kvEreco);
      vv.push_back(kvYreco);
      break;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }

  return vv;
}
//________________________________________________________________________________________
vector<KineVar_t> util::KineVarTrue(conv::KineSpace_t ks)
{
  vector<KineVar_t> vv;

  switch(ks) {
    case (kspEtrue) : 
      vv.push_back(kvEtrue);
      break;
    case (kspEreco) : 
      break;
    case (kspEvis) : 
      break;
    case (kspYreco) : 
      break;
    case (kspErecoYreco) : 
      break;
    default:
     LOG("KineVar",pERROR) 
        << "Unrecognized kinematic space: " << ks;
  }

  return vv;
}
//________________________________________________________________________________________
conv::KineSpace_t util::KineSpaceFromInt(int i_sp)
{
// Cast an integer to KineSpace_t, but with boundary check
//                [first]                   [last]
  if(i_sp >= (int)kspEtrue && i_sp <= (int) kspErecoYreco) return (KineSpace_t)i_sp;
  return kspUndefined;
}
//________________________________________________________________________________________
conv::KineSpace_t util::KineSPaceFromString(string str_sp)
{
  string lc_str_sp = util::ToLowerCase(str_sp);
  for (int i = 0 ; i < conv::kMaxKineSpaces; i++) {
    KineSpace_t sp = (KineSpace_t)i;
    string this_lc_str_sp = util::ToLowerCase(util::AsString(sp));
    if(lc_str_sp==this_lc_str_sp && this_lc_str_sp!="") {
      return sp;
    }
  }

  return kspUndefined;
}
//________________________________________________________________________________________
	
