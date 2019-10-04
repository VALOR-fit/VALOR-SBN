#!/usr/bin/env python

import argparse
import ROOT
import sys
import re
from array import array

ROOT.PyConfig.IgnoreCommandLineOptions = True

ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

try:
    ROOT.valor
except:
    ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C")

valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

_nbins = 50
_text_size = 0.03

_pval_threshold = 0.01  # Used for comparing 2 toy throw distributions witht he Kolmogorov-Smirnov test

def compare(in_filenames, labels, colours, styles, tree_names, out_filename, param_map = None, toy_limit = -1):

    if len(in_filenames) != len(tree_names):
        print "ERROR: input filename and tree name lists have different lengths."
        sys.exit()

    # Use the branch names from the first tree to determine what branches we'll look at in ALL trees
    first_file = ROOT.TFile(in_filenames[0], "READ")
    first_tree = first_file.Get(tree_names[0])
    branches = first_tree.GetListOfBranches()
    param_names = [branch.GetName() for branch in branches]

    for param_name in param_names:
        print "Considering param: ", param_name
        if param_map:
            if convert_param_name(param_name, param_map) == "" or convert_param_name(param_name, param_map) == "-":
                continue

        # First get all the values for this param across all trees, so that we can get the hist ranges
        param_vals_all = []

        for itree, (filename, treename) in enumerate(zip(in_filenames, tree_names)):
            file = ROOT.TFile(filename, "READ")
            if file.GetListOfKeys().Contains(treename):
                tree = file.Get(treename)
                ntoys = toy_limit
                if toy_limit == -1:
                    ntoys = tree.GetEntries()
                param_vals = [-999]*ntoys
                for itoy, toy in enumerate(tree):
                    name = param_name
                    if itree > 0 and param_name and param_map:
                        name = convert_param_name(name, param_map)
                    param_vals[itoy] = getattr(toy, name)
                    if itoy == ntoys -1:
                        break
                param_vals_all.append(param_vals)
                del param_vals
                del tree
            else:
                print "ERROR: Could not find requested tree:", treename
                sys.exit()
            file.Close()
            del file

        min_val = min([min(vals) for vals in param_vals_all])
        max_val = max([max(vals) for vals in param_vals_all])

        # 2 sample K-S test:
        if len(tree_names) == 2:
            gof = ROOT.Math.GoFTest(len(param_vals_all[0]), array('d', param_vals_all[0]),
                                    len(param_vals_all[1]), array('d', param_vals_all[1]))
            pval = gof.KolmogorovSmirnov2SamplesTest()
            if(pval < _pval_threshold):
                print "WARNING: The toy throw distributions for param", param_name, \
                    " have a K-S test p-value of", pval
            del gof

        # Fill the hists for this param
        hists_to_draw = []
        for i in range(0, len(tree_names)):
            hname = param_name + "_" + str(i)
            hist = ROOT.TH1D(hname, hname, _nbins, 0.9 * min_val, 1.1 * max_val)
            hist.SetDirectory(0)
            for val in param_vals_all[i]:
                hist.Fill(val)
            hists_to_draw.append(hist)

        hist_max = max([h.GetMaximum() for h in hists_to_draw])

        # Draw the distribution of throws for this param
        canv_name = "canvas_" + param_name
        canvas = ROOT.TCanvas(canv_name, canv_name, 700, 500)
        first = True
        for i, hist in enumerate(hists_to_draw):
            draw_opt = ""
            if first:
                first = False
                hist.GetXaxis().SetTitle(param_name)
                hist.GetYaxis().SetTitle("Entries")
                hist.SetMaximum(1.1 * hist_max)
            else:
                draw_opt += "SAME"
            hist.SetLineColor(colours[i])
            hist.SetLineStyle(styles[i])
            hist.Draw(draw_opt)

        # Draw the legend
        lymax = 0.89
        lymin = lymax - (1 + len(hists_to_draw)) * _text_size
        lxmin = 0.15
        lxmax = 0.3
        legend = ROOT.TLegend(lxmin, lymin, lxmax, lymax)
        legend.SetFillStyle(0)
        legend.SetBorderSize(0)
        legend.SetTextFont(132)
        legend.SetTextSize(_text_size)
        if len(labels) > 0:
            for i, hist in enumerate(hists_to_draw):
                legend.AddEntry(hist, labels[i], "l")
        legend.Draw()

        # Save to the output file
        save_name = out_filename
        if param_name == param_names[0]:
            save_name += "("
        elif param_name == param_names[len(param_names) -1]:
            save_name += ")"
        canvas.SaveAs(save_name, "RECREATE")

        # Free up memory
        del hists_to_draw[:]
        del param_vals_all[:]
        del legend
        del canvas


def convert_param_name(param_name, arg_file_name):
    if arg_file_name == "":
        return param_name
    parameters = list_of_tuples(arg_file_name)
    comp_param_name = ""
    for iparam,(name1,name2) in enumerate(parameters):
        if name1 == param_name:
            comp_param_name = name2
            break
    return comp_param_name


def list_of_tuples(filename):
    tuplelist = []
    with open(filename) as file:
        for line in file:
            filtered = re.sub('[\"\'\(]|(\)\s*\,)|[\)]|(#.*$)|^\s*$|\s', '', line)
            if re.match(r'^\s*$', filtered):
                continue
            tuplelist.append(tuple(filtered.split(',')))

    return tuplelist


if __name__=="__main__":
    parser = argparse.ArgumentParser(description="Index splines")
    parser.add_argument("-f", "--filename"      , dest="in_filenames", nargs="+"            , help="Input filename(s) for contour(s).")
    parser.add_argument("-l", "--label"         , dest="labels"      , nargs="+"            , help="Legend label(s) for contours(s). This should have either 0 length or the same number of arguments as provided to --filename.")
    parser.add_argument("-c", "--colour"        , dest="colours"     , nargs="+"            , help="Custom line colour(s) for contours(s) (optional). If used, this should have the same number of arguments as provided to --filename.")
    parser.add_argument("-s", "--style"         , dest="styles"      , nargs="+"            , help="Custom line style(s) for contours(s) (optional). If used, this should have the same number of arguments as provided to --filename.")
    parser.add_argument("-t", "--tree-name"     , dest="tree_names"  , nargs="+"            , help="Name(s) of the trees in the input file(s). If used, this should have the same number of arguments as provided to --filename.")
    parser.add_argument("-o", "--output"        , dest="out_filename"                       , help="Output PDF filename")
    parser.add_argument("-m", "--param-map"     , dest="param_map"                          , help="File name of the parameter name map, used to convert the param names read from the first file into parm names for the other files.")
    parser.add_argument(      "--toy-limit"     , dest="toy_limit"   , type=int, default=-1 , help="Only consider the first X toys in each tree. set to -1 (default) to look at all toys.")
    args = parser.parse_args()
    labels = []
    if args.labels:
        labels = [i for i in args.labels]
        if not len(args.in_filenames) == len(labels):
            print "Error: The number of filenames and labels should match"
            sys.exit()

    colours = []
    if args.colours:
        colours = [int(i) for i in args.colours]
    styles = []
    if args.styles:
        styles = [int(i) for i in args.styles]

    compare(args.in_filenames, labels, colours, styles, args.tree_names, args.out_filename, args.param_map, args.toy_limit)


