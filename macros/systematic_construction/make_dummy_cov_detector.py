#!/usr/bin/env python

# Make a dummy covariance matrix from arbitrary hardcoded info
#
# Example usage:
# python $VALOR_EXPT/src/macros/inputs/make_dummy_cov.py --output dummy_covariance_matrix.root
#
# Francis Bench

import ROOT
import argparse
import sys

ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptStat(0)

#_________________________________________________________________________________
def make_cov(outputname,val):
    # All of these values have been chosen completely arbitrarily
    params_to_add = [
        "det_fhc_sbnd_numucc_sig_00",
        "det_fhc_sbnd_numucc_sig_01",
        "det_fhc_sbnd_numucc_sig_02",
        "det_fhc_sbnd_numucc_sig_03",
        "det_fhc_sbnd_numucc_sig_04",
        "det_fhc_sbnd_numucc_sig_05",
        "det_fhc_sbnd_numucc_sig_06",
        "det_fhc_sbnd_numucc_sig_07",
        "det_fhc_sbnd_numucc_ncbkg_00",
        "det_fhc_sbnd_numucc_ncbkg_01",
        "det_fhc_sbnd_numucc_ncbkg_02",
        "det_fhc_sbnd_numucc_ncbkg_03",
        "det_fhc_sbnd_numucc_ncbkg_04",
        "det_fhc_sbnd_numucc_ncbkg_05",
        "det_fhc_sbnd_numucc_dirtbkg_00",
        "det_fhc_sbnd_numucc_cosmicbkg_00",
        "det_fhc_icarus_numucc_sig_00",
        "det_fhc_icarus_numucc_sig_01",
        "det_fhc_icarus_numucc_sig_02",
        "det_fhc_icarus_numucc_sig_03",
        "det_fhc_icarus_numucc_sig_04",
        "det_fhc_icarus_numucc_sig_05",
        "det_fhc_icarus_numucc_sig_06",
        "det_fhc_icarus_numucc_sig_07",
        "det_fhc_icarus_numucc_ncbkg_00",
        "det_fhc_icarus_numucc_ncbkg_01",
        "det_fhc_icarus_numucc_ncbkg_02",
        "det_fhc_icarus_numucc_ncbkg_03",
        "det_fhc_icarus_numucc_ncbkg_04",
        "det_fhc_icarus_numucc_ncbkg_05",
        "det_fhc_icarus_numucc_dirtbkg_00",
        "det_fhc_icarus_numucc_cosmicbkg_00"          
            ]
    nominal_vals = {
        "det_fhc_sbnd_numucc_sig_00" : 0,
        "det_fhc_sbnd_numucc_sig_01" : 0,
        "det_fhc_sbnd_numucc_sig_02" : 0,
        "det_fhc_sbnd_numucc_sig_03" : 0,
        "det_fhc_sbnd_numucc_sig_04" : 0,
        "det_fhc_sbnd_numucc_sig_05" : 0,
        "det_fhc_sbnd_numucc_sig_06" : 0,
        "det_fhc_sbnd_numucc_sig_07" : 0,
        "det_fhc_sbnd_numucc_ncbkg_00" : 0,
        "det_fhc_sbnd_numucc_ncbkg_01" : 0,
        "det_fhc_sbnd_numucc_ncbkg_02" : 0,
        "det_fhc_sbnd_numucc_ncbkg_03" : 0,
        "det_fhc_sbnd_numucc_ncbkg_04" : 0,
        "det_fhc_sbnd_numucc_ncbkg_05" : 0,
        "det_fhc_sbnd_numucc_dirtbkg_00" : 0,
        "det_fhc_sbnd_numucc_cosmicbkg_00" : 0,
        "det_fhc_icarus_numucc_sig_00" : 0,
        "det_fhc_icarus_numucc_sig_01" : 0,
        "det_fhc_icarus_numucc_sig_02" : 0,
        "det_fhc_icarus_numucc_sig_03" : 0,
        "det_fhc_icarus_numucc_sig_04" : 0,
        "det_fhc_icarus_numucc_sig_05" : 0,
        "det_fhc_icarus_numucc_sig_06" : 0,
        "det_fhc_icarus_numucc_sig_07" : 0,
        "det_fhc_icarus_numucc_ncbkg_00" : 0,
        "det_fhc_icarus_numucc_ncbkg_01" : 0,
        "det_fhc_icarus_numucc_ncbkg_02" : 0,
        "det_fhc_icarus_numucc_ncbkg_03" : 0,
        "det_fhc_icarus_numucc_ncbkg_04" : 0,
        "det_fhc_icarus_numucc_ncbkg_05" : 0,
        "det_fhc_icarus_numucc_dirtbkg_00" : 0,
        "det_fhc_icarus_numucc_cosmicbkg_00" : 0
    }
    untunued_vals = {
        "det_fhc_sbnd_numucc_sig_00" : 0,
        "det_fhc_sbnd_numucc_sig_01" : 0,
        "det_fhc_sbnd_numucc_sig_02" : 0,
        "det_fhc_sbnd_numucc_sig_03" : 0,
        "det_fhc_sbnd_numucc_sig_04" : 0,
        "det_fhc_sbnd_numucc_sig_05" : 0,
        "det_fhc_sbnd_numucc_sig_06" : 0,
        "det_fhc_sbnd_numucc_sig_07" : 0,
        "det_fhc_sbnd_numucc_ncbkg_00" : 0,
        "det_fhc_sbnd_numucc_ncbkg_01" : 0,
        "det_fhc_sbnd_numucc_ncbkg_02" : 0,
        "det_fhc_sbnd_numucc_ncbkg_03" : 0,
        "det_fhc_sbnd_numucc_ncbkg_04" : 0,
        "det_fhc_sbnd_numucc_ncbkg_05" : 0,
        "det_fhc_sbnd_numucc_dirtbkg_00" : 0,
        "det_fhc_sbnd_numucc_cosmicbkg_00" : 0,
        "det_fhc_icarus_numucc_sig_00" : 0,
        "det_fhc_icarus_numucc_sig_01" : 0,
        "det_fhc_icarus_numucc_sig_02" : 0,
        "det_fhc_icarus_numucc_sig_03" : 0,
        "det_fhc_icarus_numucc_sig_04" : 0,
        "det_fhc_icarus_numucc_sig_05" : 0,
        "det_fhc_icarus_numucc_sig_06" : 0,
        "det_fhc_icarus_numucc_sig_07" : 0,
        "det_fhc_icarus_numucc_ncbkg_00" : 0,
        "det_fhc_icarus_numucc_ncbkg_01" : 0,
        "det_fhc_icarus_numucc_ncbkg_02" : 0,
        "det_fhc_icarus_numucc_ncbkg_03" : 0,
        "det_fhc_icarus_numucc_ncbkg_04" : 0,
        "det_fhc_icarus_numucc_ncbkg_05" : 0,
        "det_fhc_icarus_numucc_dirtbkg_00" : 0,
        "det_fhc_icarus_numucc_cosmicbkg_00" : 0

    }
    error_vals = {
        "det_fhc_sbnd_numucc_sig_00" : val,
        "det_fhc_sbnd_numucc_sig_01" : val,
        "det_fhc_sbnd_numucc_sig_02" : val,
        "det_fhc_sbnd_numucc_sig_03" : val,
        "det_fhc_sbnd_numucc_sig_04" : val,
        "det_fhc_sbnd_numucc_sig_05" : val,
        "det_fhc_sbnd_numucc_sig_06" : val,
        "det_fhc_sbnd_numucc_sig_07" : val,
        "det_fhc_sbnd_numucc_ncbkg_00" : val,
        "det_fhc_sbnd_numucc_ncbkg_01" : val,
        "det_fhc_sbnd_numucc_ncbkg_02" : val,
        "det_fhc_sbnd_numucc_ncbkg_03" : val,
        "det_fhc_sbnd_numucc_ncbkg_04" : val,
        "det_fhc_sbnd_numucc_ncbkg_05" : val,
        "det_fhc_sbnd_numucc_dirtbkg_00" : val,
        "det_fhc_sbnd_numucc_cosmicbkg_00" : val,
        "det_fhc_icarus_numucc_sig_00" : val,
        "det_fhc_icarus_numucc_sig_01" : val,
        "det_fhc_icarus_numucc_sig_02" : val,
        "det_fhc_icarus_numucc_sig_03" : val,
        "det_fhc_icarus_numucc_sig_04" : val,
        "det_fhc_icarus_numucc_sig_05" : val,
        "det_fhc_icarus_numucc_sig_06" : val,
        "det_fhc_icarus_numucc_sig_07" : val,
        "det_fhc_icarus_numucc_ncbkg_00" : val,
        "det_fhc_icarus_numucc_ncbkg_01" : val,
        "det_fhc_icarus_numucc_ncbkg_02" : val,
        "det_fhc_icarus_numucc_ncbkg_03" : val,
        "det_fhc_icarus_numucc_ncbkg_04" : val,
        "det_fhc_icarus_numucc_ncbkg_05" : val,
        "det_fhc_icarus_numucc_dirtbkg_00" : val,
        "det_fhc_icarus_numucc_cosmicbkg_00" : val

    }
    correlation_vals = {
            }

    N = len(params_to_add)
    new_matrix  = ROOT.TMatrixD(N, N)
    new_nominal = ROOT.TVectorD(N)
    new_untuned = ROOT.TVectorD(N)
    new_names   = ROOT.TObjArray(N)

    # Add the new param names
    for name in params_to_add:
        new_names.Add(ROOT.TObjString(name))

    # Add the new param nominal values
    for i, name in enumerate(params_to_add):
        new_nominal[i] = nominal_vals[name]

    # Add the new param untuned values
    for i, name in enumerate(params_to_add):
        new_untuned[i] = untunued_vals[name]

    # Get a single list of 1 sigma errors
    new_errors = []
    for name in params_to_add:
        new_errors.append(error_vals[name])

    # Calculate the new covariance values from the correlations and errors using
    # cov_{ij} = corr_{ij} * err_{i} * err_{j}
    for i, name_i in enumerate(new_names):
        # Convert the param names from TObjStrings to strings (otherwise string comparisons will fail)
        name_i = name_i.GetName()
        for j, name_j in enumerate(new_names):
            # Loop over all params (new + old) because new params might have correlations with old params.
            name_j = name_j.GetName()
            if name_i not in params_to_add and name_j not in params_to_add:
                # If both params are old, then we don't need to do anything
                continue

            corr_ij = 0.0
            if i == j:
                corr_ij = 1
            #elif name_i in correlation_vals:
                #if name_j in correlation_vals[name_i]:
                    #corr_ij = correlation_vals[name_i][name_j]
            elif i != j:
                corr_ij = 1

            cov_ij = corr_ij * new_errors[i] * new_errors[j]
            new_matrix[i][j] = cov_ij

    print "Saving covariance matrix to file", outputname
    new_file = ROOT.TFile(outputname, "RECREATE")
    new_names  .Write("param_list", 1)
    new_nominal.Write("params")
    new_untuned.Write("untuned_central_values")
    new_matrix .Write("cov")
    new_file.Close()
    print "Done!"

#_________________________________________________________________________________
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Make a covariance matrix from hardcoded info")
    parser.add_argument("--output", type=str, help="Name of the output file", required=True)
    parser.add_argument("--val", type=float, help="Value (frac) to use", required=True)
    args = parser.parse_args()
    make_cov(args.output, args.val)
