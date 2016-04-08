//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

ChangeLog:

*/
//________________________________________________________________________________________

//fmwk
#include "Utilities/UtlStr.h"
#include "Messenger/Messenger.h"
//dune
#include "Conventions/KineVar.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(KineVar_t kv)
{
  switch(kv) {
    case (kvEtrue) : return "Etrue"; break;
    case (kvEreco) : return "Ereco"; break;
    case (kvEvis ) : return "Evis";  break;
    case (kvYreco) : return "yreco"; break;
    default : 
     LOG("KineVar",pERROR) << "Unrecognized kinematic variable: " << kv;
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTeX(KineVar_t kv, bool root)
{
  string name = "";

  switch(kv) {
    case (kvEtrue) : return "E_{true} (GeV)"; break;
    case (kvEreco) : return "E_{reco} (GeV)"; break;
    case (kvEvis ) : return "E_{vis} (GeV)";  break;
    case (kvYreco) : return "y_{reco}";       break;
    default : 
     LOG("KineVar",pERROR) << "Unrecognized kinematic variable: " << kv;
  }

  if(root) return name;

  // change # with \ -- later

  return name;
}
//________________________________________________________________________________________
bool util::IsReco(KineVar_t kv)
{
  switch(kv) {
    case (kvEtrue) : return false;
    case (kvEreco) : return true;
    case (kvEvis ) : return true;
    case (kvYreco) : return true;
    default:
     LOG("KineVar",pERROR) << "Unrecognized kinematic variable: " << kv;
  }
  return false;
}
//________________________________________________________________________________________
bool util::IsTrue(KineVar_t kv)
{
  bool is_reco = util::IsReco(kv);
  return (!is_reco);
}
//________________________________________________________________________________________
	
