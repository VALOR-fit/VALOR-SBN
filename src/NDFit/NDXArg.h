//____________________________________________________________________________ 
/*!

\class     valor::NDXArg

\brief     A utility class to hold command-line argument for VALOR/LBNX
           ND fit package executables

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   September 16, 2016

\copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_nd_xarg_h_
#define _valor_lbnx_nd_xarg_h_

#include <ostream>
#include <string>

#include <TROOT.h>

using namespace std;

namespace valor {

class NDXArg
{
public:
  NDXArg();
  virtual ~NDXArg();
   
  bool ParseFromCmdLine (int argc, char ** argv);
  void SetDefaults      (Option_t * opt);
  void Report           (ostream & stream);

  const char * JobTag        (void) const { return fJobTag.c_str();        }       
  int          RunNu         (void) const { return fRunNu;                 }
  int          NToyMC        (void) const { return fNToyMC;                }
  const char * FitParamList  (void) const { return fFitParamList.c_str();  }
  const char * ParamValues   (void) const { return fParamValues.c_str();   }
  bool         StatFluct     (void) const { return fStatFluct;             }
  const char * FitOption     (void) const { return fFitOption.c_str();     }
  bool         StoreSpectra  (void) const { return fStoreSpectra;          }
  const char * ConfigFile    (void) const { return fConfigFile.c_str();    }
  const char * VerbosityFile (void) const { return fVerbosityFile.c_str(); }

protected:

  void Reset (void);

  string fJobTag;             ///< job tag
  int    fRunNu;              ///< run # 
  int    fNToyMC;             ///< number of toy-MC experiments 
  string fFitParamList;       ///< fit parameter list (see NDFitParams.cxx) 
  string fParamValues;        ///< decide how to set the values of params used for toy-MC generation 
  bool   fStatFluct;          ///< include statistical fluctuation in toy MC generation? *
  string fFitOption;          ///< fitter option 
  bool   fStoreSpectra;       ///< store toy-MC and best-fit spectra? (default: store only true and best-fit parameters) 
  string fConfigFile;         ///< analysis configuration file 
  string fVerbosityFile;      ///< message thresholds 
};

} // valor

#endif

