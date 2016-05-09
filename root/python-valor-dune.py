import ROOT
import sys
import os
import glob
import math

print "\n=============================="
print   "Loading python with VALOR DUNE"

# If GENIE available, load that too
try:
  genv = os.environ["GENIE"]
  ROOT.gROOT.ProcessLine(".x ${GENIE}/src/scripts/gcint/loadlibs.C");
  print "          and GENIE"
except KeyError:
  pass
print   "==============================\n"

try:
  import numpy as np
except:
  print "Warning: Numpy not loaded"

ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");

ROOT.gROOT.ProcessLine("using namespace valor;");
ROOT.gROOT.ProcessLine("using namespace valor::util;");
ROOT.gROOT.ProcessLine("using namespace valor::conv;");

rootargs = [x for x in sys.argv if x.endswith(".root")]
i=0
for f in rootargs:
  varname = "_file"+`i`
  print "Attaching file ",f," as ",varname
  globals()[varname] = ROOT.TFile(f)
  i+=1

R = ROOT

valor = ROOT.valor
conv  = valor.conv
util  = valor.util
opt   = valor.Opt.Instance()
#~ t2kopt = valor.T2KOpt.Instance()
rnd    = valor.Rnd.Instance()
#~ arridx = util.ArrIdx.Instance()
#~ physlim = util.T2KPhysicalParameterLimits.Instance()
nr = util.NameRegistry.Instance()

opt.gDoNotDie = True # We're interactive, so don't die unless you have to.

# Make float formatting strings
for n in xrange(1,9):
  globals()["to"+`n`+"dp"] = "{0:."+`n`+"f}"
  globals()["to"+`n`+"sf"] = "{0:."+`n-1`+"e}"
  
# Quick and dirty function to get every object in a file
def fileburst(f):
  for k in f.GetListOfKeys():
    obj = k.ReadObj()
    if (obj.ClassName()=="TTree"):
      if obj.GetEntries():
        obj.GetEntry(0)
    globals()[k.GetName()] = obj
  return
