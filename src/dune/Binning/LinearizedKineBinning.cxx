//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "valor/Messenger/Messenger.h"
#include "valor/VArray/VALORArray.h"
#include "dune/Binning/LinearizedKineBinning.h"

using namespace valor;

//________________________________________________________________________________________
LinearizedKineBinning::LinearizedKineBinning() :
TNamed()
{

}
//________________________________________________________________________________________
LinearizedKineBinning::LinearizedKineBinning(
  string name, string title, conv::KineSpace_t ksp) :
TNamed(name.c_str(), title.c_str())
{

}
//________________________________________________________________________________________
LinearizedKineBinning::~LinearizedKineBinning() 
{

}
//________________________________________________________________________________________
bool LinearizedKineBinning::Read(string file)
{
  return false;
}
//________________________________________________________________________________________
int LinearizedKineBinning::NBins(void) const
{
  return 0;
}
//________________________________________________________________________________________
int LinearizedKineBinning::FindBin(vector<double> & xarr)
{
  return -1;
}
//________________________________________________________________________________________
void LinearizedKineBinning::UsingAlternativeSimpleBinningScheme(
  const KineBinningEdge2Edge * alt_simple_scheme)
{
  fAltSimpleKineBinning = alt_simple_scheme;
}
//________________________________________________________________________________________
int LinearizedKineBinning::BinMapping(vector<int> & bin_in_alt_simple_scheme)
{
  return -1;
}
//________________________________________________________________________________________

