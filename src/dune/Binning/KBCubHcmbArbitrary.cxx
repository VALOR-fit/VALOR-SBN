//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "valor/Messenger/Messenger.h"
#include "valor/VArray/VALORArray.h"
#include "dune/Binning/KBCubHcmbEdge2Edge.h"
#include "dune/Binning/KBCubHcmbArbitrary.h"

using namespace valor;

//________________________________________________________________________________________
KBCubHcmbArbitrary::KBCubHcmbArbitrary() :
TNamed()
{

}
//________________________________________________________________________________________
KBCubHcmbArbitrary::KBCubHcmbArbitrary(
  string name, string title, conv::KineSpace_t ksp) :
TNamed(name.c_str(), title.c_str())
{

}
//________________________________________________________________________________________
KBCubHcmbArbitrary::~KBCubHcmbArbitrary() 
{

}
//________________________________________________________________________________________
bool KBCubHcmbArbitrary::Read(string file)
{
  return false;
}
//________________________________________________________________________________________
int KBCubHcmbArbitrary::NBins(void) const
{
  return 0;
}
//________________________________________________________________________________________
int KBCubHcmbArbitrary::FindBin(vector<double> & xarr)
{
  return -1;
}
//________________________________________________________________________________________
void KBCubHcmbArbitrary::UseEdge2EdgeBinning(
  const KBCubHcmbEdge2Edge * kbe2e)
{
  fKBE2E = kbe2e;
}
//________________________________________________________________________________________
int KBCubHcmbArbitrary::BinMapping(vector<int> & bin_in_alt_simple_scheme)
{
  return -1;
}
//________________________________________________________________________________________

