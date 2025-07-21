#!/usr/bin/env python3
import array
import ROOT
import h5py
import argparse
import os, sys
import numpy as np
from colorama import Fore # I like coloured text + progress bars
import xml.etree.ElementTree as ET

valor_expt = os.environ.get('VALOR_EXPT')
sigma_values = [-3, -2, -1, 0, 1, 2, 3]
parser = argparse.ArgumentParser(description='''
Constructs splines in root format for valor from a single hdf5 file 
''')

parser.add_argument('-i', '--input', type=str, required=True, help='Input hdf5 with events')
parser.add_argument('-o', '--output', default=os.path.join( os.getcwd(), 'splines.root' ), help='Output path with splines')
parser.add_argument('-c', '--config', type=str, required=True, help="Config file to obtain binning")
parser.add_argument('-s', '--sample', type=str, required=True, help="Sample name")
parser.add_argument('-b', '--beam', type=str, default="BNB_FHC", help="Beam name")
parser.add_argument('-d', '--detector', type=str, default="sbn_nd", help="Detector name")
parser.add_argument('-v', '--verbosity', type=int, default=1, help="How verbosityie do you want print staments")
parser.add_argument('-m', '--modelist', action='store_true', help="store modelist?")
parser.add_argument('-n', '--names', type=str, help="name lookup csv")
parser.set_defaults(modelist=False)
#parser.add_argument('-a', '--OAAngles', nargs='+', type=float, help="You can specify off-axis bin edges, too...")
args = parser.parse_args()

def makeConfigPath(xmlText):
    if xmlText[0] == "/":
        path = xmlText
    else:
        path = os.path.join(valor_expt, 'config', xmlText)
    return path

def make_spline(dOutput, nreco, ntrue, verbosity, beamIn, sampleIn, detectorIn, modeIn, paramIn):
    os.makedirs(dOutput, exist_ok=True)
    # Create output ROOT file
    root_filename = os.path.join(dOutput, f"valor_splines_{sampleIn}_{paramIn}_{beamIn}_{detectorIn}.root")
    if os.path.exists(root_filename):
        root_file = ROOT.TFile(root_filename, "UPDATE")
    else:
        root_file = ROOT.TFile(root_filename, "RECREATE")
    if verbosity > 1:
        print(Fore.RED + "Making splines for " + paramIn + Fore.RESET)

    obj_array = ROOT.TObjArray()
    obj_array.SetName(f"spl_{modeIn}_{paramIn}")
    obj_array.SetOwner(True)
    if verbosity > 2:
        print(Fore.MAGENTA + "Mode = " + mode_name + Fore.RESET)
    weights = np.ones(len(sigma_values), dtype='float64')  # shape (n_sigma,)
    sigma_array = array.array('d', sigma_values)
    weights_array = array.array('d', weights)
    for reco_bin in range(nreco):
        for true_bin in range(ntrue):
            spline_name = f"spl_{beamIn}_{sampleIn}_{modeIn}_{paramIn}_{true_bin}_{reco_bin}"
            spline = ROOT.TSpline3(spline_name, sigma_array, weights_array, len(sigma_values))
            spline.SetTitle(spline_name)
            spline.SetName(spline_name)
            obj_array.Add(spline.Clone())
            if verbosity > 3:
                print(Fore.BLUE + "Bin = true " + str(true_bin) + ", reco " + str(reco_bin) + Fore.RESET)

    # Write TObjArray
    root_file.cd()
    obj_array.Write(obj_array.GetName(), ROOT.TObject.kSingleKey)
    root_file.Close()
    if verbosity > 1:
        print(Fore.RED + "Created: " + root_filename + Fore.RESET)

def loadBinning(configFile, sample, verbosity):
    #get binning path from config/analysis/
    configPath = makeConfigPath(configFile)
    ctree = ET.parse(configPath)
    croot = ctree.getroot()
    binPath = None
    for element in croot.findall('./element_list/element'):
        xmlsample = element.find("sample")
        xmlsampletext = xmlsample.text.strip()
        if xmlsampletext is not None and xmlsampletext == sample:
            binxml = element.find("binning")
            binPath = makeConfigPath(binxml.text.strip())
            mcxml = element.find("mc")
            mcPath = makeConfigPath(mcxml.text.strip())
    if binPath is None:
        raise ValueError(f"No binning path found for sample '{sample}' in config file '{configFile}'")
    if mcPath is None:
        raise ValueError(f"No mc path found for sample '{sample}' in config file '{configFile}'")
    mctree = ET.parse(mcPath)
    mcroot = mctree.getroot()
    modexml = mcroot.find("modelist")
    modePath= makeConfigPath(modexml.text.strip())    
    mtree = ET.parse(modePath)
    mroot = mtree.getroot()
    modes = ROOT.std.vector('std::string')()
    for m in mroot.findall("mode"):
        modes.push_back(m.text.strip())

    #get path to reco and true binning from config/binning/
    btree = ET.parse(binPath)
    broot = btree.getroot()

    breco = broot.find("reco_optimized")
    btrue = broot.find("true_simple/default")
    if breco is None:
        raise ValueError(f"No path found for reco energy binning")
    brecopath = breco.text.strip()
    if btrue is None:
        raise ValueError(f"No path found for true energy binning")
    btruepath = btrue.text.strip()
    binRecoPath = makeConfigPath(breco.text.strip())
    binTruePath = makeConfigPath(btrue.text.strip())

    #get binning from binning/e2e/
    rtree = ET.parse(binRecoPath)
    ttree = ET.parse(binTruePath)
    rroot = rtree.getroot()
    troot = ttree.getroot()

    ereco = rroot.find("Ereco_binning")
    etrue = troot.find("Etrue_binning")

    ereco_bins = ereco.find("bin_edges").text.strip()
    etrue_bins = etrue.find("bin_edges").text.strip()

    ereco_arr = np.array([float(x.strip()) for x in ereco_bins.split(',')])
    etrue_arr = np.array([float(x.strip()) for x in etrue_bins.split(',')])

    n_ereco = ereco_arr.size-1
    n_etrue = etrue_arr.size-1

    if verbosity > 1:
        print(Fore.RED + 'Using bins:')
        print('Ereco: ' + ereco_bins)
        print('Etrue: ' + etrue_bins + Fore.RESET)

    return n_ereco, n_etrue, modes

