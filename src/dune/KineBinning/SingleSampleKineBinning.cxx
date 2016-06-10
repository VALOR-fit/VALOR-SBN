//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <TSystem.h>

#include "valor/Utilities/UtlXML.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Env.h"
#include "valor/Messenger/Messenger.h"
#include "dune/KineBinning/SingleSampleKineBinning.h"
#include "dune/KineBinning/KBCubHcmbMondrian.h"
#include "dune/KineBinning/KBCubHcmbEdge2Edge.h"

using namespace valor;

//________________________________________________________________________________________
SingleSampleKineBinning::SingleSampleKineBinning(void)
{

}
//________________________________________________________________________________________
SingleSampleKineBinning::~SingleSampleKineBinning(void)
{

}
//________________________________________________________________________________________
bool SingleSampleKineBinning::Read(string file)
{
  this->CleanUp();

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






  return false;
}
//________________________________________________________________________________________
void SingleSampleKineBinning::Init(void)
{
  fRecoOptimizedBinning = 0;
  fRecoSimpleBinning    = 0;
  for(int im = 0; im < conv::kNReacModes; im++) {
     fTrueSimpleBinning [im] = 0;
  }
}
//________________________________________________________________________________________
void SingleSampleKineBinning::CleanUp(void)
{
  if (fRecoOptimizedBinning) delete fRecoOptimizedBinning;

  if (fRecoSimpleBinning   ) delete fRecoSimpleBinning;
  for(int im = 0; im < conv::kNReacModes; im++) {
     if(fTrueSimpleBinning [im]) delete fTrueSimpleBinning [im];
  }
  this->Init();
}
//________________________________________________________________________________________


