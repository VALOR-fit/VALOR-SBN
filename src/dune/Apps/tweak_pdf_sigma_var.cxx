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
             --kinevar             : The kine var to store 1D PDFs for

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
#include "dune/Conventions/Names.h"
#include "dune/Conventions/ArrIdx.h"
#include "dune/Elements/CompoundFitElements.h"
#include "dune/Elements/SingleSampleFitModelABC.h"

using namespace std;
using namespace valor;
using namespace valor::conv;


void GeneratePDFNominal(FitModelABC * model, CompoundFitModel * cm, FitParamList * fp, KineVar_t kv,
                        vector<TH1D *> & pdf, vector<vector<TH1D*>> & pdf_contrib);
void GeneratePDFTweaked(FitModelABC * model, CompoundFitModel * cm, FitParamList * fp, KineVar_t kv,
                        vector<vector<TH1D *> >  & pdf, vector<vector<vector<TH1D*>>> & pdf_contrib,
                        unsigned int ip, PhysParamId_t p, double tweak_dial);


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
  string kinevar_str      = arg.GetString("kinevar");

  KineVar_t kv = util::KineVarFromString(util::RemoveAllWhitespace(kinevar_str));
  if(kv == kvUndefined) {
    cerr << "ERROR: input kine var string [" << util::RemoveAllWhitespace(kinevar_str)
         << "] was not understood. Exiting." << std::endl;
    util::Die(-1);
  }

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

  // Get the parameters to vary
  std::vector<PhysParamId_t> param_set = util::GetParameterSet(params_to_tweak);
  assert(param_set.size());
  unsigned int n_params = param_set.size();

  // Vectors to store the spectra for the default, +/- 1 and 3 sigma variations
  // Total PDFs
  vector<TH1D *>          nom_pdf   (cm->GetNSubModels());
  vector<vector<TH1D *> > twk_pdf_p1(cm->GetNSubModels(), vector<TH1D*>(n_params));
  vector<vector<TH1D *> > twk_pdf_m1(cm->GetNSubModels(), vector<TH1D*>(n_params));
  vector<vector<TH1D *> > twk_pdf_p3(cm->GetNSubModels(), vector<TH1D*>(n_params));
  vector<vector<TH1D *> > twk_pdf_m3(cm->GetNSubModels(), vector<TH1D*>(n_params));

  // Now broken down by mode
  // TODO: This is getting horribly unwieldy. Write the hists directly to the output file instead of storing in these 1-3D vectors? Or will that be slow?
  vector<vector<TH1D*>>         nom_pdf_contrib   (cm->GetNSubModels(), vector<TH1D*>(conv::kNReacModes));                                    // [imodel][imode]
  vector<vector<vector<TH1D*>>> twk_pdf_contrib_p1(cm->GetNSubModels(), vector<vector<TH1D*>>(n_params, vector<TH1D*>(conv::kNReacModes)));   // [imodel][iparam][imode]
  vector<vector<vector<TH1D*>>> twk_pdf_contrib_m1(cm->GetNSubModels(), vector<vector<TH1D*>>(n_params, vector<TH1D*>(conv::kNReacModes)));
  vector<vector<vector<TH1D*>>> twk_pdf_contrib_p3(cm->GetNSubModels(), vector<vector<TH1D*>>(n_params, vector<TH1D*>(conv::kNReacModes)));
  vector<vector<vector<TH1D*>>> twk_pdf_contrib_m3(cm->GetNSubModels(), vector<vector<TH1D*>>(n_params, vector<TH1D*>(conv::kNReacModes)));

  const CorrelatedSystematics * syst = cm->GetSystematics();
  FitParamList * fp = util::GetFitParameterList(fplname.c_str(), fplopt.c_str(), syst);

  if (fp->Exists(conv::kPhypMixing12)) { fp->Update(conv::kPhypMixing12,mixing12); }
  if (fp->Exists(conv::kPhypMixing13)) { fp->Update(conv::kPhypMixing13,mixing13); }
  if (fp->Exists(conv::kPhypMixing23)) { fp->Update(conv::kPhypMixing23,mixing23); }
  if (fp->Exists(conv::kPhypDm12sq  )) { fp->Update(conv::kPhypDm12sq  ,dm12sq  ); }
  if (fp->Exists(conv::kPhypDm23sq  )) { fp->Update(conv::kPhypDm23sq  ,dm23sq  ); }
  if (fp->Exists(conv::kPhypCPV     )) { fp->Update(conv::kPhypCPV     ,deltacp ); }

  // Generate pdfs
  GeneratePDFNominal(model, cm, fp, kv, nom_pdf, nom_pdf_contrib);
  for (unsigned int ip = 0 ; ip < param_set.size() ; ip++) {
    PhysParamId_t p = param_set[ip];
    double bestfit = fp->InitValue(p);
    double sigma_err = syst->OneSigmaError(p);
    double tweak_p1 = bestfit + (1 * sigma_err);
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

    GeneratePDFTweaked(model, cm, fp, kv, twk_pdf_p1, twk_pdf_contrib_p1, ip, p, tweak_p1);
    GeneratePDFTweaked(model, cm, fp, kv, twk_pdf_m1, twk_pdf_contrib_m1, ip, p, tweak_m1);
    GeneratePDFTweaked(model, cm, fp, kv, twk_pdf_p3, twk_pdf_contrib_p3, ip, p, tweak_p3);
    GeneratePDFTweaked(model, cm, fp, kv, twk_pdf_m3, twk_pdf_contrib_m3, ip, p, tweak_m3);
  } // loop over params

  
  // Write to file (if requested)
  TFile * outfile = NULL;
  if (output_rootfile!="-" && output_rootfile!="none") {
    output_rootfile = util::ReplaceAll(output_rootfile,"[PARAMS]",params_to_tweak) + "_" + util::AsString(kv) + ".root";
    outfile = new TFile(output_rootfile.c_str(),"RECREATE");
    LOG("valor_dune",pNOTICE)<<"Writing to file: "<<output_rootfile;
  }
  if (outfile && outfile->IsOpen()) {
    for(unsigned int imodel = 0; imodel < cm->GetNSubModels(); imodel++) {
      SingleSampleFitModelABC * this_model = dynamic_cast<SingleSampleFitModelABC*>(cm->GetSubModel(imodel));
      Detector_t d = this_model->GetDetector();
      BeamConf_t b = this_model->GetBeam();
      Sample_t   s = this_model->GetSample();
      std::string model_name = util::nm::MdlName(d, b, s, util::KineSpaceFromKineVar(kv));

      TString save_name = TString::Format("env_sb_%s_%s", model_name.c_str(), "nom");
      nom_pdf[imodel]->Write(save_name.Data());

      // Write the nominal PDF broken down by mode contributions
      for(int im = 0; im < conv::kNReacModes; ++im) {
        conv::ReacMode_t m = util::ReacModeFromInt(im);
        if(m == conv::kmUndefined) { continue; }
        int mode_idx = util::ArrIdx::Instance()->ReacModeIdx(b, s, m);
        if(mode_idx < 0) { continue; }
        if(!nom_pdf_contrib[imodel][im]) { continue; }
        save_name = TString::Format("env_sb_%s_%s_%s", model_name.c_str(), util::AsString(m).c_str(), "nom");
        nom_pdf_contrib[imodel][im]->Write(save_name.Data());
      }

      for (unsigned int ip = 0 ; ip < param_set.size() ; ip++) {
        PhysParamId_t p = param_set[ip];
        std::string param_name = util::NameRegistry::Instance()->ParamAsStringVerySimple(p);

        // Write the total PDFs
        save_name = TString::Format("env_sb_%s_%s_%s", model_name.c_str(), param_name.c_str(), "p1" ); twk_pdf_p1 [imodel][ip]->Write(save_name.Data());
        save_name = TString::Format("env_sb_%s_%s_%s", model_name.c_str(), param_name.c_str(), "m1" ); twk_pdf_m1 [imodel][ip]->Write(save_name.Data());
        save_name = TString::Format("env_sb_%s_%s_%s", model_name.c_str(), param_name.c_str(), "p3" ); twk_pdf_p3 [imodel][ip]->Write(save_name.Data());
        save_name = TString::Format("env_sb_%s_%s_%s", model_name.c_str(), param_name.c_str(), "m3" ); twk_pdf_m3 [imodel][ip]->Write(save_name.Data());

        // Write the PDF broken down by mode contributions
        for(int im = 0; im < conv::kNReacModes; ++im) {
          conv::ReacMode_t m = util::ReacModeFromInt(im);
          if(m == conv::kmUndefined) { continue; }
          int mode_idx = util::ArrIdx::Instance()->ReacModeIdx(b, s, m);
          if (mode_idx < 0) { continue; }
          if(twk_pdf_contrib_p1 [imodel][ip][im]) {
            save_name = TString::Format("env_sb_%s_%s_%s_%s", model_name.c_str(), util::AsString(m).c_str(),
                                        param_name.c_str(), "p1");
            twk_pdf_contrib_p1[imodel][ip][im]->Write(save_name.Data());
          }
          if(twk_pdf_contrib_m1 [imodel][ip][im]) {
            save_name = TString::Format("env_sb_%s_%s_%s_%s", model_name.c_str(), util::AsString(m).c_str(),
                                        param_name.c_str(), "m1");
            twk_pdf_contrib_m1[imodel][ip][im]->Write(save_name.Data());
          }
          if(twk_pdf_contrib_p3 [imodel][ip][im]) {
            save_name = TString::Format("env_sb_%s_%s_%s_%s", model_name.c_str(), util::AsString(m).c_str(),
                                        param_name.c_str(), "p3");
            twk_pdf_contrib_p3[imodel][ip][im]->Write(save_name.Data());
          }
          if(twk_pdf_contrib_m3 [imodel][ip][im]) {
            save_name = TString::Format("env_sb_%s_%s_%s_%s", model_name.c_str(), util::AsString(m).c_str(),
                                        param_name.c_str(), "m3");
            twk_pdf_contrib_m3[imodel][ip][im]->Write(save_name.Data());
          }
        } //imode
      } // loop over tweaked params
    }//imodel

    outfile->Close();
    delete outfile;
  }

  LOG("valor_dune",pNOTICE)<<"Finished writing to file: "<<output_rootfile;
  std::cout <<"Done!"<<std::endl;
}
//________________________________________________________________________________________
void GeneratePDFNominal(FitModelABC * model, CompoundFitModel * cm, FitParamList * fp, KineVar_t kv, vector<TH1D*> & pdf,
                        vector<vector<TH1D*>> & pdf_contrib)
{
  cout << "\n\nGenerating nominal PDF:" << std::endl;
  model->ResetSystematics("all");
  fp->FromPhysParamList(model->Tweaks(),"current-silent");

  // Generate predictions
  cout << "with fit param list:" << std::endl;
  fp->Print(cout);
  model->Generate(*fp,"+SB");

  // Array to store results
  TObjArray * array = new TObjArray();
  array->SetOwner(true);

  // Write stuff out
  Option_t * write_opt = "pdfcs_rf-pdfts_rf+SB";
  if (util::IsTrue(kv)) { write_opt = "pdfcs_rf+SB"; }    // The true PDFs don't have totals in GSSFM, only the mode breakdown // TODO: util::binning::Make1DHistogram currently doesn't work with truth...
  model->Write(array,"nom",write_opt);

  // Pick results wanted
  for(unsigned int imodel = 0; imodel < cm->GetNSubModels(); imodel++) {
    SingleSampleFitModelABC * this_model = dynamic_cast<SingleSampleFitModelABC*>(cm->GetSubModel(imodel));
    Detector_t d = this_model->GetDetector();
    BeamConf_t b = this_model->GetBeam();
    Sample_t   s = this_model->GetSample();

    // Get the total PDF
    std::string model_name = util::nm::MdlName(d, b, s, util::KineSpaceFromKineVar(kv));
    if (util::IsReco(kv)) {
      TString name_tot     = TString::Format("nom_pdfts_sb_rf_%s_%s", model_name.c_str(), util::AsString(kv).c_str());
      TH1D * curr_pdf_tot = (TH1D*) array->FindObject(name_tot.Data());
      if (!curr_pdf_tot) {
        cerr<<"Could not find histogram "<<name_tot<<endl;
        exit(-1);
      }
      else {
        pdf[imodel] = new TH1D(*curr_pdf_tot);
      }
    }


    // Get the PDF broken down by mode contributions
    for(int im = 0; im < conv::kNReacModes; ++im) {
      conv::ReacMode_t m = util::ReacModeFromInt(im);
      if(m == conv::kmUndefined) { continue; }
      int mode_idx = util::ArrIdx::Instance()->ReacModeIdx(b, s, m);
      if (mode_idx < 0) {
        pdf_contrib[imodel][im] = nullptr;
      }
      else {
        TString name_contrib = TString::Format("nom_pdfcs_sb_rf_%s_%s_%s", model_name.c_str(), util::AsString(kv).c_str(), util::AsString(m).c_str());
        TH1D * curr_pdf_contrib = (TH1D*) array->FindObject(name_contrib.Data());
        if (!curr_pdf_contrib) {
          cerr<<"Could not find histogram "<<name_contrib<<endl;
          exit(-1);
        }
        else {
          pdf_contrib[imodel][im] = new TH1D(*curr_pdf_contrib);
        }
      }
    } //imode
  } //imodel
  array->Clear("C");
  delete array;
}
//________________________________________________________________________________________
void GeneratePDFTweaked(FitModelABC * model, CompoundFitModel * cm, FitParamList * fp, KineVar_t kv,
                        vector<vector<TH1D *> >  & pdf, vector<vector<vector<TH1D*>>> & pdf_contrib,
                        unsigned int ip, PhysParamId_t p, double tweak_dial)
{
  cout << "\n\nGenerating PDF with tweak dial = " << tweak_dial << std::endl;
  model->ResetSystematics("all");

  model->TweakSystematic(p, tweak_dial, "");
  fp->FromPhysParamList(model->Tweaks(),"current-silent");

  // Generate predictions
  model->Generate(*fp,"+SB");

  // Array to store results
  TObjArray * array = new TObjArray();
  array->SetOwner(true);

  // Write stuff out
  Option_t * write_opt = "pdfcs_rf-pdfts_rf+SB";
  if (util::IsTrue(kv)) { write_opt = "pdfcs_rf+SB"; }    // The true PDFs don't have totals in GSSFM, only the mode breakdown
  model->Write(array,"curr",write_opt);

  // Pick results wanted
  for(unsigned int imodel = 0; imodel < cm->GetNSubModels(); imodel++) {
    SingleSampleFitModelABC * this_model = dynamic_cast<SingleSampleFitModelABC*>(cm->GetSubModel(imodel));
    Detector_t d = this_model->GetDetector();
    BeamConf_t b = this_model->GetBeam();
    Sample_t   s = this_model->GetSample();

    // Get the total PDF
    std::string model_name = util::nm::MdlName(d, b, s, util::KineSpaceFromKineVar(kv));
    if (util::IsReco(kv)) {
      TString name = TString::Format("curr_pdfts_sb_rf_%s_%s", model_name.c_str(), util::AsString(kv).c_str());
      TH1D * curr_pdf = (TH1D*) array->FindObject(name.Data());
      if (!curr_pdf) {
        cerr<<"Could not find histogram "<<name<<endl;
        exit(-1);
      }
      else {
        pdf[imodel][ip] = new TH1D(*curr_pdf);
      }
    }

    //Get the PDF broken down by mode contributions
    for(int im = 0; im < conv::kNReacModes; ++im) {
      conv::ReacMode_t m = util::ReacModeFromInt(im);
      if(m == conv::kmUndefined) { continue; }
      int mode_idx = util::ArrIdx::Instance()->ReacModeIdx(b, s, m);
      if (mode_idx < 0) {
        pdf_contrib[imodel][ip][im] = nullptr;
      }
      else {
        TString name_contrib = TString::Format("curr_pdfcs_sb_rf_%s_%s_%s", model_name.c_str(), util::AsString(kv).c_str(), util::AsString(m).c_str());
        TH1D * curr_pdf_contrib = (TH1D*) array->FindObject(name_contrib.Data());
        if (!curr_pdf_contrib) {
          cerr<<"Could not find histogram "<<name_contrib<<endl;
          exit(-1);
        }
        else {
          pdf_contrib[imodel][ip][im] = new TH1D(*curr_pdf_contrib);
        }
      }
    } //imode
  } //imodel
  array->Clear("C");
  delete array;
}
//________________________________________________________________________________________
