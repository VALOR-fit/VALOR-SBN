
jobsub_submit \
  --group sbnd \
  --role=Analysis --memory=22000MB --expected-lifetime=48h --lines '+FERMIHTC_AutoRelease=True' --lines '+FERMIHTC_GraceMemory=4000' --append_condor_requirements='(TARGET.HAS_CVMFS_sbnd_opensciencegrid_org==true)'  --disk=60GB --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --OS=SL7 \
  -N 400 \
  --generate-email-summary \
  file:////sbnd/app/users/bslater/valor/VALOR-SBN/prod/jobsub_submit_param_scan_multifits_v2.sh \
  --tag sbn_nue_disapp_prism_2020a1_1_03c1 --param_nullhyp1 0 --param_nullhyp2 0 \--physics-hypothesis eff_sterile_osc \
  --config-file /pnfs/sbnd/persistent/users/bslater/valor/config/sbn_nue_disapp_prism_1_2020a1_1_universes_sbndonly_03c1.xml \
  --param1 sinsq2thEE --min-value1 1E-2 --max-value1 1 --log-param1 1 --npoints1 40 \
  --param2 dm41sq --min-value2 1E-2 --max-value2 1E2 --log-param2 1 --npoints2 40 \
  --param3 sinsq2thMuMu --param_nullhyp3 0 --fixed_at_val3 0 --fix_val3 1 \
  --param4 sinsq2thMuE --param_nullhyp4 0 --fixed_at_val4 0 --fix_val4 1 \
  --discovery 1 --hierarchy normal --store-spectra 1 \
  --fit-option minuit+with_simplex_fallback \
  --load-prior-from-file none --pot-override -999 \
  --mesg-thresholds verbosity.xml --param-values-option prefit-errors \
  --tarball /pnfs/sbnd/resilient/users/bslater/valor_nue_disapp_prism_03c1_updated.tar \
  --jobdir /pnfs/sbnd/persistent/users/bslater/valor/prism/nue_disapp_sbndonly_03c1_with_mec\
  --njobs 400 \
  --osc-prior-file /pnfs/sbnd/persistent/users/bslater/valor/priors/void.xml \
