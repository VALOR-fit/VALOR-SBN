//____________________________________________________________________________
/*!

\class     valor::KinematicPoint

\brief     Simple struct for a point in kinematic space.

\author    Steve Dennis <s.r.dennis \at University of Liverpool>
           University of Liverpool

\created   April 20, 2016

\copyright (c) 2010-2016, The VALOR group.

*/
//____________________________________________________________________________

#ifndef __valor_dune_kinematic_point__
#define __valor_dune_kinematic_point__

#include <iostream>

#include "Conventions/DuneBuild.h"

namespace valor {
namespace util {

struct KinematicPoint {

public:
  KinematicPoint(void);
  
  double true1;
  double true2;
  double true3;
  double reco1;
  double reco2;
  double reco3;

}; //KinematicPoint

}      // Namespace util
}      // valor namespace

#endif 
