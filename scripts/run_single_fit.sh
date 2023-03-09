#!/bin/bash

valor-run_fit \
  --tag sbn_sterile_free_2020a1_03c1_lse_floatfrom0 \
  --first-octant --run 1 --ntoymc 1 --param-values-option  prefit-errors \
  --fitter minuit+with_simplex_fallback \
  --config analysis/sbn_numu_disapp_2020a1_03c1_lse_1.xml \
  --mesg-thresholds verbosity.xml --without-stat-fluct  --normal \
  --load-prior-from-file - \
  --pot-override -999 --store-spectra \
  --physics-hypothesis eff_sterile_osc \
  --osc-prior-file priors/void_priors.xml \
  --input-sinsq2thMuE 0 --fix-at-sinsq2thMuE 0. --fix-sinsq2thMuE \
  --input-sinsq2thMuMu 0 --fix-at-sinsq2thMuMu 0. \
  --input-sinsq2thEE 0 --fix-at-sinsq2thEE 0. --fix-sinsq2thEE \
  --input-dm41sq 0 --fix-at-dm41sq 0. \
  --read-data
