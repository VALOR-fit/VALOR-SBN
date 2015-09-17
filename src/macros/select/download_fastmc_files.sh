#!/bin/sh

#echo ${VALOR_LBNX}
cd ${VALOR_LBNX}/data
#rm ?HC_LBNE_ND_Tree*.root
wget http://hep.ph.liv.ac.uk/~georgios/pdf/FHC_LBNE_ND_Tree_v25.root
wget http://hep.ph.liv.ac.uk/~georgios/pdf/RHC_LBNE_ND_Tree_v25.root
cd -
