#!/usr/bin/env python

import ROOT
import numpy as np
import math
import os
import sys

R=ROOT

env_var = "VALOR_EXPT";

try:
  R.valor
except:
  R.gROOT.ProcessLine(".x $VALOR_EXPT/root/valor_expt.C");

R.gROOT.SetBatch(1)

valor = R.valor
util =  valor.util
conv =  valor.conv

def main(recofile,truefile):
  freco = R.TFile(recofile,"UPDATE")
  ftrue = R.TFile(truefile,"UPDATE")

  recomatrix = freco.Get("frac_cov")
  truematrix = ftrue.Get("frac_cov")

  ncolsreco = recomatrix.GetNcols()
  nrowsreco = recomatrix.GetNrows()
  ncolstrue = truematrix.GetNcols()
  nrowstrue = truematrix.GetNrows()

  recosbndvector   = R.TVectorD(19)
  recouboonevector = R.TVectorD(19)
  recoicarusvector = R.TVectorD(19)
  truesbndvector   = R.TVectorD(19)
#  trueuboonevector = R.TVectorD(19)
#  trueicarusvector = R.TVectorD(19)

  recosbndentries   = 0
  recoubooneentries = 0
  recoicarusentries = 0
  truesbndentries   = 0
  trueubooneentries = 0
  trueicarusentries = 0

  for i in range(ncolsreco):
    for j in range(nrowsreco):
      if i < 19 and j < 19: # the first 19 rows and columns are SBND flux bins
        if i != j: continue
        recosbndvector[i] = np.sqrt(recomatrix(i,j))
        recosbndentries += 1
        truesbndvector[i] = np.sqrt(truematrix(i,j))
        truesbndentries += 1
      if i >= 19 and i < 38 and j >= 19 and j < 38: # the first 19 rows and columns are SBND flux bins
        if i != j: continue
        recouboonevector[i-19] = np.sqrt(recomatrix(i,j))
        recoubooneentries += 1
#        trueuboonevector[i-19] = np.sqrt(truematrix(i,j))
#        trueubooneentries += 1
      if i >= 38 and j >= 38: # the first 19 rows and columns are SBND flux bins
        if i != j: continue
        recoicarusvector[i-38] = np.sqrt(recomatrix(i,j))
        recoicarusentries += 1
#        trueicarusvector[i-38] = np.sqrt(truematrix(i,j))
#        trueicarusentries += 1

  print("Reco: \n SBND entries: {}, uBooNE entries: {}, ICARUS entries: {} \n".format(recosbndentries, recoubooneentries, recoicarusentries))
  print("True: \n SBND entries: {}, uBooNE entries: {}, ICARUS entries: {} \n".format(truesbndentries, trueubooneentries, trueicarusentries))


  # Write to the SBND flux file
  f_cov_vect = R.TFile("ereco_vs_etrue_cov_diag.root","RECREATE")
  recosbndvector.Write("vect_err_sbnd_reco")
  recouboonevector.Write("vect_err_uboone_reco")
  recoicarusvector.Write("vect_err_icarus_reco")
  truesbndvector.Write("vect_err_sbnd_true")
#  trueuboonevector.Write("vect_err_uboone_true")
#  trueicarusvector.Write("vect_err_icarus_true")
  f_cov_vect.Close()

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] patterns",description="Make plots of deltaCP sensitivity")
  parser.add_option('-r','--recofile', dest='recofile',default="",help='The reco flux covariance matrix')
  parser.add_option('-t','--truefile', dest='truefile',default="",help='The true flux covariance matrix')
  options,patterns = parser.parse_args()
  main(options.recofile,options.truefile)
