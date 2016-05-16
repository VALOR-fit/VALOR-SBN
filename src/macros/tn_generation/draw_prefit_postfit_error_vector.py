#!/usr/bin/python

# Script to make plots of relative error envelope sizes
# eg plots 9-12 in TN-183
# Takes output of macros/spectrum/test_sk_ereco_spectrum_twk_sys_throw_runAll.py

#Steve Dennis, October 2013

import ROOT
import math
import os
import glob
import numpy as np

ROOT.PyConfig.IgnoreCommandLineOptions = True

R = ROOT

max_energy = 10.
linewidth = 2
title_offset = 1.1
left_margin   = 0.18
bottom_margin = 0.20
right_margin  = 0.05
use_log_plots = False
title_size = 0.08
label_size = 0.07

prefit_color  = ROOT.kGray+1
postfit_color = ROOT.kRed

#~ prefit_style = 3244 # hatched
prefit_style = 1001 # hatched
postfit_style = 1001 # Solid

to3dp = "{0:.3f}"

default_prefit_input_file = (
  "prefit.root")
default_postfit_input_file = (
  "postfit.root")

ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

colors = [ROOT.kBlack, prefit_color, postfit_color, ROOT.kMagenta+1,  ROOT.kGreen+2, ROOT.kOrange+7, ROOT.kCyan+2,]

plot_opt = ""

try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");
  
valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

def main(config, postfit_fn,output,img_format,entry):
  config_path = os.environ["VALOR_DUNE"]+"config/"+config
  
  elem = valor.CompoundFitElements()
  elem.Read(config_path,"nosplines nomc")
  model = elem.FitModel()
  prefit_cov = model.GetSystematics().CovMatrix()
  prefit_err = util.CovarianceMatrixToErrorVector(prefit_cov)
  
  postfit_chain = ROOT.TChain("valor_dune_nd_ntp")
  postfit_chain.Add(postfit_fn)
  assert(postfit_chain.GetEntries())
  postfit_chain.GetEntry(entry)
  postfit_cov = R.TMatrixD(postfit_chain.best_fit_params.GetCovMatrix())
  postfit_err = util.CovarianceMatrixToErrorVector(postfit_cov)
  
  n_params = prefit_err.GetNrows()
  x = np.array([0.5 + i for i in xrange(n_params)])
  prefit_g  = R.TGraph(n_params,x,prefit_err .GetMatrixArray())
  postfit_g = R.TGraph(n_params,x,postfit_err.GetMatrixArray())
  
  prefit_g .SetMarkerStyle(R.kFullTriangleUp)
  prefit_g .SetMarkerColor(R.kBlue)
  postfit_g.SetMarkerStyle(R.kFullCircle)
  postfit_g.SetMarkerColor(R.kRed)
  
  canv = R.TCanvas("c","c",1280,800)
  canv.SetLogy()
  boundaries = [min(prefit_err)  , max(prefit_err),
                min(postfit_err) , min(postfit_err)]
  print boundaries
  miny = min(map(log10_floor,boundaries))
  maxy = max(map(log10_ceil ,boundaries))
  prefit_g.GetXaxis().SetRangeUser(0,n_params)
  prefit_g.GetYaxis().SetRangeUser(miny,maxy)
  prefit_g.Draw("AP")
  postfit_g.Draw("P")
  canv.Update()
  canv.Print(output+"."+img_format)
  
  return

class DUNEAnaError(Exception):
  pass
  
def log10_floor(x):
  n = math.log10(x)
  return 10**(math.floor(n))
  
def log10_ceil(x):
  n = math.log10(x)
  return 10**(math.ceil(n))
  
def get_hist(rootfile,hname):
  h = rootfile.Get(hname)
  if not h:
    print "Failed to get histogram: ",hname ; exit()
  return ROOT.TH1D( h )

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make plots of reduction of fractional error")
  parser.add_option('-c','--config', dest='config'  ,default=default_prefit_input_file  ,help='The config file we get prefit errors from.')
  parser.add_option('-p','--postfit', dest='postfit',default=default_postfit_input_file,help='The postfit input ROOT file')
  parser.add_option('-f','--format', dest='imgformat',default='eps',help='The image format')
  parser.add_option('-o','--output', dest='output',default='prefit_postfit_errors',help='Output name')
  parser.add_option('-n','--entry', dest='entry',default=0,type=int,help='The entry in the tree to get')
  
  options,other = parser.parse_args()
  
  if other:
    print "Bad arguments: ",other
    exit(-1)
  
  main(options.config,options.postfit,options.output,options.imgformat,options.entry)
