#include "dune/Utilities/UtlOscillation.h"

#include "valor/Messenger/Messenger.h"

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
      valor::conv::PhysParamId_t p = util::PhysParamFromString(
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
            LOG("UtlOscillation", pNOTICE) << "Setting fixed parameter " <<
               util::AsString(p) << " := " << fix_value;
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
               util::AsString(p) << " := " << free_value;
         }
         else
         {
            fpl.SetDoMarg(p, true);
            LOG("UtlOscillation", pNOTICE) << "Setting marginalised parameter " <<
               util::AsString(p);
         }
      }
   }
}

void SetOscillationParameterPriors(CmdLnArgList& arg, FitParamList& fpl)
{
   // This should all be done from xml
   valor::conv::PhysParamId_t p = util::PhysParamFromString("mixing12");
   fpl.SetPriorMode(p, "gaus");
   fpl.SetMeanGaus(p, 0.307); fpl.SetSigmaGaus(p, 0.013);

   p = util::PhysParamFromString("dm12sq");
   fpl.SetPriorMode(p, "gaus");
   fpl.SetMeanGaus(p, 7.53e-5); fpl.SetSigmaGaus(p, 0.18e-5);

   p = util::PhysParamFromString("mixing13");
   fpl.SetPriorMode(p, "gaus");
   fpl.SetMeanGaus(p, 2.12e-2); fpl.SetSigmaGaus(p, 0.8e-2);

   p = util::PhysParamFromString("mixing23");
   fpl.SetPriorMode(p, "flat");
   fpl.SetMinValueFlat(p, 0.3); fpl.SetMaxValueFlat(p, 0.7);

   p = util::PhysParamFromString("dm23sq");
   fpl.SetPriorMode(p, "flat");
   fpl.SetMinValueFlat(p, 2.3e-3); fpl.SetMaxValueFlat(p, 2.7e-3);

   p = util::PhysParamFromString("cpv");
   fpl.SetPriorMode(p, "flat");
   fpl.SetMinValueFlat(p, -3.14159265358979312); fpl.SetMaxValueFlat(p, +3.14159265358979312);
}

void ThrowOscillationParameters(FitParamList& fpl)
{
   string osc_parameters[7] = { "mixing12", "mixing13", "mixing23", "dm23sq",
      "dm12sq", "dm13sq", "cpv" };

   for(int i = 0; i < 7; ++i)
   {
      valor::conv::PhysParamId_t p = util::PhysParamFromString(
            osc_parameters[i].c_str());
      if(fpl.Exists(p) && fpl.IsMarginalized(p))
      {
         double value = util::GetRandomizedOscParam(p, fpl);
         // Prior range is enforced in util::GetRandomizedOscParam, so no need
         // to check here
         fpl.Update(p, value);
         fpl.SetInitValue(p, value);
      }
   }
}

void SetUnoscillated(FitParamList& fpl)
{
   string osc_parameters[4] = { "mixing12", "mixing13", "mixing23", "cpv" };
   string dm_parameters[3] = {"dm23sq", "dm12sq", "dm13sq" };

   for(int i = 0; i < 4; ++i)
   {
      valor::conv::PhysParamId_t p = util::PhysParamFromString(
            osc_parameters[i].c_str());
      if(fpl.Exists(p))
      {
         fpl.Update(p, 0.0);
         fpl.SetInitValue(p, 0.0);
      }
   }

   for(int i = 0; i < 3; ++i)
   {
      valor::conv::PhysParamId_t p = util::PhysParamFromString(
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

