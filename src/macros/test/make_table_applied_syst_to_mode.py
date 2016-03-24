#!/usr/bin/python

import ROOT
import math
import array
import sys
import os

ROOT.PyConfig.IgnoreCommandLineOptions = True

base_dir = os.environ["VALOR_DUNE"]
try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x %s/root/valor_dune.C"%base_dir);
  
ROOT.gROOT.SetBatch(1)
  
valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()
rnd  =  valor.Rnd.Instance()

col1_width = 30
coln_width = 3

#______________________________________________________________________________________________________________________________

def main(beam_mode, sample,
         output_file="syst_applied_table.tex",
         config_file = "dune_ndfit.xml",
         skipflux=False, skipint=False, skipdet =False):
  
  model = valor.NDModel()
  model.Read(base_dir+"/config/"+config_file)
  
  
  # Some ridiculous voodoo to go around ROOT's inability to identify arrays of enums or 2D arrays of bools
  modes_array     = array.array("i",[-1]*conv.kNReacModes)
  nd_params_array = array.array("i",[-1]*conv.kNNDFitParams)
  
  ROOT.gROOT.ProcessLine("using namespace valor::conv;")
  root_loop  = "{ int * mode_arr = (int*)%s;" % str(modes_array.buffer_info()[0])
  root_loop += " for (int i = 0 ; i < kNReacModes;i++){mode_arr[i]=kNDReactionModes[%s][i];};};"%str(sample)
  ROOT.gROOT.ProcessLine(root_loop)
  root_loop  = "{ int * par_arr = (int*)%s;" % str(nd_params_array.buffer_info()[0])
  root_loop += " for (int i = 0 ; i < kNNDFitParams;i++){par_arr[i]=kNDFitParam[i];};};"
  ROOT.gROOT.ProcessLine(root_loop)
  
  modes  = [m for m in modes_array     if m != conv.kmUndefined]
  params = [p for p in nd_params_array if p != conv.kPhypUndefined]
  
  tex_output = open(output_file,"w")
  
  tex_output.write("""\documentclass[10pt]{article}
\\usepackage[utf8]{inputenc}
\\usepackage{amsmath}
\\usepackage{amsfonts}
\\usepackage{amssymb}
\\usepackage{fullpage}
\\usepackage{rotate}  
\\usepackage{rotating}
\\usepackage[paperwidth=800mm,paperheight=800mm]{geometry}
\\usepackage{varwidth}

\\newcommand{\ck}{$\\checkmark$}
\\begin{document}

\%\\begin{varwidth}{\\linewidth}

{
\\setlength{\\tabcolsep}{3pt}
\\renewcommand{\\arraystretch}{1.8}
""")
  
  tex_output.write("\\begin{table} \\tiny\n")
  #~ tex_output.write("\\centering\n")
  tex_output.write("\n\n\\begin{tabular} { | c ||"+("c | "*len(modes))+" | }\n\\hline\n")
  
  for mode in modes:
    tex_output.write(" & \\begin{sideways} $"+util.ModeAsStringTeX(mode)+"$ \end{sideways} \n")
  
  tex_output.write("\\\\ \hline \n")
  
  for param in params:
    entries = ["$"+util.ParamAsStringTeX(param,0).ljust(col1_width)+"$"]
    row = False
    for m in modes:
      if util.ParamIsAppliedTo(beam_mode,sample,m,param):
        entries.append("\\ck".ljust(coln_width))
        row = True
      else:
        entries.append("".ljust(coln_width))
    if row: tex_output.write("& ".join(entries) + " \\\\ \hline \n")
    
  tex_output.write("\n\\end{tabular}\n")
  tex_output.write("\\end{table}\n}\n")
  tex_output.write("\%\\end{varwidth}\n")
  tex_output.write("\\end{document}\n")
  
  print "\n\nTable output written to ",output_file

if __name__=="__main__":
  
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make tables of applied systematics")
  
  parser.add_option('-o', '--outfile', dest='output_file', default="syst_applied_table.tex", help="Name for output TeX file.")
  
  parser.add_option('-c', '--config', dest='config', default="dune_ndfit.xml", help="Configuration file")
  
  parser.add_option('-s', '--sample' , dest='sample'      , default="numuCC1trkQE"     , help="Sample (numuCC1trkQE etc)")
  parser.add_option('--skip-flux'    , dest='skipflux'    , action="store_true", default=False, help="Skip the flux parameters")
  parser.add_option('--skip-int'     , dest='skipint', action="store_true", default=False, help="Skip the interaction parameters")
  parser.add_option('--skip-det'     , dest='skipdet', action="store_true", default=False, help="Skip the detector parameters")
  
  o,other = parser.parse_args()
  beam = conv.kbFHC
  sample = util.NDSampleFromString(o.sample)
  main(beam,sample,o.output_file,o.config, o.skipflux, o.skipint, o.skipdet)
  
  if other:
    print "Warning - ignored arguments: ",other
