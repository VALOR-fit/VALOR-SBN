#!/usr/bin/python

# Plots chi-square distribution for physics parameters at DUNE
# Steve Dennis, May 2016 (based off T2K script, June 2014)

import ROOT
import math
import array
import numpy as np
import sys
import os

env_var = "VALOR_DUNE";
try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");
  
ROOT.gROOT.SetBatch(1)

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
  
valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()
rnd  =  valor.Rnd.Instance()

opt.gOscMixingParamChoice = conv.kNuMixSinsqTheta
opt.SetDefaultParameterValues()

default_fit_param_list = "standard"

nbins = 51

write_bin_spectra = False

to3sf = "{0:.3g}"
python_undefined = 2L*sys.maxint+1

#~ input_mixing12     = 0.304
#~ input_mixing13     = 0.0248
#~ input_mixing23     = 0.527
#~ input_deltacp      = -1.55
#~ input_dm12sq       = 7.53E-5
#~ input_dm23sq       = 2.51E-3

color = ROOT.kBlack

img_format = "png"

def main(params,config_file,fit_param_list, stat_fluctuations=False, syst_tweaks = False):
  
  # Set up model and read config file
  config =  os.environ[env_var]+"/config/"+config_file
  if not os.path.exists(config):
    raise T2KAnaError("chisq_dist_for_param >> XML file does not exist: "+config)
    
  print "Reading analysis configuration from: "+config;
  elements = valor.CompoundFitElements()
  elements.Read(config)
  model = elements.FitModel()
  
  if syst_tweaks: model.RandomizeSystematics();
  
  if fit_param_list is None: fit_param_list = default_fit_param_list
  
  fparm = valor.util.GetFitParameterList(fit_param_list)
  
  if fparm.Exists(conv.kPhypMixing12    ) : fparm.SetInitValue(conv.kPhypMixing12   , input_mixing12);
  if fparm.Exists(conv.kPhypMixing13    ) : fparm.SetInitValue(conv.kPhypMixing13   , input_mixing13);
  if fparm.Exists(conv.kPhypMixing23    ) : fparm.SetInitValue(conv.kPhypMixing23   , input_mixing23);
  if fparm.Exists(conv.kPhypCPV         ) : fparm.SetInitValue(conv.kPhypCPV        , input_deltacp);
  if fparm.Exists(conv.kPhypDm12sq      ) : fparm.SetInitValue(conv.kPhypDm12sq     , input_dm12sq);
  if fparm.Exists(conv.kPhypDm23sq      ) : fparm.SetInitValue(conv.kPhypDm23sq     , input_dm23sq);
      
  data = elements.FitData()
  print model,data,fparm,stat_fluctuations
  applied_negevents_condition = data.Generate(model, fparm, stat_fluctuations)
  
  model.ResetSystematics();
  
  outfile = ROOT.TFile("chisq_output.root","RECREATE")
  
  hists = []
  
  canv = ROOT.TCanvas("canv","canv",1280,1024)
  canv.cd()
  
  if len(params)==0:
    params = [util.ParamAsString(p) for p in xrange(conv.knppmax) if fparm.Exists(p)]
    
  print "Making chisq distribution for "+`len(params)`+" parameters."
  
  fit_inputs = valor.FitInputs(data,model,fparm)
  
  for param_name in params:
    param = util.PhysParamFromString(param_name)
    
    if (param == conv.kPhypUndefined or param == python_undefined):
      try:
        param = getattr(conv,param_name)
        print param
      except:
        print "Failed to get param ",param_name
        continue
      
    if not fparm.Exists(param):
      print "Param ",param,"=",util.ParamAsString(param)," not found in FitParamList ",fit_param_list
      continue
      
    print "Doing param: ",util.ParamAsString(param)
      
    fparm.ResetCurrToInitValues()
    
    lower_limit = fparm.MinValue(param)
    upper_limit = fparm.MaxValue(param)
    
    hname = util.ParamAsString(param)+"_chisq"
    htitle = "Chisq of "+util.ParamAsString(param)
    
    h = ROOT.TH1D(hname,htitle,nbins,lower_limit,upper_limit)
    h.SetLineColor(color)
    
    for ibin in xrange(nbins):
      par_value = h.GetBinCenter(ibin+1)
      fparm.Update(param, par_value)
      chisq = fit_inputs.Statistic()
      h.Fill(par_value , chisq )
      
    hists.append(h)
    h.GetYaxis().SetRangeUser(0,h.GetMaximum()*1.1)
    h.Write(hname)
    h.Draw("c")
    canv.Update()
    canv.Print(h.GetName()+"."+img_format)
    
class T2KAnaError(Exception):
  pass
  
if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make tables of applied systematics")
  
  parser.add_option('-f', '--fit-param-list', dest='fpl', default=None, help="Name of FPL.")
  
  #~ parser.add_option('-s', '--sample' , dest='sample'      , default="1Rmu"                    , help="Sample (1Rmu, 1Re, RHC1Rmu, RHC1Re)")
  
  parser.add_option('-c', '--config'        , dest='config' , default="analysis_configuration.xml", help="Configuration file")
  parser.add_option('--stat', dest='stat_fluct',default=False,action='store_true',help="Statistical fluctuations")
  parser.add_option('--syst', dest='syst_fluct',default=False, action='store_true',help="Randomise systematics")
  
  opt,params = parser.parse_args()
  
  main(params,opt.config,opt.fpl,opt.stat_fluct,opt.syst_fluct)
