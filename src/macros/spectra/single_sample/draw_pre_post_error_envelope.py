#!/usr/bin/python

# Script to make plots of relative error envelope sizes
# eg plots 9-12 in TN-183
# Takes output of macros/spectrum/test_sk_ereco_spectrum_twk_sys_throw_runAll.py

#Steve Dennis, October 2013

import ROOT
import math
import os
import glob

ROOT.PyConfig.IgnoreCommandLineOptions = True

R = ROOT

max_energy = 10.
linewidth = 2
title_offset = 1.1
left_margin   = 0.18
bottom_margin = 0.20
right_margin  = 0.05
use_log_plots = False
title_size = 0.08
label_size = 0.07

prefit_color  = ROOT.kGray+1
postfit_color = ROOT.kRed

#~ prefit_style = 3244 # hatched
prefit_style = 1001 # hatched
postfit_style = 1001 # Solid

to3dp = "{0:.3f}"

default_prefit_input_file = (
  "prefit.root")
default_postfit_input_file = (
  "postfit.root")

ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

colors = [ROOT.kBlack, prefit_color, postfit_color, ROOT.kMagenta+1,  ROOT.kGreen+2, ROOT.kOrange+7, ROOT.kCyan+2,]

plot_opt = ""

try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");
  
valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

def main(prefit_fn, postfit_fn,img_format):
  f_prefit = ROOT.TFile(prefit_fn)
  if not f_prefit:
    raise DUNEAnaError("Could not open prefit input file")
  f_postfit = ROOT.TFile(postfit_fn)
  if not f_postfit:
    raise DUNEAnaError("Could not open postfit input file")
    
  pre_and_postfit_envelope(f_prefit,f_postfit, img_format)
  

