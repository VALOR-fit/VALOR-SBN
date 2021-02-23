#!/usr/bin/env python

# Script to make plots of relative error envelope sizes
# eg plots 9-12 in TN-183
# Takes output of macros/spectrum/test_sk_ereco_spectrum_twk_sys_throw_runAll.py

#Steve Dennis, October 2013

from __future__ import division
import ROOT
import math
import os
import glob

ROOT.PyConfig.IgnoreCommandLineOptions = True

R = ROOT

max_energy = 3.
linewidth = 1
title_offset = 1.2
left_margin   = 0.13
bottom_margin = 0.15
right_margin  = 0.05
top_margin    = 0.08
use_log_plots = False
title_size = 0.05
label_size = 0.04
font = 132 # Times Medium, scalable rotatable

data_color    = ROOT.kPink+5
prefit_color  = ROOT.kAzure+7
prefit_line   = ROOT.kAzure-1
postfit_color = ROOT.kOrange-3
postfit_line  = ROOT.kOrange+2

data_style    = 1001 # Solid
prefit_style  = 3017 # Hatched
postfit_style = 3018 # Solid

to3dp = "{0:.3f}"

default_data_input_file = (
  "")
default_prefit_input_file = (
  "")
default_postfit_input_file = (
  "")

ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

colors = [ROOT.kBlack, R.kRed, R.kBlue, ROOT.kMagenta+1,  ROOT.kGreen+2, ROOT.kOrange+7, ROOT.kCyan+2,]

plot_opt = ""

try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_EXPT/root/valor_expt.C");

valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

def main(config, data_fn, prefit_fn, postfit_fn, data_label, prefit_label, postfit_label, tag, write_tex, img_format,ratio_mult, datatag, det, mdc, ratio):

  pre_and_postfit_envelope(config, data_fn, prefit_fn, postfit_fn, data_label, prefit_label, postfit_label, tag, write_tex, img_format,ratio_mult, datatag, det, mdc, ratio)


