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
# Shweta Yadav
#Based on Rhinnon's make_int_spline_cov.py

import ROOT
import argparse
import sys

ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptStat(0)

#_________________________________________________________________________________
def make_cov(outputname):
    params_to_add = [
        "genie_ZExpAVariationResponse_Genie", 
        "genie_NCELVariationResponse_Genie",
        "genie_CCRESVariationResponse_Genie",
        "genie_NCRESVariationResponse_Genie",
        "genie_DISBYVariationResponse_Genie",
        "genie_FSI_pi_VariationResponse_Genie",
        "genie_COHVariationResponse_Genie",
        "genie_FSI_N_VariationResponse_Genie",
        "genie_RPA_CCQE_Genie",
        "genie_CoulombCCQE_Genie",
        "genie_NormCCMEC_Genie",
        "genie_NormNCMEC_Genie",
        "genie_NonRESBGvpCC1pi_Genie",
        "genie_NonRESBGvpCC2pi_Genie",
        "genie_NonRESBGvpNC1pi_Genie",
        "genie_NonRESBGvpNC2pi_Genie",
        "genie_NonRESBGvnCC1pi_Genie",
        "genie_NonRESBGvnCC2pi_Genie",
        "genie_NonRESBGvnNC1pi_Genie",
        "genie_NonRESBGvnNC2pi_Genie",
        "genie_NonRESBGvbarpCC1pi_Genie",
        "genie_NonRESBGvbarpCC2pi_Genie",
        "genie_NonRESBGvbarpNC1pi_Genie",
        "genie_NonRESBGvbarpNC2pi_Genie",
        "genie_NonRESBGvbarnCC1pi_Genie",
        "genie_NonRESBGvbarnCC2pi_Genie",
        "genie_NonRESBGvbarnNC1pi_Genie",
        "genie_NonRESBGvbarnNC2pi_Genie",
        ]
    nominal_vals = {
        "genie_ZExpAVariationResponse_Genie"     : 0.0, 
        "genie_NCELVariationResponse_Genie"      : 0.0,
        "genie_CCRESVariationResponse_Genie"     : 0.0,
        "genie_NCRESVariationResponse_Genie"     : 0.0,
        "genie_DISBYVariationResponse_Genie"     : 0.0,
        "genie_FSI_pi_VariationResponse_Genie"   : 0.0,
        "genie_COHVariationResponse_Genie"       : 0.0,
        "genie_FSI_N_VariationResponse_Genie"    : 0.0,
        "genie_RPA_CCQE_Genie"                   : 0.0,
        "genie_CoulombCCQE_Genie"                : 0.0,
        "genie_NormCCMEC_Genie"                  : 0.0,
        "genie_NormNCMEC_Genie"                  : 0.0,
        "genie_NonRESBGvpCC1pi_Genie"            : 0.0,
        "genie_NonRESBGvpCC2pi_Genie"            : 0.0,
        "genie_NonRESBGvpNC1pi_Genie"            : 0.0,
        "genie_NonRESBGvpNC2pi_Genie"            : 0.0,
        "genie_NonRESBGvnCC1pi_Genie"            : 0.0,
        "genie_NonRESBGvnCC2pi_Genie"            : 0.0,
        "genie_NonRESBGvnNC1pi_Genie"            : 0.0,
        "genie_NonRESBGvnNC2pi_Genie"            : 0.0,
        "genie_NonRESBGvbarpCC1pi_Genie"         : 0.0,
        "genie_NonRESBGvbarpCC2pi_Genie"         : 0.0,
        "genie_NonRESBGvbarpNC1pi_Genie"         : 0.0,
        "genie_NonRESBGvbarpNC2pi_Genie"         : 0.0,
        "genie_NonRESBGvbarnCC1pi_Genie"         : 0.0,
        "genie_NonRESBGvbarnCC2pi_Genie"         : 0.0,
        "genie_NonRESBGvbarnNC1pi_Genie"         : 0.0,
        "genie_NonRESBGvbarnNC2pi_Genie"         : 0.0,
    }
    untuned_vals = {
        "genie_ZExpAVariationResponse_Genie"     : 0.0, 
        "genie_NCELVariationResponse_Genie"      : 0.0,
        "genie_CCRESVariationResponse_Genie"     : 0.0,
        "genie_NCRESVariationResponse_Genie"     : 0.0,
        "genie_DISBYVariationResponse_Genie"     : 0.0,
        "genie_FSI_pi_VariationResponse_Genie"   : 0.0,
        "genie_COHVariationResponse_Genie"       : 0.0,
        "genie_FSI_N_VariationResponse_Genie"    : 0.0,
        "genie_RPA_CCQE_Genie"                   : 0.0,
        "genie_CoulombCCQE_Genie"                : 0.0,
        "genie_NormCCMEC_Genie"                  : 0.0,
        "genie_NormNCMEC_Genie"                  : 0.0,
        "genie_NonRESBGvpCC1pi_Genie"            : 0.0,
        "genie_NonRESBGvpCC2pi_Genie"            : 0.0,
        "genie_NonRESBGvpNC1pi_Genie"            : 0.0,
        "genie_NonRESBGvpNC2pi_Genie"            : 0.0,
        "genie_NonRESBGvnCC1pi_Genie"            : 0.0,
        "genie_NonRESBGvnCC2pi_Genie"            : 0.0,
        "genie_NonRESBGvnNC1pi_Genie"            : 0.0,
        "genie_NonRESBGvnNC2pi_Genie"            : 0.0,
        "genie_NonRESBGvbarpCC1pi_Genie"         : 0.0,
        "genie_NonRESBGvbarpCC2pi_Genie"         : 0.0,
        "genie_NonRESBGvbarpNC1pi_Genie"         : 0.0,
        "genie_NonRESBGvbarpNC2pi_Genie"         : 0.0,
        "genie_NonRESBGvbarnCC1pi_Genie"         : 0.0,
        "genie_NonRESBGvbarnCC2pi_Genie"         : 0.0,
        "genie_NonRESBGvbarnNC1pi_Genie"         : 0.0,
        "genie_NonRESBGvbarnNC2pi_Genie"         : 0.0,
    }
    error_vals = {
        "genie_ZExpAVariationResponse_Genie"     : 1.0, 
        "genie_NCELVariationResponse_Genie"      : 1.0,
        "genie_CCRESVariationResponse_Genie"     : 1.0,
        "genie_NCRESVariationResponse_Genie"     : 1.0,
        "genie_DISBYVariationResponse_Genie"     : 1.0,
        "genie_FSI_pi_VariationResponse_Genie"   : 1.0,
        "genie_COHVariationResponse_Genie"       : 1.0,
        "genie_FSI_N_VariationResponse_Genie"    : 1.0,
        "genie_RPA_CCQE_Genie"                   : 1.0,
        "genie_CoulombCCQE_Genie"                : 1.0,
        "genie_NormCCMEC_Genie"                  : 1.0,
        "genie_NormNCMEC_Genie"                  : 1.0,
        "genie_NonRESBGvpCC1pi_Genie"            : 1.0,
        "genie_NonRESBGvpCC2pi_Genie"            : 1.0,
        "genie_NonRESBGvpNC1pi_Genie"            : 1.0,
        "genie_NonRESBGvpNC2pi_Genie"            : 1.0,
        "genie_NonRESBGvnCC1pi_Genie"            : 1.0,
        "genie_NonRESBGvnCC2pi_Genie"            : 1.0,
        "genie_NonRESBGvnNC1pi_Genie"            : 1.0,
        "genie_NonRESBGvnNC2pi_Genie"            : 1.0,
        "genie_NonRESBGvbarpCC1pi_Genie"         : 1.0,
        "genie_NonRESBGvbarpCC2pi_Genie"         : 1.0,
        "genie_NonRESBGvbarpNC1pi_Genie"         : 1.0,
        "genie_NonRESBGvbarpNC2pi_Genie"         : 1.0,
        "genie_NonRESBGvbarnCC1pi_Genie"         : 1.0,
        "genie_NonRESBGvbarnCC2pi_Genie"         : 1.0,
        "genie_NonRESBGvbarnNC1pi_Genie"         : 1.0,
        "genie_NonRESBGvbarnNC2pi_Genie"         : 1.0,
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

    print("Saving covariance matrix to file", outputname)
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
