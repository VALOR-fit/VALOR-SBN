#ifndef valor_genie_includes
#define valor_genie_includes

#include "dune/Conventions/DuneBuild.h"

#if GENIE_VERSION >= 3
#include "Framework/Conventions/GBuild.h"
#include "Framework/Conventions/Units.h"
#include "Framework/EventGen/EventRecord.h"
#include "Framework/GHEP/GHepParticle.h"
#include "Framework/ParticleData/PDGCodes.h"
#include "Framework/ParticleData/PDGLibrary.h"
#include "Framework/ParticleData/PDGUtils.h"
#include "Framework/Messenger/Messenger.h"
#include "Framework/Ntuple/NtpMCEventRecord.h"
#include "Framework/Ntuple/NtpMCFormat.h"
#include "Framework/Ntuple/NtpMCTreeHeader.h"
#include "Framework/Utils/AppInit.h"
#include "Framework/Utils/CmdLnArgParser.h"
#include "Framework/Utils/RunOpt.h"
#include "Tools/ReWeight/GReWeight.h"
#include "Tools/ReWeight/GReWeightI.h"
#include "Tools/ReWeight/GReWeightINuke.h"
#include "Tools/ReWeight/GSyst.h"
#include "Tools/ReWeight/GSystSet.h"
#include "Tools/ReWeight/GSystUncertainty.h"


#else //genie 2

#endif


#endif // valor_genie_includes
