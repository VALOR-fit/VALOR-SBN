#ifdef __CINT__

#include <vector>

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace valor;
#pragma link C++ namespace valor::conv;
#pragma link C++ namespace valor::util;
#pragma link C++ namespace valor::util::binning;

// Vector types for use in macros:
#pragma link C++ class std::vector<std::vector<int>>;
#pragma link C++ class std::vector<TCanvas*>;
#pragma link C++ class std::vector<TH1*>;

#endif
