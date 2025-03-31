void tweak_hist(TTree * t)
{
  using namespace valor;

  //mcdst as input

  // Fill MC templates from the input VALOR/DUNE DST TTree
  // We use a single tree for all samples for a single beam configuration.

  if(!t) {
    cout << "Null DST" << endl;
    util::Die(-1) ; return;
  }

  Long_t nev = t->GetEntries();
  cout << "Input VALOR DST has " << nev << " entries" << endl;;
  
  // Get a list of all the kinematic variables we care about
  const std::vector<conv::KineVar_t> & kinevars = fBinning->KineVars();

  int    sample        = -1;
  int    beam          = -1;
  int    reac_mode     = -1;
  double wght          = 1 ; //conv::kBadResult;
  double wght_pot      = conv::kBadResult;
  double baseline      = 0.;

  // Turn off all the branches by default
  t->SetBranchStatus("*",0);

  std::map<KineVar_t,double> kinematics;

  // Set up a list of the branches associated with each kinematic variable
  std::map<KineVar_t,std::string> kinematic_branch_names;
  for (const KineVar_t & kv : kinevars) {
    kinematic_branch_names[kv] = util::DSTBranchName(kv);
  }

  int bstat_sample     = 0; 
  int bstat_beam       = 0; 
  int bstat_reac_mode  = 0; 
  int bstat_baseline   = 0;
  std::map<KineVar_t,int> bstat_kinematics;

  // And turn all the base branches on
  t->SetBranchStatus("sample"   , 1);
  t->SetBranchStatus("beam"     , 1);
  t->SetBranchStatus("reac_mode", 1);
  t->SetBranchStatus("wght"     , 1);
  t->SetBranchStatus("wght_pot" , 1);
  t->SetBranchStatus("baseline" , 1);

  bstat_sample    = t->SetBranchAddress("sample",    &sample);
  bstat_sample    = t->SetBranchAddress("beam"  ,    &beam);
  bstat_reac_mode = t->SetBranchAddress("reac_mode", &reac_mode);
  bstat_baseline  = t->SetBranchAddress("baseline",  &baseline);

  // Weight is not required - use one if failed
  t->SetBranchAddress("wght"       , &wght);
  t->SetBranchAddress("wght_pot"   , &wght_pot);

  bool any_bad_status = (bstat_sample || bstat_beam || bstat_reac_mode || bstat_baseline);

  for(const conv::KineVar_t & kv : kinevars) {
    const char * branchname = kinematic_branch_names[kv].c_str();
    t->SetBranchStatus(branchname,1);
    bool bstat = t->SetBranchAddress(branchname,&kinematics[kv]);
    any_bad_status = any_bad_status || bstat;
  }

  if (any_bad_status) {
    LOG("GenericSingleSampleFitModel",pWARN)<<"MiniDST branches not found - giving up";
    util::Die(-1);
  }

  // Also read any other branches named "wght_"
  TPRegexp wght_branch_pattern("autowght_\\w+");
  std::map<std::string,double> wght_branches;
  TObjArray * branch_list = t->GetListOfBranches();
  for (int ib = 0 ; ib < branch_list->GetEntries(); ib++) {
    const char * branchname = branch_list->At(ib)->GetName();
    t->SetBranchStatus(branchname,1);
    TObjArray * matches = wght_branch_pattern.MatchS(branchname);
    if (matches->GetEntries()==1) {
      wght_branches[branchname] = -1.;
      t->SetBranchAddress(branchname,&(wght_branches[branchname]));
    }
    delete matches;
  }

  // Let's work out what universe branches we need
  //~ bool apply_universe_weights = fSystUniverseToApply.size();
  const size_t max_n_universes = 10000;
  std::map<std::string,int> branch_n_universes;
  std::map<std::string,std::vector<float>> branch_universes;
  for (const auto & variation_name : fUniverseParametersToSave) {
    branch_universes.emplace(variation_name,std::vector<float>(max_n_universes));
    std::string branch_name   = Form("variation_%s",variation_name.c_str());
    std::string branch_name_n = Form("variation_n_%s",variation_name.c_str());
    t->SetBranchStatus (branch_name_n.c_str(),1);
    t->SetBranchStatus (branch_name  .c_str(),1);
    bool bstat_univ_n = t->SetBranchAddress(branch_name_n.c_str(),&branch_n_universes[variation_name]);
    bool bstat_univ   = t->SetBranchAddress(branch_name.  c_str(),branch_universes  [variation_name].data());
    if (bstat_univ_n || bstat_univ) {
      LOG("GenericSingleSampleModel",pFATAL) << fName<<" Failed to load needed universe branch.";
      util::Die(-1) ; return;
    }
  }

  double tree_weight = t->GetWeight();

  LOG("GenericSingleSampleFitModel",pNOTICE) << "Input VALOR DST has weight "<<tree_weight;

  const VALORBinning * reco_ob = fBinning->RecoOptBinning();
  const VALORBinning * reco_sb = fBinning->RecoSmpBinning();

  for(Long_t iev = 0; iev < nev; iev++) 
  {
    t->GetEntry(iev);

    if(iev && iev%(nev/1000)==0) {
      double pct = (100 * (double)(iev+1)) / (double)nev;
      LOG("GenericSingleSampleFitModel",pINFO) << "Reading "<< fName <<" MC DST: "<< TMath::Nint(pct) << "% done";
    }

    // Get sample index
    Sample_t s = util::SampleFromInt(sample);
    if(s == ksUndefined) {
      LOG("GenericSingleSampleFitModel",pWARN) 
        << " ** Undefined sample ID used in MC event: " << iev
        << " (value stored in DST: " << sample << ")";
      //util::Die(-1);return;
    }

    //  ================ NOTE - HACKS ================
    if(s == ksNuMuCC2piC) {
      LOG("HACK",pNOTICE) 
        << "MC event: " << iev << " belongs to sample: " << util::AsString(s) 
        << " not considered separately. Bundle in sample: " << util::AsString(ksNuMuCCoth);
      s = ksNuMuCCoth;
    }

#ifdef FORCE_NC_INCLUSIVE
    if(util::IsNC(s)) {
      LOG("HACK",pNOTICE) 
        << "MC event: " << iev << " belongs to NC sample: " << util::AsString(s) 
        << " Bundling it in sample: " << util::AsString(ksNC);
      s = ksNC;
    }
#endif

    //  ==============================================
    if(s != fSample) {
#ifdef VALOR_EXPT_LOW_LEVEL_MESG_ENABLED
      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Ignoring MC event: " << iev 
        << " (sample ID: " << s << " "<< util::AsString(s) 
        << " not matching one used for configuring model: " 
        << fSample <<" "<<util::AsString(fSample) << ")";
#endif
      continue;  
    }

    BeamConf_t b = util::BeamConfFromInt(beam);
    if(b != fBeam) {
#ifdef VALOR_EXPT_LOW_LEVEL_MESG_ENABLED
      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Ignoring MC event: " << iev 
        << " (beam ID: " << b << " "<< util::AsString(b) 
        << " not matching one used for configuring model: " 
        << fBeam <<" "<<util::AsString(fBeam) << ")";
#endif
      continue;  
    }

    // Get reaction mode index
    ReacMode_t m = util::ReacModeFromInt(reac_mode);

    if(m == kmUndefined) {
      LOG("GenericSingleSampleFitModel",pWARN) 
        << " ** Undefined reaction mode ID used in MC event: " << iev
        << " (value stored in DST: " << reac_mode << "). Ignoring event.";
      continue;
    }

    long imode = fReactionModeIndex[m];
    if(imode==-1) {
      // For a given sample we should consider a complete list of
      // true reaction modes (otherwise there are true contributions to the
      // event sample which are not taken into account).
      LOG("GenericSingleSampleFitModel",pFATAL) 
        << " ** Ignoring MC event: " << iev 
        << " (ignoring contribution to sample: " << util::AsString(s) << " from mode: " << util::AsString(m) << " ?)";
      util::Die(-1);return;
    }

    bool is_null = fMCTNullOb[imode];
    if(is_null) {
      LOG("GenericSingleSampleFitModel",pFATAL) 
        << "** Null MC template for sample: " << util::AsString(s) 
        << ", mode: " << util::AsString(m);
      util::Die(-1);return;
    }
    bool is_null_sb = fMCTNullSb[imode];
    if(is_null_sb) {
      LOG("GenericSingleSampleFitModel",pFATAL) 
        << "** Null MC template (simple binning) for sample: " << util::AsString(s) 
        << ", mode: " << util::AsString(m) << " ??";
      util::Die(-1);return;
    }

    // Get the mode appropriate binning
    const VALORBinning * true_sb = fBinning->TrueSmpBinning(m);

    // check kinematic values against built-in limits and make vectors
    std::vector<double> true_vars;
    std::vector<double> reco_vars;
    bool out_of_range = false;
    // in true
    for (conv::KineVar_t kv : true_sb->KineVars()) {
      double val = kinematics.at(kv);
      if (val < true_sb->Minimum(kv) || val > true_sb->Maximum(kv)) {
        LOG("GenericSingleSampleFitModel",pWARN) 
          << "MC event: " << iev << " has true kinematic value outside range: "<<util::AsString(kv) << " = "<<val
          << ", range used: [" << true_sb->Minimum(kv) << ", " << true_sb->Maximum(kv) << "]";
        out_of_range = true;
      }
      true_vars.push_back(val);
    }
    // and in reco
    for (conv::KineVar_t kv : reco_ob->KineVars()) {
      double val = kinematics.at(kv);
      if (val < reco_ob->Minimum(kv) || val > reco_ob->Maximum(kv)) {
        if(fSuppressOutOfBinningRangeWarning){
          // Loads of T2K events have Ereco values outside of the binning range. This is fine because studies have shown
          // that they're all intrinsic nue so we don't care about them
          SLOG("GenericSingleSampleFitModel",pDEBUG)
            << fName<<" > MC event: " << iev << " has reco kinematic value outside range: "<<util::AsString(kv) << " = "<<val
            << ", range used: [" << reco_ob->Minimum(kv) << ", " << reco_ob->Maximum(kv) << "]";
        }
        else {
          SLOG("GenericSingleSampleFitModel", pWARN)
            << fName << " > MC event: " << iev << " has reco kinematic value outside range: " << util::AsString(kv)
            << " = " << val
            << ", range used: [" << reco_ob->Minimum(kv) << ", " << reco_ob->Maximum(kv) << "]";
        }
        out_of_range = true;
      }
      reco_vars.push_back(val);
    }
    if (out_of_range) {continue;}

    // Exposure for assumed data - Weight MC templates to that exposure
    double data_pot = fPOT;

    // Calculate POT weight (assumed data exposure) / (generated MC exposure)
    double pot_wght = wght_pot * data_pot * tree_weight;

    if(fFiducialMass > 0) {
      pot_wght = pot_wght*fFiducialMass;
    }

    // Now check for weights from external tuning files
    // TODO: Currently we don't consider the nuclear target in FillFromDST, but if that changes the final argument in GetExternalWeight must be modified accordingly
    double ext_wght = GetExternalWeight(kinematics, m, conv::kntInclusive);

    // Find the appropriate bins

    int true_bin    = true_sb->FindBin(true_vars);
    int reco_bin_sb = reco_sb->FindBin(reco_vars);
    int reco_bin_ob = reco_ob->FindBin(reco_vars);

    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Inserting to MC teplates --> MC event #" << iev 
      << "\n sample      = " << s        << " (" << util::AsString(s) << ")"
      << "\n beam        = " << beam     << " (" << util::AsString(b) << ")"
      << "\n imode       = " << imode    << " (" << util::AsString(m) << ")"
      << "\n wght        = " << wght 
      << "\n pot_wght    = " << pot_wght
      << "\n ext_wght    = " << ext_wght
      << "\n true_bin    = " << true_bin
      << "\n reco_bin_ob = " << reco_bin_ob
      << "\n reco_bin_sb = " << reco_bin_sb
      << "\n  True: "<<true_vars[0]<<" , "<<true_vars[1]
      << "\n  Reco: "<<reco_vars[0]<<" , "<<reco_vars[1];

    double this_entry = wght;

    this_entry *= pot_wght * ext_wght;

#ifdef APPLY_ALL_AUTOWGHT_BRANCHES
    // Apply the "autowght" variables
    for (const auto & namewght : wght_branches) {
      this_entry *= namewght.second;
    }
#endif


    // If we're doing SBL, save the baseline per event to calculate exact oscillation probabilities
    if (util::IsShortBaseline(fDetector)) {
      if (util::IsNeutrinoAny(m)) { // we only oscillate neutrinos
        const double & trueE = kinematics.at(conv::kvEtrue);
        fLoverEPerEvent.at(imode).at(true_bin).push_back(std::make_pair(baseline/trueE,this_entry));
      }
    }


    std::map<const int,double> universe_weights;

    VLOG("GenericSingleSampleFitModel",pDEBUG) << "Getting weights from " << fUniverseParametersToSave.size() << " systematic parameters";

    // If necessary, get the weight from the systematic variations
    for (const std::string & name : fUniverseParametersToSave) {
      if(!fUniversesAsList){
        size_t universe_offset = 0;
        VLOG("GenericSingleSampleFitModel",pDEBUG) << "By range";
        for (size_t universe_id = fFirstUniverseToSave ; universe_id <= fLastUniverseToSave ; universe_id++) {
          universe_offset = universe_id - fFirstUniverseToSave;
          const std::vector<float> & universes = branch_universes.at(name);
          // Right now we'll sum up the weighted bin totals
          float universe_entry = this_entry*universes.at(universe_id);
          fUniverseVariations[name][imode].AddToEntry(
              universe_entry,
              reco_bin_ob, true_bin, universe_offset
              );
        }
      } // Universes by range
      else{
        VLOG("GenericSingleSampleFitModel",pDEBUG) << "From list";
        for (size_t universe_offset = 0; universe_offset < fUniversesToRead.size(); universe_offset++) {
          size_t universe_id = fUniversesToRead.at(universe_offset);
          const std::vector<float> & universes = branch_universes.at(name);
          // Right now we'll sum up the weighted bin totals
          float universe_entry = this_entry*universes.at(universe_id);
          fUniverseVariations[name][imode].AddToEntry(
              universe_entry,
              reco_bin_ob, true_bin, universe_offset
              );
        }
      } // Universes by range
    }

    // Add `nom' array entry (and init `tun', `sys' and `fin' arrays = `nom')
    double curr_wght = fMCTNomOb[imode]->GetEntry(reco_bin_ob, true_bin);
    curr_wght += this_entry;
    fMCTNomOb [imode]->SetEntry(curr_wght, reco_bin_ob, true_bin);
    fMCTTunOb [imode]->SetEntry(curr_wght, reco_bin_ob, true_bin);
    fMCTSysOb [imode]->SetEntry(curr_wght, reco_bin_ob, true_bin);
    fMCTFinOb [imode]->SetEntry(curr_wght, reco_bin_ob, true_bin);     
    fMCStatOb [imode]->SetEntry(        1, reco_bin_ob, true_bin);

    double curr_wght_sb = fMCTNomSb[imode]->GetEntry(reco_bin_sb, true_bin);
    curr_wght_sb += this_entry;
    fMCTNomSb [imode]->SetEntry(curr_wght_sb, reco_bin_sb, true_bin);
    fMCTTunSb [imode]->SetEntry(curr_wght_sb, reco_bin_sb, true_bin);
    fMCTSysSb [imode]->SetEntry(curr_wght_sb, reco_bin_sb, true_bin);
    fMCTFinSb [imode]->SetEntry(curr_wght_sb, reco_bin_sb, true_bin);
    fMCStatSb [imode]->SetEntry(           1, reco_bin_sb, true_bin);

  }//iev

  // If we're storing the weights from the universes, here we should
  // divide out the unweighted total to get back to a simple weight
  size_t n_universes_to_save = 0;
  if(!fUniversesAsList)
    n_universes_to_save = fLastUniverseToSave - fFirstUniverseToSave + 1;
  else
    n_universes_to_save = fUniversesToRead.size();

  int n_reco_bins_ob = reco_ob->NBins();
  for (const std::string & name : fUniverseParametersToSave) {
    for (size_t universe_offset = 0 ; universe_offset < n_universes_to_save ; universe_offset++) {
      for(size_t imode = 0; imode < fReactionModes.size(); imode++){
        ReacMode_t m = fReactionModes[imode];
        if(m == kmUndefined) continue;
        const VALORBinning * true_sb = fBinning->TrueSmpBinning(m);
        const int n_true_bins = true_sb->NBins();

        for(int reco_bin_ob = 0 ; reco_bin_ob < n_reco_bins_ob ; reco_bin_ob++) {
          for (int true_bin = 0 ; true_bin < n_true_bins ; true_bin++) {
            float varied_entry = fUniverseVariations[name][imode].GetEntry(reco_bin_ob,true_bin,universe_offset);
            const float & orig_entry = fMCTFinOb [imode]->GetEntryRef(reco_bin_ob,true_bin);
            float universe_weight = 1.;
            if (std::abs(orig_entry) > conv::kASmallNum) {
              universe_weight = varied_entry/orig_entry;
            }
            fUniverseVariations[name][imode].SetEntry(universe_weight,reco_bin_ob,true_bin,universe_offset);
          }//true bins
        }//reco bins
      }//modes
    }//universe
  }//param

  LOG("GenericSingleSampleFitModel",pDEBUG)
    << "\n\nAfter filling MC templates from the input MC tree, the fMCTNomOb integrals for each mode are:";
  double fMCTNomOb_tot_integral = 0;
  for(size_t imode = 0; imode < fReactionModes.size(); imode++) {
    ReacMode_t m = fReactionModes[imode];
    if(m == kmUndefined) continue;
    fMCTNomOb_tot_integral += fMCTNomOb[imode]->Integral();
    LOG("GenericSingleSampleFitModel",pDEBUG)
      << "fMCTNomOb[" << util::AsString(m) << "] integral = " << fMCTNomOb[imode]->Integral();
  }
  LOG("GenericSingleSampleFitModel",pDEBUG) << "fMCTNomOb integral summed over all modes = " << fMCTNomOb_tot_integral;

}
