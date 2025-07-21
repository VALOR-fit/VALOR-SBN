std::vector<std::string> genierw_systematics =
{       "ZExpA1CCQE",
        "ZExpA2CCQE",
        "ZExpA3CCQE",
        "ZExpA4CCQE",
        "RPACCQE",
        "CoulombCCQE",
        "NormCCMEC",
        "ncelAxial",
        "ncelEta",
        "ccresAxial",
        "ccresVector",
        "ncresAxial",
        "ncresVector",
        "NonResRvpCC1pi",
        "NonResRvpCC2pi",
        "NonResRvpNC1pi",
        "NonResRvpNC2pi",
        "NonResRvnCC1pi",
        "NonResRvnCC2pi",
        "NonResRvnNC1pi",
        "NonResRvnNC2pi",
        "NonResRvbarpCC1pi",
        "NonResRvbarpCC2pi",
        "NonResRvbarpNC1pi",
        "NonResRvbarpNC2pi",
        "NonResRvbarnCC1pi",
        "NonResRvbarnCC2pi",
        "NonResRvbarnNC1pi",
        "NonResRvbarnNC2pi",
        "RDecBR1gamma",
        "RDecBR1eta",
        "NormCCCOH",
        "DISAth",
        "DISBth",
        "DISCv1u",
        "DISCv2u",
        "IntraNukePImfp",
        "IntraNukePIcex",
        "IntraNukePIinel",
        "IntraNukePIabs",
        "IntraNukePIpi",
        "IntraNukeNmfp",
        "IntraNukeNcex",
        "IntraNukeNinel",
        "IntraNukeNabs",
        "IntraNukeNpi"
};
std::vector<std::string> minerva_systematics = 
{       "E2p2hAv",
        "E2p2hBv",
        "E2p2hAvbar",
        "E2p2hBvbar",
        "Mnv2p2hGaussEnhancement",
};
std::vector<std::string> misc_systematics =
{       "C12ToAr402p2hScalingv",
        "C12ToAr402p2hScalingvbar",
        "SPPLowQ2Suppression",
};
std::vector<std::string> nova_systematics =
{       "NOvANonResvbarnCC1Pi",
        "NOvANonResvbarnCC2Pi",
        "NOvANonResvbarnCC3Pi",
        "NOvANonResvbarnNC1Pi",
        "NOvANonResvbarnNC2Pi",
        "NOvANonResvbarpCC1Pi",
        "NOvANonResvbarpCC2Pi",
        "NOvANonResvbarpNC1Pi",
        "NOvANonResvbarpNC2Pi",
        "NOvANonResvnCC2Pi",
        "NOvANonResvnCC3Pi",
        "NOvANonResvnNC1Pi",
        "NOvANonResvnNC2Pi",
        "NOvANonResvnNC3Pi",
        "NOvANonResvnpCC1Pi",
        "NOvANonResvpCC2Pi",
        "NOvANonResvpCC3Pi",
        "NOvANonResvpNC1Pi",
        "NOvANonResvpNC2Pi",
        "NOvANonResvpNC3Pi",
};

std::vector<std::string> detectors =
{ "sbn_nd"
};

std::vector<std::string> detector_location =
{ ""
};

TString filename = "valor_splines_[SAMPLE]_[PARAM]_BNB_FHC_[DET]_modelist.root";
TString GetFilename(const std::string &p, const std::string &d, const std::string &s, const std::string &l, const unsigned int &i);
TString GetOutputFilename(const std::string &s, const std::string &t);

void chain_modelists_nd_04a1(const std::string &syst, const std::string &location="", const std::string &sample="numuCCincl", const std::string &tag="")
{
  using namespace valor;

  // Get the appropriate list of systematics
  std::vector<std::string> systematics;
  if(syst == "genierw"){
    systematics = genierw_systematics; 
    std::cout << " Chaining the modelists from the genie reweight interaction systematics" << std::endl;
  }
  else if(syst == "minerva"){
    systematics = minerva_systematics; 
    std::cout << " Chaining the modelists from the minerva interaction systematics" << std::endl;
  }
  else if(syst == "misc"){
    systematics = misc_systematics; 
    std::cout << " Chaining the modelists from the misc interaction systematics" << std::endl;
  }
  else if(syst == "nova"){
    systematics = nova_systematics; 
    std::cout << " Chaining the modelists from the nova interaction systematics" << std::endl;
  }
  else if(syst == "allint"){
    systematics = genierw_systematics;
    systematics.insert(systematics.end(), minerva_systematics.begin(), minerva_systematics.end());
    systematics.insert(systematics.end(), misc_systematics.begin(), misc_systematics.end());
    systematics.insert(systematics.end(), nova_systematics.begin(), nova_systematics.end());
    std::cout << " Chaining the modelists from the genie reweight, minerva, misc, and nova interaction systematics" << std::endl;
  }

  std::map< std::string, std::vector<std::string> > param_modelist;
  std::map< std::string, std::vector<std::string> >::const_iterator itr;
  for(const std::string &param : systematics){
    std::vector<std::string> modes;
    unsigned int n = 0;
    for(const std::string &det : detectors){
      TString file = GetFilename(param,det,sample,location,n);
      TFile flist(file.Data());
      if(!flist.IsZombie()){
        std::cout << " Opened file: " << file << std::endl;
        std::vector<std::string> *pmodes = 0;
        TTree *tree = static_cast<TTree*>(flist.Get("ModeList"));
        tree->SetBranchAddress(param.c_str(),&pmodes);
        // For nue, we have three distinct samples when generating the response functions 
        // Once they've been generated, I've hadd'ed everything together so this tree ends up with 3 entries(one for each sample)
        for(auto i = 0; i < tree->GetEntries(); i++){
          tree->GetEntry(i);
          for(const std::string &pm : *pmodes){ 
            std::vector<std::string>::iterator it = std::find(modes.begin(),modes.end(),pm);
            if(it == modes.end())
              modes.push_back(pm);
          }
        }
      }
      ++n;
    }
    param_modelist.emplace(param,modes);
  }
  TString output_file = GetOutputFilename(sample,tag);
  TFile f(output_file.Data(),"RECREATE");
  TTree *t = new TTree("ModeLists","Mode lists from all parameters");
  t->SetCircular(1); // Only save the very last fill: with all entries
  for(itr = param_modelist.begin(); itr != param_modelist.end(); ++itr) {
    std::string param = itr->first;
    t->Branch(param.c_str(),&param_modelist.at(param));
    t->Fill();
  }
  f.Write();
  f.Close();
}

TString GetFilename(const std::string &p, const std::string &d, const std::string &s, const std::string &l, const unsigned int &i){
  TString name = filename;
  name.ReplaceAll("[PARAM]",  p.data());
  name.ReplaceAll("[DET]",    d.data());
  name.ReplaceAll("[SAMPLE]", s.data());
  if(l != "" && s=="numuCCincl"){
    name.Prepend("/");
    name.Prepend(detector_location.at(i));
    name.Prepend("/");
    name.Prepend(l.data());
  }
  else{
    name.Prepend("/");
    //name.Prepend(detector_location.at(i));
    name.Prepend("/");
    name.Prepend(l.data());
  }

  std::cout << " Reading file: " << name << std::endl;
  return name;
}
TString GetOutputFilename(const std::string &s, const std::string &t){
  TString name = "_modelist.root";
  name.Prepend(s.data());
  if(t != ""){
    name.Prepend("_");
    name.Prepend(t.data());
  }
  return name;
}
