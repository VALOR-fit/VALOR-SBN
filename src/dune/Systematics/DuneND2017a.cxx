//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

// system
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
// fmwk
#include "valor/Conventions/Constants.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/UtlSystem.h"
// dune
#include "dune/Conventions/FitParam.h"
#include "dune/Systematics/DuneND2017a.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(DuneND2017a)

//________________________________________________________________________________________
DuneND2017a::DuneND2017a() :
CorrelatedSystematics()
{
  std::vector<PhysParamId_t> params;
  
  params.push_back(kNuisEffFHCnumuCC0pi1trk01     );
  params.push_back(kNuisEffFHCnumuCC0pi1trk02     );
  params.push_back(kNuisEffFHCnumuCC0pi1trk03     );
  params.push_back(kNuisEffFHCnumuCC0pi1trk04     );
  params.push_back(kNuisEffFHCnumuCC0pi1trk05     );
  params.push_back(kNuisEffFHCnumuCC0pi1trk06     );
  params.push_back(kNuisEffFHCnumuCC0pi1trk07     );
  params.push_back(kNuisEffFHCnumuCC0pi1trk08     );
  params.push_back(kNuisEffFHCnumuCC0pi1trk09     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk01     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk02     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk03     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk04     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk05     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk06     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk07     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk08     );
  params.push_back(kNuisEffFHCnumuCC0pi2trk09     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk01     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk02     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk03     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk04     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk05     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk06     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk07     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk08     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk09     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk10     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk11     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk12     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk13     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk14     );
  params.push_back(kNuisEffFHCnumuCC0piNtrk15     );
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta01);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta02);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta03);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta04);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta05);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta06);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta07);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta08);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta09);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta10);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta11);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta12);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta13);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta14);
  params.push_back(kNuisEffFHCnumuCC1pi3trkDelta15);
  params.push_back(kNuisEffFHCnumuCC1pic01        );
  params.push_back(kNuisEffFHCnumuCC1pic02        );
  params.push_back(kNuisEffFHCnumuCC1pic03        );
  params.push_back(kNuisEffFHCnumuCC1pic04        );
  params.push_back(kNuisEffFHCnumuCC1pic05        );
  params.push_back(kNuisEffFHCnumuCC1pic06        );
  params.push_back(kNuisEffFHCnumuCC1pic07        );
  params.push_back(kNuisEffFHCnumuCC1pic08        );
  params.push_back(kNuisEffFHCnumuCC1pic09        );
  params.push_back(kNuisEffFHCnumuCC1piz01        );
  params.push_back(kNuisEffFHCnumuCC1piz02        );
  params.push_back(kNuisEffFHCnumuCC1piz03        );
  params.push_back(kNuisEffFHCnumuCC1piz04        );
  params.push_back(kNuisEffFHCnumuCC1piz05        );
  params.push_back(kNuisEffFHCnumuCC1piz06        );
  params.push_back(kNuisEffFHCnumuCC1piz07        );
  params.push_back(kNuisEffFHCnumuCC1piz08        );
  params.push_back(kNuisEffFHCnumuCC1piz09        );
  params.push_back(kNuisEffFHCnumuCC1pic1piz01    );
  params.push_back(kNuisEffFHCnumuCC1pic1piz02    );
  params.push_back(kNuisEffFHCnumuCC1pic1piz03    );
  params.push_back(kNuisEffFHCnumuCC1pic1piz04    );
  params.push_back(kNuisEffFHCnumuCC1pic1piz05    );
  params.push_back(kNuisEffFHCnumuCC1pic1piz06    );
  params.push_back(kNuisEffFHCnumuCC1pic1piz07    );
  params.push_back(kNuisEffFHCnumuCC1pic1piz08    );
  params.push_back(kNuisEffFHCnumuCC1pic1piz09    );
  params.push_back(kNuisEffFHCnumuCCother01       );
  params.push_back(kNuisEffFHCnumuCCother02       );
  params.push_back(kNuisEffFHCnumuCCother03       );
  params.push_back(kNuisEffFHCnumuCCother04       );
  params.push_back(kNuisEffFHCnumuCCother05       );
  params.push_back(kNuisEffFHCnumuCCother06       );
  params.push_back(kNuisEffFHCnumuCCother07       );
  params.push_back(kNuisEffFHCnumuCCother08       );
  params.push_back(kNuisEffFHCnumuCCother09       );
  params.push_back(kNuisEffFHCnumuCCother10       );
  params.push_back(kNuisEffFHCnumuCCother11       );
  params.push_back(kNuisEffFHCnumuCCWS0pi01       );
  params.push_back(kNuisEffFHCnumuCCWS0pi02       );
  params.push_back(kNuisEffFHCnumuCCWS0pi03       );
  params.push_back(kNuisEffFHCnumuCCWS0pi04       );
  params.push_back(kNuisEffFHCnumuCCWS0pi05       );
  params.push_back(kNuisEffFHCnumuCCWS1pic01      );
  params.push_back(kNuisEffFHCnumuCCWS1pic02      );
  params.push_back(kNuisEffFHCnumuCCWS1pic03      );
  params.push_back(kNuisEffFHCnumuCCWS1pic04      );
  params.push_back(kNuisEffFHCnumuCCWS1pic05      );
  params.push_back(kNuisEffFHCnumuCCWS1pic06      );
  params.push_back(kNuisEffFHCnumuCCWS1pic07      );
  params.push_back(kNuisEffFHCnumuCCWS1pic08      );
  params.push_back(kNuisEffFHCnumuCCWS1piz01      );
  params.push_back(kNuisEffFHCnumuCCWS1piz02      );
  params.push_back(kNuisEffFHCnumuCCWS1piz03      );
  params.push_back(kNuisEffFHCnumuCCWSother01     );
  params.push_back(kNuisEffFHCnueCC0pi01          );
  params.push_back(kNuisEffFHCnueCC0pi02          );
  params.push_back(kNuisEffFHCnueCC0pi03          );
  params.push_back(kNuisEffFHCnueCC0pi04          );
  params.push_back(kNuisEffFHCnueCC0pi05          );
  params.push_back(kNuisEffFHCnueCC0pi06          );
  params.push_back(kNuisEffFHCnueCC0pi07          );
  params.push_back(kNuisEffFHCnueCC0pi08          );
  params.push_back(kNuisEffFHCnueCC0pi09          );
  params.push_back(kNuisEffFHCnueCC1pic01         );
  params.push_back(kNuisEffFHCnueCC1pic02         );
  params.push_back(kNuisEffFHCnueCC1pic03         );
  params.push_back(kNuisEffFHCnueCC1pic04         );
  params.push_back(kNuisEffFHCnueCC1pic05         );
  params.push_back(kNuisEffFHCnueCC1pic06         );
  params.push_back(kNuisEffFHCnueCC1pic07         );
  params.push_back(kNuisEffFHCnueCC1pic08         );
  params.push_back(kNuisEffFHCnueCC1pic09         );
  params.push_back(kNuisEffFHCnueCC1piz01         );
  params.push_back(kNuisEffFHCnueCC1piz02         );
  params.push_back(kNuisEffFHCnueCC1piz03         );
  params.push_back(kNuisEffFHCnueCC1piz04         );
  params.push_back(kNuisEffFHCnueCC1piz05         );
  params.push_back(kNuisEffFHCnueCC1piz06         );
  params.push_back(kNuisEffFHCnueCC1piz07         );
  params.push_back(kNuisEffFHCnueCC1piz08         );
  params.push_back(kNuisEffFHCnueCC1piz09         );
  params.push_back(kNuisEffFHCnueCCother01        );
  params.push_back(kNuisEffFHCnueCCother02        );
  params.push_back(kNuisEffFHCnueCCother03        );
  params.push_back(kNuisEffFHCnueCCother04        );
  params.push_back(kNuisEffFHCnueCCother05        );
  params.push_back(kNuisEffFHCnueCCother06        );
  params.push_back(kNuisEffFHCnueCCother07        );
  params.push_back(kNuisEffFHCnueCCother08        );
  params.push_back(kNuisEffFHCnueCCother09        );
  params.push_back(kNuisEffFHCnueCCother10        );
  params.push_back(kNuisEffFHCnueCCother11        );
  params.push_back(kNuisEffFHCnueCCWS01           );
  params.push_back(kNuisEffFHCnueCCWS02           );
  params.push_back(kNuisEffFHCNC0pi01             );
  params.push_back(kNuisEffFHCNC0pi02             );
  params.push_back(kNuisEffFHCNC0pi03             );
  params.push_back(kNuisEffFHCNC1pic01            );
  params.push_back(kNuisEffFHCNC1pic02            );
  params.push_back(kNuisEffFHCNC1pic03            );
  params.push_back(kNuisEffFHCNC1piz01            );
  params.push_back(kNuisEffFHCNC1piz02            );
  params.push_back(kNuisEffFHCNC1piz03            );
  params.push_back(kNuisEffFHCNCother01           );
  params.push_back(kNuisEffFHCNCother02           );
  params.push_back(kNuisEffFHCNCother03           );
  //~ params.push_back(kNuisEffFHCNeutrinoElec        );
  //~ params.push_back(kNuisEffFHCIMD                 );
  params.push_back(kNuisEffRHCnumuCC0pi1trk01     );
  params.push_back(kNuisEffRHCnumuCC0pi1trk02     );
  params.push_back(kNuisEffRHCnumuCC0pi1trk03     );
  params.push_back(kNuisEffRHCnumuCC0pi1trk04     );
  params.push_back(kNuisEffRHCnumuCC0pi1trk05     );
  params.push_back(kNuisEffRHCnumuCC0pi1trk06     );
  params.push_back(kNuisEffRHCnumuCC0pi1trk07     );
  params.push_back(kNuisEffRHCnumuCC0pi1trk08     );
  params.push_back(kNuisEffRHCnumuCC0pi1trk09     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk01     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk02     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk03     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk04     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk05     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk06     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk07     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk08     );
  params.push_back(kNuisEffRHCnumuCC0pi2trk09     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk01     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk02     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk03     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk04     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk05     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk06     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk07     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk08     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk09     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk10     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk11     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk12     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk13     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk14     );
  params.push_back(kNuisEffRHCnumuCC0piNtrk15     );
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta01);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta02);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta03);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta04);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta05);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta06);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta07);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta08);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta09);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta10);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta11);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta12);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta13);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta14);
  params.push_back(kNuisEffRHCnumuCC1pi3trkDelta15);
  params.push_back(kNuisEffRHCnumuCC1pic01        );
  params.push_back(kNuisEffRHCnumuCC1pic02        );
  params.push_back(kNuisEffRHCnumuCC1pic03        );
  params.push_back(kNuisEffRHCnumuCC1pic04        );
  params.push_back(kNuisEffRHCnumuCC1pic05        );
  params.push_back(kNuisEffRHCnumuCC1pic06        );
  params.push_back(kNuisEffRHCnumuCC1pic07        );
  params.push_back(kNuisEffRHCnumuCC1pic08        );
  params.push_back(kNuisEffRHCnumuCC1pic09        );
  params.push_back(kNuisEffRHCnumuCC1piz01        );
  params.push_back(kNuisEffRHCnumuCC1piz02        );
  params.push_back(kNuisEffRHCnumuCC1piz03        );
  params.push_back(kNuisEffRHCnumuCC1piz04        );
  params.push_back(kNuisEffRHCnumuCC1piz05        );
  params.push_back(kNuisEffRHCnumuCC1piz06        );
  params.push_back(kNuisEffRHCnumuCC1piz07        );
  params.push_back(kNuisEffRHCnumuCC1piz08        );
  params.push_back(kNuisEffRHCnumuCC1piz09        );
  params.push_back(kNuisEffRHCnumuCC1pic1piz01    );
  params.push_back(kNuisEffRHCnumuCC1pic1piz02    );
  params.push_back(kNuisEffRHCnumuCC1pic1piz03    );
  params.push_back(kNuisEffRHCnumuCC1pic1piz04    );
  params.push_back(kNuisEffRHCnumuCC1pic1piz05    );
  params.push_back(kNuisEffRHCnumuCC1pic1piz06    );
  params.push_back(kNuisEffRHCnumuCC1pic1piz07    );
  params.push_back(kNuisEffRHCnumuCC1pic1piz08    );
  params.push_back(kNuisEffRHCnumuCC1pic1piz09    );
  params.push_back(kNuisEffRHCnumuCCother01       );
  params.push_back(kNuisEffRHCnumuCCother02       );
  params.push_back(kNuisEffRHCnumuCCother03       );
  params.push_back(kNuisEffRHCnumuCCother04       );
  params.push_back(kNuisEffRHCnumuCCother05       );
  params.push_back(kNuisEffRHCnumuCCother06       );
  params.push_back(kNuisEffRHCnumuCCother07       );
  params.push_back(kNuisEffRHCnumuCCother08       );
  params.push_back(kNuisEffRHCnumuCCother09       );
  params.push_back(kNuisEffRHCnumuCCother10       );
  params.push_back(kNuisEffRHCnumuCCother11       );
  params.push_back(kNuisEffRHCnumuCCWS0pi01       );
  params.push_back(kNuisEffRHCnumuCCWS0pi02       );
  params.push_back(kNuisEffRHCnumuCCWS0pi03       );
  params.push_back(kNuisEffRHCnumuCCWS0pi04       );
  params.push_back(kNuisEffRHCnumuCCWS0pi05       );
  params.push_back(kNuisEffRHCnumuCCWS1pic01      );
  params.push_back(kNuisEffRHCnumuCCWS1pic02      );
  params.push_back(kNuisEffRHCnumuCCWS1pic03      );
  params.push_back(kNuisEffRHCnumuCCWS1pic04      );
  params.push_back(kNuisEffRHCnumuCCWS1pic05      );
  params.push_back(kNuisEffRHCnumuCCWS1pic06      );
  params.push_back(kNuisEffRHCnumuCCWS1pic07      );
  params.push_back(kNuisEffRHCnumuCCWS1pic08      );
  params.push_back(kNuisEffRHCnumuCCWS1piz01      );
  params.push_back(kNuisEffRHCnumuCCWS1piz02      );
  params.push_back(kNuisEffRHCnumuCCWS1piz03      );
  params.push_back(kNuisEffRHCnumuCCWSother01     );
  params.push_back(kNuisEffRHCnueCC0pi01          );
  params.push_back(kNuisEffRHCnueCC0pi02          );
  params.push_back(kNuisEffRHCnueCC0pi03          );
  params.push_back(kNuisEffRHCnueCC0pi04          );
  params.push_back(kNuisEffRHCnueCC0pi05          );
  params.push_back(kNuisEffRHCnueCC0pi06          );
  params.push_back(kNuisEffRHCnueCC0pi07          );
  params.push_back(kNuisEffRHCnueCC0pi08          );
  params.push_back(kNuisEffRHCnueCC0pi09          );
  params.push_back(kNuisEffRHCnueCC1pic01         );
  params.push_back(kNuisEffRHCnueCC1pic02         );
  params.push_back(kNuisEffRHCnueCC1pic03         );
  params.push_back(kNuisEffRHCnueCC1pic04         );
  params.push_back(kNuisEffRHCnueCC1pic05         );
  params.push_back(kNuisEffRHCnueCC1pic06         );
  params.push_back(kNuisEffRHCnueCC1pic07         );
  params.push_back(kNuisEffRHCnueCC1pic08         );
  params.push_back(kNuisEffRHCnueCC1pic09         );
  params.push_back(kNuisEffRHCnueCC1piz01         );
  params.push_back(kNuisEffRHCnueCC1piz02         );
  params.push_back(kNuisEffRHCnueCC1piz03         );
  params.push_back(kNuisEffRHCnueCC1piz04         );
  params.push_back(kNuisEffRHCnueCC1piz05         );
  params.push_back(kNuisEffRHCnueCC1piz06         );
  params.push_back(kNuisEffRHCnueCC1piz07         );
  params.push_back(kNuisEffRHCnueCC1piz08         );
  params.push_back(kNuisEffRHCnueCC1piz09         );
  params.push_back(kNuisEffRHCnueCCother01        );
  params.push_back(kNuisEffRHCnueCCother02        );
  params.push_back(kNuisEffRHCnueCCother03        );
  params.push_back(kNuisEffRHCnueCCother04        );
  params.push_back(kNuisEffRHCnueCCother05        );
  params.push_back(kNuisEffRHCnueCCother06        );
  params.push_back(kNuisEffRHCnueCCother07        );
  params.push_back(kNuisEffRHCnueCCother08        );
  params.push_back(kNuisEffRHCnueCCother09        );
  params.push_back(kNuisEffRHCnueCCother10        );
  params.push_back(kNuisEffRHCnueCCother11        );
  params.push_back(kNuisEffRHCnueCCWS01           );
  params.push_back(kNuisEffRHCnueCCWS02           );
  params.push_back(kNuisEffRHCNC0pi01             );
  params.push_back(kNuisEffRHCNC0pi02             );
  params.push_back(kNuisEffRHCNC0pi03             );
  params.push_back(kNuisEffRHCNC1pic01            );
  params.push_back(kNuisEffRHCNC1pic02            );
  params.push_back(kNuisEffRHCNC1pic03            );
  params.push_back(kNuisEffRHCNC1piz01            );
  params.push_back(kNuisEffRHCNC1piz02            );
  params.push_back(kNuisEffRHCNC1piz03            );
  params.push_back(kNuisEffRHCNCother01           );
  params.push_back(kNuisEffRHCNCother02           );
  params.push_back(kNuisEffRHCNCother03           );
  //~ params.push_back(kNuisEffRHCNeutrinoElec        );
  //~ params.push_back(kNuisEffRHCIMD                 );
  
  this->Init(params.size(), &params[0],"detector");
  
  this->SetName("DuneND2017a");
}
//________________________________________________________________________________________
DuneND2017a::~DuneND2017a()
{
  this->CleanUp();
}
//________________________________________________________________________________________
