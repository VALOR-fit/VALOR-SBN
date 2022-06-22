#!/bin/bash

cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/pull_studies/exclusive/fits/split/

for i in {1..50}; do
  seed=$i

  valor-run_fit \
    --tag nd-pulls-100-void-exc-nosimplex \
    --first-octant \
    --run $i \
    --ntoymc 100 \
    --param-values-option  prefit-errors \
    --fitter minuit \
    --config analysis/sbn_numu_disapp_2020a1_03c1_nd_1_exc_pull_studies.xml \
    --mesg-thresholds verbosity.xml \
    --without-stat-fluct \
    --normal \
    --load-prior-from-file - \
    --pot-override -999 \
    --store-spectra \
    --physics-hypothesis void \
    --prior-file priors/void_priors.xml \
    --tweak-parameter-set pulls \
    --seed-toys-stat $seed \
    --seed-toys-syst $seed \
    --seed-toys-osc $seed \
    --seed-fitter $seed \
    --seed-other $seed

done

cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/pull_studies/exclusive/fits/

python $VALOR_SBN/macros/fits/chain_fits.py ''split/nd-pulls-100-void-exc-nosimplex*'' -o nd-pulls-5000-void-exc-nosimplex_all.root
