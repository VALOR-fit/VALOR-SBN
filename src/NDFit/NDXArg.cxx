//________________________________________________________________________________________
/*

Copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

//#include <cassert>

//#include <TFile.h>
//#include <TTree.h>
//#include <TObjArray.h>

#include "NDFit/NDXArg.h"

#include "Parser/CmdLnArgParser.h"
#include "Utilities/Rnd.h"
#include "Utilities/Env.h"
#include "Messenger/Messenger.h"

using namespace valor;

//________________________________________________________________________________________
NDXArg::NDXArg()
{
  this->Reset();
}
//________________________________________________________________________________________
NDXArg::~NDXArg() 
{
  this->Reset();
}
//________________________________________________________________________________________
bool NDXArg::ParseFromCmdLine(int argc, char ** argv)
{
  CmdLnArgParser parser(argc,argv);

  fJobTag        = "";
  fRunNu         = 0;
  fNToyMC        = 0;
  fFitParamList  = "";
  fParamValues   = "";
  fFitOption     = "";
  fConfigFile    = "";

  if( parser.OptionExists("--mesg-thresholds") )
  {
     fVerbosityFile = parser.ArgAsString("--mesg-thresholds");
  }

  fStatFluct     = parser.OptionExists("--with-stat-fluct");
  fStoreSpectra  = parser.OptionExists("--store-spectra");

  return true;
}
//________________________________________________________________________________________
void NDXArg::Report(ostream & stream)
{
  stream << endl;
  stream << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  stream << "- Job: " << fJobTag << "/" << fRunNu << endl;
  stream << "- Analysis configuration" << endl;
  stream << "   - Read from: " << fConfigFile << endl;
  stream << "- Toy-MC generation" << endl;
  stream << "   - Number of toy experiments: " << fNToyMC << endl;
  stream << "   - Statistical fluctuations: "  << ((fStatFluct) ? "YES " : "NO") << endl;
  stream << "   - Option for setting parameter values: " << fParamValues << endl;
  stream << "- Fit" << endl;
  stream << "   - Fit Parameter List: " << fFitParamList << endl;
  stream << "   - Fitter option: " << fStatFluct << endl;
  stream << endl;
  stream << *Rnd::Instance() << endl;
  stream << *Env::Instance() << endl;
  stream << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  stream << endl;
}
//________________________________________________________________________________________
void NDXArg::Reset(void)
{
  fJobTag        = "";
  fRunNu         = 0;
  fNToyMC        = 0;
  fFitParamList  = "";
  fParamValues   = "";
  fStatFluct     = false;
  fFitOption     = "";
  fStoreSpectra  = false;
  fConfigFile    = "";
  fVerbosityFile = "";
}
//________________________________________________________________________________________
void NDXArg::SetDefaults(Option_t * /*opt*/)
{
  fJobTag        = "toymc";
  fRunNu         = 0;
  fNToyMC        = 1;
  fFitParamList  = "standard";
  fParamValues   = "randomize-all;prefit-errors";
  fStatFluct     = true;
  fFitOption     = "minuit";
  fStoreSpectra  = false;
  fConfigFile    = "lbne_ndfit-2014a-STT_baseline.xml";
  fVerbosityFile = "verbosity.xml";
}
//________________________________________________________________________________________