def pre_and_postfit_envelope(prefit_file,postfit_file,img_format):
  
  all_hists = []
  
  for ibeam in xrange(conv.kNBeamConf):
    b = util.BeamConfFromInt(ibeam)
    for isamp in xrange(conv.kNSamples):
      samp_hists = []
      
      s = util.GetActiveSample(ibeam,isamp)
      hname_prefix = "env_sb_%s_%s" % (util.BeamConfAsString(b) , util.SampleAsString(s))
      hname_nom = hname_prefix + "_nom"
      hname_p1  = hname_prefix + "_p1"
      hname_m1  = hname_prefix + "_m1"
      
      prefit_nom = get_hist(prefit_file,hname_nom)
      prefit_nom.SetLineColor(prefit_color)
      prefit_nom.SetLineStyle(1)
      prefit_nom.SetLineWidth(linewidth)
      
      postfit_nom = get_hist(postfit_file,hname_nom)
      postfit_nom.SetLineStyle(1)
      postfit_nom.SetLineWidth(linewidth)
      postfit_nom.SetLineColor(ROOT.kBlack)
      
      hplus_prefit   = get_hist(prefit_file,hname_p1)
      hminus_prefit  = get_hist(prefit_file,hname_p1)
      hplus_postfit  = get_hist(postfit_file,hname_p1)
      hminus_postfit = get_hist(postfit_file,hname_p1)
      
      hists = [prefit_nom, postfit_nom, hplus_prefit,hminus_prefit,hplus_postfit,hminus_postfit]
    
      for h in hists:
        samp_hists.append(h)
        all_hists.append(h)
        
        h.GetXaxis().SetTitleSize(title_size)
        h.GetYaxis().SetTitleSize(title_size)
        h.GetXaxis().SetLabelSize(label_size)
        h.GetYaxis().SetLabelSize(label_size)
        h.GetXaxis().SetTitle("E_{reco}")
        h.GetYaxis().SetTitle("Events per bin")
        h.SetTitle("")
        h.GetXaxis().SetRangeUser(0.,max_energy)
        h.GetYaxis().SetTitleOffset(title_offset)
      
      for h in [hplus_prefit,hminus_prefit]:
        #~ h.SetLineColor(postfit_color)
        h.SetLineStyle(0)
        h.SetLineWidth(0)
        h.GetXaxis().SetRangeUser(0.,max_energy)
        
      for h in [hplus_postfit,hminus_postfit]:
        h.SetLineStyle(1)
        h.SetLineWidth(0)
        h.GetXaxis().SetRangeUser(0.,max_energy)
        
      legend = ROOT.TLegend(0.7,0.6,0.93,0.92);
      legend.SetFillStyle(0);
      legend.SetBorderSize(0);
      #~ legend.SetTextSize(0.04);
     
      limit = max([abs(h.GetMinimum()) for h in samp_hists] + [abs(h.GetMaximum()) for h in samp_hists])
      
      canv = ROOT.TCanvas()
      canv.SetLeftMargin  (left_margin)
      canv.SetBottomMargin(bottom_margin)
      canv.SetRightMargin (right_margin )
      if use_log_plots: canv.SetLogx()
      
      for h in samp_hists:
        h.SetMinimum(0.)
        h.SetMaximum(1.05*limit)
        
      env_hists = [(hplus_prefit  , hminus_prefit ) ,
                   (hplus_postfit , hminus_postfit)]
      
      env_graph_prefit  = ROOT.TGraphAsymmErrors(hplus_prefit  .GetXaxis().GetNbins())
      env_graph_postfit = ROOT.TGraphAsymmErrors(hplus_postfit .GetXaxis().GetNbins())
      
      env_graphs = [env_graph_prefit  ,
                    env_graph_postfit , ]
      
      for (hp,hm),g in zip(env_hists,env_graphs):
        for i in xrange(h.GetXaxis().GetNbins()):
          low_edge  = hplus_prefit.GetBinLowEdge(i+1)
          high_edge = low_edge + hplus_prefit.GetBinWidth(i+1)
          centre = prefit_nom.GetBinContent(i+1)
          g.SetPoint      (i,hplus_prefit.GetBinCenter(i+1),centre)
          g.SetPointEYlow (i,abs(hm.GetBinContent(i+1)-centre))
          g.SetPointEYhigh(i,abs(hp.GetBinContent(i+1)-centre))
          g.SetPointEXlow (i,hplus_prefit.GetBinWidth(i+1)*0.5)
          g.SetPointEXhigh(i,hplus_prefit.GetBinWidth(i+1)*0.5)
          
        g.GetXaxis().SetRangeUser(0,max_energy)
        CopyHistAxisFormatting(hplus_prefit,g)
        g.GetYaxis().SetTitle("Ratio of # Total Events")
        g.SetFillColor(postfit_color)
        
      hplus_prefit.GetYaxis().SetTitleOffset(title_offset)
      #~ hplus_prefit.SetLineColor(prefit_color)
      #~ hplus_prefit.SetFillColor(prefit_color)
      #~ hplus_prefit.SetFillStyle(prefit_style)
      
      hplus_prefit.Draw("AXIS")
      #~ hplus_postfit.SetFillColor(postfit_color)
      #~ hplus_postfit.SetFillStyle(postfit_style)
      #~ hminus_postfit.SetFillStyle(postfit_style)
      
      env_graph_prefit.SetFillStyle(prefit_style)
      env_graph_prefit.SetFillColor(prefit_color)
      env_graph_prefit.Draw("same2")
      
      env_graph_postfit.SetFillStyle(postfit_style)
      env_graph_postfit.SetLineStyle(0)
      env_graph_postfit.SetLineWidth(0)
      env_graph_postfit.SetMarkerStyle(ROOT.kFullSquare)
      env_graph_postfit.SetMarkerColor(postfit_color)
      env_graph_postfit.Draw("same2p")
      
      prefit_nom.Draw("same")
      postfit_nom.Draw("same")
      
      #~ hplus_postfit.Draw("same")
      #~ prefit_nom.Draw("same")
      #~ prefit_nom.Draw("same")
      #~ hplus_prefit.Draw("same")
      
      canv.RedrawAxis()
      
      legend_prefit = ROOT.TH1D(prefit_nom)
      legend_prefit.SetFillStyle(env_graph_prefit.GetFillStyle())
      legend_prefit.SetFillColor(env_graph_prefit.GetFillColor())
      legend_prefit.SetLineStyle(prefit_nom.GetLineStyle())
      legend_prefit.SetLineColor(prefit_nom.GetLineColor())
      legend_prefit.SetLineWidth(prefit_nom.GetLineWidth())
      
      legend_postfit = ROOT.TH1D(postfit_nom)
      legend_postfit.SetFillStyle(env_graph_postfit.GetFillStyle())
      legend_postfit.SetFillColor(env_graph_postfit.GetFillColor())
      legend_postfit.SetMarkerStyle(env_graph_postfit.GetMarkerStyle())
      legend_postfit.SetMarkerColor(env_graph_postfit.GetMarkerColor())
      legend_postfit.SetMarkerSize (env_graph_postfit.GetMarkerSize())
      
      all_hists.extend([legend_prefit,legend_postfit])
      
      legend.AddEntry(legend_prefit   ,"Prefit" ,"FP")
      legend.AddEntry(legend_postfit  ,"Postfit","FL")
      
      legend.Draw()
      
      canv.Print(hname_prefix+"_envelope."+img_format)
      
      # Now do it with ratios
      ratio_plus_prefit   = R.TH1D(hplus_prefit)
      ratio_minus_prefit  = R.TH1D(hminus_prefit)
      ratio_plus_postfit  = R.TH1D(hplus_postfit)
      ratio_minus_postfit = R.TH1D(hminus_postfit)
      
      ratio_plus_prefit  .Divide(prefit_nom)
      ratio_minus_prefit .Divide(prefit_nom)
      ratio_plus_postfit .Divide(prefit_nom)
      ratio_minus_postfit.Divide(prefit_nom)
      for i in xrange(prefit_nom.GetXaxis().GetNbins()):
        if abs(prefit_nom.GetBinContent(i+1))<conv.kASmallNum:
          ratio_plus_postfit .SetBinContent(i+1,1)
          ratio_minus_postfit.SetBinContent(i+1,1)
        if abs(prefit_nom.GetBinContent(i+1))<conv.kASmallNum:
          ratio_plus_prefit .SetBinContent(i+1,1)
          ratio_minus_prefit.SetBinContent(i+1,1)
      
      ratio_hists = [(ratio_plus_prefit  , ratio_minus_prefit ) ,
                     (ratio_plus_postfit , ratio_minus_postfit)]
      
      ratio_graph_prefit  = ROOT.TGraphAsymmErrors(ratio_plus_prefit  .GetXaxis().GetNbins())
      ratio_graph_postfit = ROOT.TGraphAsymmErrors(ratio_plus_postfit .GetXaxis().GetNbins())
      
      ratio_graphs = [ratio_graph_prefit  ,
                      ratio_graph_postfit , ]
      
      for (hp,hm),g in zip(ratio_hists,ratio_graphs):
        for i in xrange(h.GetXaxis().GetNbins()):
          low_edge  = ratio_plus_prefit.GetBinLowEdge(i+1)
          high_edge = low_edge + ratio_plus_prefit.GetBinWidth(i+1)
          g.SetPoint      (i,ratio_plus_prefit.GetBinCenter(i+1),1)
          g.SetPointEYlow (i,abs(hm.GetBinContent(i+1)-1))
          g.SetPointEYhigh(i,abs(hp.GetBinContent(i+1)-1))
          g.SetPointEXlow (i,ratio_plus_prefit.GetBinWidth(i+1)*0.5 - 0.005)
          g.SetPointEXhigh(i,ratio_plus_prefit.GetBinWidth(i+1)*0.5 - 0.005)
          
        g.SetFillStyle(1001)
        g.SetLineStyle(0)
        g.SetLineWidth(0)
        g.GetXaxis().SetRangeUser(0,max_energy)
        CopyHistAxisFormatting(hplus_prefit,g)
        g.GetYaxis().SetTitle("Ratio of # Total Events")
        
      ratio_graph_prefit .SetFillColor(prefit_color)
      ratio_graph_postfit.SetFillColor(postfit_color)
      ratio_graph_prefit .SetLineColor(prefit_color)
      ratio_graph_postfit.SetLineColor(postfit_color)
      
      ratio_graph_prefit .SetLineWidth(3)
      ratio_graph_postfit.SetLineWidth(3)
      ratio_graph_prefit .SetFillStyle(1001)
      ratio_graph_postfit.SetFillStyle(1001)
      
      canv2 = ROOT.TCanvas()
      canv2.SetLeftMargin  (left_margin)
      canv2.SetBottomMargin(bottom_margin)
      canv2.SetRightMargin (right_margin )
      if use_log_plots: canv2.SetLogx()
      canv2.cd()
      
      ratio_max = 1.3*ratio_plus_prefit .GetMaximum()
      
      ratio_graph_postfit.SetMaximum(ratio_max)
      ratio_graph_postfit.SetMinimum(2-ratio_max)
      
      ratio_graph_prefit .Draw("a2")
      ratio_graph_postfit.Draw("2")
      canv2.RedrawAxis()
      
      legend2 = ROOT.TLegend(0.5,0.85,0.93,0.94);
      legend2.SetFillStyle(0);
      legend2.SetBorderSize(0);
      legend2.SetNColumns(2)
      legend2.AddEntry(ratio_graph_prefit  ,"Prefit" ,"F")
      legend2.AddEntry(ratio_graph_postfit ,"Postfit","FL")
      
      legend2.Draw("same")
      canv2.Update() # Need to update here so line gets right maximum
      
      line_at_1 = ROOT.TLine(0,1,canv2.GetUxmax(),1)
      line_at_1.SetLineWidth(2)
      line_at_1.Draw("same")
      
      canv2.Update()
      
      canv2.Print(hname_prefix+"_envelope_ratio."+img_format)
      
      
      #~ # Print out some event rates
      #~ nom_events     = prefit_nom  .Integral()
      #~ p1_events_pre  = hplus_prefit  .Integral()
      #~ m1_events_pre  = hminus_prefit .Integral()
      #~ p1_events_post = hplus_postfit .Integral()
      #~ m1_events_post = hminus_postfit.Integral()
      #~ 
      #~ p1_percent_pre  = 100.*( (p1_events_pre -nom_events)/nom_events )
      #~ m1_percent_pre  = 100.*( (m1_events_pre -nom_events)/nom_events )
      #~ p1_percent_post = 100.*( (p1_events_post-nom_events)/nom_events )
      #~ m1_percent_post = 100.*( (m1_events_post-nom_events)/nom_events )
      #~ 
      #~ items = [name+"_"+par_set,to3dp.format(nom_events)]
      #~ items.append(to3dp.format(p1_events_pre ) +" ("+to3dp.format(p1_percent_pre )+"%)")
      #~ items.append(to3dp.format(m1_events_pre ) +" ("+to3dp.format(m1_percent_pre )+"%)")
      #~ items.append(to3dp.format(p1_events_post) +" ("+to3dp.format(p1_percent_post)+"%)")
      #~ items.append(to3dp.format(m1_events_post) +" ("+to3dp.format(m1_percent_post)+"%)")
      #~ print "\t".join(items)
      
  return

