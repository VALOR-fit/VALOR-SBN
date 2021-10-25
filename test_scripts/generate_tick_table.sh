modelist_path=${VALOR_EXPT}/data/sbn_numu_inclusive/responses/03d1
config=analysis/sbn_numu_disapp_2020a1_03d1_1.xml

valor $VALOR_EXPT/macros/systematic_construction/chain_modelists.C'("mod","'${modelist_path}'","numuCCincl","modern_xsec")'


python $VALOR_EXPT/macros/systematic_construction/make_table_spline_applied_to_mode.py \
  -c ${config} \
  --skip-flux --skip-det --skip-prop \
  -b BNB_FHC -s numulikeCChigh \
  -o modern_xsec_numuCCincl_tick_table.tex \
  -m modern_xsec_numuCCincl_modelist.root

