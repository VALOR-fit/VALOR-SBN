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

R.gStyle.SetOptStat(0)
R.gStyle.SetOptTitle(0)

valor = R.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

colors = [R.kBlack, R.kRed, R.kBlue, R.kMagenta+1,  R.kGreen+2, R.kOrange+7, R.kCyan+2,]

# Add these as command line arguments
param_x = conv.kPhypMixingMuE # (numu disappearance), conv.kPhypMixingMuE for mu-e appearance, conv.kPhypMixingEEE for e-e disappearance
param_y = conv.kPhypDm41sq

ex_x_min = 1E-5 #exlusion
ex_x_max = 1

in_x_min = 4E-2 #allowed
in_x_max = 1E-1

x_npoints = 40

ex_y_min = 1E-2 #exlusion
ex_y_max = 1E2

in_y_min = 9E-1 #allowed
in_y_max = 2.

y_npoints = 40

ndim = 2

eps = 1E-10 # a small number to guarantee our point goes in its bin

def GetLoggedHist(filename,exclusion):
  print(filename)
  chain = R.TChain("valor_fit_ntp")
  chain.Add(filename)
  print "Reading ",chain.GetEntries()," fits"
  assert(chain.GetEntries())
  chain.GetEntry(0)

  # Set the maximum and minimum axes limits based on contour type
  x_max = ex_x_max
  x_min = ex_x_min
  y_max = ex_y_max
  y_min = ex_y_min
  if exclusion is False:
    print "Exclusion is false, setting inclusion limits"
    x_max = in_x_max
    x_min = in_x_min
    y_max = in_y_max
    y_min = in_y_min

  hist = R.TH2D("hist","",
    x_npoints,math.log10(x_min),math.log10(x_max),
    y_npoints,math.log10(y_min),math.log10(y_max))

  values = dict()
  for ev in chain:
    fp = ev.best_fit_params
    true = ev.true_params
    x = true.Value(param_x)
    y = true.Value(param_y)
    if exclusion is False:
      print "Exclusion is false, setting inclusion parameters"
     # x = fp.CurrValue(param_x)
      x = true.Value(param_x)
      #y = fp.CurrValue(param_y)
      y = true.Value(param_y)

    stat = max(0.,fp.GetBestFitStatistic())

    logx = math.log10(x)
    logy = math.log10(y)
    if logx >= hist.GetXaxis().GetXmax(): logx -= eps
    if logy >= hist.GetYaxis().GetXmax(): logy -= eps
    ibin = hist.FindBin(logx,logy)

    hist.SetBinContent(ibin,stat)

  return hist


def MakeContour(h,dchisq):
  tmp_hist = h.Clone()
  tmp_hist.SetContour(1,np.array([dchisq]))

  canvas = ROOT.TCanvas("c", "c", 0, 0, 700, 500)
  tmp_hist.Draw("cont3same")
  tmp_hist.Draw("CONT LIST same")
  canvas.Update()
  contours = R.gROOT.GetListOfSpecials().FindObject("contours")[0]
  graphs = [g.Clone() for g in contours]

  return graphs

def UnlogGraph(graph):
  n = graph.GetN()
  x = np.array([graph.GetX()[i] for i in xrange(n)])
  y = np.array([graph.GetY()[i] for i in xrange(n)])

  new_graph = R.TGraph(n,10**x,10**y)
  return new_graph

def main(files,tag,label,exclusion,nue):

  logged_hists = [GetLoggedHist(f,exclusion) for f in files]
  canv = R.TCanvas("canv","canv",1200,800)
  canv.SetTopMargin(0.03)
  canv.SetRightMargin(0.03)
  # ~ canv.SetLogx()
  # ~ canv.SetLogy()

  f = R.TFile("%s_contours_as_graphs.root"%(label),"RECREATE")

  for h in logged_hists:

    h.SetName("%s_log_hist"%(tag))
    h.Write()

    for cl in xrange(conv.kNConfLevels):
      clname = util.ConfLevelAsString(cl)
      dchisq = -999
      # 1-sided scan if exclusion plot
      if exclusion:
        print "Exclusion contour"
        if not nue:
          print "Looking at NuMu"
          print "One-sided delta chi-squared scan"
          dchisq = util.DeltaChisquareOneSided(cl,1)
        # 2-sided scan if acceptance plot or nue contour
        else:
          print "Looking at NuE"
          print "Two-sided delta chi-squared scan"
          dchisq = util.DeltaChisquareOneSided(cl,1)
      else:
        print "Acceptance contour"
        print "Two-sided delta chi-squared scan"
        dchisq = util.DeltaChisquare(cl,2)

      if (dchisq < 0): continue
      logged_graphs = MakeContour(h,dchisq)
      unlogged_graphs = map(UnlogGraph,logged_graphs)

      for ig in xrange(len(logged_graphs)):
        logged_graphs  [ig].SetName("%s_%s_log_%u"%(tag,clname,ig))
        unlogged_graphs[ig].SetName("%s_%s_lin_%u"%(tag,clname,ig))

        logged_graphs  [ig].Write()
        unlogged_graphs[ig].Write()

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] patterns",description="Make plots of deltaCP sensitivity")
  parser.add_option('-t','--tag', dest='tag',default="contour",help='The names to give the graphs')
  parser.add_option('-l','--label', dest='label',default="output",help='Label to add to the output filename')
  parser.add_option('-e','--exclusion', dest='exclusion',default=True,help='Boolean for whether we are producing exclusion or inclusion contours')
  parser.add_option('-n','--nue', dest='nue',default=True,help='Boolean for whether we are producing numu or nue contours')

  options,patterns = parser.parse_args()

  main(patterns,options.tag, options.label, options.exclusion, options.nue)
