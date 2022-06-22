#!/bin/bash

starttime=$(date)

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic DISAth \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic DISBth \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic DISCv1u \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic DISCv2u \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukeNabs \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukeNcex \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukeNinel \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukeNmfp \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukeNpi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukePIabs \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukePIcex \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukePIinel \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukePImfp \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic IntraNukePIpi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic ResDecayGamma \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic ccresVector \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic cohMA \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic cohR0 \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic ncelAxial \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic ncelEta \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub_cc0pi.xml \
  --systematic ncresVector \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --sample numuCC0piNtrk \
  --detector sbn_uboone

endtime=$(date)

echo "Started running splines at ${starttime} finished at ${endtime} \n"
