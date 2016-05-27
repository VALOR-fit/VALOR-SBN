//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "valor/Messenger/Messenger.h"
#include "valor/VArray/VALORArray.h"
#include "dune/Binning/SimpleKineBinning.h"

using namespace valor;

//________________________________________________________________________________________
SimpleKineBinning::SimpleKineBinning() :
TNamed()
{

}
//________________________________________________________________________________________
SimpleKineBinning::SimpleKineBinning(string name, string title) :
TNamed(name.c_str(), title.c_str())
{

}
//________________________________________________________________________________________
SimpleKineBinning::SimpleKineBinning(
  string name, string title, conv::KineSpace_t ksp, bool reco) :
TNamed(name.c_str(), title.c_str())
{

}
//________________________________________________________________________________________
SimpleKineBinning::~SimpleKineBinning() 
{

}
//________________________________________________________________________________________
bool SimpleKineBinning::Read(string file)
{
  return false;
}
//________________________________________________________________________________________
conv::KineSpace_t SimpleKineBinning::KineSpace(void) const
{
  return conv::kspUndefined;
}
//________________________________________________________________________________________
int SimpleKineBinning::NDimensions(void) const
{
  return 0;
}
//________________________________________________________________________________________
vector<conv::KineVar_t> SimpleKineBinning::KineVar(void) const
{
  vector<conv::KineVar_t> kvarr;

  return kvarr;
}
//________________________________________________________________________________________
int SimpleKineBinning::NBins(int dimension) const
{
  return 0;
}
//________________________________________________________________________________________
int SimpleKineBinning::NBins(conv::KineVar_t kv) const
{
  return 0;
}
//________________________________________________________________________________________
const double * SimpleKineBinning::BinEdgeArr(int dimension) const
{
  return 0;
}
//________________________________________________________________________________________
const double * SimpleKineBinning::BinEdgeArr(conv::KineVar_t kv) const
{
  return 0;
}
//________________________________________________________________________________________
const VALORArray * SimpleKineBinning::BinEdgeVArr(int dimension) const
{
  return 0;
}
//________________________________________________________________________________________
const VALORArray * SimpleKineBinning::BinEdgeVArr(conv::KineVar_t kv) const
{
  return 0;
}
//________________________________________________________________________________________
int SimpleKineBinning::FindBin(double x, int dimension)
{
  return 0;
}
//________________________________________________________________________________________
int SimpleKineBinning::FindBin(double x, conv::KineVar_t kv)
{
  return -1;
}
//________________________________________________________________________________________
vector<int> SimpleKineBinning::FindBin(vector<double> & xarr)
{
  vector<int> binarr;

  return binarr;
}
//________________________________________________________________________________________

