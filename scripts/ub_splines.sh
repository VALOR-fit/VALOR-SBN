#!/bin/bash

cd $VALOR_SBN/systematics/splines/03c1/flux/uboone

source $VALOR_SBN/scripts/ub_flux_splines_inc.sh
source $VALOR_SBN/scripts/ub_flux_splines_0pi.sh
source $VALOR_SBN/scripts/ub_flux_splines_oth.sh

cd $VALOR_SBN/systematics/splines/03c1/proposal_xsec/uboone

source $VALOR_SBN/scripts/ub_proposal_xsec_splines_inc.sh
source $VALOR_SBN/scripts/ub_proposal_xsec_splines_0pi.sh
source $VALOR_SBN/scripts/ub_proposal_xsec_splines_oth.sh

cd $VALOR_SBN/systematics/splines/03c1/modern_xsec/uboone

source $VALOR_SBN/scripts/ub_modern_xsec_splines_inc.sh
source $VALOR_SBN/scripts/ub_modern_xsec_splines_0pi.sh
source $VALOR_SBN/scripts/ub_modern_xsec_splines_oth.sh

cd -

