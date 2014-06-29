#!/bin/bash

#
# VALOR_LBNX oscillation analysis code setup script for RAL/PPD Tier2
#
# Input arguments:
#   1) oscillation analysis code top-level directory
#   2) valor framework code top-level directory
#

export VALOR_LBNX=$1
export VALOR_FMWK=$2
export ROOTSYS=/opt/ppd/t2k/softw/ROOT/builds/SL5_64bit/v5.34.03/

export LD_LIBRARY_PATH=${VALOR_LBNX}/lib:${VALOR_FMWK}/lib:${ROOTSYS}/lib:${LD_LIBRARY_PATH}
export PATH=${VALOR_LBNX}/root:${VALOR_LBNX}/production:${ROOTSYS}/bin:${PATH}

