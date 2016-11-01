#!/usr/bin/env python

# Script to draw star plots using fits
# Takes the largest deviation from a list of fits

#Steve Dennis, November 2016

import math
import os

import ROOT
R = ROOT

R.PyConfig.IgnoreCommandLineOptions = True
R.gROOT.SetBatch(1)
R.gStyle.SetOptStat(0)
R.gStyle.SetOptTitle(0)

colors = [R.kBlack, R.kRed, R.kBlue, R.kMagenta+1,  R.kGreen+2, R.kOrange+7, R.kCyan+2,]

canvas_x = 1280
canvas_y = 720
arrowhead_size = 0.02
line_width = 2

all_param_sets = ["allsyst","int","dis","res","ccqe","mec","nc","flux"]

try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");
  
valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

def main(file_patterns, par_x, par_y, output):
  chain = R.TChain("valor_dune_nd_ntp")
  for f in file_patterns:
    chain.Add(f)
  
  assert(chain.GetEntries())
  
  chain.GetEntry(0)
  
  min_x =  9E99
  max_x = -9E99
  min_y =  9E99
  max_y = -9E99
  
  px = util.PhysParamFromString(par_x)
  py = util.PhysParamFromString(par_y)
  if (px < 0 or px > 1E4):
    print "Unidentified parameter x: ",par_x
    exit(-1)
  if (py < 0 or py > 1E4):
    print "Unidentified parameter y: ",par_y
    exit(-1)
  
  lines    = dict()
  max_diag = dict()
  for fit in chain:
    par_set = GetVariedParameterSet(fit)
    try:
      lines[par_set]
    except KeyError:
      lines   [par_set] = []
      max_diag[par_set] = -9E9
    
    bf_x = fit.best_fit_params.BestFitValue(px)
    bf_y = fit.best_fit_params.BestFitValue(py)
    true_x = fit.true_params.Value(px)
    true_y = fit.true_params.Value(py)
    
    disp_x = bf_x-true_x
    disp_y = bf_y-true_y
    if (disp_x < -9E4 or disp_y < -9E4):# DEBUG
      print "Warning, fit failed: ",chain.GetFile().GetName()," ...skipping"
      continue 
    line = R.TArrow(0.,0.,disp_x,disp_y,arrowhead_size,"|>")
    lines[par_set].append(line)
    
    min_x = min(disp_x,min_x)
    max_x = max(disp_x,max_x)
    min_y = min(disp_y,min_y)
    max_y = max(disp_y,max_y)
    max_diag[par_set] = max(max_diag[par_set], math.sqrt((disp_x**2 + disp_y**2)))
  
  canvas = R.TCanvas("c","c",canvas_x,canvas_y)
  canvas.SetRightMargin(0.22)
  frame = R.TH2D("star_plot_frame","",1,min_x*1.2,max_x*1.2,1,min_y*1.2,max_y*1.3)
  title = "Fitted %s - True %s"
  namex = util.ParamAsStringTeX(px,True)
  namey = util.ParamAsStringTeX(py,True)
  frame.GetXaxis().SetTitle(title%(namex,namex))
  frame.GetYaxis().SetTitle(title%(namey,namey))
  frame.Draw()
  
  set_order = sorted(lines.keys(),key=lambda k: max_diag[k]/math.sqrt((max_x-min_x)*(max_y-min_y)),reverse=True)
  for p in set_order:
    print p,max_diag[p]
    
  legend = ROOT.TLegend(0.8,0.15,0.93,0.94);
  legend.SetFillStyle(0);
  legend.SetBorderSize(0);
  for iset,par_set in enumerate(set_order):
    line_list = lines[par_set]
    for line in line_list:
      line.SetFillColor(colors[iset])
      line.SetLineColor(colors[iset])
      line.SetLineWidth(line_width)
      line.Draw()
      
    legend.AddEntry(line,par_set,"l")
  
  legend.Draw()
    
  canvas.Update()
  canvas.Print(output)
  
  return
    
# Finds out which set of parameters were varied in this fit
def GetVariedParameterSet(fit):
  fp    = fit.best_fit_params
  truth = fit.true_params
  
  all_params    = []
  varied_params = []
  for ip in xrange(fp.Size()):
    p = fp.WhichParam(ip)
    if p < conv.kNuis000: continue # only consider nuisance params
    all_params.append(p)
    if (abs(fp.InitValue(p)-truth.Value(p))>conv.kASmallNum):
      varied_params.append(p)
    
  for setname in all_param_sets:
    s = util.GetParameterSet(setname)
    common_par = [p for p in s if p in all_params]
    # If we varied anything that isn't in the list, it's not right
    if (any([v not in s for v in varied_params])): continue
    # And if anything in the list wasn't varied, we've not got the right set
    if (any([v not in varied_params for v in common_par])): continue
    return setname
  print "Failed to ID parameter set."
  return None
      

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options] files",description="Make star plots")
  #~ parser.add_option('-c','--config', dest='config'  ,default="fit/dunend_fit.xml",help='The config file we get the sample list from.')
  parser.add_option('-o','--output', dest='output',default='star_plots.eps',help='Output filename')
  parser.add_option('-x','--parx', dest='parx',default="cpv"     ,help='First parameter to plot')
  parser.add_option('-y','--pary', dest='pary',default="mixing23",help='Second parameter to plot')
  
  options,files = parser.parse_args()
  
  main(files,options.parx,options.pary,options.output)
