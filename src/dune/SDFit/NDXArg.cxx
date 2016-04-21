//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

//#include <cassert>

#include <TSystem.h>
// fmwk
#include "CmdLine/CmdLnArgParser.h"
#include "Utilities/Rnd.h"
#include "Utilities/Env.h"
#include "Messenger/Messenger.h"
// dune
#include "dune/SDFit/NDXArg.h"

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

  if( parser.OptionExists("tag") ) {
     fJobTag = parser.ArgAsString("tag");
  }

  if( parser.OptionExists("run") ) {
     fRunNu = parser.ArgAsLong("run");
  }

  if( parser.OptionExists("ntoymc") ) {
     fNToyMC = parser.ArgAsInt("ntoymc");
  }

  if( parser.OptionExists("fit-param-list") ) {
     fFitParamList = parser.ArgAsString("fit-param-list");
  }

  if( parser.OptionExists("param-values-option") ) {
    fParamValuesOption = parser.ArgAsString("param-values-option");
  }

  if( parser.OptionExists("fit-opt") ) {
    fFitOption = parser.ArgAsString("fit-opt");
  }

  if( parser.OptionExists("config") ) {
    fConfigFile = parser.ArgAsString("config");
  }

  if( parser.OptionExists("mesg-thresholds") )
  {
     fVerbosityFile = parser.ArgAsString("mesg-thresholds");
  }

  if( parser.OptionExists("with-stat-fluct")    ) fStatFluct = true;
  if( parser.OptionExists("without-stat-fluct") ) fStatFluct = false;

  if( parser.OptionExists("store-spectra")   ) fStoreSpectra = true;
  if( parser.OptionExists("discard-spectra") ) fStoreSpectra = false;
  
  // seeds
  if (parser.OptionExists("seed-toys-stat")) {
    fSeedToyMCstat = parser.ArgAsUInt("seed-toys-stat");
  }
  else {
    fSeedToyMCstat = 0;
  }
  
  if (parser.OptionExists("seed-toys-syst")) {
    fSeedToyMCsyst = parser.ArgAsUInt("seed-toys-syst");
  }
  else {
    fSeedToyMCsyst = 0;
  }
  
  if (parser.OptionExists("seed-toys-osc")) {
    fSeedToyMCosc = parser.ArgAsUInt("seed-toys-osc");
  }
  else {
    fSeedToyMCosc = 0;
  }
  
  if (parser.OptionExists("seed-fitter")) {
    fSeedFitter = parser.ArgAsUInt("seed-fitter");
  }
  else {
    fSeedFitter = 0;
  }
  
  if (parser.OptionExists("seed-misc")) {
    fSeedOther = parser.ArgAsUInt("seed-misc");
  }
  else {
    fSeedOther = 0;
  }
  
  // Should this be done here? Or in macro code.
  Rnd::Instance()->SetSeeds(fSeedToyMCstat,fSeedToyMCsyst,fSeedToyMCosc,fSeedFitter,fSeedOther);
  

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
  stream << "   - Fitter option: " << fFitOption << endl;
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
string NDXArg::ConfigFile(Option_t * user_opt) const 
{ 
  string opt = (user_opt) ? user_opt : "";

  string file = fConfigFile;

  if(opt.find("check_file_exists") != string::npos) {
    // initially assume absolute path
    bool found = ! gSystem->AccessPathName(file.c_str());
    if(!found) {
      // then try in standard config path (usually $VALOR_DUNE/config/)
      Env * env = Env::Instance(); 
      string file_tried = env->TopLevelConfDir() + "/" + file;
      found = ! gSystem->AccessPathName(file_tried.c_str());
      if(!found) {
        LOG("NDXArg", pERROR) << "Can not find XML file [" << file << "]";
        return "";
      }
      file = file_tried;
    }
  }

  return file;
}
//________________________________________________________________________________________
string NDXArg::VerbosityFile(Option_t * user_opt) const 
{ 
  string opt = (user_opt) ? user_opt : "";

  string file = fVerbosityFile;

  if(opt.find("check_file_exists") != string::npos) {
    // initially assume absolute path
    bool found = ! gSystem->AccessPathName(file.c_str());
    if(!found) {
      // then try in standard config path (usually $VALOR_DUNE/config/)
      Env * env = Env::Instance(); 
      string file_tried = env->TopLevelConfDir() + "/" + file;
      found = ! gSystem->AccessPathName(file_tried.c_str());
      if(!found) {
        LOG("NDXArg", pERROR) << "Can not find XML file [" << file << "]";
        return "";
      }
      file = file_tried;
    }
  }

  return file;
}
//________________________________________________________________________________________

