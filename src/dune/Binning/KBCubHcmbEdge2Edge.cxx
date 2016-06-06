//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include <TSystem.h>
#include <TMath.h>

#include "valor/Utilities/UtlXML.h"
#include "valor/Messenger/Messenger.h"
#include "valor/VArray/VALORArray.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Env.h"
#include "dune/Binning/KBCubHcmbEdge2Edge.h"

using namespace valor;

//________________________________________________________________________________________
KBCubHcmbEdge2Edge::KBCubHcmbEdge2Edge() :
TNamed()
{
  fKineSpace   = conv::kspUndefined;
  fNDimensions = 0; 
  fKineVars.clear();
  fBinEdges.clear();
}
//________________________________________________________________________________________
KBCubHcmbEdge2Edge::KBCubHcmbEdge2Edge(
  string name, string title, conv::KineSpace_t ksp) :
TNamed(name.c_str(), title.c_str())
{
  fKineSpace   = ksp;
  fNDimensions = util::NDim(ksp); 
  fKineVars    = util::KineVar(ksp); 
  for(unsigned int i = 0; i < fNDimensions; i++) {
    conv::KineVar_t kv = fKineVars[i];
    fKineVar2Dim[kv] = i;
  }
}
//________________________________________________________________________________________
KBCubHcmbEdge2Edge::~KBCubHcmbEdge2Edge() 
{

}
//________________________________________________________________________________________
bool KBCubHcmbEdge2Edge::Read(string file)
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
    LOG("Binning", pERROR) 
      << "Input binning scheme [" << type << "] not `edge-to-edge'";
    return false;
  }

  unsigned int ndim = (unsigned int) 
      util::XML2Int(xml,root_node,"binning/ndimensions");
  if(fNDimensions != ndim) {
    LOG("Binning", pERROR) 
       << "Input binning scheme for " << ndim 
       << " dimensions not suitable for the specified " << fNDimensions
       << "-dimensional space: " << util::AsString(fKineSpace);
    return false;
  }

  fBinEdges.reserve(ndim);

  for(unsigned int idim = 0; idim < ndim; idim++) {
    string bin_size = util::XML2String(
       xml,root_node,Form("binning/dimension_%d/bin_size",idim));
    unsigned int nbins = (unsigned int) 
        util::XML2Int(xml,root_node,Form("binning/dimension_%d/nbins",idim));
    //
    //
    if(bin_size == "fixed") {
      vector<double> range = util::XML2DblArray(
         xml,root_node,Form("binning/dimension_%d/range",idim));
      if(range.size() != 2) {
         LOG("Binning", pERROR) 
           << "No range `min,max' was specified for dimension: " << idim;
         return false;
      }
      VALORArray * arr = new VALORArray(nbins+1);
      double dx = (range[1] - range[0]) / nbins;
      double x = range[0];
      for(unsigned int i = 0; i < nbins+1; i++) {
         arr->SetEntry(x,i);
         x += dx;
      }
      fBinEdges[idim] = arr;
    } 
    //
    //
    if(bin_size == "variable") {
      vector<double> bin_edges = util::XML2DblArray(
         xml,root_node,Form("binning/dimension_%d/bin_edges",idim));
      if(bin_edges.size() != nbins+1) {
         LOG("Binning", pERROR) 
           << bin_edges.size() << " bin edges were specified for the " 
           << nbins << " bins in dimension " << idim;
         return false;
      }
      VALORArray * arr = new VALORArray(nbins+1);
      for(unsigned int i = 0; i < nbins+1; i++) {
         arr->SetEntry(bin_edges[i],i);
      }
      fBinEdges[idim] = arr;
    } 
    else {
      LOG("Binning", pERROR) 
         << "Bin size is neither `fixed' nor `variable'";
      return false;
    }

  }//idim


  return true;
}
//________________________________________________________________________________________
unsigned int KBCubHcmbEdge2Edge::NBins(unsigned int dimension) const
{
  return (fBinEdges[dimension]->GetSize() - 1);
}
//________________________________________________________________________________________
unsigned int KBCubHcmbEdge2Edge::NBins(conv::KineVar_t kv) const
{
  unsigned int dimension = this->Dimension(kv);
  return this->NBins(dimension);
}
//________________________________________________________________________________________
const double * KBCubHcmbEdge2Edge::BinEdgeArr(unsigned int dimension) const
{
  return fBinEdges[dimension]->GetArray();
}
//________________________________________________________________________________________
const double * KBCubHcmbEdge2Edge::BinEdgeArr(conv::KineVar_t kv) const
{
  unsigned int dimension = this->Dimension(kv);
  return this->BinEdgeArr(dimension);
}
//________________________________________________________________________________________
const VALORArray * KBCubHcmbEdge2Edge::BinEdgeVArr(unsigned int dimension) const
{
  return fBinEdges[dimension];
}
//________________________________________________________________________________________
const VALORArray * KBCubHcmbEdge2Edge::BinEdgeVArr(conv::KineVar_t kv) const
{
  unsigned int dimension = this->Dimension(kv);
  return this->BinEdgeVArr(dimension);
}
//________________________________________________________________________________________
unsigned int KBCubHcmbEdge2Edge::FindBin(double x, unsigned int dimension)
{
  unsigned int n = 1 + this->NBins(dimension);
  const double * arr = this->BinEdgeArr(dimension);
  return TMath::BinarySearch(n,arr,x);
}
//________________________________________________________________________________________
unsigned int KBCubHcmbEdge2Edge::FindBin(double x, conv::KineVar_t kv)
{
  unsigned int dimension = this->Dimension(kv);
  return this->FindBin(x,dimension);
}
//________________________________________________________________________________________
vector<unsigned int> KBCubHcmbEdge2Edge::FindBin(vector<double> & xarr)
{
  assert(xarr.size() == fNDimensions);
  vector<unsigned int> binarr;
  binarr.reserve(fNDimensions);
  for(unsigned int i = 0; i < fNDimensions; i++) {
    double x = xarr[i];
    binarr[i] = this->FindBin(x,i);
  }
  return binarr;
}
//________________________________________________________________________________________
unsigned int KBCubHcmbEdge2Edge::Dimension(conv::KineVar_t kv) const
{
  map<conv::KineVar_t,unsigned int>::const_iterator it = fKineVar2Dim.find(kv);
  assert(it != fKineVar2Dim.end());
  int dimension = it->second;
  return dimension;
}
//________________________________________________________________________________________

