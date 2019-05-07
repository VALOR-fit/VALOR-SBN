#!/usr/bin/python

import ROOT
import math
import array
import sys
import os

R = ROOT

R.PyConfig.IgnoreCommandLineOptions = True

try:
  R.valor
except:
  R.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");
  
valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

col1_width = 12
coln_width = 20
to3dp = "{0:.3f}"
min_channels_to_landscape = 7   # If we get more than this number of channels, then switch the page to landscape orientation

#______________________________________________________________________________________________________________________________

def main(config_file,
  mixing12,mixing13,mixing23,dm12sq,dm23sq,deltacp,hierarchy,angle_scheme,octant,dmsqscheme,
  output_file,label):
  
  opt.gMassHierarchyAssumed = util.HierarchyFromString(hierarchy)
  opt.gOscMixingParamChoice = util.MixingTypeFromString(angle_scheme)
  opt.gOscOctantChoice = util.OctantFromString(octant)
  opt.gOscDmsqScheme = util.DmsqSchemeFromString(dmsqscheme)
  
  opt.SetDefaultParameterValues()
  
  phyp = valor.PhysHypothesis("3f_osc")
    
  fit_elements = valor.CompoundFitElements()
  fit_elements.Read(util.CompleteConfigPath(config_file))
  
  # ~ if mixing12 < 0.:
    # ~ mixing12 = opt.GetGlobalBestFit(conv.kPhypMixing12)
    # ~ print "Using default value for ",util.ParamAsString(conv.kPhypMixing12),": ",mixing12
  # ~ if mixing13 < 0.:
    # ~ #~ mixing13 = opt.GetGlobalBestFit(conv.kPhypMixing13)
    # ~ if hierarchy=="normal": mixing13 = conv.kT2KBestFitTheta13_NH
    # ~ else:                   mixing13 = conv.kT2KBestFitTheta13_IH
    # ~ print "Using default ("+hierarchy+") value for ",util.ParamAsString(conv.kPhypMixing13),": ",mixing13
  # ~ if mixing23 < 0.:
    # ~ mixing23 = opt.GetGlobalBestFit(conv.kPhypMixing23)
    # ~ print "Using default value for ",util.ParamAsString(conv.kPhypMixing23),": ",mixing23
  # ~ if dm12sq < 0.:
    # ~ dm12sq = opt.GetGlobalBestFit(conv.kPhypDm12sq)
    # ~ print "Using default value for ",util.ParamAsString(conv.kPhypDm12sq),": ",dm12sq
  # ~ if dm23sq < 0.:
    # ~ dm23sq = opt.GetGlobalBestFit(conv.kPhypDm23sq)
    # ~ print "Using default value for ",util.ParamAsString(conv.kPhypDm23sq),": ",dm23sq
  # ~ if deltacp <= -9:
    # ~ if hierarchy=="normal": deltacp = conv.kT2KBestFitDeltaCP_NH
    # ~ else:                   deltacp = conv.kT2KBestFitDeltaCP_IH
    # ~ print "Using default ("+hierarchy+") value for ",util.ParamAsString(conv.kPhypCPV),": ",deltacp
  
  osc_params = [(conv.kPhypMixing12,mixing12),
                (conv.kPhypMixing13,mixing13),
                (conv.kPhypMixing23,mixing23),
                (conv.kPhypCPV     ,deltacp ),
                (conv.kPhypDm12sq  ,dm12sq  ),
                (conv.kPhypDm23sq  ,dm23sq  ),]
  
  for p,val in osc_params:
    phyp.SetCurrValue(p,val)
    print util.ParamAsString(p).ljust(25),phyp.CurrValue(p)
  
  print "\n"
  
  tex_output = open(output_file,"w")
  
  tex_output.write("""\documentclass[10pt,a4paper]{article}
\\usepackage[utf8]{inputenc}
\\usepackage{amsmath}
\\usepackage{amsfonts}
\\usepackage{amssymb}
\\usepackage{fullpage}
\\usepackage{lscape}
\\usepackage{geometry}
\\geometry{margin=1in}
\\begin{document}
""")

  # Write osc params
  
  tex_output.write("\n\\section*{Job details}\n\n")
  
  tex_output.write("\n\\begin{minipage}[t]{0.5\\textwidth}")
  tex_output.write("\n\\begin{itemize}\n")
  for param,val in osc_params:
    tex_output.write("\\item[] "+util.RawParamAsStringTex(param)+" = "+str(phyp.CurrValue(param))+"\n")
  
  tex_output.write("\\end{itemize}\n\\end{minipage}")
    
  tex_output.write("\n\\\\\n\n")
  
  
  tex_output.write("Hierarchy: "+hierarchy.capitalize()+"\n\n")
  if label: tex_output.write(label+"\n\n")
  
  model = fit_elements.FitModel()
  model.Generate(phyp)
  
  n_submodels = model.GetNSubModels()
  
  for imodel in xrange(n_submodels):
    
    submodel = model.GetSubModel(imodel)
    submodel_name = submodel.Name()
    tag = "valor"
    model_arr = R.TObjArray()
    submodel.Write(model_arr,tag,"pdft_vf pdfc_vf")
    
    nev_tot = 0.
    
    modes = [m for m in submodel.GetReactionModes() if m >=0 and m<1E4]
    
    reac_types = []
    channels = [] # here channel is init neutrino flavour + final neutrino flavour
    
    for m in modes:
      init_flav  = util.ReacModeToInitFlavor(m)
      final_flav = util.ReacModeToFinalFlavor(m)
      reac_type  = util.ReacModeToType(m)
      if reac_type not in reac_types: reac_types.append(reac_type)
      channel = (init_flav,final_flav)
      if channel not in channels: channels.append(channel)

    if len(channels) > min_channels_to_landscape:
      tex_output.write("\\begin{landscape}\n")

      
    event_counts_per_channel         = dict() # Holds dictionaries of formatted strings
    total_event_counts_per_channel   = dict() # Holds float
    total_event_counts_per_reac_type = dict() # Holds float
    
    for reac_type in reac_types:
      event_counts_per_channel        [reac_type] = dict()
      total_event_counts_per_reac_type[reac_type] = 0.
      
    for channel in channels:
      total_event_counts_per_channel[channel] = 0.
      
    # Signal not implemented yet
    signal_events     = 0.
    background_events = 0.
    
    for m in modes:
      
      mode_name = util.ModeAsString(m)
      mode_array_name = ("%s_pdfc_ob_vf_%s_%s")%(tag,submodel_name,mode_name)
      spectrum = model_arr.FindObject(mode_array_name)
      
      assert(spectrum)
      
      channel = (util.ReacModeToInitFlavor(m),util.ReacModeToFinalFlavor(m))
      reac_type = util.ReacModeToType(m)
      
      nev = spectrum.Integral()
      nev_tot += nev
      total_event_counts_per_channel  [channel] += nev
      total_event_counts_per_reac_type[reac_type] += nev
      event_counts_per_channel[reac_type][channel] = to3dp.format(nev)
      
      # ~ if (signal_for_sample[sample_name]==spec): signal_events+=nev
      # ~ else: background_events+=nev
      
      # ~ print channel,"\t",util.ReacTypeAsString(reac_type),reac_type,"\t",event_counts_per_channel[reac_type][channel]
      
    
    # Format the chanenls in a nice way
    channel_pattern = r"$%s \rightarrow %s$"
    fancy_channels = dict([(c,channel_pattern%tuple(map(util.FlavourAsStringTeX,c))) for c in channels])
    fancy_channels["total"] = "Total"
    
    # Start writing output
    submodel_name_escaped_underscores = submodel_name.replace("_",r"\_")
    tex_output.write("\n\\section*{"+submodel_name_escaped_underscores+"}\n")
    tex_output.write("\\begin{tabular} { | l ||"+("r | "*len(channels))+"| r | }\n\\hline\n")
    tex_output.write(" "+"".ljust(col1_width)+" & "+ " & ".join([fancy_channels[c].ljust(coln_width) for c in channels+["total"]]) + " \\\\ \\hline\\hline\n")
    
    for reac_type in reac_types:
      ev = event_counts_per_channel[reac_type]
      if not total_event_counts_per_reac_type[reac_type]: continue
      reac_type_name = util.ReacTypeAsString(reac_type)
      tex_output.write(" "+reac_type_name.ljust(col1_width)+" & ")
      ev_counts = []
      for channel in channels:
        try:
          ev_counts.append(ev[channel].ljust(coln_width))
        except KeyError:
          ev_counts.append("N/A".ljust(coln_width))
      
      ev_counts.append(to3dp.format(total_event_counts_per_reac_type[reac_type]).ljust(coln_width))
          
      tex_output.write(" & ".join(ev_counts) + " \\\\ \\hline\n")
    
    # Write totals
    tex_output.write("\\hline\n")
    tex_output.write(" "+"Total".ljust(col1_width)+" & ")
    string_totals = [to3dp.format(total_event_counts_per_channel[channel]).ljust(coln_width) for channel in channels]
    string_totals.append(to3dp.format(nev_tot).ljust(coln_width))
    tex_output.write(" & ".join(string_totals) + " \\\\ \\hline\n")
    
    tex_output.write("\n\\end{tabular}\n")
    
    total_array_name = ("%s_pdft_ob_vf_%s")%(tag,submodel_name)
    
    total_spectrum  = model_arr.FindObject(total_array_name)
    assert(total_spectrum)
    total_events = total_spectrum.Integral()
    
    print submodel_name,total_events
    
    tex_output.write("\nTotal: "           +to3dp.format(total_events)     +"    ("+to3dp.format(nev_tot)+")\n\n")
    # ~ tex_output.write("\nTotal signal: "    +to3dp.format(signal_events)    +"\n\n")
    # ~ tex_output.write("\nTotal background: "+to3dp.format(background_events)+"\n\n")
    
    tex_output.write("POT: "+to3dp.format(submodel.GetPOT()*1E-20)+"E20\n\n")

    if len(channels) > min_channels_to_landscape:
      tex_output.write("\\end{landscape}\n")
        
    tex_output.write("\n\n\\clearpage\n\n")
    
  
  tex_output.write("\\end{document}\n")
  
  print "Table output written to ",output_file

