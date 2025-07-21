#!/usr/bin/env python

# Make a dummy covariance matrix from arbitrary hardcoded info
# Used to construct the identity covariance matrix for the interaction systematics in SBN
# These are treated as uncorrelated prefit and are parameterised in terms of prefit sigma
#
# See $VALOR_EXPT/src/macros/inputs/make_dummy_cov.py for previous implementation by F. Bench
#
# Example usage:
# python $VALOR_EXPT/src/macros/contrib/rhiannon/make_dummy_cov.py --output covariance_matrix_for_interaction_parameters.root
#
# Rhiannon Jones

import ROOT
import argparse
import sys

ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptStat(0)

#_________________________________________________________________________________
def make_cov(outputname):
    params_to_add = [
        "NOvANonResvbarnCC1Pi",
        "NOvANonResvbarnCC2Pi",
        "NOvANonResvbarnCC3Pi",
        "NOvANonResvbarnNC1Pi",
        "NOvANonResvbarnNC2Pi",
        "NOvANonResvbarpCC1Pi",
        "NOvANonResvbarpCC2Pi",
        "NOvANonResvbarpNC1Pi",
        "NOvANonResvbarpNC2Pi",
        "NOvANonResvnCC2Pi",
        "NOvANonResvnCC3Pi",
        "NOvANonResvnNC1Pi",
        "NOvANonResvnNC2Pi",
        "NOvANonResvnNC3Pi",
        "NOvANonResvnpCC1Pi",
        "NOvANonResvpCC2Pi",
        "NOvANonResvpCC3Pi",
        "NOvANonResvpNC1Pi",
        "NOvANonResvpNC2Pi",
        "NOvANonResvpNC3Pi",
        ]
    nominal_vals = {
        "NOvANonResvbarnCC1Pi"   : 0.0,
        "NOvANonResvbarnCC2Pi"   : 0.0,
        "NOvANonResvbarnCC3Pi"   : 0.0,
        "NOvANonResvbarnNC1Pi"   : 0.0,
        "NOvANonResvbarnNC2Pi"   : 0.0,
        "NOvANonResvbarpCC1Pi"   : 0.0,
        "NOvANonResvbarpCC2Pi"   : 0.0,
        "NOvANonResvbarpNC1Pi"   : 0.0,
        "NOvANonResvbarpNC2Pi"   : 0.0,
        "NOvANonResvnCC2Pi"   : 0.0,
        "NOvANonResvnCC3Pi"   : 0.0,
        "NOvANonResvnNC1Pi"   : 0.0,
        "NOvANonResvnNC2Pi"   : 0.0,
        "NOvANonResvnNC3Pi"   : 0.0,
        "NOvANonResvnpCC1Pi"   : 0.0,
        "NOvANonResvpCC2Pi"   : 0.0,
        "NOvANonResvpCC3Pi"   : 0.0,
        "NOvANonResvpNC1Pi"   : 0.0,
        "NOvANonResvpNC2Pi"   : 0.0,
        "NOvANonResvpNC3Pi"   : 0.0,
    }
    untuned_vals = {
        "NOvANonResvbarnCC1Pi"   : 0.0,
        "NOvANonResvbarnCC2Pi"   : 0.0,
        "NOvANonResvbarnCC3Pi"   : 0.0,
        "NOvANonResvbarnNC1Pi"   : 0.0,
        "NOvANonResvbarnNC2Pi"   : 0.0,
        "NOvANonResvbarpCC1Pi"   : 0.0,
        "NOvANonResvbarpCC2Pi"   : 0.0,
        "NOvANonResvbarpNC1Pi"   : 0.0,
        "NOvANonResvbarpNC2Pi"   : 0.0,
        "NOvANonResvnCC2Pi"   : 0.0,
        "NOvANonResvnCC3Pi"   : 0.0,
        "NOvANonResvnNC1Pi"   : 0.0,
        "NOvANonResvnNC2Pi"   : 0.0,
        "NOvANonResvnNC3Pi"   : 0.0,
        "NOvANonResvnpCC1Pi"   : 0.0,
        "NOvANonResvpCC2Pi"   : 0.0,
        "NOvANonResvpCC3Pi"   : 0.0,
        "NOvANonResvpNC1Pi"   : 0.0,
        "NOvANonResvpNC2Pi"   : 0.0,
        "NOvANonResvpNC3Pi"   : 0.0,
    }
    error_vals = {
        "NOvANonResvbarnCC1Pi"   : 1.0,
        "NOvANonResvbarnCC2Pi"   : 1.0,
        "NOvANonResvbarnCC3Pi"   : 1.0,
        "NOvANonResvbarnNC1Pi"   : 1.0,
        "NOvANonResvbarnNC2Pi"   : 1.0,
        "NOvANonResvbarpCC1Pi"   : 1.0,
        "NOvANonResvbarpCC2Pi"   : 1.0,
        "NOvANonResvbarpNC1Pi"   : 1.0,
        "NOvANonResvbarpNC2Pi"   : 1.0,
        "NOvANonResvnCC2Pi"   : 1.0,
        "NOvANonResvnCC3Pi"   : 1.0,
        "NOvANonResvnNC1Pi"   : 1.0,
        "NOvANonResvnNC2Pi"   : 1.0,
        "NOvANonResvnNC3Pi"   : 1.0,
        "NOvANonResvnpCC1Pi"   : 1.0,
        "NOvANonResvpCC2Pi"   : 1.0,
        "NOvANonResvpCC3Pi"   : 1.0,
        "NOvANonResvpNC1Pi"   : 1.0,
        "NOvANonResvpNC2Pi"   : 1.0,
        "NOvANonResvpNC3Pi"   : 1.0,
    }
    correlation_vals = {
    }

    N = len(params_to_add)
    new_matrix  = ROOT.TMatrixD(N, N)
    new_nominal = ROOT.TVectorD(N)
    new_untuned = ROOT.TVectorD(N)
    new_errors  = ROOT.TVectorD(N)
    new_names   = ROOT.TObjArray(N)

    # Add the new param names
    for name in params_to_add:
        new_names.Add(ROOT.TObjString(name))

    # Add the new param nominal values
    for i, name in enumerate(params_to_add):
        new_nominal[i] = nominal_vals[name]

    # Add the new param untuned values
    for i, name in enumerate(params_to_add):
        new_untuned[i] = untuned_vals[name]

    # Get a single list of 1 sigma errors
    for i, name in enumerate(params_to_add):
        new_errors[i] = error_vals[name]

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
                corr_ij = 1.0
            elif name_i in correlation_vals:
                if name_j in correlation_vals[name_i]:
                    corr_ij = correlation_vals[name_i][name_j]

            cov_ij = corr_ij * new_errors[i] * new_errors[j]
            new_matrix[i][j] = cov_ij

    print(f"Saving covariance matrix to file {outputname}")
    new_file = ROOT.TFile(outputname, "RECREATE")
    new_names  .Write("param_list", 1)
    new_nominal.Write("nominal")
    new_untuned.Write("untuned")
    new_errors.Write("errors")
    new_matrix .Write("cov")
    new_file.Close()
    print("Done!")

#_________________________________________________________________________________
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Make a covariance matrix from hardcoded info")
    parser.add_argument("--output", type=str, help="Name of the output file", required=True)
#    parser.add_argument("--param", type=str, help="Parameter to add to the covariance", required=True)
    args = parser.parse_args()
    make_cov(args.output)
