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
models = dict()

def get_systematics():
    return ["maqe_ccqe", "pfo_ccqe",
        "ebo_cc1pi", "ebo_cccoh", "ebo_ccoth", "ebo_ccqe", "ebo_mec",
        "ebo_nc1gamma", "ebo_nccoh", "ebo_ncoth", "ebo_ncpiz", "ebo_ncpipm",
        "ca5_cc1pi", "ca5_ncpiz", "ca5_ncpipm",
        "manff_cc1pi", "manff_ncpiz", "manff_ncpipm",
        "bgscl_cc1pi", "bgscl_ncpiz", "bgscl_ncpipm",
        "dismpishp_ccoth", "maqe_ccqe", "mecpdd_mec",
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

def get_param_map():
    raw_params = ["ca5", "bgscl", "maqe", "manff", "pfo", "dismpishp",
        "erpa_A", "erpa_B", "erpa_D", "erpa_E", "mecpdd", "ebo"]
    valor_params = ["CA5", "ISO_BKG", "MAQE", "MARES", "pF_O", "CC_DIS",
        "BeRPA_A", "BeRPA_B", "BeRPA_D", "BeRPA_E", "2p2h_shape_O", "ebo"]
    return list(zip(raw_params, valor_params))

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
    new_syst = syst
    for (old, new) in get_param_map():
        new_syst = new_syst.replace(old, new)
    return "spl_%s_%s_%s%s_%s_%d_%d".format(beam, selection, flavour, mode, new_syst, true_bin, reco_bin)

def get_fit_elements():
    valor.Env.Instance().AutoSet("dune")
    config_file = os.environ[env_var] + "/config/analysis/t2k_analysis_configuration_oa2018_run1-9d_v1_postfit.xml"
    elements = valor.CompoundFitElements()
    elements.Read(config_file, "nomc+nosplines")
    return elements

def set_model_map(model):
    if model.Name() == "superk__JPARC_FHC__1rmu":
        models["1Rmu"] = model
    elif model.Name() == "superk__JPARC_RHC__1rmu":
        models["RHC1Rmu"] = model
    elif model.Name() == "superk__JPARC_FHC__1re":
        models["1Re"] = model
    elif model.Name() == "superk__JPARC_RHC__1re":
        models["RHC1Re"] = model
    elif model.Name() == "superk__JPARC_FHC__multire":
        models["MultiRe"] = model
    else:
        print "Unrecognised model ", model.Name()
        sys.exit()

def get_new_binning(sample, flavour, mode, true_bin, reco_bin1, reco_bin2=0):
    # Flavour and mode included just in case this is required for true binning
    # in the future. For now, the simple 1D true binning means the index we
    # receive is the same as the format required
    binning = models[sample].GetBinning()
    reco_binning = binning.XsecRecoBinning()
    reco_edges1 = reco_binning.BinEdgeArr(0)
    reco_edges2 = reco_binning.BinEdgeArr(1)
    reco_centre1 = 0.5 * (reco_edges1[reco_bin1] + reco_edges1[reco_bin1 + 1])
    # Even the muon samples are 2D internally, so reco_bin2 default value works
    reco_centre2 = 0.5 * (reco_edges2[reco_bin2] + reco_edges2[reco_bin2 + 1])
    print "Bin centres(", true_bin, reco_bin1, reco_bin2, ") = ", reco_centre1, reco_centre2,
    reco_vec = ROOT.vector('double')()
    reco_vec.push_back(reco_centre1)
    reco_vec.push_back(reco_centre2)
    new_true_bin = true_bin
    new_reco_bin = reco_binning.FindBin(reco_vec)
    print " =>", new_true_bin, new_reco_bin
    return new_true_bin, new_reco_bin

def main(version, path, sample):
    modes = set()
    params = set()
    location = "/data/neutrino/t2k/phrdqd/analysis/valor/softw/t2xk/branches/neutrino2018_v1.0.0/inputs/official/2018/xsec/" + path
#    location = os.environ[env_var]+"/inputs/official/2017/xsec/" + path
    elements = get_fit_elements()
    compound_model = elements.FitModel()
    for i in range(compound_model.GetNSubModels()):
        selection_model = compound_model.GetSubModel(i)
        set_model_map(selection_model)

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
                print "Bin check ", junk, bins
       
                all_bins = map(int,bins.split("_"))
                if len(all_bins) == 2:
                    true_bin, reco_bin = map(int, bins.split("_"))
                    true_bin, reco_bin = get_new_binning(sample, valor_type, mode, true_bin, reco_bin)
                elif len(all_bins) == 3:
                    true_bin, reco_bin1, reco_bin2 = map(int, bins.split("_"))
                    true_bin, reco_bin = get_new_binning(sample, valor_type, mode, true_bin, reco_bin1, reco_bin2)
                else:
                    print "Unexpected binning ", bins
                    sys.exit()
              
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
    parser.add_argument('-s', '--sample', help="The SK sample.")
    args = parser.parse_args()
    main(args.version, args.location, args.sample)
 
