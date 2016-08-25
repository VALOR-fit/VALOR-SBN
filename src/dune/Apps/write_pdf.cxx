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

\author    Lorena Escudero
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
  const char * write_opt  = (char*) arg.GetString("write-opt").c_str();
  string mesg_thresholds  = arg.GetString("mesg-thresholds");
  string output_name      = arg.GetString("output-name");
  string config_file      = arg.GetString("config");

  Messenger::Instance()->Configure(mesg_thresholds);

  // Set DUNE param names inside framework       
  util::PopulateNameRegistry();

  // Set the random seeds                                                                                                          
  Rnd::Instance()->SetSeeds(arg);

  LOG("valor_dune", pNOTICE) << *Rnd::Instance();

  // Create file to store outputs
  TString outfilename = TString::Format("%s.root", output_name.c_str());

  // Get ND model & configure                
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(config_file);
  FitModelABC * model = elements->FitModel();

  // Get the specified fit parameter list (specifies which parameters are floated/fixed,                                              
  // parameter limits, initial values etc).                                                                                           
  FitParamList * fp = util::GetFitParameterList(fplname.c_str());

  // Generate predictions                                                                                                         
  Option_t * generate_opt = "+SB"; // also generate non-default (for fitting) predictions in extra binning schemes                 
  model->Generate(*fp,generate_opt);

  CompoundFitModel * cmodel = dynamic_cast<CompoundFitModel*>(model);
  for (int i = 0 ; i < cmodel->GetNSubModels() ; i++) {
    GenericSingleSampleFitModel * gmodel = dynamic_cast<GenericSingleSampleFitModel*>(cmodel->GetSubModel(i));
    gmodel->UpdateObservableBinningFromSimple();
  }

  // Write stuff out                              
  model->Write(outfilename,"valor",write_opt);

  std::cout<<"Done. Have a good day!"<<std::endl << "GO VALOR!!!" << std::endl;

}
