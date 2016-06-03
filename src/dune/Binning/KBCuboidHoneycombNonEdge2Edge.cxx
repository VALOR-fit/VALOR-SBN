//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "valor/Messenger/Messenger.h"
#include "valor/VArray/VALORArray.h"
#include "dune/Binning/KBCuboidHoneycombEdge2Edge.h"
#include "dune/Binning/KBCuboidHoneycombNonEdge2Edge.h"

using namespace valor;

//________________________________________________________________________________________
KBCuboidHoneycombNonEdge2Edge::KBCuboidHoneycombNonEdge2Edge() :
TNamed()
{

}
//________________________________________________________________________________________
KBCuboidHoneycombNonEdge2Edge::KBCuboidHoneycombNonEdge2Edge(
  string name, string title, conv::KineSpace_t ksp) :
TNamed(name.c_str(), title.c_str())
{

}
//________________________________________________________________________________________
KBCuboidHoneycombNonEdge2Edge::~KBCuboidHoneycombNonEdge2Edge() 
{

}
//________________________________________________________________________________________
bool KBCuboidHoneycombNonEdge2Edge::Read(string file)
{
  return false;
}
//________________________________________________________________________________________
int KBCuboidHoneycombNonEdge2Edge::NBins(void) const
{
  return 0;
}
//________________________________________________________________________________________
int KBCuboidHoneycombNonEdge2Edge::FindBin(vector<double> & xarr)
{
  return -1;
}
//________________________________________________________________________________________
void KBCuboidHoneycombNonEdge2Edge::AlternativeEdge2EdgeBinning(
  const KBCuboidHoneycombEdge2Edge * kbe2e)
{
  fKBE2E = kbe2e;
}
//________________________________________________________________________________________
int KBCuboidHoneycombNonEdge2Edge::BinMapping(vector<int> & bin_in_alt_simple_scheme)
{
  return -1;
}
//________________________________________________________________________________________

