nohup valor-run_fit \
       --tag sbn-hadronic-flux \
       --first-octant \
       --run 1 \
       --ntoymc 1 \
       --param-values-option prefit-errors \
       --fitter minuit+with_simplex_fallback \
       --config analysis/sbn_numu_disapp_2020a1_03c1_1_hadronic_flux.xml \
       --mesg-thresholds verbosity.xml \
       --without-stat-fluct \
       --normal \
       --load-prior-from-file - \
       --pot-override -999 \
       --store-spectra \
       --physics-hypothesis void \
       --osc-prior-file priors/void_priors.xml \
       > sbn-hadronic-flux.out 2> sbn-hadronic-flux.err < /dev/null &
