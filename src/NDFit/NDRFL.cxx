//________________________________________________________________________________________
/*

Copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

//#include <TSystem.h>

#include "NDFit/NDRFL.h"

using std::endl;

using namespace valor;

//________________________________________________________________________________________
namespace valor {
  ostream & operator<<(ostream & stream, const NDRFL & rfl)
  {
    rfl.Print(stream);
    return stream;
  }
}
//________________________________________________________________________________________
NDRFL * NDRFL::fInstance = 0;
//________________________________________________________________________________________
NDRFL::NDRFL() 
{
  fInstance = 0;
}
//________________________________________________________________________________________
NDRFL::NDRFL(const NDRFL &) 
{

}
//________________________________________________________________________________________
NDRFL::~NDRFL()
{

}
//________________________________________________________________________________________
NDRFL * NDRFL::Instance()
{
  if(fInstance == 0) {
    static NDRFL::Cleaner cleaner;
    cleaner.DummyMethodAndSilentCompiler();
    fInstance = new NDRFL;
  }
  return fInstance;
}
//________________________________________________________________________________________
void NDRFL::Print(ostream & stream) const
{
  stream << "[response functions]" << endl;

}
//________________________________________________________________________________________
