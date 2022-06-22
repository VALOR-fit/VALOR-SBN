#!/bin/bash

## This tag should be the systematic group label (e.g. 03c1)
export tag=$1

## Make sure the tag is passed
if [ $# -lt 1 ] || [ $# -gt 1 ]; then
  echo "Error, pass exactly 1 argument with the systematic tag you are running"
  return
fi

## Tar the valor directory
tar -czf $RHI_DATA/VALOR/valor_${tag}.tar ./VALOR-SDK \
  ./VALOR-SBN/bin \
  ./VALOR-SBN/config \
  ./VALOR-SBN/debug \
  ./VALOR-SBN/lib \
  ./VALOR-SBN/macros \
  ./VALOR-SBN/make \
  ./VALOR-SBN/prod \
  ./VALOR-SBN/root \
  ./VALOR-SBN/scripts \
  ./VALOR-SBN/setup \
  ./VALOR-SBN/src \
  ./VALOR-SBN/thesisSubmissionScripts \
  ./VALOR-SBN/data/sbn_numu_disappearance/dsts \
  ./VALOR-SBN/data/sbn_numu_disappearance/mock_data \
  ./VALOR-SBN/data/sbn_numu_disappearance/prior_errors \
  ./VALOR-SBN/data/sbn_numu_disappearance/responses/03c1

echo "Tar file:"
echo `ls $RHI_DATA/VALOR/valor_${tag}.tar`
echo `du -sh $RHI_DATA/VALOR/valor_${tag}.tar`

## Copy the tar file to resilient
## First check it has been successfully made
if [ ! -f $RHI_DATA/VALOR/valor_${tag}.tar ]; then
  echo "Error, the tar file has not been correctly made or doesn't exist"
  return
fi

cp $RHI_DATA/VALOR/valor_${tag}.tar /pnfs/sbnd/resilient/users/rsjones/valor/.
cp $RHI_DATA/VALOR/valor_${tag}.tar /pnfs/sbnd/resilient/users/rsjones/.
