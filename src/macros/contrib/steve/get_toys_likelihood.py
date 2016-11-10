#!/usr/bin/env python

# Throws random toy experiments
# Saves their asimov likelihood

import math
import array
import numpy as np
import sys
import os
import ROOT

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

default_fit_param_list = "standard+no-osc-params"

to3sf = "{0:.3g}"
python_undefined = 2L*sys.maxint+1

input_mixing12     = 0.304
input_mixing13     = 0.0248
input_mixing23     = 0.527
input_deltacp      = -1.55
input_dm12sq       = 7.53E-5
input_dm23sq       = 2.51E-3

def main(param,param_value,config_file,outfile,ntoys,seed=0):
  
  # Pattern replacement for output filename
  outfile = outfile.replace("[PARAM]",util.ParamAsString(param))
  outfile = outfile.replace("[VALUE]",to3sf.format(value))
  
  if (seed):
    rnd.SetSeeds(seed,seed+1,seed+2,seed+3,seed+4)
    
  # Set up model and read config file
  config =  util.CompleteConfigPath(config_file)
  if not os.path.exists(config):
    raise T2KAnaError("chisq_dist_for_param >> XML file does not exist: "+config)
    
  print "Reading analysis configuration from: "+config;
  elements = valor.CompoundFitElements()
  elements.Read(config)
  model = elements.FitModel()
  data = elements.FitData()
  
  fpl = util.GetFitParameterList(default_fit_param_list)
  fit_inputs = valor.FitInputs(data,model,fpl)
  
  # Set true parameter value and generate 'data'
  fpl.SetCurrentValue(param,value)
  applied_negevents_condition = data.Generate(model, fpl, False)
  
  model.ResetSystematics()
  
  # Output Tree
  out_param = np.array([-2] ,dtype=int)
  out_value = np.array([-3.],dtype=float)
  out_chisq = np.array([-4.],dtype=float)
  
  tf_out = ROOT.TFile(outfile,"RECREATE")
  tr_out = ROOT.TTree("toys","toys")
  tr_out.Branch("param",out_param,"param/I")
  tr_out.Branch("value",out_value,"value/D")
  tr_out.Branch("chisq",out_chisq,"chisq/D")
  
  for itoy in xrange(ntoys):
    if (itoy and not itoy%100):
      print "Generating toy ",itoy
      tr_out.AutoSave()
    model.RandomizeSystematics()
    fpl.FromPhysParamList(model.Tweaks(),"current silent")
    out_param[0] = param
    out_value[0] = value
    out_chisq[0] = fit_inputs.Statistic("likelihood-ratio nopenalty")
    tr_out.Fill()
  
  tr_out.Write()
  
  
    
class T2KAnaError(Exception):
  pass
  
if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] parameter value",description="Make tables of applied systematics")
  
  #~ parser.add_option('-f', '--fit-param-list', dest='fpl', default=None, help="Name of FPL.")                   , help="Sample (1Rmu, 1Re, RHC1Rmu, RHC1Re)")
  parser.add_option('-c', '--config'        , dest='config' , default="analysis_configuration.xml", help="Configuration file")
  parser.add_option('--seed', dest='seed',default=0, type=int,help="Random seed")
  parser.add_option('-o', dest='outfile',default="toys_[PARAM]=[VALUE].root",help="Output file")
  parser.add_option('-n', dest='ntoys',default=1000,type=int,help="Number of toys to run")
  
  opt,pv = parser.parse_args()
  assert(len(pv)==2)
  param_s,value_s = pv
  param = util.PhysParamFromString(param_s)
  assert(param>=0 and param < python_undefined)
  value = float(value_s)
  
  main(param,value,opt.config,opt.outfile,opt.ntoys,opt.seed)
