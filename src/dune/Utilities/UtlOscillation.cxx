#include "dune/Utilities/UtlOscillation.h"

#include <algorithm>

#include "valor/Messenger/Messenger.h"
#include "valor/Conventions/NuOscDmsqScheme.h"
#include "valor/Conventions/NuOscDeltaCP.h"
#include "valor/Conventions/NuOscDmsqScheme.h"
#include "valor/Conventions/NuMassHierarchy.h"
#include "valor/Conventions/Opt.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/NameRegistry.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/UtlNumStat.h"

#include <TSystem.h>
#include <TMath.h>

namespace valor
{
namespace util
{
namespace oscillation
{
void SetOscillationParameters(CmdLnArgList& arg, FitParamList& fpl)
{
   string osc_parameters[7] = { "mixing12", "mixing13", "mixing23", "dm23sq",
      "dm12sq", "dm13sq", "cpv" };

   string free_param1 = arg.GetString("fit-param1");
   string free_param2 = arg.Exists("fit-param2") ? arg.GetString("fit-param2") : "";

   for(int i = 0; i < 7; ++i)
   {
      valor::conv::PhysParamId_t p = util::NameRegistry::Instance()->PhysParamFromString(
            osc_parameters[i].c_str());
      if(fpl.Exists(p))
      {
         double fix_value = arg.GetDouble(TString::Format("fix-at-%s",
                  osc_parameters[i].c_str()).Data());
         double min_value = util::OscParamMinValue(p);
         double max_value = util::OscParamMaxValue(p);
         if(fix_value >= min_value && fix_value < max_value)
         {
            fpl.Update(p, fix_value);
            fpl.SetInitValue(p, fix_value);
            fpl.FixParameter(p);
            LOG("UtlOscillation", pNOTICE) << "Setting fixed parameter "
                                           << util::NameRegistry::Instance()->ParamAsString(p) << " := " << fix_value;
         }
         else if(free_param1 == osc_parameters[i] ||
            free_param2 == osc_parameters[i])
         {
            double free_value = 0.0;
            if(free_param1 == osc_parameters[i])
            {
               free_value = arg.GetDouble("fit-param1-value");
            }
            else
            {
               if(arg.Exists("fit-param2-value"))
               {
                  free_value = arg.GetDouble("fit-param2-value");
               }
               else
               {
                  LOG("UtlOscillation", pERROR) << "--fit-param2 specified " <<
                     "without accompanying --fit-param2-value.";
                  exit(1);
               }
            }
            fpl.Update(p, free_value);
            fpl.SetInitValue(p, free_value);
            fpl.FreeParameter(p);
            LOG("UtlOscillation", pNOTICE) << "Setting free parameter " <<
              util::NameRegistry::Instance()->ParamAsString(p) << " := " << free_value;
         }
         else
         {
            fpl.SetDoMarg(p, true);
            LOG("UtlOscillation", pNOTICE) << "Setting marginalised parameter " <<
              util::NameRegistry::Instance()->ParamAsString(p);
         }
      }
   }
}

//____________________________________________________________________________
void SetOscillationParameterPriors(CmdLnArgList& arg, FitParamList& fpl)
{
   // Read in the priors XML file
   std::string prior_file_name = arg.GetString("prior-file");
   std::string file_priors_full = util::CompleteConfigPath(prior_file_name);

   // Check that the prior file exists, either in the config directory or the current directory
   FileStat_t dummy;
   if (gSystem->GetPathInfo(file_priors_full.c_str(), dummy))
   {
      file_priors_full = prior_file_name.c_str();
      if (gSystem->GetPathInfo(file_priors_full.c_str(), dummy)) {
         LOG("UtlOscillation", pERROR) << "Prior config file not found: " << prior_file_name;
         exit(1);
      }
   }

   // Parse the input XML priors file
   TXMLEngine* xmleng = new TXMLEngine;
   XMLDocPointer_t xmldoc = xmleng->ParseFile(file_priors_full.c_str());
   if (xmldoc==0) {
      LOG("UtlOscillation", pERROR) << "Can not parse input XML file [" << file_priors_full << "]";
      exit(1);
   }
   XMLNodePointer_t root_node = xmleng->DocGetRootElement(xmldoc);
   const char * list_name_cstr = xmleng->GetAttr(root_node,"name");
   LOG("UtlOscillation", pNOTICE) << "Reading priors from element list named" << list_name_cstr;

   XMLNodePointer_t curr_node = xmleng->GetChild(root_node);
   int npriors_set = 0;
   while(curr_node) {
      string curr_node_name = xmleng->GetNodeName(curr_node);
      if(!strcmp(curr_node_name.c_str(),"prior")) {
         bool success = util::oscillation::SetSinglePrior(xmleng,curr_node,fpl);
         if (!success) {
            LOG("UtlOscillation", pERROR) << "Failed to read prior list. Exiting.";
            exit(1);
         }
         npriors_set++;
      }
      curr_node = xmleng->GetNext(curr_node);
   }

   // TODO: Put in some check to see if we've set priors on every oscillation parameter in our phys hypothesis
}

//____________________________________________________________________________
bool SetSinglePrior(TXMLEngine* xmleng, XMLNodePointer_t top_node, FitParamList& fpl)
{
   // First read the information that's common to each prior type
   string param_names    = "";  // Comma-separated list of simple parameter names
   string prior_type     = "";  // 'flat', 'gaus', or 'user'
   string opt            = "";
   XMLNodePointer_t curr_node = xmleng->GetChild(top_node);
   while(curr_node) {
      string curr_node_name = xmleng->GetNodeName(curr_node);
      if(xmleng->GetNodeContent(curr_node)) {
         string content = util::TrimSpaces(xmleng->GetNodeContent(curr_node));
         if(curr_node_name == "params") { param_names = content; }
         if(curr_node_name == "type"  ) { prior_type = content; }
         if(curr_node_name == "scheme") { opt        = content; }
      }
      curr_node = xmleng->GetNext(curr_node);
   }

   // Now read the information that's specific to each prior type
   string prior_attribute1 = "";    // If type = flat, this is the lower end of the range. If type = gaus, this is the mean.  If type = user, this is the NH prior file
   string prior_attribute2 = "";    // If type = flat, this is the upper end of the range. If type = gaus, this is the sigma. If type = user, this is the IH prior file
   string prior_attribute3 = "";    // If type = user, this is the prior hist name. Otherwise this stays as an empty string
   curr_node = xmleng->GetChild(top_node);   // Put the current node back to the top of the list
   while(curr_node) {
      string curr_node_name = xmleng->GetNodeName(curr_node);
      if(xmleng->GetNodeContent(curr_node)) {
         string content = util::TrimSpaces(xmleng->GetNodeContent(curr_node));
         if(prior_type == "flat") {
            if(curr_node_name == "low" ) { prior_attribute1 = content; }
            if(curr_node_name == "high") { prior_attribute2 = content; }
         }
         else if(prior_type == "gaus") {
            if(curr_node_name == "mean" ) { prior_attribute1 = content; }
            if(curr_node_name == "sigma") { prior_attribute2 = content; }
         }
         else if(prior_type == "user") {
            if(curr_node_name == "file_nh"  ) { prior_attribute1 = content; }
            if(curr_node_name == "file_ih"  ) { prior_attribute2 = content; }
            if(curr_node_name == "hist_name") { prior_attribute3 = content; }
         }
         else {
            LOG("UtlOscillation", pERROR) << "Could not understand the prior type [" << prior_type << "]";
            exit(1);
         }
      }
      curr_node = xmleng->GetNext(curr_node);
   }

   // Check that we read the correct number of attributes for each prior type
   if(prior_type == "flat" && (prior_attribute1 == "" || prior_attribute2 == "" || prior_attribute3 != "")) {
      LOG("UtlOscillation", pERROR) << "Something went wrong when setting the flat prior named [" << param_names << "]";
      exit(1);
   }
   else if(prior_type == "gaus" && (prior_attribute1 == "" || prior_attribute2 == "" || prior_attribute3 != "")) {
      LOG("UtlOscillation", pERROR) << "Something went wrong when setting the Gaussian prior named [" << param_names << "]";
      exit(1);
   }
   else if(prior_type == "user" && (prior_attribute1 == "" || prior_attribute2 == "" || prior_attribute3 == "")) {
      LOG("UtlOscillation", pERROR) << "Something went wrong when setting the user prior named [" << param_names << "]";
      exit(1);
   }

   // Get the parameter(s) that we'll apply this prior to
   const util::NameRegistry * nr = util::NameRegistry::Instance();
   std::vector<std::string> tokens = util::Tokens(param_names, ",");
   std::vector<conv::PhysParamId_t> params;
   for(std::string param_name : tokens) {
      param_name = util::RemoveAllWhitespace(param_name);
      conv::PhysParamId_t p = nr->PhysParamFromString(param_name);
      if(p == conv::kPhypUndefined) {
         LOG("UtlOscillation", pERROR) << "Could not parse parameter [" << param_name << "]";
         exit(1);
      }
      params.push_back(p);
   }

   // Check that the number of parameters is as expected
   if((prior_type == "flat" || prior_type == "gaus") && params.size() != 1) {
      LOG("UtlOscillation", pERROR) << "The number of parameters specified for flat or Gaussian prior named [" << param_names << "] was != 1";
      exit(1);
   }
   else if(!(params.size() == 1 || params.size() == 2)){
      LOG("UtlOscillation", pERROR) << "The number of parameters specified for user prior named [" << param_names << "] was not 1 or 2";
      exit(1);
   }

   // Check the dmsq scheme for all prior. Also check the mixing param scheme and phase scheme for user priors
   // TODO is this the correct handling for the 'auto' dmsq scheme?
   if(util::IsMassSplitting(params[0]) &&
         !(opt.find("auto") != std::string::npos) &&
           opt.find(util::DmsqSchemeAsStringSimple(Opt::Instance()->gOscDmsqScheme)) == std::string::npos ) {
      LOG("UtlOscillation", pERROR) << "The input prior dmsq scheme [" << opt << "] did not match the set scheme";
      exit(1);
   }
   if(prior_type == "user" &&
         util::IsMixingAngle(params[0]) &&
         opt.find(util::MixingTypeAsStringSimple(Opt::Instance()->gOscMixingParamChoice)) == std::string::npos) {
      LOG("UtlOscillation", pERROR) << "The input prior mixing angle scheme [" << opt << "] did not match the set scheme";
      exit(1);
   }
   if(prior_type == "user" &&
         util::IsPhase(params[0]) &&
         opt.find(util::CPVChoiceAsStringSimple(Opt::Instance()->gOscDeltaCP)) == std::string::npos) {
      LOG("UtlOscillation", pERROR) << "The input delta scheme [" << opt << "] did not match the set scheme";
      exit(1);
   }
   if(params.size() == 2) {
      if(util::IsMassSplitting(params[1]) &&
            !(opt.find("auto") != std::string::npos) &&
              opt.find(util::DmsqSchemeAsStringSimple(Opt::Instance()->gOscDmsqScheme)) == std::string::npos ) {
         LOG("UtlOscillation", pERROR) << "The input prior dmsq scheme [" << opt << "] did not match the set scheme";
         exit(1);
      }
      if(prior_type == "user" &&
            util::IsMixingAngle(params[1]) &&
            opt.find(util::MixingTypeAsStringSimple(Opt::Instance()->gOscMixingParamChoice)) == std::string::npos) {
         LOG("UtlOscillation", pERROR) << "The input prior mixing angle scheme [" << opt << "] did not match the set scheme";
         exit(1);
      }
      if(prior_type == "user" &&
            util::IsPhase(params[1]) &&
            opt.find(util::CPVChoiceAsStringSimple(Opt::Instance()->gOscDeltaCP)) == std::string::npos) {
         LOG("UtlOscillation", pERROR) << "The input delta scheme [" << opt << "] did not match the set scheme";
         exit(1);
      }
   }

   // Set the prior
   if(prior_type == "flat") {
      double low  = atof(prior_attribute1.c_str());
      double high = atof(prior_attribute2.c_str());

      // Convert single to double angle (or vice-versa) based on settings, if needed
      if(util::IsMixingAngle(params[0])) {
         if(Opt::Instance()->gOscMixingParamChoice == util::MixingTypeFromString("sinsq2theta") &&
               opt.find("sinsqtheta") != std::string::npos) {
            // Convert input prior limits from single angle to double angle
            low  = util::SingleAngleToDoubleAngle(low);
            high = util::SingleAngleToDoubleAngle(high);
         }
         else if(Opt::Instance()->gOscMixingParamChoice == util::MixingTypeFromString("sinsqtheta") &&
               opt.find("sinsq2theta") != std::string::npos) {
            // Convert input prior limits from double angle to single angle
            low  = util::DoubleAngleToSingleAngle(low);
            high = util::DoubleAngleToSingleAngle(high);
         }
      }
      // Convert delta to sin(delta) (or vice-versa) based on settings, if needed
      else if(util::IsPhase(params[0])) { //gOscDeltaCP           = util::CPVChoiceFromString(cpvchoice);
         if(Opt::Instance()->gOscDeltaCP == util::CPVChoiceFromString("sindelta") &&
               opt.find("delta") != std::string::npos) {
            // Convert input prior limits from delta to sin(delta)
            low  = TMath::Sin(low);
            high = TMath::Sin(high);
         }
         else if(Opt::Instance()->gOscDeltaCP == util::CPVChoiceFromString("delta") &&
                 opt.find("sindelta") != std::string::npos) {
            // Convert input prior limits from sin(delta) to delta
            low  = TMath::ASin(low);
            high = TMath::ASin(high);
         }
      }

      fpl.SetPriorMode   (params[0], "flat");
      fpl.SetMinValueFlat(params[0], low   );
      fpl.SetMaxValueFlat(params[0], high  );
      LOG("UtlOscillation", pNOTICE) << "Setting flat prior for param " << param_names
                                     << ": [" << low << ", " << high << "]";
   }
   else if(prior_type == "gaus") {
      double mean  = atof(prior_attribute1.c_str());
      double sigma = atof(prior_attribute2.c_str());

      // Convert single to double angle (or vice-versa) based on settings, if needed
      if(Opt::Instance()->gOscMixingParamChoice == util::MixingTypeFromString("sinsq2theta") &&
            opt.find("sinsqtheta") != std::string::npos) {
         // Convert input prior mean and sigma from single angle to double angle
         sigma = util::SingleAngleSigmaToDoubleAngleSigma(mean, sigma); // sigma must be converted first, as it requires the un-converted mean!
         mean  = util::SingleAngleToDoubleAngle(mean);
      }
      else if(Opt::Instance()->gOscMixingParamChoice == util::MixingTypeFromString("sinsqtheta") &&
              opt.find("sinsq2theta") != std::string::npos) {
         // Convert input prior mean and sigma from double angle to single angle
         sigma = util::DoubleAngleSigmaToSingleAngleSigma(mean, sigma);
         mean  = util::DoubleAngleToSingleAngle(mean);
      }
      // Convert delta to sin(delta) (or vice-versa) based on settings, if needed
      else if(util::IsPhase(params[0])) { //gOscDeltaCP           = util::CPVChoiceFromString(cpvchoice);
         if(Opt::Instance()->gOscDeltaCP == util::CPVChoiceFromString("sindelta") &&
               opt.find("delta") != std::string::npos) {
            // Convert input prior limits from delta to sin(delta)
            sigma = util::PhaseSigmaToSinPhaseSigma(mean, sigma);
            mean  = TMath::Sin(mean);
         }
         else if(Opt::Instance()->gOscDeltaCP == util::CPVChoiceFromString("delta") &&
                 opt.find("sindelta") != std::string::npos) {
            // Convert input prior limits from sin(delta) to delta
            sigma = util::SinPhaseSigmaToPhaseSigma(mean, sigma);
            mean  = TMath::ASin(mean);
         }
      }

      fpl.SetPriorMode(params[0], "gaus");
      fpl.SetMeanGaus (params[0], mean  );
      fpl.SetSigmaGaus(params[0], sigma );
      LOG("UtlOscillation", pNOTICE) << "Setting Gaussian prior for param " << param_names
                                     << ": mean = " << mean << ", sigma = " << sigma;
   }
   else {
      // TODO: This will not work if we throw the mass hierarchy!
      std::string prior_hist_file_name = "";
      if(Opt::Instance()->gMassHierarchyAssumed == util::HierarchyFromString("normal")) {
         prior_hist_file_name = prior_attribute1;
      }
      else {
         prior_hist_file_name = prior_attribute2;
      }
      TString base_dir = Env::Instance()->TopLevelDataDir().c_str();
      TFile* prior_root_file = new TFile((base_dir + "/" + prior_hist_file_name.c_str()).Data(), "read");
      if(!prior_root_file->IsOpen()) {
         LOG("UtlOscillation", pERROR) << "Could not find prior hist file [" << prior_hist_file_name << "]";
         exit(1);
      }

      if(params.size() == 1) {
         TH1D* prior_hist = (TH1D*) prior_root_file->Get(prior_attribute3.c_str());
         if(!prior_hist) {
            LOG("UtlOscillation", pERROR) << "Could not find 1D prior hist [" << prior_attribute3 << "] in file ["
                                          << prior_hist_file_name << "]";
            exit(1);
         }
         fpl.SetPriorMode (params[0], "user");
         fpl.SetPriorHisto(params[0], prior_hist);
         LOG("UtlOscillation", pNOTICE) << "Setting 1D hist prior for param " << param_names
                                        << ": file = " << prior_hist_file_name;
      }
      else {
         // Set the axis titles to the parameter names they correspond to, so we know which is which when we come to throw from the hist
         TH2D* prior_hist = (TH2D*) prior_root_file->Get(prior_attribute3.c_str());
         if(!prior_hist) {
            LOG("UtlOscillation", pERROR) << "Could not find 1D prior hist [" << prior_attribute3 << "] in file ["
                                          << prior_hist_file_name << "]";
            exit(1);
         }
         prior_hist->GetXaxis()->SetTitle(nr->ParamAsStringVerySimple(params[0]).c_str());
         prior_hist->GetYaxis()->SetTitle(nr->ParamAsStringVerySimple(params[1]).c_str());
         fpl.SetPriorMode   (params[0], "user");
         fpl.SetPriorHisto2D(params[0], prior_hist);
         fpl.SetPriorMode   (params[1], "user");
         fpl.SetPriorHisto2D(params[1], prior_hist);
         LOG("UtlOscillation", pNOTICE) << "Setting 2D hist prior for params " << param_names
                                        << ": file = " << prior_hist_file_name;
      }
      prior_root_file->Close();
      delete prior_root_file;
   }

   return true;
}

//____________________________________________________________________________
void ThrowOscillationParameters(FitParamList& fpl)
{
   string osc_parameters[7] = { "mixing12", "mixing13", "mixing23", "dm23sq",
      "dm12sq", "dm13sq", "cpv" };

   // First check if we're using any 1D or 2D hists as priors
   std::vector<conv::PhysParamId_t> pars_with_1D_prior_hists;
   std::vector<conv::PhysParamId_t> pars_with_2D_prior_hists;
   std::vector<conv::PhysParamId_t> pars_with_no_prior_hists;
   for(int i = 0; i < 7; ++i)
   {
      conv::PhysParamId_t p = util::NameRegistry::Instance()->PhysParamFromString(
        osc_parameters[i].c_str());
      if(fpl.Exists(p) && fpl.IsMarginalized(p))
      {
         if(fpl.GetPriorModeName(p) == "user") {
            // Is it a 1D or a 2D prior?
            if     (fpl.GetPriorHisto(p)  ) { pars_with_1D_prior_hists.push_back(p); }
            else if(fpl.GetPriorHisto2D(p)) { pars_with_2D_prior_hists.push_back(p); }
         }
         else {
            pars_with_no_prior_hists.push_back(p);
         }
      }
   }

   // Make sure we only have 0 or 2 parameters with a 2D prior hist
   if(!(pars_with_2D_prior_hists.size() == 0 || pars_with_2D_prior_hists.size() == 2)) {
      LOG("UtlOscillation", pERROR) << "The number of osc params with 2D priors is " << pars_with_2D_prior_hists.size()
                                    << ". Expected either 0 or 2.";
      exit(1);
   }

   // First deal with parameters that have no prior hist
   for(conv::PhysParamId_t p : pars_with_no_prior_hists) {
      double value = util::GetRandomizedOscParam(p, fpl);
      // Prior range is enforced in util::GetRandomizedOscParam, so no need
      // to check here
      fpl.Update(p, value);
      fpl.SetInitValue(p, value);
   }

   // Now parameters with 1D prior hists
   for(conv::PhysParamId_t p : pars_with_1D_prior_hists) {
      // Rethrow until we get a value inside the physical limits
      double min = util::OscParamMinValue(p);
      double max = util::OscParamMaxValue(p);
      double value = min - 1.0;
      do
      {
         value = fpl.GetPriorHisto(p)->GetRandom();
      }
      while(value < min || value > max);

      fpl.Update(p, value);
      fpl.SetInitValue(p, value);
   }

   // Finally do the 0 or 2 parameters that have a 2D prior. Throw them together to maintain correlations
   if(pars_with_2D_prior_hists.size() == 2) {
      // Make sure we know which param corresponds to the x and y axes of the prior hist
      std::string xtitle = fpl.GetPriorHisto2D(pars_with_2D_prior_hists[0])->GetXaxis()->GetTitle();
      std::string ytitle = fpl.GetPriorHisto2D(pars_with_2D_prior_hists[0])->GetYaxis()->GetTitle();
      int xindex = -1;
      int yindex = -1;
      if     (util::NameRegistry::Instance()->AsString(pars_with_2D_prior_hists[0]) == xtitle) { xindex = 0; }
      else if(util::NameRegistry::Instance()->AsString(pars_with_2D_prior_hists[0]) == ytitle) { yindex = 0; }
      if     (util::NameRegistry::Instance()->AsString(pars_with_2D_prior_hists[1]) == xtitle) { xindex = 1; }
      else if(util::NameRegistry::Instance()->AsString(pars_with_2D_prior_hists[1]) == ytitle) { yindex = 1; }
      if(xindex == -1 || yindex == -1) {
         LOG("UtlOscillation", pERROR) << "Failed to associate parameter "
                                       << util::NameRegistry::Instance()->AsString(pars_with_2D_prior_hists[0])
                                       << " and/or "
                                       << util::NameRegistry::Instance()->AsString(pars_with_2D_prior_hists[1])
                                       << " with the x (" << xtitle << ") or y  (" << ytitle
                                       << ") titles of the 2D prior hist.";
         exit(1);
      }

      conv::PhysParamId_t p0 = pars_with_2D_prior_hists[xindex];
      conv::PhysParamId_t p1 = pars_with_2D_prior_hists[yindex];

      // Rethrow until we get a value inside the physical limits
      double min0 = util::OscParamMinValue(p0);
      double max0 = util::OscParamMaxValue(p0);
      double min1 = util::OscParamMinValue(p1);
      double max1 = util::OscParamMaxValue(p1);
      double value0 = min0 - 1.0;
      double value1 = min1 - 1.0;
      do
      {
         fpl.GetPriorHisto2D(p0)->GetRandom2(value0, value1);
      }
      while(value0 < min0 || value0 > max0 || value1 < min1 || value1 > max1);
      fpl.Update(p0, value0);
      fpl.SetInitValue(p0, value0);
      fpl.Update(p1, value1);
      fpl.SetInitValue(p1, value1);
   }
}

//____________________________________________________________________________
void SetUnoscillated(FitParamList& fpl)
{
   string osc_parameters[4] = { "mixing12", "mixing13", "mixing23", "cpv" };
   string dm_parameters[3] = {"dm23sq", "dm12sq", "dm13sq" };

   for(int i = 0; i < 4; ++i)
   {
      valor::conv::PhysParamId_t p = util::NameRegistry::Instance()->PhysParamFromString(
            osc_parameters[i].c_str());
      if(fpl.Exists(p))
      {
         fpl.Update(p, 0.0);
         fpl.SetInitValue(p, 0.0);
      }
   }

   for(int i = 0; i < 3; ++i)
   {
      valor::conv::PhysParamId_t p = util::NameRegistry::Instance()->PhysParamFromString(
            dm_parameters[i].c_str());
      if(fpl.Exists(p))
      {
         double value = fpl.InitValue(p);
         fpl.Update(p, value);
         fpl.SetInitValue(p, value);
      }
   }
}

}
}
}

