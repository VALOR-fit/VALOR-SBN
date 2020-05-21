#!/usr/bin/env python

import ROOT
import math
import array
import sys
import os

ROOT.PyConfig.IgnoreCommandLineOptions = True

base_dir = os.environ["VALOR_EXPT"]
try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x %s/root/valor_expt.C"%base_dir);

ROOT.gROOT.SetBatch(1)

valor = ROOT.valor
util  = valor.util
conv  = valor.conv
opt   = valor.Opt.Instance()
env   = valor.Env.Instance()
rnd   = valor.Rnd.Instance()

col1_width = 30
coln_width = 3

#______________________________________________________________________________________________________________________________

def main(beam_mode_arg = None, sample_arg = None,
    output_file="syst_applied_table.tex",
    modeslist="",
    config_file = "dune_ndfit.xml",
    skipflux=False, skipint=False, skipdet =False, include_empty = False, color = True, unosc = False):

  elements = valor.CompoundFitElements();
  elements.Read(base_dir+"/config/"+config_file,"nosplines nomc")
  model = elements.FitModel()

  syst = model.GetSystematics()
  if not syst.Size():
    print "You haven't got any systematics defined. This is never going to work."
    exit(-1)


  tick_from_config = False
  if not modeslist:
    print "File containing the list of parameters and their associated modes not provided, will tick based on parameter configurations"
    tick_from_config = True

  ROOT.gROOT.ProcessLine("using namespace valor;")
  ROOT.gROOT.ProcessLine("using namespace valor::util;")
  ROOT.gROOT.ProcessLine("using namespace valor::conv;")

  # Start writing tex file
  tex_output = open(output_file,"w")

  tex_output.write("""\\documentclass[10pt]{article}
      \\usepackage[utf8]{inputenc}
      \\usepackage{amsmath}
      \\usepackage{amsfonts}
      \\usepackage{amssymb}
      \\usepackage{fullpage}
      \\usepackage{rotate}
      \\usepackage{rotating}
      \\usepackage[a1paper, landscape, margin=1cm]{geometry} % This is huge - use pdfcrop
      \\usepackage[table]{xcolor}
      \\usepackage{nopageno}
""")

  if color:
    tex_output.write("\\newcommand{\ck}{$\\cellcolor{green!50} \\checkmark$}\n")
  else:
    tex_output.write("\\newcommand{\ck}{$\\checkmark$}\n")

  tex_output.write("\\begin{document}\n")

  first_page = True

  for isubmodel in xrange(model.GetNSubModels()):
    submodel  = model.GetSubModel(isubmodel)
    sample    = submodel.GetSample()
    beam_mode = submodel.GetBeam()
    detector  = submodel.GetDetector()
    # Get the mode list for this sample
    modes  = [m for m in submodel.GetReactionModes() if m != conv.kmUndefined]

    if unosc:
      modes = [m for m in modes if util.ReacModeToInitFlavor(m) == util.ReacModeToFinalFlavor(m)]

    if first_page:
      first_page = False
    else:
      tex_output.write("\n\\clearpage\n")

    # Begin the table
    tex_output.write("""{
        \\setlength{\\tabcolsep}{6pt}
        \\renewcommand{\\arraystretch}{2}\n""")
    tex_output.write("\\begin{table} \\large\n")
    tex_output.write("\\centering\n")

    # Build the format row - single lines between similar modes, double lines if the neutrino flavour or current charge changes
    table_col_spec = "| c |"
    last_flav = -1
    last_was_cc = -1
    for mode in modes:
      flav  = util.ReacModeToInitFlavor(mode)
      is_cc = util.ModeIsCC(mode)
      if (flav!= last_flav or is_cc != last_was_cc):
        table_col_spec+="|"
      table_col_spec += " c |"
      last_flav = flav
      last_was_cc = is_cc

    tex_output.write("\n\n\\begin{tabular} { "+table_col_spec+" | }\n\\hline\n")

    #  Write the first row (mode list)
    for mode in modes:
      tex_output.write(" & \\begin{sideways} $"+util.ModeAsStringTeX(mode)+"$ \\end{sideways} \n")

    tex_output.write("\\\\ \hline \n")

    # Write all the other rows (per param)
    pool = valor.ParameterPool.Instance()
    for iparam in xrange(syst.Size()):
      param = pool.GetParam(syst.WhichParam(iparam))
      if skipflux and param.SearchCategories("flux")        : continue
      if skipint  and param.SearchCategories("interaction") : continue
      if skipdet  and param.SearchCategories("det")         : continue

      # Add second line if we're at the beginning of a new group
      # Also check for varying detector
      if iparam:
        this_categories = [c for c in param.GetCategories()]
        last_categories = [c for c in last_param.GetCategories()]
        if "sbnd" in param.GetName() and "sbn_nd" in submodel.Name() or "uboone" in param.GetName() and "uboone" in submodel.Name() or "icarus" in param.GetName() and "icarus" in submodel.Name():
          if this_categories!=last_categories:
            tex_output.write(" \\hline ")

      # Rewrite name for nice reading
      param_name = param.GetTeXName()
      param_long = param.GetName()
      if "numu" in param.GetTeXName() and not "numubar" in param.GetTeXName():
        param_name = param_name.replace("numu"," \\mbox{ } \\nu_{\\mu} \\mbox{ } ")
      elif "numubar" in param.GetTeXName():
        param_name = param_name.replace("numubar"," \\mbox{ } \\bar{\\nu_{\\mu}} \\mbox{ } ")
      elif "nue" in param.GetTeXName() and not "nuebar" in param.GetTeXName():
        param_name = param_name.replace("nue"," \\mbox{ } \\nu_{e} \\mbox{ } ")
      elif "nuebar" in param.GetTeXName():
        param_name = param_name.replace("nuebar"," \\mbox{ } \\bar{\\nu_{e}} \\mbox{ } ")

      entries = ["$"+param_name.ljust(col1_width)+"$"]
      include_row = include_empty
      for m in modes:
        if tick_from_config:
          if util.IsAppliedTo(param.GetApplyMask(),beam_mode,sample,detector,m,conv.kntArgon):
            entries.append("\\ck".ljust(coln_width))
            include_row = True
          else:
            entries.append("".ljust(coln_width))
        else: # If we want to define the ticks based on the modelist for the current parameter
          f = ROOT.TFile(modeslist)
          mytree   = f.ModeLists
          modelist = ROOT.vector('string')()
          mytree.SetBranchAddress(param_long,modelist)
          mytree.GetEntry(0)
          found_mode = False
          for l in modelist:
            if l == util.ModeAsString(m):
              found_mode = True
          if found_mode:
            entries.append("\\ck".ljust(coln_width))
            include_row = True
          else:
            entries.append("".ljust(coln_width))

      if not include_row: continue
      tex_output.write("& ".join(entries) + " \\\\ \\hline ")
      tex_output.write("\n")
      last_param = param

    # Close table and finalise tex document
    tex_output.write("\n\\end{tabular}\n")
    tex_output.write(("\\caption{" + util.DetectorAsString(detector)+" "+util.BeamConfAsString(beam_mode)+" "+util.SampleAsString(sample)+ "}\n").replace("_"," "))
    tex_output.write("\\end{table}\n}\n")

  # End of submodel loop


  tex_output.write("\\end{document}\n")

  print "\n\nTable output written to",output_file
  print "It's huge. I suggest using pdfcrop after building it."

