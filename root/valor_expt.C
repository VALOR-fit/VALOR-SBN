void valor_expt()
{   
    TString curr_dir = gSystem->pwd();
    gSystem->cd(curr_dir.Data());

    TString top_dir = gSystem->Getenv("VALOR_DUNE");

    TString loadincs = ".x " + top_dir + "/root/valor_expt_loadincs.C";
    TString loadlibs = ".x " + top_dir + "/root/valor_expt_loadlibs.C";
    
    gROOT->ProcessLine(loadincs.Data());
    gROOT->ProcessLine(loadlibs.Data());
    
    TString loadutils = ".x " + top_dir + "/root/valor_expt_utils.C";
    gROOT->ProcessLine(loadutils.Data());
}
