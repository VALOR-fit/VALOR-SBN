//________________________________________________________________________________________
/*

Copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

//#include <cassert>

// fmwk
#include "Parser/CmdLnArgParser.h"
#include "Utilities/Rnd.h"
#include "Utilities/Env.h"
#include "Messenger/Messenger.h"
// lbnx
#include "NDFit/NDXArg.h"

using namespace valor;

//________________________________________________________________________________________
namespace valor {
  ostream & operator << (ostream & stream, const NDXArg & arg)
  {
    arg.Report(stream);
    return stream;
  }
}
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

  if( parser.OptionExists("--tag") ) {
     fJobTag = parser.ArgAsString("--tag");
  }

  if( parser.OptionExists("--run") ) {
     fRunNu = parser.ArgAsLong("--run");
  }

  if( parser.OptionExists("--ntoymc") ) {
     fNToyMC = parser.ArgAsInt("--ntoymc");
  }

  if( parser.OptionExists("--fit-param-list") ) {
     fFitParamList = parser.ArgAsString("--fit-param-list");
  }

  if( parser.OptionExists("--param-values-option") ) {
    fParamValuesOption = parser.ArgAsString("--param-values-option");
  }

  if( parser.OptionExists("--fit-opt") ) {
    fFitOption = parser.ArgAsString("--fit-opt");
  }

  if( parser.OptionExists("--config") ) {
    fConfigFile = parser.ArgAsString("--config");
  }

  if( parser.OptionExists("--mesg-thresholds") )
  {
     fVerbosityFile = parser.ArgAsString("--mesg-thresholds");
  }

  if( parser.OptionExists("--with-stat-fluct")    ) fStatFluct = true;
  if( parser.OptionExists("--without-stat-fluct") ) fStatFluct = false;

  if( parser.OptionExists("--store-spectra")   ) fStoreSpectra = true;
  if( parser.OptionExists("--discard-spectra") ) fStoreSpectra = false;

  return true;
}
//________________________________________________________________________________________
void NDXArg::Report(ostream & stream) const
{
  stream << endl;
  stream << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  stream << "- Job: " << fJobTag << "/" << fRunNu << endl;
  stream << "- Analysis configuration" << endl;
  stream << "   - Read from: " << fConfigFile << endl;
  stream << "- Toy-MC generation" << endl;
  stream << "   - Number of toy experiments: " << fNToyMC << endl;
  stream << "   - Statistical fluctuations: "  << ((fStatFluct) ? "YES " : "NO") << endl;
  stream << "   - Option for setting parameter values: " << fParamValuesOption << endl;
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
  fJobTag             = "";
  fRunNu              = 0;
  fNToyMC             = 0;
  fFitParamList       = "";
  fParamValuesOption  = "";
  fStatFluct          = false;
  fFitOption          = "";
  fStoreSpectra       = false;
  fConfigFile         = "";
  fVerbosityFile      = "";
}
//________________________________________________________________________________________
void NDXArg::SetDefaults(Option_t * /*opt*/)
{
  fJobTag            = "toymc";
  fRunNu             = 0;
  fNToyMC            = 1;
  fFitParamList      = "standard";
  fParamValuesOption = "randomize-all;prefit-errors";
  fStatFluct         = true;
  fFitOption         = "minuit";
  fStoreSpectra      = false;
  fConfigFile        = "";
  fVerbosityFile     = "verbosity.xml";
}
//________________________________________________________________________________________
