config_file=${VALOR_EXPT}/config/analysis/sbn_numu_disapp_2020a1_1.xml   # numu config
#config_file=${VALOR_EXPT}/config/analysis/sbn_nue_2020a1.xml             # nue config

output_file=mytest_spectra

kGlobFitSinsq2ThetaEE=0.05310;   # Global best fit: https://arxiv.org/pdf/1906.00045.pdf 
kGlobFitSinsq2ThetaMuMu=0.07157;   # Global best fit: https://arxiv.org/pdf/1906.00045.pdf 
kGlobFitSinsq2ThetaMuE=0.0009809; # Global best fit: https://arxiv.org/pdf/1906.00045.pdf 
kGlobFitDm41sq=1.32;      # Global best fit: https://arxiv.org/pdf/1906.00045.pdf 

sinsq2thMuMu=0.0
sinsq2thMuE=0.0
sinsq2thEE=0.0
dm41sq=1.32

valor-write_pdf \
    --config ${config_file} \
    --write-opt all+SB \
    --physics-hypothesis eff_sterile_osc \
    --input-sinsq2thMuMu ${sinsq2thMuMu} --input-sinsq2thMuE ${sinsq2thMuE} --input-sinsq2thEE ${sinsq2thEE} --input-dm41sq ${dm41sq} \
    --output-name ${output_file}
