void valor_dune()
{   
    TString curr_dir = gSystem->pwd();
    gSystem->cd(curr_dir.Data());

    TString top_dir = gSystem->Getenv("VALOR_DUNE");

    TString loadincs = ".x " + top_dir + "/root/loadincs.C";
    TString loadlibs = ".x " + top_dir + "/root/loadlibs.C";
    
    gROOT->ProcessLine(loadincs.Data());
    gROOT->ProcessLine(loadlibs.Data());
    
    TString loadutils = ".x " + top_dir + "/root/valor_dune_utils.C";
    gROOT->ProcessLine(loadutils.Data());
}
