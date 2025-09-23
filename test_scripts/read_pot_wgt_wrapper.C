#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

#include "TROOT.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TList.h"
#include "TString.h"
#include "TSystem.h"
//#include "TIter.h"

int read_pot_wgt_wrapper(std::string directory) {
  TSystemDirectory dir(gSystem->BaseName(TString(directory)), directory.c_str());
  TList * files = dir.GetListOfFiles();
  TIter next(files);
  TSystemFile * file;
  std::vector<std::string> files_to_get_pot_from;

  while( (file = dynamic_cast<TSystemFile *>(next())) ) {
    TString fname = file->GetName();
    if( !file->IsDirectory() && fname.Contains("minidst") && fname.EndsWith(".root") ) {
      files_to_get_pot_from.emplace_back( std::string( Form("%s/%s", directory.c_str(), fname.Data())) );
      //std::cout << "Getting POT from file " << Form("%s/%s", directory.c_str(), fname.Data()) << std::endl;
    }
  }

  std::sort( files_to_get_pot_from.begin(), files_to_get_pot_from.end(), 
	     [](std::string a, std::string b){
	       TObjString as(a.c_str());
	       TObjString bs(b.c_str());
	       return as.GetString() < bs.GetString();
	     } );

  for( std::vector<std::string>::iterator it_fl = files_to_get_pot_from.begin(); 
       it_fl != files_to_get_pot_from.end(); ++it_fl ) {
    std::cout << "Getting POT from " << *it_fl << "..." << std::endl;
  }

  // ready cout to capture the buffer
  std::stringstream buffer;
  std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

  gROOT->ProcessLine(".L read_pot_wgt.C+");
  for ( std::vector<std::string>::iterator it_fl = files_to_get_pot_from.begin(); 
	it_fl != files_to_get_pot_from.end(); ++it_fl ) {
    gROOT->ProcessLine(Form(".x read_pot_wgt.C(\"%s\")", (*it_fl).c_str()));
  }

  // restore cout
  std::cout.rdbuf(old);
  
  std::string captured = buffer.str();
  double totalPOT = 0.0;
  
  // put that into a vector
  std:stringstream bfsts(captured);
  std::string line;

  while( std::getline(bfsts, line) ) {
    if(!line.empty()) {
      // sanitise line and yeet newlines
      line.erase( std::remove(line.begin(), line.end(), '\n'), line.end() );
      // YEET out the return message, YUCK
      if( line.find("int") != std::string::npos ) continue;

      std::cout << line.c_str() << std::endl;
      totalPOT += std::stod(line);
    }
  }

  std::cout << "\n" << captured;
  std::cout << "which corresponds to total POT = " << totalPOT << std::endl;
  
  return 0;
}
