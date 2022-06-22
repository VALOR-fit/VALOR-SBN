#!/bin/bash

cd $VALOR_SBN/systematics/splines/03c1/flux/sbnd

source $VALOR_SBN/scripts/nd_flux_splines_inc.sh
source $VALOR_SBN/scripts/nd_flux_splines_0pi.sh
source $VALOR_SBN/scripts/nd_flux_splines_oth.sh

cd $VALOR_SBN/systematics/splines/03c1/proposal_xsec/sbnd

source $VALOR_SBN/scripts/nd_proposal_xsec_splines_inc.sh
source $VALOR_SBN/scripts/nd_proposal_xsec_splines_0pi.sh
source $VALOR_SBN/scripts/nd_proposal_xsec_splines_oth.sh

cd $VALOR_SBN/systematics/splines/03c1/modern_xsec/sbnd

source $VALOR_SBN/scripts/nd_modern_xsec_splines_inc.sh
source $VALOR_SBN/scripts/nd_modern_xsec_splines_0pi.sh
source $VALOR_SBN/scripts/nd_modern_xsec_splines_oth.sh

cd -
