#!/usr/bin/python

import sys
import math
import ROOT
import re
import glob

ROOT.PyConfig.IgnoreCommandLineOptions = True

R = ROOT

R.gROOT.SetBatch(1)

try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");
  
valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

def main(prefit_file, postfit_file, output_file, scale, params, prefit_num=0, postfit_num=0):
  
  prefit_tf = R.TFile(prefit_file)
  prefit_tree = prefit_tf.Get("valor_dune_nd_ntp")
  
  postfit_tf = R.TFile(postfit_file)
  postfit_tree = postfit_tf.Get("valor_dune_nd_ntp")
  
  assert(prefit_tree)
  assert(postfit_tree)
  
  prefit_tree .GetEntry(prefit_num)
  postfit_tree.GetEntry(postfit_num)
  
  prefit_fp  = prefit_tree.best_fit_params
  postfit_fp = postfit_tree.best_fit_params
  
  
  prefit_cov  = R.TMatrixD(prefit_fp.GetCovMatrix())
  prefit_corr = util.CovarianceMatrixToCorrelationMatrix(prefit_cov)
  prefit_err  = util.CovarianceMatrixToErrorVector(prefit_cov)
  
  postfit_cov  = R.TMatrixD(postfit_fp.GetCovMatrix())
  postfit_corr = util.CovarianceMatrixToCorrelationMatrix(postfit_cov)
  postfit_err  = util.CovarianceMatrixToErrorVector(postfit_cov)
  
  final_err = R.TVectorD(postfit_err)
  
  # Pick the matching parameters
  selected_params = []
  for ip in xrange(prefit_fp.Size()):
    p = prefit_fp.WhichParam(ip)
    for sel_p in params.split(","):
      if sel_p.lower() in util.ParamAsString(p).lower():
        selected_params.append(p)
  
  for p in selected_params:
    i = prefit_fp.Id(p)
    assert(i == postfit_fp.Id(p))
    final_err[i] = prefit_err[i] * scale
    print "Setting value of",util.ParamAsString(p),"error to",final_err[i]
    
  final_cov = util.CorrelationAndErrorToCovarianceMatrix(prefit_cov,final_err)
  
  output_tf = R.TFile(output_file,"RECREATE")
  output_tree = prefit_tree.CloneTree(0)
  output_tree.best_fit_params.SetCovMatrix(util.MatrixToSymMatrix(final_cov))
  output_tree.Fill()
  output_tree.Write()
  
  print "Done"
  return
  

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] patterns",description="Make plots of deltaCP sensitivity")
  parser.add_option('-s','--scale', dest='scale',default=0.1,help='The value to scale the prefit error by',type=float)
  parser.add_option('-o','--output', dest='output',default="rescaled_errors.root",help='The output file to write')
  parser.add_option('-p','--params', dest='params',default="flux",help='The set of parameters to rescale')
  parser.add_option('--prefit_num', dest='pref_num',default=0,help='Prefit tree entry number to use',type=int)
  parser.add_option('--postfit_num', dest='post_num',default=0,help='Postfit tree entry number to use',type=int)
  
  options,files = parser.parse_args()
  
  assert(len(files)==2)
  prefit,postfit=files
  
  main(prefit,postfit,options.output,options.scale,options.params,options.pref_num,options.post_num)
