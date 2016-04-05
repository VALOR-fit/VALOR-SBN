{
  TString libs0 = gSystem->GetDynamicPath();
  TString libs  = libs0 + ":/usr/lib:/usr/local/lib:/opt/lib:/opt/local/lib:$VALOR_FMWK/lib:$VALOR_DUNE/lib";
  gSystem->SetDynamicPath(libs.Data());
  
  TString features(gROOT->GetConfigFeatures());

  // extra ROOT libs
  gSystem->Load("libGpad");
  gSystem->Load("libPhysics");
  gSystem->Load("libMatrix");
  gSystem->Load("libHist");
  gSystem->Load("libGraf");
  gSystem->Load("libTree");
  gSystem->Load("libRIO");
  gSystem->Load("libXMLIO");
  gSystem->Load("libMinuit");
  gSystem->Load("libMinuit2");
  
  if (features.Contains("mathmore")) {gSystem->Load("libMathMore"); }

  // log4cpp lib
  gSystem->Load("liblog4cpp");

  // VALOR libs
  gSystem->Load("libValorConv.so");
  gSystem->Load("libValorMesg.so");
  gSystem->Load("libValorFitCore.so");
  gSystem->Load("libValorUtil.so");
  gSystem->Load("libValorParse.so");
  gSystem->Load("libValorDuneConv.so");
  gSystem->Load("libValorDuneSDFit.so");
}

