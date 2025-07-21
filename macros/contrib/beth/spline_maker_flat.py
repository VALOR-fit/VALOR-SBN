#!/usr/bin/env python3
import array
import ROOT
import argparse
import os, sys
import numpy as np
from colorama import Fore # I like coloured text + progress bars
import xml.etree.ElementTree as ET

valor_expt = os.environ.get('VALOR_EXPT')
sigma_values = [-3, -2, -1, 0, 1, 2, 3]
parser = argparse.ArgumentParser(description='''
Constructs flat splines for given configuration 
''')

parser.add_argument('-o', '--output', default=os.path.join( os.getcwd(), 'splines.root' ), help='Output path with splines')
parser.add_argument('-c', '--config', type=str, required=True, help="Config file to obtain binning")
parser.add_argument('-s', '--sample', type=str, required=True, help="Sample name")
parser.add_argument('-b', '--beam', type=str, default="BNB_FHC", help="Beam name")
parser.add_argument('-d', '--detector', type=str, default="sbn_nd", help="Detector name")
parser.add_argument('-p', '--param', type=str, required=True, help="Systematic parameter name")
parser.add_argument('-m', '--mode', type=str, required=True, help="Mode (flavour/reac_type) name")
parser.add_argument('-v', '--verbosity', type=int, default=1, help="How verbosityy do you want print staments")
#parser.add_argument('-a', '--OAAngles', nargs='+', type=float, help="You can specify off-axis bin edges, too...")
args = parser.parse_args()

def makeConfigPath(xmlText):
    if xmlText[0] == "/":
        path = xmlText
    else:
        path = os.path.join(valor_expt, 'config', xmlText)
    return path

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
    if binPath is None:
        raise ValueError(f"No binning path found for sample '{sample}' in config file '{configFile}'")
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

    return n_ereco, n_etrue, ereco_arr, etrue_arr

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

def main():
    print(Fore.GREEN + "Using verbosity level " + str(args.verbosity) + Fore.RESET)
    if args.verbosity > 0:
        print(Fore.YELLOW + 'Loading binning' + Fore.RESET)
    n_ereco_bins, n_etrue_bins, ereco_bins, etrue_bins = loadBinning(args.config, args.sample, args.verbosity)

    if args.verbosity > 0:
        print(Fore.YELLOW + 'Making spline' + Fore.RESET)
    make_spline(args.output, n_ereco_bins, n_etrue_bins, args.verbosity, args.beam, args.sample, args.detector, args.mode, args.param)

if __name__ == "__main__":
    print(Fore.GREEN + 'Hello world!' + Fore.RESET)
    main()
    print(Fore.GREEN + 'Goodbye world!' + Fore.RESET)
