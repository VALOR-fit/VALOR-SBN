//____________________________________________________________________________
/*!

\class     valor::MakeSplines - Write the leptonic and hadronic energy scale into splines 

\brief     LBNE ND Makesplines class.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <n.grant \at lancaster.ac.uk>
           University of Lancaster

\created   July 21, 2014

\copyright (c) 2010-2014, The VALOR group
*/
//____________________________________________________________________________
#ifndef MAKESPLINES
#define MAKESPLINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"
#include "TGraph.h"
#include "TH1.h"
#include "TSpline.h"

#include "Utilities/UtlXML.h"

#include "NDFit/NDModel.h"

using namespace std;
// --------------------------------------------------------------------------
namespace valor {
  class MakeSplines
  {
  public:

    MakeSplines();

    virtual ~MakeSplines();

    // Matrix containing the +/- 1,2,3 sigma energy scale
    TMatrixD MakeGraphs(string confile);
    // Array of trees saving the energy scale application 
    TObjArray* CreateArray(string inFile, string inTree, bool leptonic);

    // Read the datacard
    void ReadXMLDatacard(string datacard);

  protected:
    // Tree variables
    double ELScale[7], EhadScale[7];
    int sample, reactionmode;
    double Ev, Ev_reco, y_reco, POTWeight;
    double Ehad_reco, EL_reco;
    // NDModel
    NDModel *ndmodel;
  private:
    ClassDef(MakeSplines,1)
      };

} // valor
#endif
