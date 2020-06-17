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

def main(covfile):
  f = R.TFile(covfile[0],"UPDATE")
  mymatrix = f.Get("frac_cov")
  mycorr   = f.Get("corr")
  mymean   = f.Get("mean")

  ncols = mymatrix.GetNcols()
  nrows = mymatrix.GetNrows()

  sbndmatrix = R.TMatrixD(19,19)
  uboonematrix = R.TMatrixD(19,19)
  icarusmatrix = R.TMatrixD(19,19)

  sbndcorr = R.TMatrixD(19,19)
  uboonecorr = R.TMatrixD(19,19)
  icaruscorr = R.TMatrixD(19,19)

  sbndmean = R.TVectorD(19)
  uboonemean = R.TVectorD(19)
  icarusmean = R.TVectorD(19)

  sbndentries   = 0
  ubooneentries = 0
  icarusentries = 0

  maxlength = 19 # number of rows and columns per experiment
  for i in range(ncols):
    for j in range(nrows):
      if i < 19 and j < 19: # the first 19 rows and columns are SBND flux bins
        sbndmatrix[i][j] = mymatrix(i,j)
        sbndcorr[i][j]   = mycorr(i,j)
        sbndmean[i]      = mymean(i)
        sbndentries += 1
      if i >= 19 and i < 38 and j >= 19 and j < 38: # the first 19 rows and columns are SBND flux bins
        uboonematrix[i-19][j-19] = mymatrix(i,j)
        uboonecorr[i-19][j-19]   = mycorr(i,j)
        uboonemean[i-19]         = mymean(i)
        ubooneentries += 1
      if i >= 38 and j >= 38: # the first 19 rows and columns are SBND flux bins
        icarusmatrix[i-38][j-38] = mymatrix(i,j)
        icaruscorr[i-38][j-38]   = mycorr(i,j)
        icarusmean[i-38]         = mymean(i)
        icarusentries += 1

  print("SBND entries: {}, uBooNE entries: {}, ICARUS entries: {} \n".format(sbndentries, ubooneentries, icarusentries))
  print("Writing to 3 files: sbnd_flux.root, uboone_flux.root, icarus_flux.root, located in $VALOR_DUNE/data/sbn/syst/proposal/split/")

  # Write to the SBND flux file
  f_sbnd   = R.TFile("$VALOR_DUNE/data/sbn/syst/proposal/split/sbnd_flux.root","RECREATE")
  sbndmatrix.Write("frac_cov")
  sbndcorr.Write("corr")
  sbndmean.Write("mean")
  f_sbnd.Close()

  # Write to the uBooNE flux file
  f_uboone   = R.TFile("$VALOR_DUNE/data/sbn/syst/proposal/split/uboone_flux.root","RECREATE")
  uboonematrix.Write("frac_cov")
  uboonecorr.Write("corr")
  uboonemean.Write("mean")
  f_uboone.Close()

  # Write to the ICARUS flux file
  f_icarus   = R.TFile("$VALOR_DUNE/data/sbn/syst/proposal/split/icarus_flux.root","RECREATE")
  icarusmatrix.Write("frac_cov")
  icaruscorr.Write("corr")
  icarusmean.Write("mean")
  f_icarus.Close()

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] patterns",description="Make plots of deltaCP sensitivity")
  options,patterns = parser.parse_args()
  main(patterns)
