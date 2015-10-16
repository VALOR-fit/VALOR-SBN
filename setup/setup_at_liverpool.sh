#!/bin/bash

#
# VALOR_DUNE oscillation analysis code setup script
#
# Input arguments:
#   1) oscillation analysis code top-level directory
#   2) valor framework code top-level directory
#

export VALOR_DUNE=/hepstore/georgios/lbne/valor/softw/dune/trunk
export VALOR_FMWK=/hepstore/georgios/lbne/valor/softw/fmwk/trunk
# this will load all the libraries
source /hepstore/georgios/genie/R-2_8_0/geniesetup.sh

export LD_LIBRARY_PATH=${VALOR_DUNE}/lib:${VALOR_FMWK}/lib:${ROOTSYS}/lib:${LD_LIBRARY_PATH}
export PATH=${VALOR_DUNE}/root:${VALOR_DUNE}/production:${ROOTSYS}/bin:${PATH}