def pre_and_postfit_envelope(config, data_file, prefit_file, postfit_file, data_label, prefit_label, postfit_label, tag,write_tex,img_format, ratio_mult, datatag, det, mdc, ratio):

  envelope_images = []
  ratio_images = []
  envelope_captions = []
  ratio_captions = []

  elem = valor.CompoundFitElements()
  elem.Read(util.CompleteConfigPath(config),"nomc nosplines")
  cm = elem.FitModel()
  fd = elem.FitData()

  plot_data    = False
  plot_prefit  = False
  plot_postfit = False

  f_data = ROOT.TFile()
  if data_file:
    f_data = ROOT.TFile(data_file)
    plot_data = True

  f_prefit = ROOT.TFile()
  if prefit_file:
    f_prefit = ROOT.TFile(prefit_file)
    plot_prefit = True

  f_postfit = ROOT.TFile()
  if postfit_file:
    f_postfit = ROOT.TFile(postfit_file)
    plot_postfit = True

  n_files = int(plot_data) + int(plot_prefit) + int(plot_postfit)

  #if n_files < 2:
  #  raise DUNEAnaError("Must pass at least 2 files to plot")

  for imodel in xrange(cm.GetNSubModels()):
    all_labels   = []
    all_legend   = []
    all_hists    = []
    all_graphs   = []
    ratio_labels = []
    ratio_legend = []
    ratio_hists  = []
    ratio_graphs = []

    m = cm.GetSubModel(imodel)
    s = m.GetSample()
    b = m.GetBeam()

    hname_prefix = "env_sb_%s_%s" % (util.BeamConfAsString(b) , util.SampleAsString(s))
    # When running all tweaks at the same time, specify using the detector identifier:
    #hname_nom = hname_prefix + "_nom;" + det
    #hname_p1  = hname_prefix + "_p1;" + det
    #hname_m1  = hname_prefix + "_m1;" + det
    # When running the tweaks for each detector individually:
    hname_nom = hname_prefix + "_nom"#;1"
    hname_p1  = hname_prefix + "_p1"#;1"
    hname_m1  = hname_prefix + "_m1"#;1"
    #hname_data = "toymc_data_sb_rf_sbn_icarus__BNB_FHC__numulikeCChigh_Ereco"
    if det == '1':
      if mdc is False:
        hname_data = "valor_pdfts_sb_rf_sbn_nd__%s__%s_Ereco" % (util.BeamConfAsString(b), util.SampleAsString(s))
      else:
        hname_data = "toymc_data_sb_rf_sbn_nd__%s__%s" % (util.BeamConfAsString(b), util.SampleAsString(s))

    elif det == '2':
      if mdc is False:
        hname_data = "valor_pdfts_sb_rf_sbn_uboone__%s__%s_Ereco" % (util.BeamConfAsString(b), util.SampleAsString(s))
      else:
        hname_data = "toymc_data_sb_rf_sbn_uboone__%s__%s" % (util.BeamConfAsString(b), util.SampleAsString(s))

    elif det == '3':
      if mdc is False:
        hname_data = "valor_pdfts_sb_rf_sbn_icarus__%s__%s_Ereco" % (util.BeamConfAsString(b), util.SampleAsString(s))
      else:
        hname_data = "toymc_data_sb_rf_sbn_icarus__%s__%s" % (util.BeamConfAsString(b), util.SampleAsString(s))

    else:
      hname_data = "valor_pdfts_sb_rf_sbn_nd__%s__%s_Ereco" % (util.BeamConfAsString(b), util.SampleAsString(s))
      print("No detector given, defaulting to the ND")

    print "Data histogram found: ", hname_data
    print "MC histogram found: ", hname_nom

    out_prefix = "%s_sb_%s_%s" % (tag, util.BeamConfAsString(b) , util.SampleAsString(s))

    hists         = []
    prefit_plots  = []
    postfit_plots = []

    if plot_data:
      data_nom       = get_hist(f_data,hname_data)
      hists.append(data_nom)

    if plot_prefit:
      prefit_nom    = get_hist(f_prefit,hname_nom)
      hplus_prefit  = get_hist(f_prefit,hname_p1)
      hminus_prefit = get_hist(f_prefit,hname_m1)
      hists.extend([prefit_nom, hplus_prefit, hminus_prefit])
      prefit_plots.extend([prefit_nom, hplus_prefit, hminus_prefit])

    if plot_postfit:
      postfit_nom    = get_hist(f_postfit,hname_nom)
      hplus_postfit  = get_hist(f_postfit,hname_p1)
      hminus_postfit = get_hist(f_postfit,hname_m1)
      hists.extend([postfit_nom, hplus_postfit, hminus_postfit])
      postfit_plots.extend([postfit_nom, hplus_postfit, hminus_postfit])

    for h in hists:
      h.UseCurrentStyle()

      h.GetXaxis().SetTitleSize(title_size)
      h.GetYaxis().SetTitleSize(title_size)
      h.GetXaxis().SetLabelSize(label_size)
      h.GetYaxis().SetLabelSize(label_size)
      h.GetXaxis().SetTitle("Reconstructed Neutrino Energy [GeV]")
      h.GetYaxis().SetTitle("Event rate / 1 GeV")
      h.SetTitle("")
      h.GetXaxis().SetRangeUser(0.,max_energy)
      h.GetYaxis().SetTitleOffset(title_offset)
      h.GetYaxis().SetMaxDigits(3)

    legend = ROOT.TLegend(0.46,0.66,0.91,0.86);
    legend.SetFillStyle(0);
    legend.SetBorderSize(0);

    canv_name = "c_%s" % util.SampleAsString(s)
    canv = ROOT.TCanvas(canv_name,"",700,900)
    canv.SetLeftMargin  (left_margin)
    canv.SetBottomMargin(bottom_margin)
    canv.SetRightMargin (right_margin )
    canv.SetTopMargin (top_margin )
    if use_log_plots: canv.SetLogx()

    env_hists  = []
    env_graphs = []

    if plot_prefit:
      env_hists.append(prefit_plots)
      env_graph_prefit = ROOT.TGraphAsymmErrors(hplus_prefit  .GetXaxis().GetNbins())
      env_graphs.append(env_graph_prefit)
    if plot_postfit:
      env_hists.append(postfit_plots)
      env_graph_postfit = ROOT.TGraphAsymmErrors(hplus_postfit  .GetXaxis().GetNbins())
      env_graphs.append(env_graph_postfit)

    for (hn,hp,hm),g in zip(env_hists,env_graphs):
      for i in xrange(hp.GetXaxis().GetNbins()):
        low_edge  = hp.GetBinLowEdge(i+1)
        high_edge = low_edge + hp.GetBinWidth(i+1)
        centre    = hn.GetBinContent(i+1)
        y_centre  = centre / hp.GetBinWidth(i+1)
        y_low     = abs(hm.GetBinContent(i+1)-centre) / hm.GetBinWidth(i+1)
        y_high    = abs(hp.GetBinContent(i+1)-centre) / hp.GetBinWidth(i+1)
        g.SetPoint      (i, hp.GetBinCenter(i+1), y_centre)
        g.SetPointEYlow (i, y_low)
        g.SetPointEYhigh(i, y_high)
        g.SetPointEXlow (i,hp.GetBinWidth(i+1)*0.5)
        g.SetPointEXhigh(i,hp.GetBinWidth(i+1)*0.5)

