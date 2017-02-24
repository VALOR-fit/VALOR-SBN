#include "dune/Utilities/UtlBinning.h"

#include <algorithm>

// valor
#include "valor/Utilities/UtlSystem.h"
#include "valor/Messenger/Messenger.h"

namespace valor
{
namespace util
{

TH1D* UtlBinning::Make1DHistogram(const VALORArray& v,
      const SingleSampleKineBinning& b, conv::KineVar_t k)
{
   return nullptr;
}

TH2D* UtlBinning::Make2DOptimisedHistogram(const VALORArray& v,
      const SingleSampleKineBinning& b, const std::vector<conv::KineVar_t>& ks)
{
   // Get the reco binning and associated kinematic variables for the VALORArray
   KBCubHcmbMondrian& recoBinning = (*b.RecoOptBinning());
   const std::vector<conv::KineVar_t>& recoKv = recoBinning.KineVars();

   // Check that the request kinematic variables match those for the VALORArray
   // (This should use the contraction method in the future)
   if(ks.size() != recoKv.size())
   {
      LOG("UtlBinning", pERROR) << "Expected " << recoKv.size() <<
         " kinematic variables to plot, found " << ks.size();
      util::Die(-1);
   }
   for(auto kv : ks)
   {
      if(std::find(recoKv.begin(), recoKv.end(), kv) == recoKv.end())
      {  // Mismatch in variables
         LOG("UtlBinning", pERROR) << "Kinematic variable " <<
            util::AsString(kv) << " not found in template kinematic space " <<
            util::AsString(recoBinning.KineSpace());
         util::Die(-1);
      }
   }
   // Integrate over the truth variables
   unsigned int nbins = recoBinning.NBins();
   double events[nbins];
   for(unsigned int i = 0; i < nbins; ++i)
   {
      // Reco is always first dimension in VALORArray, so fix the bins in this
      // dimension and integrate over the rest
      events[i] = v.Integral(i, i);
   }
   
   // Map the events to a ROOT compatible histogram
   TH2D* histo = RemapOptimised2D(events, recoBinning);
   
   return histo;
}

TH2D* UtlBinning::Make2DSimpleHistogram(const VALORArray& v,
      const SingleSampleKineBinning& b, const std::vector<conv::KineVar_t>& ks)
{
   // Get the reco binning and associated kinematic variables for the VALORArray
   KBCubHcmbEdge2Edge& recoBinning = (*b.RecoSmpBinning());
   const std::vector<conv::KineVar_t>& recoKv = recoBinning.KineVars();

   // Check that the request kinematic variables match those for the VALORArray
   // (This should use the contraction method in the future)
   if(ks.size() != recoKv.size())
   {
      LOG("UtlBinning", pERROR) << "Expected " << recoKv.size() <<
         " kinematic variables to plot, found " << ks.size();
      util::Die(-1);
   }
   for(auto kv : ks)
   {
      if(std::find(recoKv.begin(), recoKv.end(), kv) == recoKv.end())
      {  // Mismatch in variables
         LOG("UtlBinning", pERROR) << "Kinematic variable " <<
            util::AsString(kv) << " not found in template kinematic space " <<
            util::AsString(recoBinning.KineSpace());
         util::Die(-1);
      }
   }
   // Integrate over the truth variables
   unsigned int nbins = recoBinning.NBins();
   double events[nbins];
   for(unsigned int i = 0; i < nbins; ++i)
   {
      // Reco is always first dimension in VALORArray, so fix the bins in this
      // dimension and integrate over the rest
      events[i] = v.Integral(i, i);
   }
   
   // Map the events to a ROOT compatible histogram
   TH2D* histo = RemapSimple2D(events, recoBinning);
   
   return histo;
}

VALORArray* UtlBinning::Contract(const VALORArray& v,
      const SingleSampleKineBinning& b, const std::vector<conv::KineVar_t>& ks)
{
   return nullptr;
}

TH1D* UtlBinning::Remap1D(const double* events, const KBCubHcmbEdge2Edge& b)
{
   return nullptr;
}

TH2D* UtlBinning::RemapOptimised2D(const double* events,
      const KBCubHcmbMondrian& b)
{
   // Find all bin edges in each dimension
   std::set<double> dim1Edges;
   std::set<double> dim2Edges;
   for(int i = 0; i < b.NBins(); ++i)
   {
      // Minimum edge of first dimension for bin i
      dim1Edges.insert(b.BinMinimum(i, 0));
      // Maximum edge of first dimension for bin i
      dim1Edges.insert(b.BinMaximum(i, 0));
      // Minimum edge of second dimension for bin i
      dim2Edges.insert(b.BinMinimum(i, 1));
      // Maximum edge of second dimension for bin i
      dim2Edges.insert(b.BinMaximum(i, 1));
   }
   // No need to sort or remove duplicate edges as both properties are
   // guaranteed by set
   // Create the Root histogram
   int nDim1Bins = dim1Edges.size() - 1;
   double dim1BinEdges[nDim1Bins + 1];
   std::copy(dim1Edges.begin(), dim1Edges.end(), dim1BinEdges);
   int nDim2Bins = dim2Edges.size() - 1;
   double dim2BinEdges[nDim2Bins + 1];
   std::copy(dim2Edges.begin(), dim2Edges.end(), dim2BinEdges);
   TH2D* histo = new TH2D("histo", "histo", nDim1Bins, dim1BinEdges,
         nDim2Bins, dim2BinEdges);

   // Get the number of bins from our ROOT histogram
   int xbins = histo->GetNbinsX();
   int ybins = histo->GetNbinsY();
   std::vector<double> coords = {0.0, 0.0};
   for(int i = 1; i <= xbins; ++i)
   {
      coords[0] = histo->GetXaxis()->GetBinCenter(i);
      for(int j = 1; j <= ybins; ++j)
      {
         coords[1] = histo->GetYaxis()->GetBinCenter(j);
         int index = b.FindBin(coords);
         histo->SetBinContent(i, j, events[index]);
      }
   }

   return histo;
}

TH2D* UtlBinning::RemapSimple2D(const double* events,
      const KBCubHcmbEdge2Edge& b)
{
   // Find all bin edges in each dimension
   std::set<double> dim1Edges;
   std::set<double> dim2Edges;
   for(unsigned int i = 0; i < b.NBins(); ++i)
   {
      // Minimum edge of first dimension for bin i
      dim1Edges.insert(b.BinMinimum(i, 0));
      // Maximum edge of first dimension for bin i
      dim1Edges.insert(b.BinMaximum(i, 0));
      // Minimum edge of second dimension for bin i
      dim2Edges.insert(b.BinMinimum(i, 1));
      // Maximum edge of second dimension for bin i
      dim2Edges.insert(b.BinMaximum(i, 1));
   }
   // No need to sort or remove duplicate edges as both properties are
   // guaranteed by set
   // Create the Root histogram
   int nDim1Bins = dim1Edges.size() - 1;
   double dim1BinEdges[nDim1Bins + 1];
   std::copy(dim1Edges.begin(), dim1Edges.end(), dim1BinEdges);
   int nDim2Bins = dim2Edges.size() - 1;
   double dim2BinEdges[nDim2Bins + 1];
   std::copy(dim2Edges.begin(), dim2Edges.end(), dim2BinEdges);
   TH2D* histo = new TH2D("histo", "histo", nDim1Bins, dim1BinEdges,
         nDim2Bins, dim2BinEdges);

   // Get the number of bins from our ROOT histogram
   int xbins = histo->GetNbinsX();
   int ybins = histo->GetNbinsY();
   std::vector<double> coords = {0.0, 0.0};
   for(int i = 1; i <= xbins; ++i)
   {
      coords[0] = histo->GetXaxis()->GetBinCenter(i);
      for(int j = 1; j <= ybins; ++j)
      {
         coords[1] = histo->GetYaxis()->GetBinCenter(j);
         int index = b.FindBin(coords);
         histo->SetBinContent(i, j, events[index]);
      }
   }

   return histo;
}

}
}

