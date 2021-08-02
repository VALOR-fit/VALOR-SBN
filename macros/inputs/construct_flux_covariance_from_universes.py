#!/usr/bin/python

# Make parameter matrices using spectra made with varied universes
# These come from eg write_sbn_spectra_using_universes
# Steve Dennis
# November 2019

import sys
import math
import ROOT
import re
import glob
import numpy as np

ROOT.PyConfig.IgnoreCommandLineOptions = True

R = ROOT

R.gROOT.SetBatch(1)

try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_EXPT/root/valor_expt.C");

valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

def main(files,config,output,input_tag,nominal,kinematic,grouping,scale):

  elements = valor.CompoundFitElements()
  elements.Read(util.CompleteConfigPath(config),"nomc nosplines")
  params = valor.ParameterPool.Instance().GetParams() # instance of the list of parameters from the configuration

  # Print details of what is in the parameter list for clarity
  print "There are a total of ", params.size(), " parameters defined in the configuration"
  n_flux = 0
  n_int  = 0
  for p in params:
    if "flux" in p.GetCategories():
      n_flux += 1
    if "interaction" in p.GetCategories():
      n_int += 1
  print "    ", n_flux, "of which are flux parameters"
  print "    ", n_int, "of which are interaction parameters"

  scaleVector = R.TVectorD(0)
  scaleVectorEmpty = False
  if scale != "":
    scaleFile = R.TFile(scale)
    scaleVector = scaleFile.Get("scales")
    if scaleVector.GetNrows() == 0:
      scaleVectorEmpty = True
    else:
      print "Scale vector found and is populated, will apply to the covariance construction"


  kv = util.KineVarFromString(kinematic)
  is_true = util.KineVarIsTrue(kv)
  is_reco = util.KineVarIsReco(kv)

  # Calculate the number of entries that we'll put in the matrix
  row_size = 0
  model_nbins = []
  for model in elements.FitModel().GetSubModels():
    n_bins = 0
    if (is_true):
      for p in params:
        if "flux" not in p.GetCategories(): continue
        if "sbnd" in p.GetName() and "sbn_nd" in model.Name() or "uboone" in p.GetName() and "uboone" in model.Name() or "icarus" in p.GetName() and "icarus" in model.Name():
          n_bins += p.GetKineRanges().size()

    elif (is_reco):
      full_binning = model.GetBinning()
      binning = None
      binning = full_binning.RecoOptBinning()
      n_bins = binning.NBinsByKV(kv)

    model_nbins.append(n_bins)

    row_size += n_bins

  print "Our flux covariance will have",row_size,"elements."

  # Make the TPrincipal we'll use to actually get covariances
  tp = R.TPrincipal(row_size)
  
  zeroes = [] # hold all the diagonal entries which are empty
  
  # Loop over each file (containing a universe each)
  flav = [""]*row_size # array for the neutrino flavour of each row entry to fill any empty cases with alternative flavour entries later
  for ifile,f in enumerate(files):
    myfile = R.TFile(f)

    row  = np.array([0.]*row_size)
    ientry = 0
    for imodel,model in enumerate(elements.FitModel().GetSubModels()):
      first_entry_for_sample = ientry
      for mode in model.GetReactionModes():
        if mode < 0 or mode > 1E5: continue
        # Check for if the reac mode contains numu, numubar, nue, nuebar
        # Sum over all histograms for each flavour
        ientry = first_entry_for_sample
        histname = "%s_%s_%s_%s_%s"%(input_tag,"pdfcs_ob_rf",model.Name(),kinematic,util.ModeAsString(mode))
        hist = myfile.Get(histname)
        if not hist:
          print "Failed to get",histname,"from",f
          exit(-1)

        #
        # New plan:
        #   Check if the histogram bin edge is within the range defined by the parameter_matrix and fill that way
        #   Count from ibin+1 to skip over the weird -0.2 something something bin, think it's a ROOT thing
        #

        for ibin in xrange(hist.GetXaxis().GetNbins()):
          # Check what neutrino flavour we're looking at and only sum for each of the 4 separately

          if(is_true):
            for ip, p in enumerate(params):
              if "sbnd" in p.GetName() and "sbn_nd" in histname or "uboone" in p.GetName() and "uboone" in histname or "icarus" in p.GetName() and "icarus" in histname:
                for kinerange in p.GetKineRanges():
                  minbin = min(kinerange.first,kinerange.second)
                  maxbin = max(kinerange.first,kinerange.second)
                  if hist.GetBinCenter(ibin+1) >= minbin and hist.GetBinCenter(ibin+1) < maxbin:
                    ientry = ip

                    if util.IsNuMu(mode) and not util.IsCosmic(mode) and "numu" in p.GetName() and "numubar" not in p.GetName() and not "cosmic" in p.GetName():
                      row[ientry] += hist.GetBinContent(ibin+1)
                      # check if the flavour entry has already been filled and fill if not
                      if not flav[ientry]:
                        flav[ientry] = "numu"
                    elif util.IsNuMuBar(mode) and not util.IsCosmic(mode) and "numubar" in p.GetName() and not "cosmic" in p.GetName():
                      row[ientry] += hist.GetBinContent(ibin+1)
                      # check if the flavour entry has already been filled and fill if not
                      if not flav[ientry]:
                        flav[ientry] = "numubar"
                    elif util.IsNuE(mode) and not util.IsCosmic(mode) and "nue" in p.GetName() and "nuebar" not in p.GetName() and not "cosmic" in p.GetName():
                      row[ientry] += hist.GetBinContent(ibin+1)
                      # check if the flavour entry has already been filled and fill if not
                      if not flav[ientry]:
                        flav[ientry] = "nue"
                    elif util.IsNuEBar(mode) and not util.IsCosmic(mode) and "nuebar" in p.GetName() and not "cosmic" in p.GetName():
                      row[ientry] += hist.GetBinContent(ibin+1)
                      # check if the flavour entry has already been filled and fill if not
                      if not flav[ientry]:
                        flav[ientry] = "nuebar"
                    elif util.IsNuMuToNuE(mode) and not util.IsCosmic(mode) and "numu" in p.GetName() and not "cosmic" in p.GetName():
                      row[ientry] += hist.GetBinContent(ibin+1)
                      # check if the flavour entry has already been filled and fill if not
                      if not flav[ientry]:
                        flav[ientry] = "numu"
                    elif util.IsNuMuBarToNuEBar(mode) and not util.IsCosmic(mode) and "numubar" in p.GetName() and not "cosmic" in p.GetName():
                      row[ientry] += hist.GetBinContent(ibin+1)
                      # check if the flavour entry has already been filled and fill if not
                      if not flav[ientry]:
                        flav[ientry] = "numubar"

                    #end if mode
                  #end if within kinematic range
                #end loop kinematic ranges
              #end if parameter matches histogram
            #end loop params
          #end if true
          else:
            # We're summing over all reaction modes here
            row[ientry] += hist.GetBinContent(ibin)
            ientry+=1
        #end loop ibin
      #end loop mode
    #end loop model
    if(is_true):
      assert(ientry+1 == row_size)
    else:
      assert(ientry == row_size)
    print "Adding row to covariance from file ",ifile, "\r"
    # Get all diagonal bins which are empty in 1+ universes
    for i in range(0, row_size):
      if row[i] == 0:
        if i not in zeroes:
          zeroes.append(i)
    tp.AddRow(row)
  #end loop files
  cov = R.TMatrixD(util.LowerTriangularMatrixToSymMatrix(tp.GetCovarianceMatrix()))
  mean = tp.GetMeanValues()

  nRows = cov.GetNrows()
  nCols = cov.GetNcols()
  # If a scale root file has been passed, apply it now
  for n in range(nRows):
    for m in range(nCols):
      # scale if needed
      if not scaleVectorEmpty and n < scaleVector.GetNrows() and m < scaleVector.GetNrows():
        cov[n][m] *= scaleVector[n] * scaleVector[m]
        print " Covariance entry has been scaled"

  ''' HACK: If a diagonal element of the matrix is empty (we see this in low energy
  nue and nubar bins due to statistics at the moment) then fill that diagonal element with
  a huge uncertainty value.
  Set the off-diagonal elements of the empty bins to be 0.'''
  print "List of parameters with no entries: \r"
  for n in range(mean.GetNrows()):
    for i in zeroes:
      if n == i:
        mean[n] = float('nan');
        print params[n].GetName(), "\r"    