#        print("Energy range {} - {}, fractional error {}".format(low_edge,high_edge,y_low/y_centre))

      g.GetXaxis().SetRangeUser(0,max_energy)
      CopyHistAxisFormatting(hp,g)
      g.GetYaxis().SetTitle("Ratio of # Total Events")


    widths    = []
    integrals = []
    wintegrals = []

    if plot_data:
      data_width = data_nom
      widths.append(data_width)
    if plot_prefit:
      prefit_width = prefit_nom
      widths.append(prefit_width)
    if plot_postfit:
      postfit_width = postfit_nom
      widths.append(postfit_width)

    for w in widths:
      for i in xrange(w.GetXaxis().GetNbins()):
        old_bin_content = w.GetBinContent(i+1)
        bin_width       = w.GetXaxis().GetBinWidth(i+1)
        new_bin_content = old_bin_content/bin_width
        w.SetBinContent(i+1,new_bin_content)
      wintegrals.append(w.Integral("width"))
      integrals.append(w.Integral())

    if det == '1':
      max_y = max(wintegrals)*1.4
    else:
      max_y = max(wintegrals)*1.4

    envelope_fn = out_prefix+"_envelope."+img_format
    f_output = ROOT.TFile(envelope_fn,"RECREATE")
    if not f_output.IsOpen():
      print "Unable to open root file named: ", envelope_fn
    else:
      print "Opened output file named: ", envelope_fn

    ROOT.gDirectory.cd()

    if plot_prefit:
      hplus_prefit.GetYaxis().SetRangeUser(1, max_y)
      hplus_prefit.GetYaxis().SetTitleOffset(title_offset)
      hplus_prefit.SetLineColor(prefit_color)
      hplus_prefit.SetLineStyle(1)
      hplus_prefit.Draw("AXIS same")

      env_graph_prefit.SetFillStyle(prefit_style)
      env_graph_prefit.SetFillColor(prefit_color)
      env_graph_prefit.SetLineWidth(0)
      env_graph_prefit.SetLineStyle(0)
      env_graph_prefit.SetMarkerStyle(ROOT.kFullSquare)
      env_graph_prefit.SetMarkerColor(prefit_color)
      env_graph_prefit.Draw("same2")

      prefit_width.SetLineWidth(linewidth)
      prefit_width.SetLineStyle(1)
      prefit_width.SetLineColor(prefit_line)
      prefit_width.Draw("same")

      legend_prefit = ROOT.TH1D(prefit_width)
      legend_prefit.SetLineStyle(5)
      legend_prefit.SetFillStyle(env_graph_prefit.GetFillStyle())
      legend_prefit.SetFillColor(env_graph_prefit.GetFillColor())
      legend_prefit.SetMarkerStyle(env_graph_prefit.GetMarkerStyle())
      legend_prefit.SetMarkerColor(env_graph_prefit.GetMarkerColor())
      legend_prefit.SetMarkerSize (env_graph_prefit.GetMarkerSize())

      if ratio == '1' or ratio == '2' or ratio == '3':
        print "Filling ratio list with prefit"
        ratio_hists.append(prefit_width)
        ratio_graphs.append(env_graph_prefit)
        ratio_labels.append(prefit_label)
        ratio_legend.append(legend_prefit)

      all_hists.append(prefit_width)
      all_graphs.append(env_graph_prefit)
      all_labels.append(prefit_label)
      all_legend.append(legend_prefit)

      legend.AddEntry(legend_prefit, prefit_label, "FL")

      prefit_width.Write("prefit_hist")
      env_graph_prefit.Write("prefit_env")

    if plot_postfit:
      hplus_postfit.GetYaxis().SetRangeUser(1, max_y)
      hplus_postfit.GetYaxis().SetTitleOffset(title_offset)
      hplus_postfit.Draw("AXIS same")

      env_graph_postfit.SetFillStyle(postfit_style)
      env_graph_postfit.SetFillColor(postfit_color)
      env_graph_postfit.SetLineWidth(0)
      env_graph_postfit.SetLineStyle(0)
      env_graph_postfit.SetMarkerStyle(ROOT.kFullSquare)
      env_graph_postfit.SetMarkerColor(postfit_color)
      env_graph_postfit.Draw("same2")

      postfit_width.SetLineWidth(linewidth)
      postfit_width.SetLineStyle(7)
      postfit_width.SetLineColor(postfit_line)
      postfit_width.Draw("same")

      if plot_prefit:
        prefit_width.SetLineStyle(5)
        prefit_width.Draw("same")

      legend_postfit = ROOT.TH1D(postfit_width)
      legend_postfit.SetFillStyle(env_graph_postfit.GetFillStyle())
      legend_postfit.SetFillColor(env_graph_postfit.GetFillColor())
      legend_postfit.SetMarkerStyle(env_graph_postfit.GetMarkerStyle())
      legend_postfit.SetMarkerColor(env_graph_postfit.GetMarkerColor())
      legend_postfit.SetMarkerSize (env_graph_postfit.GetMarkerSize())

      if ratio == '0' or ratio == '1':
        print "Filling ratio list with postfit"
        ratio_hists.append(postfit_width)
        ratio_graphs.append(env_graph_postfit)
        ratio_labels.append(postfit_label)
        ratio_legend.append(legend_postfit)

      all_hists.append(postfit_width)
      all_graphs.append(env_graph_postfit)
      all_labels.append(postfit_label)
      all_legend.append(legend_postfit)

      legend.AddEntry(legend_postfit, postfit_label, "FL")

      postfit_width.Write("postfit_hist")
      env_graph_postfit.Write("postfit_env")

    if plot_data:
      data_width.SetLineColor(data_color)
      data_width.SetLineStyle(2)
      data_width.SetLineWidth(linewidth+1)
      data_width.Draw("same")

      legend_data = ROOT.TH1D(data_width)
      legend_data.SetLineStyle(data_width.GetLineStyle())
      legend_data.SetLineColor(data_width.GetLineColor())
      legend_data.SetLineWidth(data_width.GetLineWidth())

      if ratio == '0' or ratio == '2' or ratio == '3':
        print "Filling ratio list with data"
        ratio_hists.append(legend_data)
        ratio_graphs.append(legend_data)
        ratio_labels.append(data_label)
        ratio_legend.append(legend_data)

      all_hists.append(legend_data)
      all_graphs.append(legend_data)
      all_labels.append(data_label)
      all_legend.append(legend_data)

      legend.AddEntry(legend_data, data_label, "L")

      data_width.Write("data_hist")

    canv.RedrawAxis()

    legend.SetTextFont(font)
    legend.Draw()
    legend.Write("legend")
    canv.Write("c")
    envelope_images.append(envelope_fn)
    cap = "%s %s %s"%(tag,util.BeamConfAsString(b),util.SampleAsString(s))
    envelope_captions.append(cap.replace("_"," "))

    # Make sure at least two plots are being overlaid for the ratio
    plot_n   = plot_data+plot_postfit+plot_prefit
    if plot_n > 1 and ratio >= 0 and ratio_hists:

      # Now if we want to plot the overlay and the ratio, repeat and split the pads
      r_legend = ROOT.TLegend(0.49,0.67,0.96,0.86);
      r_legend.SetFillStyle(0);
      r_legend.SetBorderSize(0);

      r_canv_name = "cr_%s" % util.SampleAsString(s)
      r_canv = ROOT.TCanvas(r_canv_name,"",750,900)
      if use_log_plots: r_canv.SetLogx()

      # Top pad: all histograms with envelopes
      # Setup the pad
      pad1 = ROOT.TPad("pad1","",0.0,0.35,1.0,1.0);
      pad1.SetBottomMargin(0.02);
      pad1.SetTopMargin(0.05);
      pad1.SetRightMargin(0.02);
      pad1.Draw();
      pad1.cd();

      # Loop over all the histograms
      for i, h in enumerate(all_hists):
        label = all_labels[i]
        graph = all_graphs[i]
        legend = all_legend[i]
        if i == 0:
          h.Draw()
          graph.Draw("same2")
          h.GetYaxis().SetRangeUser(0.,max_y)
          h.GetYaxis().SetTitleSize(0.045)
          h.GetYaxis().SetTitleOffset(1.4)
          h.GetYaxis().SetLabelSize(0.035)
          h.GetXaxis().SetLabelColor(0)
        else:
          h.Draw("same")
          graph.Draw("same2")
        r_legend.AddEntry(legend,label,"FL")
      r_legend.SetTextFont(font)
      r_legend.Draw()

      pad1.Modified();
      r_canv.cd();

      # Bottom pad: data postfit ratio
      pad2 = ROOT.TPad("pad2","",0.0,0.0,1.0,0.35);
      pad2.SetTopMargin(0.02);
      pad2.SetBottomMargin(0.22);
      pad2.SetRightMargin(0.02);
      pad2.SetGridy();
      pad2.Draw();
      pad2.cd();

      # Get the percentage rate difference between the plots
      ratio_diff = ROOT.TH1D(ratio_hists[0])
      if ratio != '3':
        ratio_diff.Add(ratio_hists[1],-1)

      # Get the magnitude of the uncertainty on each bin and scale the bin content by it
      yhigh = -1.
      ylow  = -1.
      if ratio == '2':
        yhigh = env_graph_prefit.GetEYhigh()
        ylow  = env_graph_prefit.GetEYlow()
      elif ratio == '0' or ratio == '1':
        yhigh = env_graph_postfit.GetEYhigh()
        ylow  = env_graph_postfit.GetEYlow()


      if ratio != '3':
        for b in range(ratio_diff.GetNbinsX()):
          if yhigh[b] < 0 or ylow[b] < 0:
            print "Error: Negative uncertainty defined: ", yhigh, ", ", ylow
            util.Die(-1)
          yavg  = (yhigh[b]+ylow[b])/2.
          ratio_diff.SetBinContent(b,ratio_diff.GetBinContent(b)/yavg)
      else:
        ratio_diff.Divide(ROOT.TH1D(ratio_hists[1]))


      ratio_diff.Draw("hist")
      ratio_diff.SetLineColor(ROOT.kTeal-5)
      ratio_diff.SetLineStyle(1)
      ratio_diff.SetLineWidth(linewidth)
      if ratio == '0':
        ratio_diff.GetYaxis().SetTitle("#frac{(Postfit-Mock data)}{#sigma_{Postfit}}");
      elif ratio == '1':
        ratio_diff.GetYaxis().SetTitle("#frac{(Prefit-Postfit)}{#sigma_{Postfit}}");
      elif ratio == '2':
        ratio_diff.GetYaxis().SetTitle("#frac{(Prefit-Mock data)}{#sigma_{Prefit}}");
      elif ratio == '3':
        ratio_diff.GetYaxis().SetTitle("#frac{Prefit}{Mock data}");

      ratio_diff.GetYaxis().SetTitleFont(132);
      ratio_diff.GetYaxis().SetLabelFont(132);
      ratio_diff.GetYaxis().SetTitleSize(0.075);
      ratio_diff.GetYaxis().SetTitleOffset(0.75);
      ratio_diff.GetYaxis().SetLabelSize(0.065);
      ratio_diff.GetXaxis().SetTitleFont(132);
      ratio_diff.GetXaxis().SetLabelFont(132);
      ratio_diff.GetXaxis().SetTitleSize(0.075);
      ratio_diff.GetXaxis().SetTitleOffset(1.1);
      ratio_diff.GetXaxis().SetLabelSize(0.065);
      ratio_diff.GetXaxis().SetLabelColor(1);
      ratio_diff.GetYaxis().SetRangeUser(0,2)

      r_canv.RedrawAxis()
      r_canv.Write("cr")
      r_canv.SaveAs("testSave.png")

    f_output.Close()
  # End of model loop

  if (write_tex):
    tex = start_latex_file("%s_envelopes.tex"%(tag))
    add_figures_to_tex(tex,envelope_images,envelope_captions)
    tex.write("\n\n\\clearpage\n\n")
    add_figures_to_tex(tex,ratio_images,ratio_captions)
    end_latex_file(tex)

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

