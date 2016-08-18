#ifdef __CINT__

#include <vector>

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace valor;
#pragma link C++ namespace valor::conv;
#pragma link C++ namespace valor::util;
#pragma link C++ namespace valor::util::nm;

#pragma link C++ enum valor::conv::KineVar_t;
#pragma link C++ enum valor::conv::KineSpace_t;
#pragma link C++ enum valor::conv::BeamConf_t;
#pragma link C++ enum valor::conv::Sample_t;
#pragma link C++ enum valor::conv::ReacMode_t;
#pragma link C++ enum valor::conv::ReacModeCoarse_t;
#pragma link C++ enum valor::conv::ReacType_t;
#pragma link C++ enum valor::conv::FitParamGroup_t;

#pragma link C++ struct valor::DataID;
#pragma link C++ class std::vector<valor::DataID>+;

#pragma link C++ class valor::util::ArrIdx+;
#pragma link C++ class valor::util::PhysicalParameterLimits+;

#endif
