#!/usr/bin/env python

# Plots chi-square distribution for physics parameters at DUNE
# Steve Dennis, May 2016 (based off T2K script, June 2014)

import ROOT
import math
import array
import numpy as np
import sys
import os

env_var = "VALOR_EXPT";
try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_EXPT/root/valor_expt.C")

ROOT.gROOT.SetBatch(1)

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()
rnd  =  valor.Rnd.Instance()
nr   =  util.NameRegistry.Instance()

opt.gOscMixingParamChoice = conv.kNuMixSinsqTheta
opt.SetDefaultParameterValues()

default_hyp = "eff_sterile_osc"
tree_name = "valor_fit_ntp"

nbins = 40

write_bin_spectra = False

to3sf = "{0:.3g}"
python_undefined = 2L*sys.maxint+1

input_mixingmumu = 0.05
input_dm41sq     = 30

color = ROOT.kBlack

img_format = "png"

def main(params,config_file,hypname, fit_param_opt, input_fpl, stat_fluctuations=False, syst_tweaks = False, reset = False, spline_only = False, seed = 0):

  if (seed):
    rnd.SetSeeds(seed,seed+1,seed+2,seed+3,seed+4)

  # Set up model and read config file
  config =  os.environ[env_var]+"/config/"+config_file
  if not os.path.exists(config):
    raise T2KAnaError("chisq_dist_for_param >> XML file does not exist: "+config)

  print "Reading analysis configuration from: "+config;
  elements = valor.CompoundFitElements()
  elements.Read(config)
  model = elements.FitModel()

  if syst_tweaks: model.RandomizeSystematics();

  if hypname is None: hypname = default_hyp
  if fit_param_opt is None: fit_param_opt = ""

  fparm = 0

  if input_fpl is None:
    fparm = valor.util.GetFitParameterList(hypname, fit_param_opt)

  else:
    prior_file = ROOT.TFile(input_fpl)
    prior_tree = prior_file.Get(tree_name)
    prior_tree.GetEntry(0)
    prior_fpl  = prior_tree.best_fit_params
    fparm = prior_fpl
    fparm.Print()

  true_values = model.Tweaks()

  if input_fpl is None:
    fparm.FromPhysParamList(true_values,"current")

  data = elements.FitData()
  applied_negevents_condition = data.Generate(model, fparm, stat_fluctuations)

  if not reset:
    fparm.CopyCurrToInitValues()

  model.ResetSystematics(fparm)
  fparm.ResetCurrToInitValues()

  outfile = ROOT.TFile("chisq_output.root","RECREATE")

  hists = []

  canv = ROOT.TCanvas("canv","canv",1280,1024)
  canv.cd()

  if len(params)==0:
    params = [nr.ParamAsString(p) for p in xrange(conv.knppmax) if fparm.Exists(p)]

  print "Making chisq distribution for "+`len(params)`+" parameters."

  fit_inputs = valor.Likelihood(data,model,fparm)

  pool = valor.ParameterPool.Instance()
  for param_name in params:
    param = nr.PhysParamFromString(param_name)

    if (param == conv.kPhypUndefined or param == python_undefined):
      try:
        param = getattr(conv,param_name)
        print param
      except:
        print "Failed to get param ",param_name
        continue

    if spline_only and pool.GetParam(param).GetType() != conv.kSystResponse:
      continue

    if not fparm.Exists(param):
      print "Param ",param,"=",nr.ParamAsString(param)," not found in FitParamList"
      continue

    print "Doing param: ",nr.ParamAsString(param)

    fparm.ResetCurrToInitValues()

    lower_limit = fparm.MinValue(param)
    upper_limit = fparm.MaxValue(param)

    hname = nr.ParamAsString(param)+"_chisq"
    htitle = "Chisq of "+nr.ParamAsString(param)

    h = ROOT.TH1D(hname,htitle,nbins,lower_limit,upper_limit)
    h.SetLineColor(color)

    for ibin in xrange(nbins):
      par_value = h.GetBinCenter(ibin+1)
      fparm.Update(param, par_value)
      chisq = fit_inputs.Statistic()
      h.Fill(par_value , chisq )

    ymin = 0.
    ymax = h.GetMaximum()*1.1

    true_val = true_values.Value(param)
    truth_line = ROOT.TLine(true_val,ymin,true_val,ymax)
    truth_line.SetLineColor(ROOT.kBlue)
    truth_line.SetLineWidth(2)
    truth_line.SetLineStyle(7)

    hists.append(h)
    h.GetYaxis().SetRangeUser(ymin,ymax)
    h.Write(hname)
    h.Draw()
    truth_line.Draw()
    canv.Update()
    canv.Print(h.GetName()+"."+img_format)

class T2KAnaError(Exception):
  pass

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make tables of applied systematics")

  parser.add_option('-f', '--physics-hypothesis', dest='hypname', default=None, help="Name of FPL.")
  parser.add_option('-o', '--fit-param-opt' , dest='fpl_opt', default=None, help="FPL options.")
  parser.add_option('-i', '--load-prior-from-file' , dest='input_fpl', default=None, help="Input FPL from previous fit.")
  parser.add_option('-c', '--config'        , dest='config' , default="analysis_configuration.xml", help="Configuration file")
  parser.add_option('--stat', dest='stat_fluct',default=False,action='store_true',help="Statistical fluctuations")
  parser.add_option('--syst', dest='syst_fluct',default=False, action='store_true',help="Randomise systematics")
  parser.add_option('--reset', dest='reset',default=False, action='store_true',help="Chisq around nominal, not true.")
  parser.add_option('--spline-only', dest='spline_only',default=False, action='store_true',help="Only draw spline parameters")
  parser.add_option('--seed', dest='seed',default=0, type=int,help="Random seed")

  opt,params = parser.parse_args()

  main(params,opt.config,opt.hypname,opt.fpl_opt,opt.input_fpl,opt.stat_fluct,opt.syst_fluct,opt.reset,opt.spline_only,opt.seed)
