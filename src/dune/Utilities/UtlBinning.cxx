#include "dune/Utilities/UtlBinning.h"

namespace valor
{
namespace util
{

TH1D* Make1DHistogram(VALORArray v, SingleSampleKineBinning b,
     conv::KineVar_t k)
{
   return nullptr;
}

TH2D* Make2DOptimisedHistogram(VALORArray v, SingleSampleKineBinning b,
     std::vector<conv::KineVar_t> ks)
{
   return nullptr;
}

TH2D* Make2DSimpleHistogram(VALORArray v, SingleSampleKineBinning b,
     std::vector<conv::KineVar_t> ks)
{
   return nullptr;
}

VALORArray* Contract(VALORArray v, SingleSampleKineBinning b,
     std::vector<conv::KineVar_t> ks)
{
   return nullptr;
}

TH1D* Remap1D(VALORArray v, SingleSampleKineBinning b,
      conv::KineVar_t k)
{
   return nullptr;
}

TH2D* RemapOptimised2D(VALORArray v, SingleSampleKineBinning b,
      std::vector<conv::KineVar_t> ks)
{
   return nullptr;
}

TH2D* RemapSimple2D(VALORArray v, SingleSampleKineBinning b,
      std::vector<conv::KineVar_t> ks)
{
   return nullptr;
}

}
}

