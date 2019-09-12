//________________________________________________________________________________________
/*

Copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

// dune
#include "dune/Conventions/SampleReacMode.h"

using std::vector;

using namespace valor;

//________________________________________________________________________________________
vector<conv::ReacMode_t> util::GetActiveModes (int isample)
{
  vector<conv::ReacMode_t> vec;
  for(int im = 0; im < conv::kNReacModes; ++im) {
    conv::ReacMode_t m = conv::kReactionModes[isample][im];
    if (m != conv::kmUndefined) { vec.push_back(m); }
  }
  return vec;
}
//________________________________________________________________________________________

