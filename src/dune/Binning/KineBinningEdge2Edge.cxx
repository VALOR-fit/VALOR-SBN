//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include <TSystem.h>

#include "valor/Utilities/UtlXML.h"
#include "valor/Messenger/Messenger.h"
#include "valor/VArray/VALORArray.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Env.h"
#include "dune/Binning/KineBinningEdge2Edge.h"

using namespace valor;

//________________________________________________________________________________________
KineBinningEdge2Edge::KineBinningEdge2Edge() :
TNamed()
{
  fKineSpace   = conv::kspUndefined;
  fNDimensions = 0; 
  fKineVars.clear();
}
//________________________________________________________________________________________
KineBinningEdge2Edge::KineBinningEdge2Edge(
  string name, string title, conv::KineSpace_t ksp) :
TNamed(name.c_str(), title.c_str())
{
  fKineSpace   = ksp;
  fNDimensions = util::NDim(ksp); 
  fKineVars    = util::KineVar(ksp); 

}
//________________________________________________________________________________________
KineBinningEdge2Edge::~KineBinningEdge2Edge() 
{

}
//________________________________________________________________________________________
bool KineBinningEdge2Edge::Read(string file)
{
  TString ts_file = file.c_str();
  gSystem->ExpandPathName(ts_file);

  // See if it works as a normal path
  FileStat_t dummy;
  if (gSystem->GetPathInfo(ts_file.Data(), dummy)) 
  {
    // If not, try the config folder
    ts_file = TString::Format("%s/%s",
       Env::Instance()->TopLevelConfDir().c_str(),ts_file.Data());
    if (gSystem->GetPathInfo(ts_file.Data(), dummy)) {
      LOG("Binning", pERROR) << "Binning file not found: " << file;
      util::Die(1); return false;
    }
  }

  // Parse the input binning configuration XML file
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(ts_file.Data());
  if (xmldoc==0) {
    LOG("Binning",pERROR) 
        << "Can not parse input XML file [" << ts_file << "]";
    delete xml;
    util::Die(1); return false;
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);

  string type = util::XML2String(xml,root_node,"binning/type");
  if(type != "edge-to-edge") {
    // complain
    return false;
  }

  int ndim = util::XML2Int(xml,root_node,"binning/ndimensions");
  if(fNDimensions != ndim) {
    // complain
    return false;
  }

  for(int idim = 0; idim < ndim; idim++) {
    string bin_size = util::XML2String(
       xml,root_node,Form("binning/dimension_%d/bin_size",idim));
    int nbins = util::XML2Int(
       xml,root_node,Form("binning/dimension_%d/nbins",idim));
    if(bin_size == "fixed") {
      vector<double> range = util::XML2DblArray(
         xml,root_node,Form("binning/dimension_%d/range",idim));
    } 
    if(bin_size == "variable") {
      vector<double> bin_edges = util::XML2DblArray(
         xml,root_node,Form("binning/dimension_%d/bin_edges",idim));
    } 
    else {
      // complain
      return false;
    }

  }//idim


  return true;
}
//________________________________________________________________________________________
int KineBinningEdge2Edge::NBins(int dimension) const
{
  return 0;
}
//________________________________________________________________________________________
int KineBinningEdge2Edge::NBins(conv::KineVar_t kv) const
{
  return 0;
}
//________________________________________________________________________________________
const double * KineBinningEdge2Edge::BinEdgeArr(int dimension) const
{
  return 0;
}
//________________________________________________________________________________________
const double * KineBinningEdge2Edge::BinEdgeArr(conv::KineVar_t kv) const
{
  return 0;
}
//________________________________________________________________________________________
const VALORArray * KineBinningEdge2Edge::BinEdgeVArr(int dimension) const
{
  return 0;
}
//________________________________________________________________________________________
const VALORArray * KineBinningEdge2Edge::BinEdgeVArr(conv::KineVar_t kv) const
{
  return 0;
}
//________________________________________________________________________________________
int KineBinningEdge2Edge::FindBin(double x, int dimension)
{
  return 0;
}
//________________________________________________________________________________________
int KineBinningEdge2Edge::FindBin(double x, conv::KineVar_t kv)
{
  return -1;
}
//________________________________________________________________________________________
vector<int> KineBinningEdge2Edge::FindBin(vector<double> & xarr)
{
  vector<int> binarr;

  return binarr;
}
//________________________________________________________________________________________

