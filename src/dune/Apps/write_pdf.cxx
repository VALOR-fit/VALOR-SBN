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

\author    VALOR DUNE people, aka Costas, Steve, Lorena
\created   March 27, 2014                                                                                                     
                                                                                                                                   
\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved                                                              
                                                                                                                                      
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
// dune                                                                                                                        
#include "dune/Conventions/FitParam.h"
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
  
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/write_pdf.arg:$VALOR_DUNE/config/apps/seeds.arg");
  LOG("valor_dune", pNOTICE) << arg;

  string fplname          = arg.GetString("fit-param-list"); 
  const char * write_opt  = arg.GetString("write-opt").c_str();
  string mesg_thresholds  = arg.GetString("mesg-thresholds");
  string output_name      = arg.GetString("output-name");
  string config_file      = arg.GetString("config");
  
  // If pot_override is set to a positive number, every sample will be initialised with the same POT - this number
  double pot_override     = arg.GetDouble("pot-override");
  if (pot_override > 0 ) {
    Opt::Instance()->MutableGlobalRegistry().Set("pot_override",pot_override);
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
  elements->Read(util::CompleteConfigPath(config_file));
  FitModelABC * model = elements->FitModel();

  // Get the specified fit parameter list (specifies which parameters are floated/fixed,                                              
  // parameter limits, initial values etc).                                                                                           
  FitParamList * fp = util::GetFitParameterList(fplname.c_str());

  //change if something different to default (i.e. normal, sinsqtheta, first octant and dmsq12abs23)                                  
  Opt::Instance()->gMassHierarchyAssumed = ( (arg.GetBool("inverted"))     ? conv::kNmhInverted      : conv::kNmhNormal);
  Opt::Instance()->gOscMixingParamChoice = ( (arg.GetBool("sinsq2theta"))  ? conv::kNuMixSinsq2Theta : conv::kNuMixSinsqTheta);
  Opt::Instance()->gOscOctantChoice      = ( (arg.GetBool("second-octant"))? conv::kNuOctantTwo      : conv::kNuOctantOne);
  Opt::Instance()->gOscDmsqScheme        = ( (arg.GetBool("foglilisi"))    ? conv::kNuDmsqFogliLisi  : conv::kNuDmsq12andAbs23);

  // Update values of oscillation parameters 
  if(fplname != "only-nd"){
    double mixing12 = arg.GetDouble("input-mixing12");
    PhysParamId_t p = util::PhysParamFromString("mixing12");
    fp->Update(p, mixing12);
    fp->SetInitValue(p, mixing12);

    double mixing23 = arg.GetDouble("input-mixing23");
    p = util::PhysParamFromString("mixing23");
    fp->Update(p, mixing23);
    fp->SetInitValue(p, mixing23);

    double mixing13 = arg.GetDouble("input-mixing13");
    p = util::PhysParamFromString("mixing13");
    fp->Update(p, mixing13);
    fp->SetInitValue(p, mixing13);

    double dm23sq = arg.GetDouble("input-dm23sq");
    p = util::PhysParamFromString("dm23sq");
    fp->Update(p, dm23sq);
    fp->SetInitValue(p, dm23sq);

    double dm12sq = arg.GetDouble("input-dm12sq");
    p = util::PhysParamFromString("dm12sq");
    fp->Update(p, dm12sq);
    fp->SetInitValue(p, dm12sq);

    double deltacp = arg.GetDouble("input-deltaCP");
    p = util::PhysParamFromString("cpv");
    fp->Update(p, deltacp);
    fp->SetInitValue(p, deltacp);

    // fix them? 
    if(arg.GetBool("fix-mixing12")) fp->FixParameter(util::PhysParamFromString("mixing12"));
    if(arg.GetBool("fix-mixing13")) fp->FixParameter(util::PhysParamFromString("mixing13"));
    if(arg.GetBool("fix-mixing23")) fp->FixParameter(util::PhysParamFromString("mixing23"));
    if(arg.GetBool("fix-dm23sq"))   fp->FixParameter(util::PhysParamFromString("dm23sq"));
    if(arg.GetBool("fix-dm12sq"))   fp->FixParameter(util::PhysParamFromString("dm12sq"));
    if(arg.GetBool("fix-deltaCP"))  fp->FixParameter(util::PhysParamFromString("cpv"));
  }

  // Generate predictions                                                                                                         
  Option_t * generate_opt = "+SB"; // also generate non-default (for fitting) predictions in extra binning schemes                 
  model->Generate(*fp,generate_opt);

  CompoundFitModel * cmodel = dynamic_cast<CompoundFitModel*>(model);
  for (unsigned int i = 0 ; i < cmodel->GetNSubModels() ; i++) {
    GenericSingleSampleFitModel * gmodel = dynamic_cast<GenericSingleSampleFitModel*>(cmodel->GetSubModel(i));
    gmodel->UpdateObservableBinningFromSimple();
  }

  // Write stuff out                              
  model->Write(outfilename,"valor",write_opt);

  std::cout<<"Done. Have a good day!"<<std::endl << "GO VALOR!!!" << std::endl;

}
