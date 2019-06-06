//____________________________________________________________________________
/*!

\app       valor_dune-tweak_pdf_sigma_var

\brief     Vary the MC spectra by setting systematics to +/- 1 and 3 sigma

\options     --output              : Where to save tweaked histograms to. [def: sigma_var_[PARAMS].root]
             --fit-param-list      : Fit parameter list [def: "nuosc3f"]
             --fit-param-opt       : Options used when setting up the FitParamList
                                     [def: "NONE"]
             --config              : Analysis configuration file [required]
             --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]
             --params              : Which parameters to tweak [def: allsyst]

             --input-mixing12,etc  : Option to give input values to osc params (in .arg)

             --load-prior-from-file : Option for file to give constrained prior matrix [ use default prior ]
             --prior-fit-number     : Option to specify the entry in the tree for above file [ 0 ]
             
             [--nthreads ]         : Number of CPU threads to use [ std::thread::hardware_concurrency ]
             

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool
           Francis Bench <f.bench \at liverpool.ac.uk>
           University of Liverpool

\created   June 2019

\copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// root
#include "TFile.h"
#include "TObjArray.h"
#include "TString.h"
#include "TSystem.h"
// fmwk
#include "valor/Conventions/Opt.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/FitCore/CorrelatedSystematics.h"
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
#include "valor/Utilities/VThreadPool.h"
#include "valor/Utilities/NameRegistry.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Ntuple/StdFitNtp.h"
// dune
#include "dune/Utilities/UtlParam.h"
#include "dune/Conventions/OscParamValues.h"
#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Elements/CompoundFitElements.h"
#include "dune/Elements/SingleSampleFitModelABC.h"

using namespace std;
using namespace valor;
using namespace valor::conv;


void GeneratePDFNominal(FitModelABC * model, CompoundFitModel * cm, FitParamList * fp, vector<TH1D *> & pdf, vector<TH1D *> & pdf_werr);
void GeneratePDFTweaked(FitModelABC * model, CompoundFitModel * cm, FitParamList * fp, vector<vector<TH1D *> >  & pdf, PhysParamId_t p, double tweak_dial);


int main(int argc, char ** argv)
{
  Env::Instance()->AutoSet("dune");
  valor::util::PrintBanner(Env::Instance()->Banner(),500);
 
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/tweak_pdf_sigma_var.arg:$VALOR_DUNE/config/apps/seeds.arg");
  LOG("valor_dune", pNOTICE) << arg;
  
  // Read the command line
  int n_threads           = arg.GetInt("nthreads");
  string fplname          = arg.GetString("fit-param-list");
  string fplopt           = arg.GetString("fit-param-opt");
  string output_rootfile  = arg.GetString("output");
  string params_to_tweak  = arg.GetString("params");
  
  string read_prior_from_file = arg.GetString("load-prior-from-file");
  int prior_fit_number = arg.GetInt("prior-fit-number");
  
  std::string mesg_thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(mesg_thresholds);
  
  // Set up the thread pool
  if(n_threads>0) {//without n-cores specified, use as many as the host has
    util::VThreadPool::Instance()->SetNThreads(n_threads);
  }
  
  // Set the random seeds
  Rnd::Instance()->SetSeeds(arg);
  
  // And OA parameters
  Opt::Instance()->gMassHierarchyAssumed = ( (arg.GetBool("inverted"))     ? conv::kNmhInverted      : conv::kNmhNormal);
  Opt::Instance()->gOscDmsqScheme        = ( (arg.GetBool("foglilisi"))    ? conv::kNuDmsqFogliLisi  : conv::kNuDmsq12andAbs23);

  // TODO: Update this with the new input param search
  double mixing12 = arg.GetDouble("input-mixing12");
  double mixing13 = arg.GetDouble("input-mixing13");
  double mixing23 = arg.GetDouble("input-mixing23");
  double dm12sq   = arg.GetDouble("input-dm12sq");
  double dm23sq   = arg.GetDouble("input-dm23sq");
  double deltacp  = arg.GetDouble("input-deltaCP");
  
  // Config
  std::string config_path = util::CompleteConfigPath(arg.GetString("config"));

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Reading analysis configuration from: " << config_path << endl;
  cout << "- Model parameter list used : " << fplname << endl;
  
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(config_path.c_str());
  FitModelABC * model = elements->FitModel();
  CompoundFitModel * cm = dynamic_cast<CompoundFitModel*>(model);
  assert(cm);
  
  TFile * postfit_matrix_file = NULL;
  if (read_prior_from_file!="-" && read_prior_from_file!="none") {
    postfit_matrix_file = new TFile(read_prior_from_file.c_str());
    FitParamList * fp = new FitParamList;
    cout << "Using postfit matrix "<<prior_fit_number<<" from "<<read_prior_from_file<<endl;
    TTree * fit_tree = (TTree*)postfit_matrix_file->Get("valor_dune_nd_ntp");
    assert(fit_tree);
    fit_tree->SetBranchAddress("best_fit_params",&fp);
    fit_tree->GetEntry(prior_fit_number);
    TMatrixD * cov_m = new TMatrixD(*(fp->GetCovMatrix()));
    
    if (cov_m->GetNrows() != fp->Size()) {
      std::cerr<<"Input matrix has "<<cov_m->GetNrows()<<" entries, need "<<fp->Size()<<endl;
      util::Die(-1);
    }
    cm->GetSystematics()->SetCovMatrix(*cov_m);
    cout<<"Read postfit matrix."<<endl;
  }
  else {
    cout << "Using prefit"<<endl;
  }

  // Vectors to store the spectra for the default, +/- 1 and 3 sigma variations
  vector<TH1D *> nom_pdf_werr;
  vector<TH1D *> nom_pdf     ;
  vector<vector<TH1D *> > twk_pdf_p1(cm->GetNSubModels());
  vector<vector<TH1D *> > twk_pdf_m1(cm->GetNSubModels());
  vector<vector<TH1D *> > twk_pdf_p3(cm->GetNSubModels());
  vector<vector<TH1D *> > twk_pdf_m3(cm->GetNSubModels());

  const CorrelatedSystematics * syst = cm->GetSystematics();
  FitParamList * fp = util::GetFitParameterList(fplname.c_str(), fplopt.c_str(), syst);

  if (fp->Exists(conv::kPhypMixing12)) { fp->Update(conv::kPhypMixing12,mixing12); }
  if (fp->Exists(conv::kPhypMixing13)) { fp->Update(conv::kPhypMixing13,mixing13); }
  if (fp->Exists(conv::kPhypMixing23)) { fp->Update(conv::kPhypMixing23,mixing23); }
  if (fp->Exists(conv::kPhypDm12sq  )) { fp->Update(conv::kPhypDm12sq  ,dm12sq  ); }
  if (fp->Exists(conv::kPhypDm23sq  )) { fp->Update(conv::kPhypDm23sq  ,dm23sq  ); }
  if (fp->Exists(conv::kPhypCPV     )) { fp->Update(conv::kPhypCPV     ,deltacp ); }

  // Get the parameters to vary
  std::vector<PhysParamId_t> param_set = util::GetParameterSet(params_to_tweak);
  assert(param_set.size());

  // Generate pdfs
  GeneratePDFNominal(model, cm, fp, nom_pdf, nom_pdf_werr);
  for (unsigned int ip = 0 ; ip < param_set.size() ; ip++) {
    PhysParamId_t p = param_set[ip];
    double bestfit = fp->InitValue(p);                    // TODO: check that the T2K init values are correct     TODO: set the init value for SKEscale to 0
    double sigma_err = syst->OneSigmaError(p);
    double tweak_p1 = bestfit + (1 * sigma_err);   // TODO: check that the T2K errors are correct
    double tweak_m1 = bestfit - (1 * sigma_err);
    double tweak_p3 = bestfit + (3 * sigma_err);
    double tweak_m3 = bestfit - (3 * sigma_err);

    LOG("valor_dune", pNOTICE)
      << "Tweak systematic parameter: "  << util::NameRegistry::Instance()->ParamAsString(p)
      << "\n  Nominal value = "          << bestfit
      << "\n  sigma error = "            << sigma_err
      << "\n  nominal +1 sigma tweak = " << tweak_p1
      << "\n  nominal -1 sigma tweak = " << tweak_m1
      << "\n  nominal +3 sigma tweak = " << tweak_p3
      << "\n  nominal -3 sigma tweak = " << tweak_m3;

    GeneratePDFTweaked(model, cm, fp, twk_pdf_p1, p, tweak_p1);
    GeneratePDFTweaked(model, cm, fp, twk_pdf_m1, p, tweak_m1);
    GeneratePDFTweaked(model, cm, fp, twk_pdf_p3, p, tweak_p3);
    GeneratePDFTweaked(model, cm, fp, twk_pdf_m3, p, tweak_m3);

    // bestfit = 1 for all SKDetFSI params except SKEscale, which is 0
    // skexp.GetBANFF()->InitialValues()(idx); for BANFF params
    //tweak_p1 = bestfit + (1 * sqrt(skexp.GetSuperkDetectorFSI()->CovMatrix()(idx,idx)));  // skdetfsi
    //tweak_m1 = bestfit - (1 * sqrt(skexp.GetSuperkDetectorFSI()->CovMatrix()(idx,idx)));  // skdetfsi
    // for kNuisBANFFShape2p2h, tweak_p1 = bestfit + 0.5 and   tweak_p3 = bestfit + 1.0

  } // loop over params

  
  // Write to file (if requested)
  TFile * outfile = NULL;
  if (output_rootfile!="-" && output_rootfile!="none") {
    output_rootfile = util::ReplaceAll(output_rootfile,"[PARAMS]",params_to_tweak);
    outfile = new TFile(output_rootfile.c_str(),"RECREATE");
    LOG("valor_dune",pNOTICE)<<"Writing to file: "<<output_rootfile;
  }
  
  for(unsigned int imodel = 0; imodel < cm->GetNSubModels(); imodel++) {
    SingleSampleFitModelABC * this_model = dynamic_cast<SingleSampleFitModelABC*>(cm->GetSubModel(imodel));
    BeamConf_t b = this_model->GetBeam();
    Sample_t   s = this_model->GetSample();

    TString name_nom = TString::Format("env_sb_%s_%s",
                                       util::AsString(b).c_str(), util::AsString(s).c_str());

    // TODO: Work-around until util::binning::contract is fixed
    if(nom_pdf[imodel] != nullptr) { nom_pdf[imodel]->Write((name_nom+"_nom").Data()); } else { LOG("valor_dune",pNOTICE)<<"Not saving null PDF [" << (name_nom+"_nom").Data() << "]"; }

    for (unsigned int ip = 0 ; ip < param_set.size() ; ip++) {
      PhysParamId_t p = param_set[ip];
      if (outfile->IsOpen()) {
        TString name = TString::Format("env_sb_%s_%s_%s",
                                       util::AsString(b).c_str(), util::AsString(s).c_str(),
                                       util::NameRegistry::Instance()->ParamAsStringVerySimple(p) );
        // TODO: Work-around until util::binning::contract is fixed
        if(twk_pdf_p1 [imodel][ip] != nullptr) { twk_pdf_p1 [imodel][ip]->Write((name+"_p1" ).Data()); } else { LOG("valor_dune",pNOTICE)<<"Not saving null PDF [" << (name+"_p1" ).Data() << "]"; }
        if(twk_pdf_m1 [imodel][ip] != nullptr) { twk_pdf_m1 [imodel][ip]->Write((name+"_m1" ).Data()); } else { LOG("valor_dune",pNOTICE)<<"Not saving null PDF [" << (name+"_m1" ).Data() << "]"; }
        if(twk_pdf_p3 [imodel][ip] != nullptr) { twk_pdf_p3 [imodel][ip]->Write((name+"_p3" ).Data()); } else { LOG("valor_dune",pNOTICE)<<"Not saving null PDF [" << (name+"_p3" ).Data() << "]"; }
        if(twk_pdf_m3 [imodel][ip] != nullptr) { twk_pdf_m3 [imodel][ip]->Write((name+"_m3" ).Data()); } else { LOG("valor_dune",pNOTICE)<<"Not saving null PDF [" << (name+"_m3" ).Data() << "]"; }
      }
    } // loop over tweaked params
  }//imodel
  
  if (outfile) {
    outfile->Close();
    delete outfile;
  }
  
  std::cout <<"Done!"<<std::endl;
}
//________________________________________________________________________________________
void GeneratePDFNominal(FitModelABC * model, CompoundFitModel * cm, FitParamList * fp, vector<TH1D *> & pdf, vector<TH1D *> & pdf_werr)
{
  model->ResetSystematics("all");
  fp->FromPhysParamList(model->Tweaks(),"current");

  // Generate predictions
  model->Generate(*fp,"+SB");

  // Array to store results
  TObjArray * array = new TObjArray();
  array->SetOwner(true);

  // Write stuff out
  model->Write(array,"curr","pdfts_rf +SB");

  // Pick results wanted
  for(unsigned int imodel = 0; imodel < cm->GetNSubModels(); imodel++) {
    SingleSampleFitModelABC * this_model = dynamic_cast<SingleSampleFitModelABC*>(cm->GetSubModel(imodel));
    BeamConf_t b = this_model->GetBeam();
    Sample_t   s = this_model->GetSample();
    TString name = TString::Format("curr_pdfts_sb_rf_%s_%s",
                                   util::AsString(b).c_str(), util::AsString(s).c_str());
    TH1D * curr_pdf = (TH1D*) array->FindObject(name.Data());
    if (!curr_pdf) {
      cerr<<"Could not find histogram "<<name<<endl;
      //exit(-1);
      // TODO: Work-around until util::binning::contract is fixed
      pdf_werr.push_back(nullptr);
      pdf     .push_back(nullptr);
    }
    else {
      pdf_werr.push_back(new TH1D(*curr_pdf));
      pdf     .push_back(new TH1D(*curr_pdf));
    }
  } //imodel
  array->Clear("C");
  delete array;
}
//________________________________________________________________________________________
void GeneratePDFTweaked(FitModelABC * model, CompoundFitModel * cm, FitParamList * fp, vector<vector<TH1D *> >  & pdf, PhysParamId_t p, double tweak_dial)
{
  model->ResetSystematics("all");

  model->TweakSystematic(p, tweak_dial, "");
  fp->FromPhysParamList(model->Tweaks(),"current");

  // Generate predictions
  model->Generate(*fp,"+SB");

  // Array to store results
  TObjArray * array = new TObjArray();
  array->SetOwner(true);

  // Write stuff out
  // TODO: Writing with PDFTS is currently broken for samples with 2D binning, as util::binning::contract is broken (see Git issue #5). So until that's fixed, this app is broken
  model->Write(array,"curr","pdfts_rf +SB");

  // Pick results wanted
  for(unsigned int imodel = 0; imodel < cm->GetNSubModels(); imodel++) {
    SingleSampleFitModelABC * this_model = dynamic_cast<SingleSampleFitModelABC*>(cm->GetSubModel(imodel));
    BeamConf_t b = this_model->GetBeam();
    Sample_t   s = this_model->GetSample();
    TString name = TString::Format("curr_pdfts_sb_rf_%s_%s",
                                   util::AsString(b).c_str(), util::AsString(s).c_str());
    TH1D * curr_pdf = (TH1D*) array->FindObject(name.Data());
    if (!curr_pdf) {
      // TODO: Work-around until util::binning::contract is fixed
      cerr<<"Could not find histogram "<<name<<endl;
      //exit(-1);
      pdf[imodel].push_back(nullptr);   // TODO: add a check for nullptr
    }
    else {
      pdf[imodel].push_back(new TH1D(*curr_pdf));
    }
  } //imodel
  array->Clear("C");
  delete array;
}
//________________________________________________________________________________________
