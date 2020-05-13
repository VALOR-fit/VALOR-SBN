std::vector<std::string> interaction_systematics =
{ "genie_ccresAxial_Genie",
  "genie_ncresAxial_Genie",
  "genie_qema_Genie",
  "genie_NC_Genie",
  "genie_NonResRvbarp1pi_Genie",
  "genie_NonResRvbarp2pi_Genie",
  "genie_NonResRvp1pi_Genie",
  "genie_NonResRvp2pi_Genie",
};

TString filename = "valor_splines_numulikeCChigh_[PARAM]_BNB_FHC_modelist.root";
TString GetFilename(const std::string &p);

void chain_modelists()
{
  using namespace valor;

  std::map< std::string, std::vector<std::string> > param_modelist;
  std::map< std::string, std::vector<std::string> >::const_iterator itr;
  for(const std::string &param : interaction_systematics){
    TString file = GetFilename(param);
    TFile flist(file.Data());
    if(!flist.IsZombie()){
      std::cout << " Opened file: " << file << std::endl;
      std::vector<std::string> *pmodes = 0;
      std::vector<std::string> modes;
      TTree *tree = static_cast<TTree*>(flist.Get("ModeList"));
      tree->SetBranchAddress(param.c_str(),&pmodes);
      tree->GetEntry(0);
      modes = *pmodes;
      param_modelist.emplace(param,modes);
    }
  }
  TFile f("all_modelists.root","RECREATE");
  TTree *t = new TTree("ModeLists","Mode lists from all interaction parameters");
  t->SetCircular(1); // Only save the very last fill: with all entries
  for(itr = param_modelist.begin(); itr != param_modelist.end(); ++itr) {
    std::string param = itr->first;
    t->Branch(param.c_str(),&param_modelist.at(param));
    t->Fill();
  }
  f.Write();
  f.Close();
}

TString GetFilename(const std::string &p){
  TString name = filename;
  name = name.ReplaceAll("[PARAM]",p.data());
  return name;
}
