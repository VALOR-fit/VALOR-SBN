//____________________________________________________________________________
/*!

\file      FitParamNew

\brief     Reads and stores a single parameter specified from in an XML file

\note      Expects the parameter to be specified as per the following example:
           <param_list name="dune_nd">

            <param>
              <name>
              <simple> int_ccqe_nu_1 </simple>
              <rootex> f_{int^{ccqe}_{#nu ; 1}} </rootex>   <!-- default: simple name -->
              </name>
              <apply_to_range>
                <etrue> 0, inf  </etrue>
                <q2true> 0, 0.3 </q2true>
              </apply_to_range>

              <type> normalisation </type>                  <!-- default: normalisation -->

              <categories>
                <category> int         </category>          <!-- If the only category is either "mixing", "mass_splitting", or "phase" then the parameter is treated as an oscillation parameter -->
                <category> constrained </category>
                <category> nu          </category>
              </categories>

              <apply_to>                                    <!-- default: apply to all -->
                <detector>  all    </detector>              <!-- Naming from Conventions/FitParamApply.cxx -->
                <beam>      all    </beam>
                <selection> all    </selection>
                <reac_type> ccqe   </reac_type>
                <flav>      nu any </flav>
                <target>    all    </target>
              </apply_to>

              <limits> 0, inf </limits>                     <!-- default depends on type: norm. = [0, inf]; lateral = [-inf, inf]; response = [0, inf] -->

            </param>

            ....

          </param_list>


\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Francis Bench <f.bench \at liverpool.ac.uk>
           University of Liverpool

\created   June 26, 2018

\copyright (c) 2010-2018, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

//TODO: This class and file has a placeholder name of FitParamNew, but as it will eventually replace the current FitParam class, this name should be changed

#ifndef _valor_dune_fit_param_new_definition_h_
#define _valor_dune_fit_param_new_definition_h_

#include <TXMLEngine.h>
#include <vector>
#include <utility>
#include <map>

#include "valor/Conventions/KineVar.h"

#include "dune/Conventions/SystType.h"
#include "dune/Conventions/FitParamApply.h"

using namespace valor;

namespace valor {
  class FitParamNew {
    public:
      // TODO: does each instance of this class need to be tied to a specific PhysParamID? If so, put in constructor
      FitParamNew(TXMLEngine* xml, XMLNodePointer_t param_node);

      std::string                 GetName      (void)               const { return fName;          }
      std::string                 GetRootexName(void)               const { return fRootexName;    }
      std::pair<double,double>    GetRange     (conv::KineVar_t kv) const { return fRange.at(kv);  }
      conv::SystType_t            GetType      (void)               const { return fType;          }
      std::vector<std::string>    GetCategories(void)               const { return fCategories;    }
      conv::ApplyMask_t           GetApplyMask (void)               const { return fApply;         }
      std::pair<double,double>    GetLimits    ()                   const { return fLimits;        }
      // TODO: In the old FitParam class, the nuclear target was hard-coded into this function, but now it's an input argument. Make sure that all usages of this function are updated to supply the target
      bool ParamIsAppliedTo(conv::BeamConf_t b, conv::Sample_t s, conv::Detector_t d,
                            conv::ReacMode_t m, conv::NuclearTarget_t nt) const;

      std::vector<conv::KineVar_t> GetKineVars() const;

      // Print out the parameter names, ranges, type, categories etc.
      void Print(std::ostream & stream = std::cout) const;

      // Search the list of user-specified categories for an entry with content exactly matching to_find (after converting to lower case and removing whitespace)
      bool SearchCatergories(std::string to_find, bool one_category_only = false) const;

      // TODO: Want these functions here or in a class which stores each instance of FitParamNew?
      bool IsMixingAngle   (void) const { return (SearchCatergories("mixing",true) || SearchCatergories("mix",true)); }
      bool IsMassSplitting (void) const { return (SearchCatergories("masssplitting",true) || SearchCatergories("splitting",true)); }
      bool IsPhase         (void) const { return SearchCatergories("phase",true); }
      bool IsOscParam      (void) const { return (IsMixingAngle() || IsMassSplitting() || IsPhase() ); }
      bool IsSystematic    (void) const { return !IsOscParam(); }
      bool IsNuFluxRelated (void) const { return SearchCatergories("flux"); }
      bool IsNuIntRelated  (void) const { return (SearchCatergories("int") || SearchCatergories("interaction")); }
      bool IsNuDetRelated  (void) const { return (SearchCatergories("det") || SearchCatergories("detector")); }
      bool IsFSI           (void) const { return SearchCatergories("FSI"); }
      bool IsNDFluxRelated (void) const { return ((SearchCatergories("ND") || SearchCatergories("near")) && IsNuFluxRelated()); }
      bool IsFDFluxRelated (void) const { return ((SearchCatergories("FD") || SearchCatergories("far"))  && IsNuFluxRelated()); }
      bool IsNuNDDetRelated(void) const { return ((SearchCatergories("ND") || SearchCatergories("near")) && IsNuDetRelated()); }
      bool IsNuFDDetRelated(void) const { return ((SearchCatergories("FD") || SearchCatergories("far"))  && IsNuDetRelated()); }
      bool ParamHasSplines (void) const { return (GetType() == conv::ksystResponse); }

    private:
      // Simple parameter name for printing etc.
      std::string fName;

      // ROOT Tex name for displaying on plots
      std::string fRootexName;

      // The range of each kinematic variable over which the parameter is applied
      std::map<conv::KineVar_t,std::pair<double,double>> fRange;

      // Is the parameter normalisation, lateral or a response function
      conv::SystType_t fType;

      // Whether the parameter is a mixing angle, phase, detector systematic etc.
      std::vector<std::string> fCategories;

      // xml file containing parameters
      TXMLEngine* fxml;

      // Node where this parameter is specified within fxml
      XMLNodePointer_t fParamNode;

      // What beams, detectors, true nu flavours, selections, reaction types and targets this parameter should be applied to
      conv::ApplyMask_t fApply;

      // Min. and max. physical limits of the possible values of this parameter
      std::pair<double,double> fLimits;

      // Default values of each apply mask
      const conv::DetectorApplyMask_t      fDefApplyDetector      = conv::kdApplyToAll;
      const conv::BeamApplyMask_t          fDefApplyBeam          = conv::kbApplyToAll;
      const conv::FlavApplyMask_t          fDefApplyFlav          = conv::kfApplyToAll;
      const conv::SelecApplyMask_t         fDefApplySelec         = conv::ksApplyToAllND;
      const conv::ReacTypeApplyMask_t      fDefApplyReacType      = conv::ktApplyToAll;
      const conv::NuclearTargetApplyMask_t fDefApplyNuclearTarget = conv::kntApplyToAll;

      void Init(TXMLEngine* xml, XMLNodePointer_t param_node);
      void ReadNames       ();
      // TODO: Sensible defaults for each kinevar in each used binning scheme should be set, but does each parameter apply to every kinevar in each binning scheme?
      void ReadRanges      ();
      void ReadType        ();
      void ReadCategories  ();
      void ReadApplyMaskAll();
      void ReadLimits      ();
      conv::DetectorApplyMask_t      ReadDetectorApplyMask     (std::string node_name) const;
      conv::BeamApplyMask_t          ReadBeamApplyMask         (std::string node_name) const;
      conv::FlavApplyMask_t          ReadFlavApplyMask         (std::string node_name) const;
      conv::SelecApplyMask_t         ReadSelecApplyMask        (std::string node_name) const;
      conv::ReacTypeApplyMask_t      ReadReacTypeApplyMask     (std::string node_name) const;
      conv::NuclearTargetApplyMask_t ReadNuclearTargetApplyMask(std::string node_name) const;

      // For a specified node which should contain a string: Does this node exist and is the string not empty?
      bool IsNodeSpecified(const std::string node_path) const;

    // TODO: There will likely be a class which stores all instances of FitParamNew. In that class implement all of the
    // TODO: following functions (copied from the old FitParam class)
    /*
      string  AsString    (conv::PhysParamId_t p);
      string  AsStringSimple(conv::PhysParamId_t p);
      string  AsStringTeX (conv::PhysParamId_t p, bool root = false);

      // Aliases for above
      string  ParamAsString    (conv::PhysParamId_t p) ;
      string  ParamAsStringTeX (conv::PhysParamId_t p, bool root = false);

      conv::PhysParamId_t PhysParamFromString(string p);

      // If you give a CorrelatedSystematics object, it'll ignore your list's standard systematics and use this set instead
      FitParamList * GetFitParameterList (Option_t * param_list = "standard", const CorrelatedSystematics * syst = 0);

      conv::FitParamGroup_t GetParameterGroup(conv::PhysParamId_t p);
      // Get the list of parameters associated with a set name (eg flux, int, ccqe, fsi, 3fosc)
      std::vector<conv::PhysParamId_t> GetParameterSet(std::string set_name);

      bool OscProbIsAppliedTo(conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s,
                              conv::ReacMode_t m);

      // Return pointer to array of min/max
      const double * EtrueRange (conv::PhysParamId_t p);
      const double * Q2trueRange(conv::PhysParamId_t p);

      // Tell the framework classes what our parameter names are
      void PopulateNameRegistry(void);
     */

  };
} // valor


#endif
