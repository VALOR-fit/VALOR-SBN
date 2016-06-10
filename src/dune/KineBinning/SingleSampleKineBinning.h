//____________________________________________________________________________
/*!

\class     valor::SingleSampleKineBinning

\brief     Kinematic binning choices for a single sample

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

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


\created   April 7, 2016

\copyright (c) 2010-2016, The VALOR group.

*/
//____________________________________________________________________________

#ifndef __valor_single_sample_kinematic_binning__
#define __valor_single_sample_kinematic_binning__

#include <string>

#include "dune/Conventions/SampleReacMode.h"

namespace valor {

class KBCubHcmbMondrian;
class KBCubHcmbEdge2Edge;

class SingleSampleKineBinning {

public:
  SingleSampleKineBinning();
 ~SingleSampleKineBinning();

  bool Read(string file);

  KBCubHcmbMondrian *  RecoOptBinning(void)   const { return fRecoOptimizedBinning;    }
  KBCubHcmbEdge2Edge * RecoSmpBinning(void)   const { return fRecoSimpleBinning;       }
  KBCubHcmbEdge2Edge * TrueSmpBinning(int im) const { return fTrueSimpleBinning [im];  }

private:

  void Init    (void);
  void CleanUp (void);

  KBCubHcmbMondrian *  fRecoOptimizedBinning;
  KBCubHcmbEdge2Edge * fRecoSimpleBinning; 
  KBCubHcmbEdge2Edge * fTrueSimpleBinning [conv::kNReacModes]; 
};

} // valor namespace

#endif 
