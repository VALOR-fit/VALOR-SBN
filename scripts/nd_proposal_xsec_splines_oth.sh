#!/bin/bash

starttime=$(date)

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic qema \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic ccresAxial \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic ncresAxial \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NC \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NonResRvbarp1pi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NonResRvbarp2pi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NonResRvp1pi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NonResRvp2pi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NonResRvbarp1piAlt \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NonResRvbarp2piAlt \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NonResRvp1piAlt \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd_ccoth.xml \
  --systematic NonResRvp2piAlt \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCCoth \
  --detector sbn_nd

endtime=$(date)

echo "Started running splines at ${starttime} finished at ${endtime} \n"
