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

def main(infile,outfile,mod):
  f = R.TFile(infile)
  fraccov = f.Get("frac_cov")
  fracerr = f.Get("frac_err")
  corr    = f.Get("corr")

  ncols = fraccov.GetNcols()
  nrows = fraccov.GetNrows()

  newcov = R.TMatrixD(ncols,nrows)
  newerr = R.TVectorD(ncols)

  for i in range(ncols):
    newerr[i] = fracerr[i]*mod*mod
    for j in range(nrows):
      newcov[i][j] = fraccov[i][j]*mod

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
    parser.add_argument("--mod", type=float, help="Fraction to modify the errors by", required=True)
    args = parser.parse_args()
    main(args.infile,args.outfile,args.mod)
