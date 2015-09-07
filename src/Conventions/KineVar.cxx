//________________________________________________________________________________________
/*

Copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

//fmwk
#include "Utilities/UtlStr.h"
//lbnx
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
    default        : return "--";
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
    default        : return "--";
  }

  if(root) return name;

  // change # with \ -- later

  return name;
}
//________________________________________________________________________________________
	