def start_latex_file(name):
  f = open(name,"w")
  f.write(r"""\documentclass[10pt]{article}
\usepackage[utf8]{inputenc}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{fullpage}
\usepackage{graphicx}
\usepackage{float}
\usepackage{setspace}

\setlength\parindent{0pt}

\begin{document}

\begin{doublespacing}

""")
  return f

def end_latex_file(f):
  f.write(r"""
\end{doublespacing}
\end{document}""")
  f.close()

def add_figures_to_tex(f,figure_names,captions,plots_per_row=2):
  figure_width  = str(0.99/float(plots_per_row))+"\\textwidth"

  n_figs = len(figure_names)
  for i in xrange(n_figs):
    if (i%plots_per_row == 0):
      f.write(" \\begin{figure*}\n")
    image = figure_names[i]
    caption = captions[i]
    label =  "fig:"+image.split("/")[-1].rsplit(".",1)[0]
    f.write("\n \\begin{minipage}[t]{"+figure_width+"}\n")
    f.write("  \\includegraphics[width=0.95\\textwidth]{"+image+"}\n")
    f.write("  \\caption{"+caption+"}\n")
    f.write("  \\label{"+label+"}\n")
    f.write("\\end{minipage}")
    if i%plots_per_row or i==n_figs-1:
      f.write("\\end{figure*}\n")
  return