#    if not float(mean[n]):
#      print params[n].GetName(), "\r"

  frac_cov = util.CovarianceMatrixToFractionalCovarianceMatrix(cov,mean)
  # If a scale root file has been passed, apply it now
  for n in range(nRows):
    for m in range(nCols):
      # Check the diagonal case
      if n == m:
        if math.isnan(frac_cov[n][m]):
          #frac_cov[n][m] = 1 # 100% for used table
          frac_cov[n][m] = 0.0001 # Set diagonal value to 0
        
      else:
        if math.isnan(frac_cov[n][m]):
          frac_cov[n][m] = 0.0 # setting the off-diagonal elements of the empty bins to be 0


  corr = util.CovarianceMatrixToCorrelationMatrix(frac_cov)
  err  = util.CovarianceMatrixToErrorVector(frac_cov)

  outfile = R.TFile(output,"RECREATE")
  frac_cov.Write("frac_cov")
  err.Write("frac_err")
  corr.Write("corr")

  print "Done"
  return

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] patterns",description="Make covariance matrix using universes")
  parser.add_option('-c','--config', dest='config',default="analysis/default.xml",help='The config file')
  parser.add_option('-o','--output', dest='output',default="covariance.root",help='The output file to write')
  parser.add_option('-k','--kinematic',dest='kinematic',default="etrue",help="The kinematic variable to parameterise in")
  parser.add_option('-n','--nominal',dest='nominal',default=None,help="If a nominal spectrum is given, we can write the central values too [NOT YET IMPLEMENTED")
  parser.add_option('-g','--grouping',dest='grouping',default="all",help="How to group modes. Options all,flav")
  parser.add_option('-s','--scales',dest='scale',default="",help="Root file containing a vector of values to scale the rates by")
  parser.add_option('--input-tag',dest='input_tag',default="valor",help="The first part of the histogram name")
  parser.add_option('--write-xml',dest='write_xml',action="store_true",default=False,help="Write parameter XML definitions [NOT YET IMPLEMENTED]")

  options,files = parser.parse_args()

  main(files,options.config,options.output,options.input_tag,options.nominal,options.kinematic,options.grouping, options.scale)
