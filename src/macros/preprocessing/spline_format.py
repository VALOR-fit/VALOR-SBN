#!/usr/bin/env python

import ROOT
import math
import array
import numpy as np
import sys
import os
import ctypes

try:
    ROOT.valor
except:
    ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");

env_var = "VALOR_DUNE"
  
ROOT.gROOT.SetBatch(1)
  
valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()
rnd  =  valor.Rnd.Instance()
arridx= util.ArrIdx.Instance()

# File naming convention
pattern = "[VERSION]_t2ksk.14a.neut5.3.2.13a_tuned_v1r1.[CURRENT].fine.[TYPE]_[SELECTION].root"

#samples   = ["1Rmu","1Re","RHC1Rmu","RHC1Re","MultiRe"]
samples = ["1Rmu"]

def get_systematics():
    return ["maqe_ccqe", "pfo_ccqe",
        "ebo_cc1pi", "ebo_cccoh", "ebo_ccoth", "ebo_ccqe", "ebo_mec",
        "ebo_nc1gamma", "ebo_nccoh", "ebo_ncoth", "ebo_ncpiz", "ebo_ncpipm",
        "ca5_cc1pi", "ca5_ncpiz", "ca5_ncpipm",
        "manff_cc1pi", "manff_ncpiz", "manff_ncpipm",
        "bgscl_cc1pi", "bgscl_ncpiz", "bgscl_ncpipm",
        "dismpishp_ccoth", "maqesf_ccqe", "mecpdd_mec",
        "erpa_A_ccqe", "erpa_B_ccqe", "erpa_D_ccqe", "erpa_E_ccqe"]

def get_mode_map():
    valor_modes = ["CCQE","CCcoh","CCMEC","CCoth","CC1piC","NCcoh","NCoth",
        "NC1piC","NC1pi0","NC1Gamma"]
    raw_modes = ["ccqe","cccoh","mec","ccoth","cc1pi","nccoh","ncoth","ncpipm",
        "ncpiz","nc1gamma"]
    return list(zip(raw_modes, valor_modes))

def get_flavour_map():
    raw_flavours = ["numu_x_numu","numubar_x_numubar",
        "nue_x_nue","nuebar_x_nuebar",
        "numu_x_nue","numubar_x_nuebar"]
    valor_flavours = ["numu","numubar",
        "nue","nuebar",
        "numutonue","numubartonuebar"]
    return list(zip(raw_flavours, valor_flavours))

def get_beam(sample):
    if sample in ["1Rmu","1Re","MultiRe"]:
        return "250ka"
    elif sample in ["RHC1Rmu","RHC1Re"]:
        return "m250ka"
    else:
        print "Error: Unknown sample ", sample
        sys.exit()

def get_selection_map(sample):
    if "1Re" in sample:
        return "nueselec"
    elif "1Rmu" in sample:
        return "numuselec"
    elif "MultiRe" in sample:
        return "cc1piselec"
    else:
        print "Error: Unknown sample ", sample
        sys.exit()

def build_spline_name(sample, syst, flavour, mode, true_bin, reco_bin):
    if "RHC" in sample:
        beam = "JPARC_RHC"
    else:
        beam  = "JPARC_FHC"
    if "1Rmu" in sample:
        selection = "1rmu"
    elif "1Re" in sample:
        selection = "1re"
    else:
        selection = "multire"
    return "spl_%s_%s_%s%s_%s_%d_%d".format(beam, selection, flavour, mode, syst, true_bin, reco_bin)

def main(version, path):
    modes = set()
    params = set()
    location = "/data/neutrino/t2k/phrdqd/analysis/valor/softw/t2xk/branches/neutrino2018_v1.0.0/inputs/official/2018/xsec/" + path
#    location = os.environ[env_var]+"/inputs/official/2017/xsec/" + path
    for sample in samples:
        current   = get_beam(sample)
        selection = get_selection_map(sample)
    
        output_file  = ROOT.TFile("splines_"+version+"_"+sample+".root","RECREATE") # Output for this sample's splines
    
        for orig_type,valor_type in get_flavour_map():
            # Find the right input file
            infile = pattern
            indir  = location
            for old,new in [("[CURRENT]"  ,current),
                            ("[TYPE]"     ,orig_type),
                            ("[SELECTION]",selection),
                            ("[VERSION]"  ,version) ]:
                infile   = infile .replace(old,new)
                indir    = indir.replace(old,new)
      
            print "Processing file: ",infile
            path = indir+"/"+infile
            tf = ROOT.TFile(path)
            if not tf:
                print "Failed to open file:\n",path
      
            # Loop over spline types - systematic+mode
            for syst in get_systematics():
                par  = ""
                mode = ""
                if "erpa" in syst:
                    ppar,coeff,mode = syst.split("_")
                    par = ppar +"_"+ coeff
                else:  
                    par,mode = syst.split("_")
                for (old,new) in get_mode_map():
                    mode = mode.replace(old,new)
            
                # Get all the splines for this systematic+mode
                spline_dict = dict()
                for key in tf.GetListOfKeys():
                    name = key.GetName()
                    if not (syst in name and "_sp_" in name):
                        continue
                    tokens = name.split("_")
                    p = tokens[1]
                    if p == "erpa":
                        p = "erpa_" + tokens[2]
                        m = tokens[3]
                    else:
                        m = tokens[2]
                    modes.add(m)
                    params.add(p)
                    spline_dict[name] = key.ReadObj()
          
                output_file.cd()
            
                # Loop over the splines - rename them and write them to the file.
                for orig_spl_name, spline in spline_dict.iteritems():
                    junk,bins = orig_spl_name.rsplit("_sp_")
            
                    true_bin,reco_bin = map(int,bins.split("_"))
                  
                    if reco_bin < 0:
                        continue
                    new_spl_name = build_spline_name(sample, par, valor_type, mode, true_bin, reco_bin)
                  
                    nknots = spline.GetNp()
                    knots = np.zeros(nknots,dtype=float)
                  
                    new_spline = ROOT.TSpline3(spline)
                    new_spline.SetName(new_spl_name)
                    
                    new_spline.Write(new_spl_name)
            tf.Close()
        output_file.Close()
    print "Params:"
    for p in params:
        print p
    print "Modes:"
    for m in modes:
        print m
  
if __name__=="__main__":
    import argparse
    parser = argparse.ArgumentParser(usage="%prog [options]..",description="Reformat splines")
    parser.add_argument('-v', '--version', help="Current spline version.")
    parser.add_argument('-l', '--location', help="Input spline location.")
    args = parser.parse_args()
    main(args.version, args.location)
 
