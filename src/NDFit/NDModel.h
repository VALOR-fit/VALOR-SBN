//____________________________________________________________________________
/*!

\class     valor::NDModel

\brief     LBNE ND Model class. Derives from FitModelABC

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <n.grant \at lancaster.ac.uk>
           University of Lancaster

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_nd_model_h_
#define _valor_lbnx_nd_model_h_

#include <string>
#include <TObjArray.h>
#include <TTree.h>
#include <TH1D.h>

//fmwk
#include "FitCore/FitModelABC.h"
#include "FitCore/PhysHypothesis.h"
#include "FitCore/PhysParamList.h"
#include "Utilities/VALORArray.h"
//lbnx
#include "Conventions/BeamConf.h"
#include "NDFit/NDArrIdx.h"
#include "NDFit/NDSample.h"
#include "NDFit/NDSampleBinning.h"
#include "NDFit/NDSampleModes.h"

namespace valor {

class NDModel: public FitModelABC
{
public:
  NDModel();
 ~NDModel();

  //
  // Implement the FitModelABC interface
  // See FitModelABC for method decription
  //

  string        Name                   (void);
  bool          Read                   (string file, Option_t * opt = 0);
  bool          Generate               (const PhysHypothesis & ph);
  void          RandomizeSystematics   (void);
  void          TweakSystematic        (string syst_name, double twkdial=0., Option_t * opt = 0); 
  void          TweakSystematic        (conv::PhysParamId_t syst, double twkdial=0., Option_t * opt = 0);
  void          ResetSystematics       (void);  
  void          PrintSystematics       (ostream & stream = std::cout) const;
  PhysParamList Tweaks                 (void);
  bool          Generate               (const FitParamList & fp);
  bool          Write                  (TObjArray * collection, const char * tag = "model", Option_t * write_opt = 0);
  bool          Write                  (const char * filename,  const char * tag = "model", Option_t * write_opt = 0, Option_t * file_opt = 0);
  double        GetFitStatisticPenalty (Option_t * opt = 0) const;

private:

  void Init  (void);
  void Book  (void);
  void Clean (void);

  void ZeroTemplates    (void);
  void FillTemplates    (TTree * t);
  void ApplyTuning      (void);
  void ApplySystematics (void);
  void ApplyPhysics     (void);

  util::NDArrIdx * fArrIdx;

  PhysHypothesis fPhysHypothesis;

  // Exposure (assumed) for each beam configuration (in POT)
  double fPOT [conv::kNBeamConf];

  // MC templates for all samples/reac_modes/bin_zones
  // - nom: Nominal MC 
  // - tun: Nominal MC + Ext. tuning (eg tuning based on *external* hadro-production or neutrino cross-section data)
  // - sys: Nominal MC + Ext. tuning + Systematic param variations
  // - fin: Nominal MC + Ext. tuning + Systematic param variations + Physics param variations
  // Note: 
  // The language/convention above (nom, tun, sys, fin) derives from our oscillation analysis.
  // All parameters we are handling here are "systematics" from the oscilation analysis point of view.
  // However, the following distrinction is made:
  // - Systematics "systematics". These are the ones we marginalize (eg detector systematics, uncorrelated cross-sections). 
  //   The effect of their variation is included in the sys templates.
  // - Physics "systematics" are the ones we attempt to constrain and are included in the output covariance matrix (eg. 
  //   correlated flux and cross-sections). The effect of their variation is included in the fin templates.
  bool         fNullMCTempl [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones];
  VALORArray * fMCTemplNom  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTemplTun  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTemplSys  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTemplFin  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 

  //
  PhysParamList fSystCurrValues;

  // Input VALOR MC DSTs
  bool fUseMCDST;
  TTree * fMCDST[conv::kNBeamConf];
};

} // valor

#endif

