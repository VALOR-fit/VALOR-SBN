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

\copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved
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

#include "Conventions/ReacMode.h"
#include "NDFit/NDSample.h"
#include "NDFit/NDModel.h"
#include "NDFit/NDSampleBinning.h"

using namespace std;
// --------------------------------------------------------------------------
namespace valor {
  class MakeSplines
  {
  public:

    MakeSplines();

    virtual ~MakeSplines();

    // Matrix containing the +/- 1,2,3 sigma energy scale
    TMatrixD MakeGraphs(string confile, int zone, bool sb = false);
    // Array of trees saving the energy scale application 
    TObjArray* CreateArray(string inFile, string inTree, bool leptonic);

    // Read the datacard
    void ReadXMLDatacard(string datacard);

    // Return the number of E_reco, E_true, y_reco bins
    int GetERecoBins(){return erecobins;};
    int GetETrueBins(){return etruebins;};
    int GetYRecoBins(){return yrecobins;};

    // Get the number of samples and the number of reaction modes
    int GetNumberOfSamples(){return   conv::kNNDSamples;};
    int GetNumberOfReacModes(){return conv::kNReacModes;};
    int GetNumberOfBinZones(){return  conv::kNMaxBinZones;};

  protected:
    // Tree variables
    double ELScale[7], EhadScale[7];
    int sample, reactionmode;
    double Ev, Ev_reco, y_reco, POTWeight;
    double Ehad_reco, EL_reco;
    // NDModel
    //NDModel *ndmodel;
    // Number of bins
    int erecobins, etruebins, yrecobins;

    void SetERecoBins(int ferecobins){erecobins = ferecobins;};
    void SetETrueBins(int fetruebins){etruebins = fetruebins;};
    void SetYRecoBins(int fyrecobins){yrecobins = fyrecobins;};

  private:
    ClassDef(MakeSplines,1)
      };

} // valor
#endif
