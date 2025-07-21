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
        "AhtBY",
        "BhtBY",
        "C12ToAr40_2p2hScaling_nubar",
        "C12ToAr40_2p2hScaling_nu",
        "CoulombCCQE",
        "CV1uBY",
        "CV2uBY",
        "E2p2h_A_nubar",
        "E2p2h_A_nu",
        "E2p2h_B_nubar",
        "E2p2h_B_nu",
        "EtaNCEL",
        "FrAbs_N",
        "FrAbs_pi",
        "FrCEx_N",
        "FrCEx_pi",
        "FrInel_N",
        "FrInel_pi",
        "FrPiProd_N",
        "FrPiProd_pi",
        "MaCCRES",
        "MaNCEL",
        "MaNCRES",
        "MFP_N",
        "MFP_pi",
        "Mnv2p2hGaussEnhancement",
        "MvCCRES",
        "MvNCRES",
        "NonRESBGvbarnCC1pi",
        "NonRESBGvbarnCC2pi",
        "NonRESBGvbarnNC1pi",
        "NonRESBGvbarnNC2pi",
        "NonRESBGvbarpCC1pi",
        "NonRESBGvbarpCC2pi",
        "NonRESBGvbarpNC1pi",
        "NonRESBGvbarpNC2pi",
        "NonRESBGvnCC1pi",
        "NonRESBGvnCC2pi",
        "NonRESBGvnNC1pi",
        "NonRESBGvnNC2pi",
        "NonRESBGvpCC1pi",
        "NonRESBGvpCC2pi",
        "NonRESBGvpNC1pi",
        "NonRESBGvpNC2pi",
        "NormCCCOH",
        "NormCCMEC",
        "NR_nubar_n_CC_1Pi",
        "NR_nubar_n_CC_2Pi",
        "NR_nubar_n_CC_3Pi",
        "NR_nubar_n_NC_1Pi",
        "NR_nubar_n_NC_2Pi",
        "NR_nubar_p_CC_1Pi",
        "NR_nubar_p_CC_2Pi",
        "NR_nubar_p_NC_1Pi",
        "NR_nubar_p_NC_2Pi",
        "NR_nu_n_CC_2Pi",
        "NR_nu_n_CC_3Pi",
        "NR_nu_n_NC_1Pi",
        "NR_nu_n_NC_2Pi",
        "NR_nu_n_NC_3Pi",
        "NR_nu_np_CC_1Pi",
        "NR_nu_p_CC_2Pi",
        "NR_nu_p_CC_3Pi",
        "NR_nu_p_NC_1Pi",
        "NR_nu_p_NC_2Pi",
        "NR_nu_p_NC_3Pi",
        "RDecBR1eta",
        "RDecBR1gamma",
        "RPA_CCQE",
        "SPPLowQ2Suppression",
        "ZExpA1CCQE",
        "ZExpA2CCQE",
        "ZExpA3CCQE",
        "ZExpA4CCQE"
        ]
    nominal_vals = {
        "AhtBY"   : 0.0,
        "BhtBY"   : 0.0,
        "C12ToAr40_2p2hScaling_nubar"   : 0.0,
        "C12ToAr40_2p2hScaling_nu"   : 0.0,
        "CoulombCCQE"   : 0.0,
        "CV1uBY"   : 0.0,
        "CV2uBY"   : 0.0,
        "E2p2h_A_nubar"   : 0.0,
        "E2p2h_A_nu"   : 0.0,
        "E2p2h_B_nubar"   : 0.0,
        "E2p2h_B_nu"   : 0.0,
        "EtaNCEL"   : 0.0,
        "FrAbs_N"   : 0.0,
        "FrAbs_pi"   : 0.0,
        "FrCEx_N"   : 0.0,
        "FrCEx_pi"   : 0.0,
        "FrInel_N"   : 0.0,
        "FrInel_pi"   : 0.0,
        "FrPiProd_N"   : 0.0,
        "FrPiProd_pi"   : 0.0,
        "MaCCRES"   : 0.0,
        "MaNCEL"   : 0.0,
        "MaNCRES"   : 0.0,
        "MFP_N"   : 0.0,
        "MFP_pi"   : 0.0,
        "Mnv2p2hGaussEnhancement"   : 0.0,
        "MvCCRES"   : 0.0,
        "MvNCRES"   : 0.0,
        "NonRESBGvbarnCC1pi"   : 0.0,
        "NonRESBGvbarnCC2pi"   : 0.0,
        "NonRESBGvbarnNC1pi"   : 0.0,
        "NonRESBGvbarnNC2pi"   : 0.0,
        "NonRESBGvbarpCC1pi"   : 0.0,
        "NonRESBGvbarpCC2pi"   : 0.0,
        "NonRESBGvbarpNC1pi"   : 0.0,
        "NonRESBGvbarpNC2pi"   : 0.0,
        "NonRESBGvnCC1pi"   : 0.0,
        "NonRESBGvnCC2pi"   : 0.0,
        "NonRESBGvnNC1pi"   : 0.0,
        "NonRESBGvnNC2pi"   : 0.0,
        "NonRESBGvpCC1pi"   : 0.0,
        "NonRESBGvpCC2pi"   : 0.0,
        "NonRESBGvpNC1pi"   : 0.0,
        "NonRESBGvpNC2pi"   : 0.0,
        "NormCCCOH"   : 0.0,
        "NormCCMEC"   : 0.0,
        "NR_nubar_n_CC_1Pi"   : 0.0,
        "NR_nubar_n_CC_2Pi"   : 0.0,
        "NR_nubar_n_CC_3Pi"   : 0.0,
        "NR_nubar_n_NC_1Pi"   : 0.0,
        "NR_nubar_n_NC_2Pi"   : 0.0,
        "NR_nubar_p_CC_1Pi"   : 0.0,
        "NR_nubar_p_CC_2Pi"   : 0.0,
        "NR_nubar_p_NC_1Pi"   : 0.0,
        "NR_nubar_p_NC_2Pi"   : 0.0,
        "NR_nu_n_CC_2Pi"   : 0.0,
        "NR_nu_n_CC_3Pi"   : 0.0,
        "NR_nu_n_NC_1Pi"   : 0.0,
        "NR_nu_n_NC_2Pi"   : 0.0,
        "NR_nu_n_NC_3Pi"   : 0.0,
        "NR_nu_np_CC_1Pi"   : 0.0,
        "NR_nu_p_CC_2Pi"   : 0.0,
        "NR_nu_p_CC_3Pi"   : 0.0,
        "NR_nu_p_NC_1Pi"   : 0.0,
        "NR_nu_p_NC_2Pi"   : 0.0,
        "NR_nu_p_NC_3Pi"   : 0.0,
        "RDecBR1eta"   : 0.0,
        "RDecBR1gamma"   : 0.0,
        "RPA_CCQE"   : 0.0,
        "SPPLowQ2Suppression"   : 0.0,
        "ZExpA1CCQE"   : 0.0,
        "ZExpA2CCQE"   : 0.0,
        "ZExpA3CCQE"   : 0.0,
        "ZExpA4CCQE"   : 0.0,
    }
    untuned_vals = {
        "AhtBY"   : 0.0,
        "BhtBY"   : 0.0,
        "C12ToAr40_2p2hScaling_nubar"   : 0.0,
        "C12ToAr40_2p2hScaling_nu"   : 0.0,
        "CoulombCCQE"   : 0.0,
        "CV1uBY"   : 0.0,
        "CV2uBY"   : 0.0,
        "E2p2h_A_nubar"   : 0.0,
        "E2p2h_A_nu"   : 0.0,
        "E2p2h_B_nubar"   : 0.0,
        "E2p2h_B_nu"   : 0.0,
        "EtaNCEL"   : 0.0,
        "FrAbs_N"   : 0.0,
        "FrAbs_pi"   : 0.0,
        "FrCEx_N"   : 0.0,
        "FrCEx_pi"   : 0.0,
        "FrInel_N"   : 0.0,
        "FrInel_pi"   : 0.0,
        "FrPiProd_N"   : 0.0,
        "FrPiProd_pi"   : 0.0,
        "MaCCRES"   : 0.0,
        "MaNCEL"   : 0.0,
        "MaNCRES"   : 0.0,
        "MFP_N"   : 0.0,
        "MFP_pi"   : 0.0,
        "Mnv2p2hGaussEnhancement"   : 0.0,
        "MvCCRES"   : 0.0,
        "MvNCRES"   : 0.0,
        "NonRESBGvbarnCC1pi"   : 0.0,
        "NonRESBGvbarnCC2pi"   : 0.0,
        "NonRESBGvbarnNC1pi"   : 0.0,
        "NonRESBGvbarnNC2pi"   : 0.0,
        "NonRESBGvbarpCC1pi"   : 0.0,
        "NonRESBGvbarpCC2pi"   : 0.0,
        "NonRESBGvbarpNC1pi"   : 0.0,
        "NonRESBGvbarpNC2pi"   : 0.0,
        "NonRESBGvnCC1pi"   : 0.0,
        "NonRESBGvnCC2pi"   : 0.0,
        "NonRESBGvnNC1pi"   : 0.0,
        "NonRESBGvnNC2pi"   : 0.0,
        "NonRESBGvpCC1pi"   : 0.0,
        "NonRESBGvpCC2pi"   : 0.0,
        "NonRESBGvpNC1pi"   : 0.0,
        "NonRESBGvpNC2pi"   : 0.0,
        "NormCCCOH"   : 0.0,
        "NormCCMEC"   : 0.0,
        "NR_nubar_n_CC_1Pi"   : 0.0,
        "NR_nubar_n_CC_2Pi"   : 0.0,
        "NR_nubar_n_CC_3Pi"   : 0.0,
        "NR_nubar_n_NC_1Pi"   : 0.0,
        "NR_nubar_n_NC_2Pi"   : 0.0,
        "NR_nubar_p_CC_1Pi"   : 0.0,
        "NR_nubar_p_CC_2Pi"   : 0.0,
        "NR_nubar_p_NC_1Pi"   : 0.0,
        "NR_nubar_p_NC_2Pi"   : 0.0,
        "NR_nu_n_CC_2Pi"   : 0.0,
        "NR_nu_n_CC_3Pi"   : 0.0,
        "NR_nu_n_NC_1Pi"   : 0.0,
        "NR_nu_n_NC_2Pi"   : 0.0,
        "NR_nu_n_NC_3Pi"   : 0.0,
        "NR_nu_np_CC_1Pi"   : 0.0,
        "NR_nu_p_CC_2Pi"   : 0.0,
        "NR_nu_p_CC_3Pi"   : 0.0,
        "NR_nu_p_NC_1Pi"   : 0.0,
        "NR_nu_p_NC_2Pi"   : 0.0,
        "NR_nu_p_NC_3Pi"   : 0.0,
        "RDecBR1eta"   : 0.0,
        "RDecBR1gamma"   : 0.0,
        "RPA_CCQE"   : 0.0,
        "SPPLowQ2Suppression"   : 0.0,
        "ZExpA1CCQE"   : 0.0,
        "ZExpA2CCQE"   : 0.0,
        "ZExpA3CCQE"   : 0.0,
        "ZExpA4CCQE"   : 0.0,
    }
    error_vals = {
        "AhtBY"   : 1.0,
        "BhtBY"   : 1.0,
        "C12ToAr40_2p2hScaling_nubar"   : 1.0,
        "C12ToAr40_2p2hScaling_nu"   : 1.0,
        "CoulombCCQE"   : 1.0,
        "CV1uBY"   : 1.0,
        "CV2uBY"   : 1.0,
        "E2p2h_A_nubar"   : 1.0,
        "E2p2h_A_nu"   : 1.0,
        "E2p2h_B_nubar"   : 1.0,
        "E2p2h_B_nu"   : 1.0,
        "EtaNCEL"   : 1.0,
        "FrAbs_N"   : 1.0,
        "FrAbs_pi"   : 1.0,
        "FrCEx_N"   : 1.0,
        "FrCEx_pi"   : 1.0,
        "FrInel_N"   : 1.0,
        "FrInel_pi"   : 1.0,
        "FrPiProd_N"   : 1.0,
        "FrPiProd_pi"   : 1.0,
        "MaCCRES"   : 1.0,
        "MaNCEL"   : 1.0,
        "MaNCRES"   : 1.0,
        "MFP_N"   : 1.0,
        "MFP_pi"   : 1.0,
        "Mnv2p2hGaussEnhancement"   : 1.0,
        "MvCCRES"   : 1.0,
        "MvNCRES"   : 1.0,
        "NonRESBGvbarnCC1pi"   : 1.0,
        "NonRESBGvbarnCC2pi"   : 1.0,
        "NonRESBGvbarnNC1pi"   : 1.0,
        "NonRESBGvbarnNC2pi"   : 1.0,
        "NonRESBGvbarpCC1pi"   : 1.0,
        "NonRESBGvbarpCC2pi"   : 1.0,
        "NonRESBGvbarpNC1pi"   : 1.0,
        "NonRESBGvbarpNC2pi"   : 1.0,
        "NonRESBGvnCC1pi"   : 1.0,
        "NonRESBGvnCC2pi"   : 1.0,
        "NonRESBGvnNC1pi"   : 1.0,
        "NonRESBGvnNC2pi"   : 1.0,
        "NonRESBGvpCC1pi"   : 1.0,
        "NonRESBGvpCC2pi"   : 1.0,
        "NonRESBGvpNC1pi"   : 1.0,
        "NonRESBGvpNC2pi"   : 1.0,
        "NormCCCOH"   : 1.0,
        "NormCCMEC"   : 1.0,
        "NR_nubar_n_CC_1Pi"   : 1.0,
        "NR_nubar_n_CC_2Pi"   : 1.0,
        "NR_nubar_n_CC_3Pi"   : 1.0,
        "NR_nubar_n_NC_1Pi"   : 1.0,
        "NR_nubar_n_NC_2Pi"   : 1.0,
        "NR_nubar_p_CC_1Pi"   : 1.0,
        "NR_nubar_p_CC_2Pi"   : 1.0,
        "NR_nubar_p_NC_1Pi"   : 1.0,
        "NR_nubar_p_NC_2Pi"   : 1.0,
        "NR_nu_n_CC_2Pi"   : 1.0,
        "NR_nu_n_CC_3Pi"   : 1.0,
        "NR_nu_n_NC_1Pi"   : 1.0,
        "NR_nu_n_NC_2Pi"   : 1.0,
        "NR_nu_n_NC_3Pi"   : 1.0,
        "NR_nu_np_CC_1Pi"   : 1.0,
        "NR_nu_p_CC_2Pi"   : 1.0,
        "NR_nu_p_CC_3Pi"   : 1.0,
        "NR_nu_p_NC_1Pi"   : 1.0,
        "NR_nu_p_NC_2Pi"   : 1.0,
        "NR_nu_p_NC_3Pi"   : 1.0,
        "RDecBR1eta"   : 1.0,
        "RDecBR1gamma"   : 1.0,
        "RPA_CCQE"   : 1.0,
        "SPPLowQ2Suppression"   : 1.0,
        "ZExpA1CCQE"   : 1.0,
        "ZExpA2CCQE"   : 1.0,
        "ZExpA3CCQE"   : 1.0,
        "ZExpA4CCQE"   : 1.0,
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
