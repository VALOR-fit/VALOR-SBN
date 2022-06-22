#!/usr/bin/env python

import ROOT
import argparse
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

def main(infile,outfile):
  f = R.TFile(infile)
  fraccov = f.Get("frac_cov")
  fracerr = f.Get("frac_err")
  corr    = f.Get("corr")

  ncols = fraccov.GetNcols()
  nrows = fraccov.GetNrows()

  newcov  = R.TMatrixD(60,60)
  newcorr = R.TMatrixD(60,60)
  newerr  = R.TVectorD(60)

  newi = 0
  for i in range(ncols):
    if i > 19 and i < 33 or i > 52 and i < 66 or i > 85: continue
    newerr[newi] = fracerr[i]
    print "New i: ", newi
    newj = 0
    for j in range(nrows):
      if j > 19 and j < 33 or j > 52 and j < 66 or j > 85: continue
      print "New j: ", newj
      newcov[newi][newj]  = fraccov[i][j]
      newcorr[newi][newj] = corr[i][j]
      newj += 1
    newi += 1
  # Write to the SBND flux file
  f_out = R.TFile(outfile,"RECREATE")
  newcov.Write("frac_cov")
  newerr.Write("frac_err")
  corr.Write("corr")
  f_out.Close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Make a covariance matrix from hardcoded info")
    parser.add_argument("--infile", type=str, help="Name of the input file", required=True)
    parser.add_argument("--outfile", type=str, help="Name of the output file", required=True)
    args = parser.parse_args()
    main(args.infile,args.outfile)
