//____________________________________________________________________________
/*!

\class     valor::ToyBuilder

\brief     A class that builds marginalisation and fake data toys.

\author    Andy Chappell <A.Chappell \at warwick.ac.uk>
           University of Warwick

           Francis Bench <F.Bench \at liverpool.ac.uk>
           University of Liverpool

\created   November 21, 2019

\copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// TODO: Update descriptions
// TODO: What to do with fitParam1Bin and fitParam2Bin? Maybe move the filename construction out of ToyBuilder?
// TODO: Remove _va_format being a class member?

#ifndef _valor_toy_builder_h_
#define _valor_toy_builder_h_

#include <string>

#include "dune/Elements/CompoundFitElements.h"

#include "valor/FitCore/FitDataABC.h"
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/FitResult.h"

#include "TH1.h"
#include "TH2.h"

#include <TTree.h>

using std::string;
using namespace valor;

namespace valor
{

class ToyBuilder
{
public:
   /**
      Constructs a ToyBuilder object.

      \param elements The CompoundFitElements object used to generate the MC
             spectra.
      \param filePrefix The prefix to be used for the marginalisation toy files
             to be written.
      \param va_format The format that VALORArrays are stored as.
   */
   ToyBuilder(CompoundFitElements& elements, string filePrefix, bool use_simple_binning,
                   bool save_throws_to_tree = false, string va_format = "pdft");

   /**
      Destructor.

      This class does not own the FitModel object, so it does not destroy it.
   */
   virtual ~ToyBuilder();

   /**
      Builds a batch of marginalisation or fake data toys, depending on the supplied option.

      To facilitate incremental building of toys, a complete set
      of toys can be split into batches, each of which should
      have the same number of toys in it.

      \param fitParamBin The bin associated with the current unmarginalised
             oscillation parameter.
      \param batch The numeric ID for the batch of toys to be generated. This
             should start with batch 0.
      \param Ntoys The number of toys to be created in *this*
             batch.
      \param fpl The FitParamList defining the parameters to be used in
             generating the toys. This method will only throw
             those parameters that return true for FitParamList::IsMarginalized.
      \param randomizeSystematics Whether or not to randomize the systematics.
             Default true (kind of the point of marginalisation, but might be
             useful for testing).
      \param options The options associated with randomizing systematics.
      \param rethrowUnphysical Whether or not to rethrow parameters that exceed
             their physical boundaries (Cholesky decomposition can cause
             parameters to move beyond bounds even if they are thrown with
             limits). Default true.
      \param toy_throw_file_to_read Read throws from a pre-existing file instead of
             generating them. This is used e.g. to convert T2K legacy toy throws
             into SDK marginalisation toys.
             NOTE: As this reads thrown parameter values, statistical fluctuations
             are not copied
      \param param_name_map_file If using toy_throw_file_to_read, also specify this
             argument, which is used to convert SDK parameter names into the parameter
             names used by the toy_throw_file_to_read.
   */
   void BuildToys(const int fitParamBin, const int batch, const int Ntoys,
         FitParamList& fpl, bool randomizeSystematics = true,
         const char* options = "randomize-all;prefit-errors",
         bool rethrowUnphysical = true, std::string toy_throw_file_to_read = "",
         std::string param_name_map_file = "");

   /**
      Builds a batch of marginalisation or fake data toys.

      To facilitate incremental building of toys, a complete set
      of toys can be split into batches, each of which should
      have the same number of toys in it.

      \param fitParam1Bin The bin associated with the first unmarginalised
             oscillation parameter.
      \param fitParam2Bin The bin associated with the second unmarginalised
             oscillation parameter.
      \param batch The numeric ID for the batch of toys to be generated. This
             should start with batch 0.
      \param Ntoys The number of toys to be created in *this*
             batch.
      \param fpl The FitParamList defining the parameters to be used in
             generating the toys. This method will only throw
             those parameters that return true for FitParamList::IsMarginalized.
      \param randomizeSystematics Whether or not to randomize the systematics.
             Default true (kind of the point of marginalisation, but might be
             useful for testing).
      \param options The options associated with randomizing systematics.
      \param rethrowUnphysical Whether or not to rethrow parameters that exceed
             their physical boundaries (Cholesky decomposition can cause
             parameters to move beyond bounds even if they are thrown with
             limits). Default true.
      \param toy_throw_file_to_read Read throws from a pre-existing file instead of
             generating them. This is used e.g. to convert T2K legacy toy throws
             into SDK marginalisation toys.
             NOTE: As this reads thrown parameter values, statistical fluctuations
             are not copied
      \param param_name_map_file If using toy_throw_file_to_read, also specify this
             argument, which is used to convert SDK parameter names into the parameter
             names used by the toy_throw_file_to_read.
   */
   void BuildToys(const int fitParam1Bin, const int fitParam2Bin,
         const int batch, const int Ntoys, FitParamList& fpl,
         bool randomizeSystematics = true,
         const char* options = "randomize-all;prefit-errors",
         bool rethrowUnphysical = true, std::string toy_throw_file_to_read = "",
         std::string param_name_map_file = "");


private:

   /**
      Saves all parameter values in the input FitParamList to a tree.

      \param fpl The fit param list to save.

      \param write_tree Write the tree to an output file
   */
   void SaveParamThrows(FitParamList& fpl, bool write_tree, std::string binary_file_name);

  /**
     Read a single set of parameter throws from a T2K legacy toy throw file into the input FitParamList.

     \param fpl Store the read parameter throws in this FitParamList
     \param toy_throw_file_to_read Read throws from a pre-existing file instead of
            generating them. This is used e.g. to convert T2K legacy toy throws
            into SDK marginalisation toys.
            NOTE: As this reads thrown parameter values, statistical fluctuations
            are not copied
     \param param_name_map_file This file is used to convert SDK parameter names
            into the parameter names used by the toy_throw_file_to_read.
  */
  void ReadParamsFromThrowFile(FitParamList& fpl, std::string toy_throw_file_to_read,
                               std::string param_name_map_file, const char* options, int toy_number);

private:
   string       _filePrefix;
   FitModelABC* _model;
   FitDataABC*  _data;
   bool         _use_simple_binning;
   bool         _save_throws_to_tree;
   TTree*       _tree_pars;
   string       _va_format;

   // For reading throws from an input file
   double*      _read_params;
   TFile*       _toy_throw_file;
};

} // valor

#endif

