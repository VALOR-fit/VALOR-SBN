
/*

This macro makes selected event samples from LBNE fast MC files using reconstructed information only. 
All events reconstruced as numu CC or NC are written to the output tree. The sample for each event 
is given by sampleIndex, and this corresponds to the enum in NDSample.h. The samples are 

NumuCC1Track: reconstructed as numu CC with no track in hadronic system
NumuCC2Track: reconstructed as numu CC with exactly 1 track in hadronic system with length > trackLengthCut
NumuCC1ChPi:  reconstructed as numu CC with exactly 2 tracks in hadronic system with length > trackLengthCut
NumuCC1Pi0:   reconstructed as numu CC with >= 2 tracks in hadronic system and exactly 2 EM objects; longest track has
              length > trackLengthCut, second longest track has length < trackLengthCut, and shortest track has
              length < trackLengthCut
NumuCCOther:  other numu CC
NueCC:        reconstructed as nue CC (there are no true nue CC events)
NC1Pi0:       reconstructed as NC with >= 1 track in hadronic system and exactly 2 EM objects; both longest and
              shortest tracks have length < trackLengthCut
NCOther:      other NC


CC event samples can be normalised using the scale factor

2.20471e-12 * POT * fiducial mass (kt) / nCCEvents

where

2.20471e-12 is number of true CC interactions / POT / kt in near detector - this is NuMuCCEventRate / POTperYear
in /lbne/data/users/lblpwg_tools/FastMC_Data/flux_files/v3r0p10/nominal/g4lbne_v3r0p10_FHC_ND.root.

nCCEvents is the number of true CC events in event sample before selection - this is in the gst tree.


NC event samples can be normalised in a similar way using the scale factor

7.44098e-13 * POT * fiducial mass (kt) / nNCEvents

where

7.44098e-13 is the number of true NC interactions / POT / kt in near detector - this is NuMuNCEventRate / POTperYear
in /lbne/data/users/lblpwg_tools/FastMC_Data/flux_files/v3r0p10/nominal/g4lbne_v3r0p10_FHC_ND.root.

nNCEvents is the number of true NC events in event sample before selection - this is in the gst tree.

Nick Grant 5 May 2014

*/

