valor-tweak_pdf_N \
  --config $VALOR_EXPT/config/analysis/sbn_numu_disapp_2020a1_03d1_nd_1.xml \
  --output tweaks_pdf_modern_xsec.root \
  --params allsyst \
  --ntoys 1000 \
  --physics-hypothesis eff_sterile_osc

valor_sbn-universe_variation_tweaks \
  --config $VALOR_EXPT/config/analysis/sbn_numu_disapp_2020a1_03d1_nd_1.xml \
  --input $data/VALOR/data/universes/sbn_numu_inclusive/2020a1/valor_sbncode_fhc_numuccinc_disappearance_nd_minidst_mc.root \
  --params modern_xsec \
  --ntoys 500 \
  --sample numuCCincl