if __name__=="__main__":
  
  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Make tables of validation spectra")

  # T2K+reactors (sinsqtheta)
  parser.add_option('--mixing12', dest='mixing12',default=0.304   ,type=float, help='Value of sinsqtheta12 or sinsq2theta12 depending on mixing param choice')
  parser.add_option('--mixing13', dest='mixing13',default=0.0248  ,type=float, help='Value of sinsqtheta13 or sinsq2theta13 depending on mixing param choice')
  parser.add_option('--mixing23', dest='mixing23',default=0.527   ,type=float, help='Value of sinsqtheta23 or sinsq2theta23 depending on mixing param choice')
  parser.add_option('--dm12sq'  , dest='dm12sq'  ,default=7.53E-5 ,type=float, help='Value of small mass splitting')
  parser.add_option('--dm23sq'  , dest='dm23sq'  ,default=2.51E-3 ,type=float, help='Value of large mass splitting')
  parser.add_option('--deltacp' , dest='deltacp' ,default=-1.55    ,type=float, help='Value of delta CP')

  parser.add_option(     '--hierarchy'          , dest="hierarchy"     , default="normal"    , help='Mass hierarchy: "normal" or "inverted"')
  parser.add_option('-m','--mixing-param-choice', dest="mixparamchoice", default="sinsqtheta", help='Mixing param coice: "sinsqtheta" or "sinsq2theta"')
  parser.add_option('-t','--mixing-param-octant', dest="mixparamoctant", default="two"       , help='Mixing param octant: "one" or "two"')
  parser.add_option('-a','--dmsq-scheme', dest="dmsqscheme", default="abs23"       , help='"abs23", "abs31" or "fogli"')
  
  parser.add_option('-f', '--file', dest='output_file', default="validation.tex", help="Name for output TeX file.")
  
  parser.add_option('-c', '--config', dest='config', default="default_configuration.xml", help="Configuration file")
  
  parser.add_option('-l', '--label' , dest='label' , default=None, help="Label to put in file.")
  
  v = optparse.Values()
  parser.parse_args(values=v) # v contains only the values that were specified, not defaults
  
  o,other = parser.parse_args()
  
  main(o.config,
    o.mixing12,o.mixing13,o.mixing23,o.dm12sq,o.dm23sq,o.deltacp,o.hierarchy,o.mixparamchoice,o.mixparamoctant,o.dmsqscheme,
    o.output_file,o.label)
  
  if other:
    print "Warning - ignored arguments: ",other