class DUNEAnaError(Exception):
  pass
  
def CopyHistAxisFormatting(hfrom,hto):
  for (afrom,ato) in [(hfrom.GetXaxis(),hto.GetXaxis()),
                      (hfrom.GetYaxis(),hto.GetYaxis())]:
    ato.SetTitle      (afrom.GetTitle      ())
    ato.SetTitleOffset(afrom.GetTitleOffset())
    ato.SetTitleSize  (afrom.GetTitleSize  ())
    ato.SetLabelSize  (afrom.GetLabelSize  ())
    ato.SetLabelOffset(afrom.GetLabelOffset())
    
  return
  
def get_hist(rootfile,hname):
  h = rootfile.Get(hname)
  if not h:
    print "Failed to get histogram: ",hname ; exit()
  return ROOT.TH1D( h )

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make plots of size of systematic/statistical effects")
  #~ parser.add_option('-s', dest='sample',default="RHC1Rmu"  ,help='The sample')
  parser.add_option('-a','--prefit', dest='prefit'  ,default=default_prefit_input_file  ,help='The prefit input ROOT file')
  parser.add_option('-b','--postfit', dest='postfit',default=default_postfit_input_file,help='The postfit input ROOT file')
  parser.add_option('-f','--format', dest='imgformat',default='eps',help='The image format')
  
  options,other = parser.parse_args()
  
  if other:
    print "Bad arguments: ",other
    exit(-1)
  
  main(options.prefit,options.postfit,options.imgformat)
