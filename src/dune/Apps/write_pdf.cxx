//____________________________________________________________________________                                                       
/*!                                                                                                                                  
                                                                                                                                      
\app       valor_dune-write_pdf  

\brief     Write out generic single sample PDFs and MC templates 

\options
           --fit-param-list      : Fit parameter list (see FitParam.cxx)                                                              
                                     [def: "standard"]    				     
           --config              : Analysis configuration file [required]
           --write-opt           : Options defining what to write-out [def:pdft_vf]
           --output-name         : Output file name [def:test]
           --mesg-thresholds     : Message thresholds [def: "verbosity.xml"] 
           --input               : Input values of the oscillation parameters
           --fix                 : Oscillation parameters to be fixed 
           --pot-override        : Fix all samples to given POT (use 1E21 when making template files)
           --force-dst           : Ignore the XML requesting you use prebuilt templates and read the DST anyway (useful for making the prebuilt templates)

\author    VALOR DUNE people, aka Costas, Steve, Lorena
\created   March 27, 2014

\copyright (c) 2010-2017, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________ 

// root
#include "TFile.h"
#include "TSystem.h"
#include "TObjArray.h"
#include "TString.h"
#include "TVirtualFitter.h"
// fmwk
#include "valor/Conventions/Opt.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/FitCore/PhysParamList.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/FitDataABC.h"
#include "valor/FitCore/FitInputs.h"
#include "valor/FitCore/FitterABC.h"
#include "valor/FitCore/UtlFit.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/Env.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Ntuple/StdFitNtp.h"
#include "valor/Utilities/NameRegistry.h"
// dune
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/OscParams.h"
#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Elements/CompoundFitElements.h"
#include "dune/Elements/GenericSingleSampleFitModel.h"

using namespace std;
using namespace valor;
using namespace valor::conv;

int main(int argc, char ** argv)
{

  Env::Instance()->AutoSet("dune");
  valor::util::PrintBanner(Env::Instance()->Banner(),500);
  
  util::InitializeOAPriors();
  
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/write_pdf.arg:$VALOR_DUNE/config/apps/oscparams.arg:$VALOR_DUNE/config/apps/seeds.arg");
  LOG("valor_dune", pNOTICE) << arg;

  string fplname          = arg.GetString("fit-param-list"); 
  std::string write_opt   = arg.GetString("write-opt");
  string mesg_thresholds  = arg.GetString("mesg-thresholds");
  string output_name      = arg.GetString("output-name");
  string config_file      = arg.GetString("config");
  
  // If pot_override is set to a positive number, every sample will be initialised with the same POT - this number
  double pot_override     = arg.GetDouble("pot-override");
  if (pot_override > 0 ) {
    Opt::Instance()->MutableGlobalRegistry().Set("pot_override",pot_override);
  }
  
  TString readopt;
  // Check if we want to force the fit to read trees rather than templates, ignoring the config file
  bool force_dst = arg.GetBool("force-dst");
  if (force_dst) {
    readopt += " forcedst";
  }
  
  Messenger::Instance()->Configure(util::CompleteConfigPath(mesg_thresholds));

  // Set DUNE param names inside framework       
  util::PopulateNameRegistry();

  // Set the random seeds                                                                                                          
  Rnd::Instance()->SetSeeds(arg);

  LOG("valor_dune", pNOTICE) << *Rnd::Instance();

  // Create file to store outputs
  TString outfilename = TString::Format("%s.root", output_name.c_str());

  // Get ND model & configure                
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(util::CompleteConfigPath(config_file),readopt.Data());
  FitModelABC * model = elements->FitModel();
  NameRegistry * nr = util::NameRegistry::Instance();

  // Get the specified fit parameter list (specifies which parameters are floated/fixed,                                              
  // parameter limits, initial values etc).            
  CorrelatedSystematics * syst = model->GetSystematics();                                                                               
  FitParamList * fp = util::GetFitParameterList(fplname.c_str(),syst);

  //change if something different to default (i.e. normal, sinsqtheta, first octant and dmsq12abs23)                                  
  Opt::Instance()->gMassHierarchyAssumed = ( (arg.GetBool("inverted"))     ? conv::kNmhInverted      : conv::kNmhNormal);
  Opt::Instance()->gOscMixingParamChoice = ( (arg.GetBool("sinsq2theta"))  ? conv::kNuMixSinsq2Theta : conv::kNuMixSinsqTheta);
  Opt::Instance()->gOscOctantChoice      = ( (arg.GetBool("second-octant"))? conv::kNuOctantTwo      : conv::kNuOctantOne);
  Opt::Instance()->gOscDmsqScheme        = ( (arg.GetBool("foglilisi"))    ? conv::kNuDmsqFogliLisi  : conv::kNuDmsq12andAbs23);

  // Update values of oscillation parameters 
  
  if (fp->Exists(conv::kPhypMixing12)) {
    double mixing12 = arg.GetDouble("input-mixing12");
    if ( std::fabs(mixing12 + 999. ) < conv::kASmallNum ) { 
      mixing12 = Opt::Instance()->GetGlobalBestFit(conv::kPhypMixing12);
    }
    fp->Update      (nr->PhysParamFromString("mixing12"), mixing12);
    fp->SetInitValue(nr->PhysParamFromString("mixing12"), mixing12);
  }

  double mixing13 = arg.GetDouble("input-mixing13");
  if ( std::fabs(mixing13 + 999. ) < conv::kASmallNum ) { 
    mixing13 = Opt::Instance()->GetGlobalBestFit(conv::kPhypMixing13);
  }
  fp->Update      (nr->PhysParamFromString("mixing13"), mixing13);
  fp->SetInitValue(nr->PhysParamFromString("mixing13"), mixing13);
  
  double mixing23 = arg.GetDouble("input-mixing23");
  if ( std::fabs(mixing23 + 999. ) < conv::kASmallNum ) { 
    mixing23 = Opt::Instance()->GetGlobalBestFit(conv::kPhypMixing23);
  }
  
  //~ if (flip_23_octant) {
    //~ mixing23 = util::FlipOctantAroundMaxDisap(mixing23,mixing13);
  //~ }
  //~ fp->Update      (nr->PhysParamFromString("mixing23"), mixing23);
  //~ fp->SetInitValue(nr->PhysParamFromString("mixing23"), mixing23);
  
  double dm23sq = arg.GetDouble("input-dm23sq");
  if ( std::fabs(dm23sq + 999. ) < conv::kASmallNum ) {
    dm23sq = Opt::Instance()->GetGlobalBestFit(conv::kPhypDm23sq);
  }
  fp->Update      (nr->PhysParamFromString("dm23sq"), dm23sq);
  fp->SetInitValue(nr->PhysParamFromString("dm23sq"), dm23sq);

  double dm12sq = arg.GetDouble("input-dm12sq");
  if ( std::fabs(dm12sq + 999. ) < conv::kASmallNum ) { 
    dm12sq = Opt::Instance()->GetGlobalBestFit(conv::kPhypDm12sq);
  }
  fp->Update      (nr->PhysParamFromString("dm12sq"), dm12sq);
  fp->SetInitValue(nr->PhysParamFromString("dm12sq"), dm12sq);

  double deltacp = arg.GetDouble("input-deltaCP");
  if ( std::fabs(deltacp + 999. ) < conv::kASmallNum ) {
    deltacp = Opt::Instance()->GetGlobalBestFit(conv::kPhypCPV);
  }
  fp->Update      (nr->PhysParamFromString("cpv"), deltacp);
  fp->SetInitValue(nr->PhysParamFromString("cpv"), deltacp);

  // Generate predictions                                                                                                         
  Option_t * generate_opt = "+SB"; // also generate non-default (for fitting) predictions in extra binning schemes                 
  model->Generate(*fp,generate_opt);

  CompoundFitModel * cmodel = dynamic_cast<CompoundFitModel*>(model);
  for (unsigned int i = 0 ; i < cmodel->GetNSubModels() ; i++) {
    GenericSingleSampleFitModel * gmodel = dynamic_cast<GenericSingleSampleFitModel*>(cmodel->GetSubModel(i));
    gmodel->UpdateObservableBinningFromSimple();
  }

  // Write stuff out                              
  model->Write(outfilename,"valor",write_opt.c_str());

  std::cout<<"Done. Have a good day!"<<std::endl << "GO VALOR!!!" << std::endl;
  
  fp->Print(cout);

}
