//____________________________________________________________________________
/*!

\file      NDSystDef

\brief     Typedef specific LBNx ND systematics to free PhysParamId_t slots
           of the VALOR framework

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <n.grant \at lancaster.ac.uk>
           University of Lancaster
          
\created   March 20, 2014

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_nd_syst_def_h_
#define _valor_lbnx_nd_syst_def_h_

#include <string>

#include "Conventions/PhysParamId.h"

using std::string;

namespace valor {
namespace conv {

static const PhysParamId_t kNuisNuMuFlux00 = kNuis000; 
static const PhysParamId_t kNuisNuMuFlux01 = kNuis001; 
static const PhysParamId_t kNuisNuMuFlux02 = kNuis002; 
static const PhysParamId_t kNuisNuMuFlux03 = kNuis003; 
static const PhysParamId_t kNuisNuMuFlux04 = kNuis004; 
static const PhysParamId_t kNuisNuMuFlux05 = kNuis005; 
static const PhysParamId_t kNuisNuMuFlux06 = kNuis006; 
static const PhysParamId_t kNuisNuMuFlux07 = kNuis007; 
static const PhysParamId_t kNuisNuMuFlux08 = kNuis008; 
static const PhysParamId_t kNuisNuMuFlux09 = kNuis009; 

} // conv
} // valor
  
#endif 