if __name__=="__main__":
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make plots of size of systematic/statistical effects")
  parser.add_option('-c','--config', dest='config'  ,default="fit/dunend_fit.xml",help='The config file we get the sample list from.')
  parser.add_option('-a','--data', dest='data'  ,default=default_data_input_file  ,help='The data input ROOT file')
  parser.add_option('--alabel', dest='data_label'  ,default="Data"  ,help='The label for the data')
  parser.add_option('-b','--postfit', dest='postfit',default=default_postfit_input_file,help='The postfit input ROOT file')
  parser.add_option('--blabel', dest='postfit_label'  ,default="Postfit"  ,help='The label for the postfit')
  parser.add_option('-p','--prefit', dest='prefit',default=default_prefit_input_file,help='The prefit input ROOT file')
  parser.add_option('--plabel', dest='prefit_label'  ,default="Prefit"  ,help='The label for the prefit')
  parser.add_option('-f','--format', dest='imgformat',default='eps',help='The image format')
  parser.add_option('-t','--tag', dest='tag',default='env',help='Prefix for output filenames')
  parser.add_option('-w','--write-tex', dest='tex',action="store_true",default=False,help='Write TeX file with images in.')
  parser.add_option('-r','--ratio-mult', dest='ratiomult',type=float,default=None,help='Multiply the postfit envelope size in the ratio plots by this number.')
  parser.add_option('-d','--datatag', dest='datatag',default='toymc',help='Prefix for input data histogram name')
  parser.add_option('-e','--experiment', dest='det',default='',help='Experiment enum: SBND = 1, uBooNE = 2, ICARUS = 3')
  parser.add_option('-m','--mdc', dest='mdc',default=False,help='Whether or not we are looking at the Mock Data Challenge')
  parser.add_option('--ratio', dest='ratio',default='-1',help='Whether to take the ratio and of which two hists: -1 = no ratio, 0 = Data/Postfit, 1 = PostFit/Prefit, 2 = Data/Prefit')

  options,other = parser.parse_args()

  if other:
    print "Bad arguments: ",other
    exit(-1)

  main(options.config, options.data, options.prefit, options.postfit,
       options.data_label, options.prefit_label, options.postfit_label,
       options.tag, options.tex, options.imgformat, options.ratiomult,
       options.datatag, options.det, options.mdc, options.ratio)
