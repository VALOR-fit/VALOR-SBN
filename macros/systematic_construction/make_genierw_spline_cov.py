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
        "ZExpA1CCQE",
        "ZExpA2CCQE",
        "ZExpA3CCQE",
        "ZExpA4CCQE",
        "RPACCQE",
        "CoulombCCQE",
        "NormCCMEC",
        "ncelAxial",
        "ncelEta",
        "ccresAxial",
        "ccresVector",
        "ncresAxial",
        "ncresVector",
        "NonResRvpCC1pi",
        "NonResRvpCC2pi",
        "NonResRvpNC1pi",
        "NonResRvpNC2pi",
        "NonResRvnCC1pi",
        "NonResRvnCC2pi",
        "NonResRvnNC1pi",
        "NonResRvnNC2pi",
        "NonResRvbarpCC1pi",
        "NonResRvbarpCC2pi",
        "NonResRvbarpNC1pi",
        "NonResRvbarpNC2pi",
        "NonResRvbarnCC1pi",
        "NonResRvbarnCC2pi",
        "NonResRvbarnNC1pi",
        "NonResRvbarnNC2pi",
        "RDecBR1gamma",
        "RDecBR1eta",
        "NormCCCOH",
        "DISAth",
        "DISBth",
        "DISCv1u",
        "DISCv2u",
        "IntraNukePImfp",
        "IntraNukePIcex",
        "IntraNukePIinel",
        "IntraNukePIabs",
        "IntraNukePIpi",
        "IntraNukeNmfp",
        "IntraNukeNcex",
        "IntraNukeNinel",
        "IntraNukeNabs",
        "IntraNukeNpi"
        ]
    nominal_vals = {
        "ZExpA1CCQE" :0.0,
        "ZExpA2CCQE" :0.0,
        "ZExpA3CCQE" :0.0,
        "ZExpA4CCQE" :0.0,
        "RPACCQE" :0.0,
        "CoulombCCQE" :0.0,
        "NormCCMEC" :0.0,
        "ncelAxial" :0.0,
        "ncelEta" :0.0,
        "ccresAxial" :0.0,
        "ccresVector" :0.0,
        "ncresAxial" :0.0,
        "ncresVector" :0.0,
        "NonResRvpCC1pi" :0.0,
        "NonResRvpCC2pi" :0.0,
        "NonResRvpNC1pi" :0.0,
        "NonResRvpNC2pi" :0.0,
        "NonResRvnCC1pi" :0.0,
        "NonResRvnCC2pi" :0.0,
        "NonResRvnNC1pi" :0.0,
        "NonResRvnNC2pi" :0.0,
        "NonResRvbarpCC1pi" :0.0,
        "NonResRvbarpCC2pi" :0.0,
        "NonResRvbarpNC1pi" :0.0,
        "NonResRvbarpNC2pi" :0.0,
        "NonResRvbarnCC1pi" :0.0,
        "NonResRvbarnCC2pi" :0.0,
        "NonResRvbarnNC1pi" :0.0,
        "NonResRvbarnNC2pi" :0.0,
        "RDecBR1gamma" :0.0,
        "RDecBR1eta" :0.0,
        "NormCCCOH" :0.0,
        "DISAth" :0.0,
        "DISBth" :0.0,
        "DISCv1u" :0.0,
        "DISCv2u" :0.0,
        "IntraNukePImfp" :0.0,
        "IntraNukePIcex" :0.0,
        "IntraNukePIinel" :0.0,
        "IntraNukePIabs" :0.0,
        "IntraNukePIpi" :0.0,
        "IntraNukeNmfp" :0.0,
        "IntraNukeNcex" :0.0,
        "IntraNukeNinel" :0.0,
        "IntraNukeNabs" :0.0,
        "IntraNukeNpi" :0.0
    }
    untuned_vals = {
        "ZExpA1CCQE" :0.0,
        "ZExpA2CCQE" :0.0,
        "ZExpA3CCQE" :0.0,
        "ZExpA4CCQE" :0.0,
        "RPACCQE" :0.0,
        "CoulombCCQE" :0.0,
        "NormCCMEC" :0.0,
        "ncelAxial" :0.0,
        "ncelEta" :0.0,
        "ccresAxial" :0.0,
        "ccresVector" :0.0,
        "ncresAxial" :0.0,
        "ncresVector" :0.0,
        "NonResRvpCC1pi" :0.0,
        "NonResRvpCC2pi" :0.0,
        "NonResRvpNC1pi" :0.0,
        "NonResRvpNC2pi" :0.0,
        "NonResRvnCC1pi" :0.0,
        "NonResRvnCC2pi" :0.0,
        "NonResRvnNC1pi" :0.0,
        "NonResRvnNC2pi" :0.0,
        "NonResRvbarpCC1pi" :0.0,
        "NonResRvbarpCC2pi" :0.0,
        "NonResRvbarpNC1pi" :0.0,
        "NonResRvbarpNC2pi" :0.0,
        "NonResRvbarnCC1pi" :0.0,
        "NonResRvbarnCC2pi" :0.0,
        "NonResRvbarnNC1pi" :0.0,
        "NonResRvbarnNC2pi" :0.0,
        "RDecBR1gamma" :0.0,
        "RDecBR1eta" :0.0,
        "NormCCCOH" :0.0,
        "DISAth" :0.0,
        "DISBth" :0.0,
        "DISCv1u" :0.0,
        "DISCv2u" :0.0,
        "IntraNukePImfp" :0.0,
        "IntraNukePIcex" :0.0,
        "IntraNukePIinel" :0.0,
        "IntraNukePIabs" :0.0,
        "IntraNukePIpi" :0.0,
        "IntraNukeNmfp" :0.0,
        "IntraNukeNcex" :0.0,
        "IntraNukeNinel" :0.0,
        "IntraNukeNabs" :0.0,
        "IntraNukeNpi" :0.0
    }
    error_vals = {
        "ZExpA1CCQE" :1.0,
        "ZExpA2CCQE" :1.0,
        "ZExpA3CCQE" :1.0,
        "ZExpA4CCQE" :1.0,
        "RPACCQE" :1.0,
        "CoulombCCQE" :1.0,
        "NormCCMEC" :1.0,
        "ncelAxial" :1.0,
        "ncelEta" :1.0,
        "ccresAxial" :1.0,
        "ccresVector" :1.0,
        "ncresAxial" :1.0,
        "ncresVector" :1.0,
        "NonResRvpCC1pi" :1.0,
        "NonResRvpCC2pi" :1.0,
        "NonResRvpNC1pi" :1.0,
        "NonResRvpNC2pi" :1.0,
        "NonResRvnCC1pi" :1.0,
        "NonResRvnCC2pi" :1.0,
        "NonResRvnNC1pi" :1.0,
        "NonResRvnNC2pi" :1.0,
        "NonResRvbarpCC1pi" :1.0,
        "NonResRvbarpCC2pi" :1.0,
        "NonResRvbarpNC1pi" :1.0,
        "NonResRvbarpNC2pi" :1.0,
        "NonResRvbarnCC1pi" :1.0,
        "NonResRvbarnCC2pi" :1.0,
        "NonResRvbarnNC1pi" :1.0,
        "NonResRvbarnNC2pi" :1.0,
        "RDecBR1gamma" :1.0,
        "RDecBR1eta" :1.0,
        "NormCCCOH" :1.0,
        "DISAth" :1.0,
        "DISBth" :1.0,
        "DISCv1u" :1.0,
        "DISCv2u" :1.0,
        "IntraNukePImfp" :1.0,
        "IntraNukePIcex" :1.0,
        "IntraNukePIinel" :1.0,
        "IntraNukePIabs" :1.0,
        "IntraNukePIpi" :1.0,
        "IntraNukeNmfp" :1.0,
        "IntraNukeNcex" :1.0,
        "IntraNukeNinel" :1.0,
        "IntraNukeNabs" :1.0,
        "IntraNukeNpi" :1.0
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
