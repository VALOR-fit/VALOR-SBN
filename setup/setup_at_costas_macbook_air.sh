#!/bin/bash

#
# VALOR_LBNX oscillation analysis code setup script for Costas' MacBookPro
#
# Input arguments: 
#   1) oscillation analysis code top-level directory
#   2) valor framework code top-level directory
#

export VALOR_LBNX=$1
export VALOR_FMWK=$2
export ROOTSYS=/hep/root/v5.32.01/

export DYLD_LIBRARY_PATH=${VALOR_LBNX}/lib:${VALOR_FMWK}/lib:${ROOTSYS}/lib:${DYLD_LIBRARY_PATH}
export PATH=${VALOR_LBNX}/root:${VALOR_LBNX}/production:${ROOTSYS}/bin:${PATH}
