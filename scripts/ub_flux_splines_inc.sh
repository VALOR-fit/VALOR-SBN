#!/bin/bash

starttime=$(date)

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic horncurrent \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic expskin \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic nucleoninexsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic nucleontotxsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic nucleonqexsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic pioninexsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic piontotxsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic pionqexsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

endtime=$(date)

echo "Started running splines at ${starttime} finished at ${endtime} \n"
