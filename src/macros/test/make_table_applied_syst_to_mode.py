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

def main(beam_mode_arg = None, sample_arg = None,
         output_file="syst_applied_table.tex",
         config_file = "dune_ndfit.xml",
         skipflux=False, skipint=False, skipdet =False, include_empty = False):
  
  model = valor.NDModel()
  model.Read(base_dir+"/config/"+config_file)
  
  
  # Some ridiculous voodoo to go around ROOT's inability to identify arrays of enums or 2D arrays of bools
  ROOT.gROOT.ProcessLine("using namespace valor;")
  ROOT.gROOT.ProcessLine("using namespace valor::util;")
  ROOT.gROOT.ProcessLine("using namespace valor::conv;")
  
  nd_params_array  = array.array("i",[-1]*conv.kNNDFitParams)
  
  root_loop  = "{ int * par_arr = (int*)%s;" % str(nd_params_array.buffer_info()[0])
  root_loop += " for (int i = 0 ; i < kNNDFitParams;i++){par_arr[i]=kNDFitParam[i];};};"
  ROOT.gROOT.ProcessLine(root_loop)
  
  params = [p for p in nd_params_array if p != conv.kPhypUndefined]


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
\\usepackage[paperwidth=400mm,paperheight=400mm]{geometry} % This is huge - use pdfcrop

\\newcommand{\ck}{$\\checkmark$}
\\begin{document}

""")

  first_page = True
  
  if beam_mode_arg is None:
    beam_modes = list(range(conv.kNBeamConf))
  else:
    beam_modes = [beam_mode_arg]
    
  for beam_mode in beam_modes:
    nd_samples_array = array.array("i",[-1]*conv.kNNDSamples)
    root_loop  = "{ int * smp_arr = (int*)%s;" % str(nd_samples_array.buffer_info()[0])
    root_loop += " for (int i = 0 ; i < kNNDSamples;i++){smp_arr[i]=kNDSample[%s][i];};};"%str(beam_mode)
    ROOT.gROOT.ProcessLine(root_loop)
    
    if sample_arg is None:
      samples = [s for s in nd_samples_array if s != conv.ksNDUndefined]
    else:
      samples = [sample_arg]
  
      
    for sample in samples:
      # Get the mode list for this sample
      modes_array      = array.array("i",[-1]*conv.kNReacModes)
      root_loop  = "{ int * mode_arr = (int*)%s;" % str(modes_array.buffer_info()[0])
      root_loop += "int is = NDArrIdx::Instance()->NDSampleIdx((BeamConf_t)%s,(NDSample_t)%s);"%(str(beam_mode),str(sample))
      root_loop += " for (int i = 0 ; i < kNReacModes;i++){mode_arr[i]=kNDReactionModes[is][i];};};"
      ROOT.gROOT.ProcessLine(root_loop)
      modes  = [m for m in modes_array     if m != conv.kmUndefined]
      
      if first_page:
        first_page = False
      else:
        tex_output.write("\n\\clearpage\n")
        
      # Begin the table
      tex_output.write("""{
\\setlength{\\tabcolsep}{3pt}
\\renewcommand{\\arraystretch}{1.8}\n""")
      tex_output.write("\\begin{table} \\tiny\n")
      #~ tex_output.write("\\centering\n")
      tex_output.write("\n\n\\begin{tabular} { | c ||"+("c | "*len(modes))+" | }\n\\hline\n")
      
      #  Write the first row (mode list)
      for mode in modes:
        tex_output.write(" & \\begin{sideways} $"+util.ModeAsStringTeX(mode)+"$ \\end{sideways} \n")
      
      tex_output.write("\\\\ \hline \n")
      
      # Write all the other rows (per param)
      for param in params:
        if skipflux and util.IsNuFluxRelated(param): continue
        if skipint  and util.IsNuIntRelated(param) : continue
        if skipdet  and util.IsNuDetRelated(param) : continue
        entries = ["$"+util.ParamAsStringTeX(param,0).ljust(col1_width)+"$"]
        include_row = include_empty
        for m in modes:
          if util.ParamIsAppliedTo(beam_mode,sample,m,param):
            entries.append("\\ck".ljust(coln_width))
            include_row = True
          else:
            entries.append("".ljust(coln_width))
        if not include_row: continue
        tex_output.write("& ".join(entries) + " \\\\ \\hline ")
        # Add second line if we're at the end of a group
        if util.GetNDParameterGroup(param)!=util.GetNDParameterGroup(param+1):
          tex_output.write(" \\hline ")
        tex_output.write("\n")
      
      # Close table and finalise tex document
      tex_output.write("\n\\end{tabular}\n")
      tex_output.write("\\caption{" + util.BeamConfAsString(beam_mode) +" "+util.NDSampleAsString(sample)+ "}\n")
      tex_output.write("\\end{table}\n}\n")
  
  
  
  tex_output.write("\\end{document}\n")
  
  print "\n\nTable output written to ",output_file

if __name__=="__main__":
  
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make tables of applied systematics")
  
  parser.add_option('-o', '--outfile', dest='output_file', default="syst_applied_table.tex", help="Name for output TeX file.")
  
  parser.add_option('-c', '--config', dest='config', default="dune_ndfit.xml", help="Configuration file")
  
  parser.add_option('-b', '--beam'   , dest='beam'     , default=None     , help="Beam current (FHC/RHC)")
  parser.add_option('-s', '--sample' , dest='sample'   , default=None     , help="Sample (numuCC1trkQE etc)")
  parser.add_option('--skip-flux'    , dest='skipflux' , action="store_true", default=False, help="Skip the flux parameters")
  parser.add_option('--skip-int'     , dest='skipint'  , action="store_true", default=False, help="Skip the interaction parameters")
  parser.add_option('--skip-det'     , dest='skipdet'  , action="store_true", default=False, help="Skip the detector parameters")
  parser.add_option('--include-empty', dest='incempty' , action="store_true", default=False, help="Write completely empty rows in the table")
  
  o,other = parser.parse_args()
  
  if o.beam is not None:
    beam = util.BeamConfFromString(o.beam)
  else:
    beam = None
  if o.sample is not None:
    sample = util.NDSampleFromString(o.sample)
  else:
    sample = None
  
  main(beam,sample,o.output_file,o.config, o.skipflux, o.skipint, o.skipdet,o.incempty)
  
  if other:
    print "Warning - ignored arguments: ",other
