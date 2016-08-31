#!/usr/bin/env python

import ROOT as R
import math
import array
import sys
import os

R.PyConfig.IgnoreCommandLineOptions = True

base_dir = os.environ["VALOR_DUNE"]
try:
  R.valor
except:
  R.gROOT.ProcessLine(".x %s/root/valor_dune.C"%base_dir);
  
R.gROOT.SetBatch(1)
  
valor = R.valor
util  = valor.util
conv  = valor.conv
opt   = valor.Opt.Instance()
env   = valor.Env.Instance()
rnd   = valor.Rnd.Instance()

arridx = util.ArrIdx.Instance()

treename = "valor_dune_nd_ntp"
stepsname = "mcsteps"

#______________________________________________________________________________________________________________________________

def main(input_fpl_file, fit_number, output_file, mcmc_files, burnin = 1000):
  infile = R.TFile(input_fpl_file)
  assert(infile.IsOpen())
  intree = infile.Get(treename)
  assert(intree)
  
  intree.GetEntry(fit_number)
  
  fparm = intree.best_fit_params
  
  outfile = R.TFile(output_file,"RECREATE")
  out_tree = intree.CloneTree(0)
  
  npar = fparm.Size()
  
  n_entries_so_far = 0
  
  pca = R.TPrincipal(npar)
  
  for f in mcmc_files:
    mcfile = R.TFile(f)
    steptree = mcfile.Get(stepsname)
    
    n_entries = steptree.GetEntries()
    for iev in xrange(burnin, steptree.GetEntries()):
      steptree.GetEntry(iev)
      par = steptree.params
      
      n_entries_so_far += 1
      
      if n_entries_so_far % 100 == 0:
        print "Reading step ",n_entries_so_far
      
      pca.AddRow(par.GetMatrixArray())
          
    print "Finished reading",f,"for",n_entries_so_far," steps (ignored",burnin," for burn-in)"
  
  pca_mat = util.LowerTriangularMatrixToSymMatrix(pca.GetCovarianceMatrix())
  pca_vec = pca.GetMeanValues()
  
  fparm.SetCovMatrix(pca_mat)
  out_tree.Fill()
  outfile.cd()
  out_tree.Write()
  
  pca_vec.Print()
  
  print "Done!"

if __name__=="__main__":
  
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make tables of applied systematics")
  
  parser.add_option('-o', '--output', dest='output_file', default="combined_mcmc.root", help="Name for output FPL file.")
  parser.add_option('-i', '--input' , dest='input_file', default="fparm.root" , help="Input file result file")
  parser.add_option('-n', '--fit-number', dest='fit_number', default=0, type=int, help="Input tree entry")
  parser.add_option('-b', '--burn-in' , dest='burnin', default=1000, type=int, help="Number of steps to skip per chain")
  
  o,other = parser.parse_args()
  
  main(o.input_file, o.fit_number, o.output_file, other, o.burnin)
  
