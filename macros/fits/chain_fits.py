#!/usr/bin/env python

from __future__ import division
import ROOT
import numpy as np
import math
import os
import sys
from ctypes import *

R=ROOT

env_var = "VALOR_EXPT";

try:
  R.valor
except:
  R.gROOT.ProcessLine(".x $VALOR_EXPT/root/valor_expt.C");

R.gROOT.SetBatch(1)

R.gStyle.SetOptStat(0)
R.gStyle.SetOptTitle(0)

valor = R.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

def main(filenames,treename,outputname):
  chain = R.TChain(treename)
  for f in filenames:
    chain.Add(f)
  assert(chain.GetEntries())
  #print "Chaining ",chain.GetEntries()," fits"
  chain.Merge(outputname)

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] patterns",description="Make plots of deltaCP sensitivity")
  parser.add_option('-o','--output', dest='outputname',default="chained-fits",help='Output filename')
  parser.add_option('-t','--tree', dest='treename',default="valor_fit_ntp",help='Input TTree name')

  options,patterns = parser.parse_args()

  main(patterns,options.treename,options.outputname)