void make_event_sample_from_reco
(
 TString sampleFileName = "NDEventSamples.root",
 double trackLengthCut = 0.05
)
{

  using namespace valor::conv;

  const int nSamples = 10;

  TString sampleName[nSamples] = {"CCInc", "CC1Track", "CC2Track", "CC1ChPi", "CC1Pi0", "CCOther", "NueCC", "NCInc", "NC1Pi0", "NCOther"};

  TChain *fastMCchain = new TChain("gst");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_1.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_2.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_3.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_4.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_5.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_6.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_7.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_8.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_9.root");
  fastMCchain->Add("/lbne/data/users/lblpwg_tools/FastMC_Data/outputs/nigrant/fastMC_ND_FHC_numuflux_numu_10.root");

  int neu;  
  bool cc;
  bool nc;
  //number of CC + NC interactions per kt per POT - according to https://cdcvs.fnal.gov/redmine/projects/fast_mc/wiki/Nominal_Flux_Normalizations
  //or number of CC + NC interactions per POT - according to comment in gNtpConv_FastMC.cxx
  double POTWeight;

  //number of initial state pi plus; "i" means "initial", i.e. after primary interaction but before intranuclear rescattering
  int nip;
  int nipip;
  int nipim;
  int nipi0;
  int nikp;
  int nikm;
  int nik0;
  int niem;
  int niother;
  int ni;
  //number of pi plus in final state; "f" means "final", i.e. after intranuclear rescattering
  int nfp;
  int nfpip;
  int nfpim;
  int nfpi0;

  //EVClass_reco is reco type of event: 0 = numu CC, 1 = nue CC, 2 = NC. This is copied from the fast MC code:
  //  1) If there is a track longer than 2.0 m.
  //     The event will be classifies as a CC-numu, and 
  //     the longest track above 2.0 m will be considered the muon
  //  2) If there is no track longer than 2.0 m then the event will be serched for unmatched EM showers
  //     If an unmatched EM shower is found than  the event will be classified as a CC-nue, and
  //     the unmatched shower will be taken as the electron
  //     Unmatched refers to an alorithm that serches the list of final state EM particles for pairs that reconstruct to pi0s (more details below)
  //  3) If there is no track longer than 2.0m and there is no unmatched EM shower, then the event is classified as and NC event.
  int EvClass_reco;

  //Upper case L refers to the particle reconstructed as the primary lepton.
  //It is not necessarily the true primary lepton.
  int PdgL;
  double pL_reco;
  double pxL_reco;
  double pyL_reco;
  double pzL_reco;
  double Ehad_reco;
  double EhadB_reco;
  double cthL_reco;
  double TrkL_reco;
  bool IsContL_reco;

  const int maxParticles = 100;

  const int nf;
  int pdgf[maxParticles];
  double Ef[maxParticles];
  double pxf[maxParticles];
  double pyf[maxParticles];
  double pzf[maxParticles];
  double pf[maxParticles];
  double cthf[maxParticles];
  double Ef_reco[maxParticles];
  double pxf_reco[maxParticles];
  double pyf_reco[maxParticles];
  double pzf_reco[maxParticles];
  double Trkf_reco[maxParticles];
  double cthf_reco[maxParticles];

  const int nEMf;
  int EMpdgf[maxParticles];
  double EMpxf[maxParticles];
  double EMpyf[maxParticles];
  double EMpzf[maxParticles];
  double EMpf[maxParticles];
  double EMcthf[maxParticles];
  double EMEf[maxParticles];
  double Ef_reco[maxParticles];
  double EMpxf_reco[maxParticles];
  double EMpyf_reco[maxParticles];
  double EMpzf_reco[maxParticles];
  double EMTrkf_reco[maxParticles];
  double EMcthf_reco[maxParticles];
  double EMPizMass_reco[maxParticles];
  double EMElPizM_reco[maxParticles];

  gst->SetBranchAddress("neu",&neu);
  gst->SetBranchAddress("cc",&cc);
  gst->SetBranchAddress("nc",&nc);
  gst->SetBranchAddress("POTWeight",&POTWeight);
  gst->SetBranchAddress("nip",&nip);
  gst->SetBranchAddress("nipip",&nipip);
  gst->SetBranchAddress("nipim",&nipim);
  gst->SetBranchAddress("nipi0",&nipi0);
  gst->SetBranchAddress("nikp",&nikp);
  gst->SetBranchAddress("nikm",&nikm);
  gst->SetBranchAddress("nik0",&nik0);
  gst->SetBranchAddress("niem",&niem);
  gst->SetBranchAddress("niother",&niother);
  gst->SetBranchAddress("ni",&ni);
  gst->SetBranchAddress("nfp",&nfp);
  gst->SetBranchAddress("nfpip",&nfpip);
  gst->SetBranchAddress("nfpim",&nfpim);
  gst->SetBranchAddress("nfpi0",&nfpi0);

  gst->SetBranchAddress("EvClass_reco",&EvClass_reco);

  gst->SetBranchAddress("PdgL",&PdgL);
  gst->SetBranchAddress("pL_reco",&pL_reco);
  gst->SetBranchAddress("pxL_reco",&pxL_reco);
  gst->SetBranchAddress("pyL_reco",&pyL_reco);
  gst->SetBranchAddress("pzL_reco",&pzL_reco);
  gst->SetBranchAddress("cthL_reco",&cthL_reco);
  gst->SetBranchAddress("TrkL_reco",&TrkL_reco);
  gst->SetBranchAddress("IsContL_reco",&IsContL_reco);

  gst->SetBranchAddress("nf",&nf);
  gst->SetBranchAddress("pdgf",pdgf);
  gst->SetBranchAddress("Ef",Ef);
  gst->SetBranchAddress("pxf",pxf);
  gst->SetBranchAddress("pyf",pyf);
  gst->SetBranchAddress("pzf",pzf);
  gst->SetBranchAddress("pf",pf);
  gst->SetBranchAddress("cthf",cthf);
  gst->SetBranchAddress("Ef_reco",Ef_reco);
  gst->SetBranchAddress("pxf_reco",pxf_reco);
  gst->SetBranchAddress("pyf_reco",pyf_reco);
  gst->SetBranchAddress("pzf_reco",pzf_reco);
  gst->SetBranchAddress("Trkf_reco",Trkf_reco);
  gst->SetBranchAddress("cthf_reco",cthf_reco);
  gst->SetBranchAddress("nEMf",&nEMf);
  gst->SetBranchAddress("EMpdgf",EMpdgf);
  gst->SetBranchAddress("EMEf",EMEf);
  gst->SetBranchAddress("EMpxf",EMpxf);
  gst->SetBranchAddress("EMpyf",EMpyf);
  gst->SetBranchAddress("EMpzf",EMpzf);
  gst->SetBranchAddress("EMpf",EMpf);
  gst->SetBranchAddress("EMcthf",EMcthf);
  gst->SetBranchAddress("Ef_reco",Ef_reco);
  gst->SetBranchAddress("EMpxf_reco",EMpxf_reco);
  gst->SetBranchAddress("EMpyf_reco",EMpyf_reco);
  gst->SetBranchAddress("EMpzf_reco",EMpzf_reco);
  gst->SetBranchAddress("EMTrkf_reco",EMTrkf_reco);
  gst->SetBranchAddress("EMcthf_reco",EMcthf_reco);
  gst->SetBranchAddress("EMPizMass_reco",EMPizMass_reco);
  gst->SetBranchAddress("EMElPizM_reco",EMElPizM_reco);

  TFile *sampleFile = new TFile(sampleFileName, "RECREATE");
  //clone tree from input fast MC file but don't write any events yet
  TTree *sampleTree = gst->CloneTree(0);

  int sampleIndex, nEvents, nCCEvents, nNCEvents, br_sampleIndex, br_nEvents, br_nCCEvents, br_nNCEvents;
  double maxTrackLength, maxTrackLength2, minTrackLength;

  //add some braches to tree containing selected events
  sampleTree->Branch("sampleIndex", &br_sampleIndex, "sampleIndex/I");
  sampleTree->Branch("nEvents", &br_nEvents, "nEvents/I");
  sampleTree->Branch("nCCEvents", &br_nCCEvents, "nCCEvents/I");
  sampleTree->Branch("nNCEvents", &br_nNCEvents, "nNCEvents/I");

  nEvents = 0;
  nCCEvents = 0;
  nNCEvents = 0;

  //number of true events in each sample
  int nTrueEvents[nSamples] = {0};
  int nTrueEventsPassSel[nSamples] = {0};
  int nEventsPassSel[nSamples] = {0};

  for(Long64_t i = 0; i < gst->GetEntries(); i++)
    {
      gst->GetEntry(i);
      if(i%10000 == 0)
        cout<<"Doing event "<<i<<endl;

      nEvents++;

      if(cc)
        nCCEvents++;

      if(nc)
        nNCEvents++;
    }//end of loop over events

  for(Long64_t i = 0; i < gst->GetEntries(); i++)
    {
      gst->GetEntry(i);
      if(i%10000 == 0)
        cout<<"Doing event "<<i<<endl;

      maxTrackLength = -999.9;
      maxTrackLength2 = -999.9;
      minTrackLength = 99999.9;
      for(int j=0; j<nf; j++)
	{
        if(Trkf_reco[j] > maxTrackLength)
          {
	  maxTrackLength2 = maxTrackLength;
	  maxTrackLength = Trkf_reco[j];
          }
        if(Trkf_reco[j] < maxTrackLength && Trkf_reco[j] > maxTrackLength2)
	  maxTrackLength2 = Trkf_reco[j];
        if(Trkf_reco[j] > 0.0 && Trkf_reco[j] < minTrackLength)
          minTrackLength = Trkf_reco[j];
	}

      if(cc && neu == 14)
	{
	if(ni == 0)
	  nTrueEvents[ksNDNuMuCC1trkQE]++;
	else if(nip == 1 && (nipip + nipim == 0) && nipi0 == 0 && nikp == 0 && nikm == 0 && nik0 == 0)
	  nTrueEvents[ksNDNuMuCC2trkQE]++;
	else if((nipip + nipim == 1) && nipi0 == 0 && nikp == 0 && nikm == 0 && nik0 == 0)
	  nTrueEvents[ksNDNuMuCC1piC]++;
	else if((nipip + nipim == 0) && nipi0 == 1 && nikp == 0 && nikm == 0 && nik0 == 0)
	  nTrueEvents[ksNDNuMuCC1pi0]++;
	else
	  nTrueEvents[ksNDNuMuCCoth]++;
	}

      if(EvClass_reco == 0)
	{
	if(nf == 0 && nEMf == 0)
	  {
	  br_sampleIndex = ksNDNuMuCC1trkQE;
	  nEventsPassSel[ksNDNuMuCC1trkQE]++;
          if(cc && ni == 0)
            nTrueEventsPassSel[ksNDNuMuCC1trkQE]++;
	  }
	else if(nf == 1 && Trkf_reco[0] > trackLengthCut && nEMf == 0)
	  {
	  br_sampleIndex = ksNDNuMuCC2trkQE;
	  nEventsPassSel[ksNDNuMuCC2trkQE]++;
	  if(cc && nip == 1 && (nipip + nipim == 0) && nipi0 == 0 && nikp == 0 && nikm == 0 && nik0 == 0)
	    nTrueEventsPassSel[ksNDNuMuCC2trkQE]++;
	  }
	else if(nf == 2 && Trkf_reco[0] > trackLengthCut && Trkf_reco[1] > trackLengthCut && nEMf == 0)
	  {
	  br_sampleIndex = ksNDNuMuCC1piC;
	  nEventsPassSel[ksNDNuMuCC1piC]++;
	  if(cc && (nipip + nipim == 1) && nipi0 == 0 && nikp == 0 && nikm == 0 && nik0 == 0)
	    nTrueEventsPassSel[ksNDNuMuCC1piC]++;
	  }
	else if(nf >= 2 && maxTrackLength > trackLengthCut && maxTrackLength2 < trackLengthCut && minTrackLength < trackLengthCut && nEMf == 2)
	  {
	  br_sampleIndex = ksNDNuMuCC1pi0;
	  nEventsPassSel[ksNDNuMuCC1pi0]++;
	  if(cc && (nipip + nipim == 0) && nipi0 == 1)
	    nTrueEventsPassSel[ksNDNuMuCC1pi0]++;
	  }
	else
	  {
	  br_sampleIndex = ksNDNuMuCCoth;
	  nEventsPassSel[ksNDNuMuCCoth]++;
	  if(cc 
             && !(nip == 1 && (nipip + nipim == 0) && nipi0 == 0  && nikp == 0 && nikm == 0 && nik0 == 0) 
             && !((nipip + nipim == 1) && nipi0 == 0 && nikp == 0 && nikm == 0 && nik0 == 0) 
	     && !((nipip + nipim == 0) && nipi0 == 1 && nikp == 0 && nikm == 0 && nik0 == 0))
	     nTrueEventsPassSel[ksNDNuMuCCoth]++;
	  }
	}//end of if(EvClass_reco == 0)

      if(EvClass_reco == 1)
	br_sampleIndex = ksNDNuECC;

      if(nc)
        {
	if((nipip + nipim == 0) && nipi0 == 1 && nikp == 0 && nikm == 0 && nik0 == 0)
	  nTrueEvents[ksNDNC1pi0]++;
	else
	  nTrueEvents[ksNDNCoth]++;
        }

      if(EvClass_reco == 2)
        {
        if(nf >= 1 && minTrackLength < trackLengthCut && maxTrackLength < trackLengthCut && nEMf == 2)
	  {
          br_sampleIndex = ksNDNC1pi0;
	  nEventsPassSel[ksNDNC1pi0]++;
	  if(nc && (nipip + nipim == 0) && nipi0 == 1 && nikp == 0 && nikm == 0 && nik0 == 0)
	    nTrueEventsPassSel[ksNDNC1pi0]++;
	  }
        else
	  {
          br_sampleIndex = ksNDNCoth;
	  nEventsPassSel[ksNDNCoth]++;
	  if(nc && !((nipip + nipim == 0) && nipi0 == 1) && nikp == 0 && nikm == 0 && nik0 == 0)
	    nTrueEventsPassSel[ksNDNCoth]++;
	  }
        }

      br_nEvents = nEvents;
      br_nCCEvents = nCCEvents;
      br_nNCEvents = nNCEvents;

      sampleTree->Fill();

    }//end of loop over events

  cout<<setprecision(3);
  cout<<endl;
  for(int j=0; j<nSamples; j++)
    {
    if(j == ksNDNuMuCC || j == ksNDNuECC || j == ksNDNC)
      continue;
    cout<<"Efficiency / purity of sample "<<sampleName[j]<<" is "<<(double)nTrueEventsPassSel[j] / nTrueEvents[j]
    <<" / "<<(double)nTrueEventsPassSel[j] / nEventsPassSel[j]<<endl; 
    cout<<endl;
    }

  sampleTree->Write();

}//end of make_event_sample_from_reco()


