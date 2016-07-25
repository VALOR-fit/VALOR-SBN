//____________________________________________________________________________
/*!

\class     valor::conv::

\brief     Enumeration of default initial values for oscillation parameters

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

	   Lorena Escudero <escudero \at hep.phy.cam.ac.uk>
	   University of Cambridge
          
\created   July, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_expt_oscparams_h_
#define _valor_expt_oscparams_h_

#include "dune/Conventions/FitParam.h"

namespace valor {
namespace conv {

//
// Default values of oscillation parameters - same as used in fmw (global)
//

// Dm^2 global fit results                                               
  static const double kInitDm12sq    = 7.5E-5;
  static const double kInitErrDm12sq = 0.024; // ~2.4% (PDG 2014)
  static const double kInitSinsqTheta12  = 0.304;
  static const double kInitSinsq2Theta12  = 0.8463; // (PDG 2014)
  static const double kInitErrSinsq2Theta12  = 0.025; // ~2.5% (PDG 2014) 
  static const double kInitErrSinsqTheta12  = 0.025; // ~2.5% (PDG 2014) 

  static const double kInitDm23sq    = 2.509E-3;
  static const double kInitErrDm23sq = 0.04; // ~4% (T2K Run1-4 NH)   
  static const double kInitDmFL      = 2.36E-3;
  static const double kInitSinsqTheta23  = 0.528;
  static const double kInitSinsq2Theta23 = 0.997;
  static const double kInitErrSinsq2Theta23  = 0.109;  // ~10.9% (T2K Run1-4 NH)  
  static const double kInitErrSinsqTheta23  = 0.109;  // ~10.9% (T2K Run1-4 NH)  

  static const double kInitSinsqTheta13  = 0.0217; // (PDG 2015) 
  static const double kInitSinsq2Theta13  = 0.085;  // (PDG 2015) 
  static const double kInitErrSinsq2Theta13  = 0.324; // ~32.4% (T2K Run1-4 NH) 
  static const double kInitErrSinsqTheta13  = 0.324; // ~32.4% (T2K Run1-4 NH) 

  static const double kInitDeltaCP = -1.601;
  static const double kInitErrDeltaCP = 0.10; // ~10%  
    
} // conv

//
// Associated utilities
//
namespace util {

  double OscParamInitValue(conv::PhysParamId_t p);

} // util

} // valor
  
#endif 

