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

def main(dstfile):
  f = R.TFile(dstfile[0],"UPDATE")
  mytree = f.Get("valor_sbncode_mini_dst")
  new_tree = mytree.CloneTree(0)
  new_baseline = np.array([-1.])
  new_tree.SetBranchAddress("baseline",new_baseline)
  for event in mytree:
    new_baseline[0] = mytree.baseline-0.01
    new_tree.Fill()
  new_tree.Write("valor_sbncode_mini_dst",R.TObject.kOverwrite)

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] patterns",description="Make plots of deltaCP sensitivity")
  options,patterns = parser.parse_args()
  main(patterns)