def convert_h5(fInput, dOutput, nreco, ntrue, verbosity, beamIn, sampleIn, detectorIn, saveModelist, modelistIn, namesIn):
    os.makedirs(dOutput, exist_ok=True)

    names_data = np.loadtxt(namesIn, delimiter=',', dtype=str)

    # Open HDF5 file
    with h5py.File(fInput, 'r') as fin:
        for beam_key in fin.keys():
            if not beam_key.startswith("beam_"):
                continue
            beam_name = beam_key.replace("beam_","") 
            if beam_name != beamIn:
                print(Fore.WHITE + "Skipping beam " + beam_name + Fore.RESET)
                continue
            beam_grp = fin[beam_key]

            for sample_key in beam_grp.keys():
                if not sample_key.startswith("sample_"):
                    continue
                sample_name = sample_key.replace("sample_","") 
                sample_name = sample_name.replace("Incl","incl") 
                sample_name = sample_name.replace("_OAA_","OA0") 
                if sample_name != sampleIn:
                    print(Fore.WHITE + "Skipping sample " + sample_name + Fore.RESET)
                    continue
                sample_grp = beam_grp[sample_key]

                #print(Fore.RED + 'Params:')
                for param in sample_grp.keys():
                    param_grp = sample_grp[param]
                    for row in names_data:
                        if row[0] == param:
                            param_name = row[1]

                    applied_to_modes = ROOT.std.vector('std::string')()
                    applied_to_modes_flat = ROOT.std.vector('std::string')()
                    modes_used = ROOT.std.vector('std::string')()

                    # Create output ROOT file
                    root_filename = os.path.join(dOutput, f"valor_splines_{sample_name}_{param_name}_{beam_name}_{detectorIn}.root") 
                    modelist_filename = os.path.join(dOutput, f"valor_splines_{sample_name}_{param_name}_{beam_name}_{detectorIn}_modelist.root") 
                    root_file = ROOT.TFile(root_filename, "RECREATE") 

                    #print(param)
                    if verbosity > 1:
                        print(Fore.RED + "Making splines for " + param_name + Fore.RESET)

                    for mode_key in param_grp.keys():
                        if not mode_key.startswith("mode_"):
                            continue
                        mode_name = mode_key.replace("mode_","") 
                        mode_grp = param_grp[mode_key]
                        mode_used = False
                        mode_used2 = False
                        if "Splines" not in mode_grp:
                            print(Fore.WHITE + "Skipping " + sample_name + " / " + param_name + " / " + mode_name+ " — no Splines" + Fore.RESET)
                            continue
                        splines = mode_grp["Splines"]
                        shape = splines.shape  # should be (n_reco, n_true, n_sigma)

                        n_reco, n_true, n_sigma = shape
                        if n_reco != nreco:
                            print(Fore.WHITE + "N reco bins mismatch: expected " + str(nreco) + ", got " + str(n_reco) + " - skippinig " + sample_name + " / " + param_name + " / " + mode_name + Fore.RESET)
                            continue
                        if n_true != ntrue:
                            print(Fore.WHITE + "N true bins mismatch: expected " + str(ntrue) + ", got " + str(n_true) + " - skippinig " + sample_name + " / " + param_name + " / " + mode_name + Fore.RESET)
                            continue
                        tweaks = np.array(mode_grp["Tweaks"], dtype='float64')
                        if not np.array_equal(tweaks, sigma_values):
                            print(Fore.WHITE + f"Tweaks don't match expected sigma values. expected {sigma_values}, got {tweaks}" + Fore.RESET)
                        #if n_sigma != len(sigma_values):
                            #print(Fore.WHITE + "Sigma dimension mismatch: expected " + str(len(sigma_values)) + ", got " + str(n_sigma) + " for " + sample_name + " / " + param + " / " + mode_name + Fore.RESET)
                            #continue #replace with checks to pull in good sigma values

                        obj_array = ROOT.TObjArray()
                        obj_array.SetName(f"spl_{mode_name}_{param_name}")
                        obj_array.SetOwner(True)
                        if verbosity > 2:
                            print(Fore.MAGENTA + "Mode = " + mode_name + Fore.RESET)
                        for reco_bin in range(n_reco):
                            for true_bin in range(n_true):
                                weights = np.array(splines[reco_bin, true_bin, :], dtype='float64')  # shape (n_sigma,)
                                #if reco_bin == 0 and true_bin == 0:
                                #    print(Fore.WHITE + f"weights for {mode_name} {param} bin 0,0 = {weights}" + Fore.RESET)
                                # Make TGraph and TSpline3
                                #doubel check against old spline maker
                                #graph = ROOT.TGraph(len(sigma_values), np.array(sigma_values, dtype='float64'), np.array(weights, dtype='float64'))
                                #spl_BNB_FHC_numuCCincl_numubartonuebarCCcoh_horncurrent_FluxUnisim_0_0 example name old
                                spline_name = f"spl_{beam_name}_{sample_name}_{mode_name}_{param_name}_{true_bin}_{reco_bin}"
                                #spline = ROOT.TSpline3(spline_name, graph)
                                
                                assert weights.shape == tweaks.shape
                                weights = np.nan_to_num(weights, nan=1.)
                                spline = ROOT.TSpline3(spline_name, tweaks, weights, len(tweaks))
                                spline.SetTitle(spline_name)
                                spline.SetName(spline_name)
                                obj_array.Add(spline.Clone())
                                if verbosity > 3:
                                    print(Fore.BLUE + "Bin = true " + str(true_bin) + ", reco " + str(reco_bin) + Fore.RESET)
                                if not mode_used2:
                                    modes_used.push_back(mode_name)
                                    mode_used2 = True
                                if saveModelist and not mode_used and np.any((weights != 0) & (weights != 1)): #check for at least 1 element in weights thats not 0 or 1
                                    applied_to_modes.push_back(mode_name)
                                    mode_used = True

                        # Write TObjArray
                        root_file.cd()
                        # Create a subdirectory for the mode
                        #subdir = root_file.mkdir(f"{mode_name}_{param}")
                        #subdir.cd()
                        #print(f"TObjArray has {obj_array.GetEntriesFast()} splines")
                        obj_array.Write(obj_array.GetName(), ROOT.TObject.kSingleKey)
                    root_file.Close()
                    if verbosity > 1:
                        print(Fore.RED + "Created: " + root_filename + Fore.RESET)
                    print(f"modelistIn = {modelistIn}")
                    print(f"applied_to_modes = {applied_to_modes}")
                    print(f"modes_used = {modes_used}")
                    for m in modelistIn:
                       if m not in modes_used:
                         print(Fore.WHITE + f"making missing spline for {m}_{param_name}" + Fore.RESET)
                         make_spline(dOutput, n_reco, n_true, verbosity, beam_name, sample_name, detectorIn, m, param_name)
                         if saveModelist:
                           applied_to_modes_flat.push_back(m)
                    if saveModelist:
                        if not bool(applied_to_modes):
                            print(Fore.WHITE + "Wanted to save modelist but is empty" + Fore.RESET)
                        else:
                            modelist_file = ROOT.TFile(modelist_filename, "RECREATE") 
                            modelist_file.cd()
                            mode_tree = ROOT.TTree("ModeList","List of modes impacted by each systematic parameter")
                            mode_tree_flat = ROOT.TTree("FlatModeList","List of modes for flat splines to fill gaps in valor")
                            mode_tree.Branch(param_name, applied_to_modes)
                            mode_tree_flat.Branch(param_name, applied_to_modes_flat)
                            mode_tree.Fill()
                            mode_tree_flat.Fill()
                            modelist_file.Write()
                            modelist_file.Close()
                            if verbosity > 1:
                                print(Fore.RED + "Created: " + modelist_filename + Fore.RESET)
           

def main():
    print(Fore.GREEN + "Using verbosity level " + str(args.verbosity) + Fore.RESET)
    if args.verbosity > 0:
        print(Fore.YELLOW + 'Loading binning' + Fore.RESET)
    n_ereco_bins, n_etrue_bins, configModes = loadBinning(args.config, args.sample, args.verbosity)

    if args.verbosity > 0:
        print(Fore.YELLOW + 'Converting h5' + Fore.RESET)
    convert_h5(args.input, args.output, n_ereco_bins, n_etrue_bins, args.verbosity, args.beam, args.sample, args.detector, args.modelist, configModes, args.names)

if __name__ == "__main__":
    print(Fore.GREEN + 'Hello world!' + Fore.RESET)
    main()
    print(Fore.GREEN + 'Goodbye world!' + Fore.RESET)
