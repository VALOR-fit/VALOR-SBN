//____________________________________________________________________________
/*!

\class     valor::SingleSampleKineBinning

\brief     Kinematic binning choices for a single sample

           It specifies:
           - a single optimized binning for reco kine quantities (Mondrian type)
           - a corresponding simple binning for reco kine quantities (E2E type)
           - a simple binning for true kine quantities (E2E type) with reaction
             mode granuarity
           
           Configured using an XML file with the following schema:
           ..................................................................
           <?xml version="1.0" encoding="ISO-8859-1"?>

           <sample_binning>

               <!--
                 Single Mondrian binning scheme for reco quantities -->
               <reco_optimized>
                  mondrian_binning_scheme.xml
               </reco_optimized>

               <!--
                 Single edge-to-edge binning scheme for reco quantities -->
               <reco_simple>
                  edge_to_edge_binning_scheme.xml
               </reco_simple>

               <!--
                 Single edge-to-edge binning scheme for treue quantities.
                 Used both for optimized and simple templates
                -->
               <true_simple>
                   <!-- 
                     Applies to all modes unless a mode binning scheme
                     is specified explicitly below -->
                   <default>
                      another_edge_to_edge_binning_scheme.xml
                   <default>
                   <!--
                     Exception for specific modes (optional) -->
                   <a_weird_mode>
                      yet_another_edge_to_edge_binning_scheme.xml
                   </a_weird_mode>
               </true_simple>

           </sample_binning>
           ..................................................................

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   April 7, 2016

\copyright (c) 2010-2016, The VALOR group.

*/
//____________________________________________________________________________

#ifndef __valor_single_sample_kinematic_binning__
#define __valor_single_sample_kinematic_binning__

#include <string>

#include "valor/KineBinning/KBCubHcmbMondrian.h"
#include "valor/KineBinning/KBCubHcmbEdge2Edge.h"

#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/UniqueSampleID.h"
#include "dune/Conventions/Sample.h"
#include "dune/Conventions/SampleReacMode.h"

namespace valor {

// class KBCubHcmbMondrian;
// class KBCubHcmbEdge2Edge;

class SingleSampleKineBinning {

public:
  SingleSampleKineBinning(conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s);
  SingleSampleKineBinning(UniqueSampleID usid);
 ~SingleSampleKineBinning();

  bool Read(string file);

  KBCubHcmbMondrian *  RecoOptBinning(void)   const { return fRecoOptimizedBinning;    }
  KBCubHcmbEdge2Edge * RecoSmpBinning(void)   const { return fRecoSimpleBinning;       }
  KBCubHcmbEdge2Edge * TrueSmpBinning(int im) const { return fTrueSimpleBinning [im];  }
  // Return Simple Binning for the reaction mode, m
  KBCubHcmbEdge2Edge * TrueSmpBinning(conv::ReacMode_t m) const;
  KBCubHcmbEdge2Edge * XsecSmpBinning(void)   const { return fXsecSimpleBinning;       }

  conv::BeamConf_t     GetBeamConf(void)      const { return fBeamConf; }
  conv::Sample_t       GetSample(void)        const { return fSample;   }

private:

  void Init    (void);
  void CleanUp (void);

  conv::Detector_t             fDetector;
  conv::BeamConf_t             fBeamConf;
  conv::Sample_t               fSample;
  KBCubHcmbMondrian *          fRecoOptimizedBinning;                   //
  KBCubHcmbEdge2Edge *         fRecoSimpleBinning;                      //
  KBCubHcmbEdge2Edge *         fTrueSimpleBinning [conv::kNReacModes];  //
  KBCubHcmbEdge2Edge *         fXsecSimpleBinning;                      // Binning for Xsec params
  vector<KBCubHcmbEdge2Edge *> fTrueSimpleBinningUnique;                //
};

} // valor namespace

#endif 
