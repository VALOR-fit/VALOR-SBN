std::vector<std::string> proposal_systematics =
{ "genie_ccresAxial_Genie",
  "genie_ncresAxial_Genie",
  "genie_qema_Genie",
  "genie_NC_Genie",
  "genie_NonResRvpCC1pi_Genie",
  "genie_NonResRvnCC1pi_Genie",
  "genie_NonResRvbarnCC1pi_Genie",
  "genie_NonResRvbarpCC1pi_Genie",
  "genie_NonResRvpCC2pi_Genie",
  "genie_NonResRvnCC2pi_Genie",
  "genie_NonResRvbarnCC2pi_Genie",
  "genie_NonResRvbarpCC2pi_Genie",
  "genie_NonResRvpNC1pi_Genie",
  "genie_NonResRvnNC1pi_Genie",
  "genie_NonResRvbarnNC1pi_Genie",
  "genie_NonResRvbarpNC1pi_Genie",
  "genie_NonResRvpNC2pi_Genie",
  "genie_NonResRvnNC2pi_Genie",
  "genie_NonResRvbarnNC2pi_Genie",
  "genie_NonResRvbarpNC2pi_Genie"
};
std::vector<std::string> modern_systematics = 
{ "genie_DISAth_Genie",
  "genie_DISBth_Genie",
  "genie_DISCv1u_Genie",
  "genie_DISCv2u_Genie",
  "genie_IntraNukeNabs_Genie",
  "genie_IntraNukeNcex_Genie",
  "genie_IntraNukeNinel_Genie",
  "genie_IntraNukeNmfp_Genie",
  "genie_IntraNukeNpi_Genie",
  "genie_IntraNukePIabs_Genie",
  "genie_IntraNukePIcex_Genie",
  "genie_IntraNukePIinel_Genie",
  "genie_IntraNukePImfp_Genie",
  "genie_IntraNukePIpi_Genie",
  "genie_ResDecayGamma_Genie",
  "genie_ccresVector_Genie",
  "genie_cohMA_Genie",
  "genie_cohR0_Genie",
  "genie_ncelAxial_Genie",
  "genie_ncelEta_Genie",
  "genie_ncresVector_Genie"
};
std::vector<std::string> flux_systematics =
{ "horncurrent_FluxUnisim",
  "expskin_FluxUnisim",
  "nucleoninexsec_FluxUnisim",
  "nucleonqexsec_FluxUnisim",
  "nucleontotxsec_FluxUnisim",
  "pioninexsec_FluxUnisim",
  "pionqexsec_FluxUnisim",
  "piontotxsec_FluxUnisim"
};

std::vector<std::string> detectors =
{ "sbn_nd",
  "sbn_uboone",
  "sbn_icarus"
};

std::vector<std::string> detector_location =
{ "sbnd",
  "uboone",
  "icarus"
};

TString filename = "valor_splines_[SAMPLE]_[PARAM]_BNB_FHC_[DET]_modelist.root";
TString GetFilename(const std::string &p, const std::string &d, const std::string &s, const std::string &l, const unsigned int &i);
TString GetOutputFilename(const std::string &s, const std::string &t);

void chain_modelists(const std::string &syst, const std::string &location="", const std::string &sample="numuCCincl", const std::string &tag="")
{
  using namespace valor;

  // Get the appropriate list of systematics
  std::vector<std::string> systematics;
  if(syst == "mod"){
    systematics = modern_systematics; 
    std::cout << " Chaining the modelists from the modern systematics" << std::endl;
  }
  else if(syst == "prop"){
    systematics = proposal_systematics; 
    std::cout << " Chaining the modelists from the proposal systematics" << std::endl;
  }
  else if(syst == "flux"){
    systematics = flux_systematics; 
    std::cout << " Chaining the modelists from the flux systematics" << std::endl;
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
        tree->GetEntry(0);
        for(const std::string &pm : *pmodes){ 
          std::vector<std::string>::iterator it = std::find(modes.begin(),modes.end(),pm);
          if(it == modes.end())
            modes.push_back(pm);
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
  if(l != ""){
    name.Prepend("/");
    name.Prepend(detector_location.at(i));
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
