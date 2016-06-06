{
  TString fmwk_loadlibs = ".x $VALOR_FMWK/root/loadlibs.C";
  gSystem->ExpandPathName(fmwk_loadlibs);
  gROOT->ProcessLine(fmwk_loadlibs.Data());
  
  TString baselibs = gSystem->GetDynamicPath();
  TString dune_libs = "$VALOR_DUNE/lib:";
  dune_libs += baselibs;
  
  gSystem->SetDynamicPath(dune_libs.Data());
  
  gSystem->Load("libValorDuneConv.so");
  gSystem->Load("libValorDuneBinning.so");
  gSystem->Load("libValorDuneUtil.so");
  gSystem->Load("libValorDuneElements.so");
  gSystem->Load("libValorDuneSystematics.so");
  gSystem->Load("libValorDuneSDFit.so");
}