if __name__=="__main__":

  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make tables of applied systematics")

  parser.add_option('-o', '--outfile', dest='output_file', default="syst_applied_table.tex", help="Name for output TeX file.")
  parser.add_option('-m', '--modes',   dest='modeslist',   default="", help="ROOT file containing the list of modes affected by each parameter")
  parser.add_option('-c', '--config',  dest='config',      default="fit/dune_ndfit.xml", help="Configuration file")

  parser.add_option('-b', '--beam'     , dest='beam'     , default=None     , help="Beam current (FHC/RHC)")
  parser.add_option('-s', '--sample'   , dest='sample'   , default=None     , help="Sample (numuCC1trkQE etc)")
  parser.add_option('--skip-flux'      , dest='skipflux' , action="store_true", default=False, help="Skip the flux parameters")
  parser.add_option('--skip-int'       , dest='skipint'  , action="store_true", default=False, help="Skip the interaction parameters")
  parser.add_option('--skip-det'       , dest='skipdet'  , action="store_true", default=False, help="Skip the detector parameters")
  parser.add_option('--include-empty'  , dest='incempty' , action="store_true", default=False, help="Write completely empty rows in the table")
  parser.add_option('-n',"--no-color"  , dest='nocolor'  , action="store_true", default=False, help="Color backgrounds of ticked cells")
  parser.add_option('-u',"--unosc-only", dest='unosc'    , action="store_true", default=False, help="Don't write oscillated modes.")

  o,other = parser.parse_args()

  if o.beam is not None:
    beam = util.BeamConfFromString(o.beam)
  else:
    beam = None
  if o.sample is not None:
    sample = util.SampleFromString(o.sample)
  else:
    sample = None

  main(beam, sample, o.output_file, o.modeslist, o.config, o.skipflux, o.skipint, o.skipdet, o.incempty, not o.nocolor, o.unosc)

  if other:
    print "Warning - ignored arguments: ",other
