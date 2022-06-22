#!/bin/bash

starttime=$(date)

valor_dune-make_sbn_interaction_splines --config analysis/sbn/sbn_numu_disapp_2019b3_1_universes.xml --systematic qema --variations /sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/src/macros/contrib/rhiannon/sbn_universe_variations_from_mastbaum.txt --store-spectra --save-modelist

valor_dune-make_sbn_interaction_splines --config analysis/sbn/sbn_numu_disapp_2019b3_1_universes.xml --systematic ccresAxial --variations /sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/src/macros/contrib/rhiannon/sbn_universe_variations_from_mastbaum.txt --store-spectra --save-modelist

valor_dune-make_sbn_interaction_splines --config analysis/sbn/sbn_numu_disapp_2019b3_1_universes.xml --systematic ncresAxial --variations /sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/src/macros/contrib/rhiannon/sbn_universe_variations_from_mastbaum.txt --store-spectra --save-modelist

valor_dune-make_sbn_interaction_splines --config analysis/sbn/sbn_numu_disapp_2019b3_1_universes.xml --systematic NC --variations /sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/src/macros/contrib/rhiannon/sbn_universe_variations_from_mastbaum.txt --store-spectra --save-modelist

valor_dune-make_sbn_interaction_splines --config analysis/sbn/sbn_numu_disapp_2019b3_1_universes.xml --systematic NonResRvbarp1pi --variations /sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/src/macros/contrib/rhiannon/sbn_universe_variations_from_mastbaum.txt --store-spectra --save-modelist

valor_dune-make_sbn_interaction_splines --config analysis/sbn/sbn_numu_disapp_2019b3_1_universes.xml --systematic NonResRvbarp2pi --variations /sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/src/macros/contrib/rhiannon/sbn_universe_variations_from_mastbaum.txt --store-spectra --save-modelist

valor_dune-make_sbn_interaction_splines --config analysis/sbn/sbn_numu_disapp_2019b3_1_universes.xml --systematic NonResRvp1pi --variations /sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/src/macros/contrib/rhiannon/sbn_universe_variations_from_mastbaum.txt --store-spectra --save-modelist

valor_dune-make_sbn_interaction_splines --config analysis/sbn/sbn_numu_disapp_2019b3_1_universes.xml --systematic NonResRvp2pi --variations /sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/src/macros/contrib/rhiannon/sbn_universe_variations_from_mastbaum.txt --store-spectra --save-modelist

endtime=$(date)

echo "Started running splines at ${starttime} finished at ${endtime} \n"
