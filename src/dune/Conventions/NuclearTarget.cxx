//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <algorithm>

//fmwk
#include "valor/Utilities/UtlStr.h"
#include "valor/Messenger/Messenger.h"
//dune
#include "dune/Conventions/NuclearTarget.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(NuclearTarget_t nt)
{
  string name = "";
  switch(nt) {
    case (kntAll      ) : name = "All";       break;
    case (kntHydrogen ) : name = "Hydrogen";  break;
    case (kntCarbon   ) : name = "Carbon";    break;
    case (kntOxygen   ) : name = "Oxygen";    break;
    case (kntArgon    ) : name = "Argon";     break;
    case (kntCalcium  ) : name = "Calcium";   break;
    case (kntOther    ) : name = "Other";     break;      
    default : 
     LOG("NuclearTarget",pERROR) 
        << "Unrecognized nuclear target " << nt;
  }
  return name;
}
//________________________________________________________________________________________
string util::AsStringTeX(NuclearTarget_t nt, bool root)
{
  string name = "";
  switch(nt) { // Maybe change these to the isotope notation
    case (kntAll      ) : name = "All";       break;
    case (kntHydrogen ) : name = "Hydrogen";  break;
    case (kntCarbon   ) : name = "Carbon";    break;
    case (kntOxygen   ) : name = "Oxygen";    break;
    case (kntArgon    ) : name = "Argon";     break;
    case (kntCalcium  ) : name = "Calcium";   break;
    case (kntOther    ) : name = "Other";     break;      
    default : 
     LOG("NuclearTarget",pERROR) 
        << "Unrecognized nuclear target " << nt;
  }

  if(root) {
    replace( name.begin(), name.end(), '\\', '#' ); // Make slashes hashes for RooTeX
    // Get rid of hashes preceding sin
    size_t ind = name.find("#sin",0);
    if (ind !=  string::npos) (name.replace(ind,4," sin"));
    return util::TrimSpaces(name);
  }

  return name;
}
//________________________________________________________________________________________
