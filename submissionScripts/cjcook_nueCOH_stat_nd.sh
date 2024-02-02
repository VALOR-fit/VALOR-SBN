jobsub_submit \
  --group sbnd \
  --role=Analysis --memory=6500MB --expected-lifetime=52h  --disk=50GB \
  --onsite-only \
  --singularity-image /cvmfs/singularity.opensciencegrid.org/fermilab/fnal-wn-sl7:latest \
  -N 2 \
  --generate-email-summary \
  file:////sbnd/app/users/rsjones/VALOR/VALOR-SBN/prod/jobsub_submit_param_scan_multifits_v2.sh \
  --tag sbn_modern_nue_app --param_nullhyp1 0 --param_nullhyp2 0 \
  --physics-hypothesis eff_sterile_osc \
  --config-file /pnfs/sbnd/persistent/users/cjcook/config/mc_sbndonly/sbn_nue_2020a1_03d1_1.xml \
  --param1 sinsq2thMuE --min-value1 1E-5 --max-value1 1 --log-param1 1 --npoints1 2 \
  --param2 dm41sq --min-value2 1E-2 --max-value2 1E2 --log-param2 1 --npoints2 2 \
  --param3 sinsq2thMuMu --param_nullhyp3 0 --fixed_at_val3 0 --fix_val3 1 \
  --param4 sinsq2thEE --param_nullhyp4 0 --fixed_at_val4 0 --fix_val4 1 \
  --discovery 1 --hierarchy normal --store-spectra 1 \
  --fit-option minuit+with_simplex_fallback \
  --load-prior-from-file none --pot-override -999 \
  --mesg-thresholds verbosity.xml --param-values-option prefit-errors \
  --tarball /pnfs/sbnd/resilient/users/cjcook/valor.tar \
  --jobdir /pnfs/sbnd/scratch/users/rsjones/nue_app_03d1_coh \
  --njobs 2 \
  --osc-prior-file /pnfs/sbnd/persistent/users/cjcook/prior/void.xml \

  
