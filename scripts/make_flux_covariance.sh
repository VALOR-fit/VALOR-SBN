#!/bin/bash

INPUT="$VALOR_SBN//fits/sbn-hadronic-flux_1.root"
PREFIT_FLUX="$VALOR_SBN/data/sbn_numu_disappearance/prior_errors/03c1/numu_hadronic_flux_parameter_covariance.root"
NFLUX=20

cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/covariances/03c1/hadronic_flux

valor -l -b -q $VALOR_SBN/macros/contrib/rhiannon/draw_hadronicflux_covariance_matrix.C'("'${INPUT}'","'${PREFIT_FLUX}'",'${NFLUX}')'

