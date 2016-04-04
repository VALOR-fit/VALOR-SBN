//____________________________________________________________________________ 
/*!

\class     valor::NDXArg

\brief     A utility class to hold command-line argument for VALOR/DUNE
           ND fit package executables

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   September 16, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nd_xarg_h_
#define _valor_dune_nd_xarg_h_

#include <ostream>
#include <string>

#include <TROOT.h>

using namespace std;

namespace valor {

class NDXArg //: public TObject
{
public:
  NDXArg();
  virtual ~NDXArg();
   
  bool ParseFromCmdLine (int argc, char ** argv);
  void SetDefaults      (Option_t * opt = 0);
  void Report           (ostream& stream)  const;

  const char * JobTag            (void) const { return fJobTag.c_str();            }       
  long         RunNu             (void) const { return fRunNu;                     }
  int          NToyMC            (void) const { return fNToyMC;                    }
  const char * FitParamList      (void) const { return fFitParamList.c_str();      }
  const char * ParamValuesOption (void) const { return fParamValuesOption.c_str(); }
  bool         StatFluct         (void) const { return fStatFluct;                 }
  const char * FitOption         (void) const { return fFitOption.c_str();         }
  bool         StoreSpectra      (void) const { return fStoreSpectra;              }
  const char * ConfigFile        (Option_t * opt = "check_file_exists") const;
  const char * VerbosityFile     (Option_t * opt = "check_file_exists") const;
  
  UInt_t RndSeedToyMCstat() const {return fSeedToyMCstat;}
  UInt_t RndSeedToyMCsyst() const {return fSeedToyMCsyst;}
  UInt_t RndSeedToyMCosc () const {return fSeedToyMCosc; }
  UInt_t RndSeedFitter   () const {return fSeedFitter;   }
  UInt_t RndSeedOther    () const {return fSeedOther;    }

protected:

  void Reset (void);

  string fJobTag;             ///< job tag
  long   fRunNu;              ///< run # 
  int    fNToyMC;             ///< number of toy-MC experiments in job
  string fFitParamList;       ///< fit parameter list (see NDFitParams.cxx) 
  string fParamValuesOption;  ///< decide how to set the values of params used for toy-MC generation 
  bool   fStatFluct;          ///< include statistical fluctuation in toy MC generation? *
  string fFitOption;          ///< fitter option 
  bool   fStoreSpectra;       ///< store toy-MC and best-fit spectra? (default: store only true and best-fit parameters) 
  string fConfigFile;         ///< analysis configuration file 
  string fVerbosityFile;      ///< message thresholds 
  
  // Random seeds
  UInt_t fSeedToyMCstat;      ///< initial seeds for RNG - stat fluctuations
  UInt_t fSeedToyMCsyst;      ///< initial seeds for RNG - syst fluctuations
  UInt_t fSeedToyMCosc;       ///< initial seeds for RNG - osc param fluctutations
  UInt_t fSeedFitter;         ///< initial seeds for RNG - randomisation of start points in fitter
  UInt_t fSeedOther;          ///< initial seeds for RNG - misc
        
};

std::ostream& operator<< (std::ostream& stream, const valor::NDXArg & arg);

} // valor

#endif

