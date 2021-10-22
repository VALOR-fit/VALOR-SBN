config_file=${VALOR_EXPT}/config/analysis/sbn_numu_disapp_2020a1_1.xml
#config_file=${VALOR_EXPT}/config/analysis/sbn_nue_2020a1.xml

output_file=mytest_event_rate_table.tex

sinsq2thMuMu=0.0
sinsq2thMuE=0.0
sinsq2thEE=0.0
dm41sq=1.32

${VALOR_FMWK}/macros/spectra/make_validation_spectrum_tables.py \
--config ${config_file} \
--physics-hypothesis eff_sterile_osc \
--sinsq2thMuMu ${sinsq2thMuMu} --sinsq2thMuE ${sinsq2thMuE} --sinsq2thEE ${sinsq2thEE} --dm41sq ${dm41sq} \
--file ${output_file}
