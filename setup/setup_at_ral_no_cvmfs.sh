#!/bin/bash

#
# VALOR_DUNE oscillation analysis code setup script for RAL/PPD Tier2
#
# Input arguments:
#   1) oscillation analysis code top-level directory
#   2) valor framework code top-level directory
#

export VALOR_DUNE=$1
export VALOR_FMWK=$2
export ROOTSYS=/opt/ppd/t2k/softw/ROOT/builds/SL6.x86_64/v5.34.30/

export LD_LIBRARY_PATH=${VALOR_DUNE}/lib:${VALOR_FMWK}/lib:${ROOTSYS}/lib:${LD_LIBRARY_PATH}:/opt/ppd/t2k/softw/LOG4CPP/builds/SL5_64bit/v1.0/src/.libs/:/usr/lib64/
export PATH=${VALOR_DUNE}/bin:${VALOR_DUNE}/root:${VALOR_DUNE}/production:${ROOTSYS}/bin:${PATH}

