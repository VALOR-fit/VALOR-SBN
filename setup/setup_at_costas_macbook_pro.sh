#!/bin/bash

#
# VALOR/DUNE analysis code setup script for Costas' MacBookPro2
#
# Input arguments: 
#   1) oscillation analysis code top-level directory
#   2) valor framework code top-level directory
#

export VALOR_LBNX=$1
export VALOR_FMWK=$2
export ROOTSYS=/hep/soft/root/v5.34.34/

export DYLD_LIBRARY_PATH=${VALOR_LBNX}/lib:${VALOR_FMWK}/lib:${ROOTSYS}/lib:${DYLD_LIBRARY_PATH}
export PATH=${VALOR_LBNX}/bin:${VALOR_LBNX}/root:${VALOR_LBNX}/production:${ROOTSYS}/bin:${PATH}
