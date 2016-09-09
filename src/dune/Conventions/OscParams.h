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
namespace duneosc{
//
// Default values of oscillation parameters - updated from PDG 2016, except dcp, bf from T2K reactor
//

// Dm^2 global fit results                                               
  static const double kInitDm12sq    = 7.53E-5;//(PDG 2015)
  static const double kMinDm12sq     = 1.0E-5;
  static const double kMaxDm12sq     = 15.0E-5;
  static const double kStepDm12sq    = 2.0E-6;

  
  static const double kInitErrDm12sq = 0.024; // ~2.4% (PDG 2015)
  static const double kInitSinsqTheta12  = 0.304;//(PDG 2015)
  static const double kInitSinsq2Theta12  = 0.846; // (PDG 2015)
  static const double kInitErrSinsq2Theta12  = 0.025; // ~2.5% (PDG 2015) 
  static const double kInitErrSinsqTheta12  = 0.046; // ~2.5% (PDG 2015) 
  static const double kStepSinsqTheta12        = 1.0E-2;
  static const double kStepSinsq2Theta12       = 1.0E-2;


  static const double kInitDm23sq    = 2.44E-3;//(PDG 2015, NH) 
  static const double kMinDm23sq     = 1.0E-3;
  static const double kMaxDm23sq     = 5.0E-3;
  static const double kInitErrDm23sq = 0.025; // ~2.5% (PDG 2015)
  static const double kInitDmFL      = 2.48E-3; //(PDG 2015)  
  static const double kStepDm23sq    = 1.0E-4;

  static const double kInitSinsqTheta23     = 0.514; //(PDG 2015, NH)  
  static const double kInitSinsq2Theta23    = 0.999; //(PDG 2015, NH)
  static const double kInitErrSinsq2Theta23 = 0.018;  // (PDG 2015, NH) 
  static const double kInitErrSinsqTheta23  = 0.108;  // (PDG 2015, NH) 
  static const double kStepSinsqTheta23     = 5.0E-3;
  static const double kStepSinsq2Theta23    = 5.0E-3;

  static const double kInitSinsqTheta13     = 0.0219; // (PDG 2015) 
  static const double kInitSinsq2Theta13    = 0.085;  // (PDG 2015) 
  static const double kInitErrSinsq2Theta13 = 0.059; // (PDG 2015)
  static const double kInitErrSinsqTheta13  = 0.055; // (PDG 2015)
  static const double kStepSinsqTheta13     = 1.0E-3;
  static const double kStepSinsq2Theta13    = 1.0E-3;

  static const double kInitDeltaCP = -1.55; // T2K BF NH with reactor
  //  static const double kInitDeltaCP = 0.0;
    static const double kInitErrDeltaCP = 0.10; // ~10%  
  static const double kStepDeltaCP = 1.0E-2;

} // duneosc
} // conv

//
// Associated utilities
//
namespace util {

  double OscParamInitValue(conv::PhysParamId_t p);
  double OscParamInitError(conv::PhysParamId_t p);
  double OscParamMaxValue (conv::PhysParamId_t p);
  double OscParamMinValue (conv::PhysParamId_t p);
  double OscParamStepSize (conv::PhysParamId_t p);

  double GetRandomizedOscParam (conv::PhysParamId_t p, string mode);

  void InitializeOAPriors();

} // util

} // valor
  
#endif 

