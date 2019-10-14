import ROOT
import sys
import os
import glob
import math
import itertools

print "\n=============================="
print   "Loading python with VALOR"

# If GENIE available, load that too
try:
  genv = os.environ["GENIE"]
  ROOT.gROOT.ProcessLine(".x ${GENIE}/src/scripts/gcint/loadlibs.C");
  print "          and GENIE"
except KeyError:
  pass
print   "==============================\n"

ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_expt.C");


ROOT.gROOT.ProcessLine("using namespace valor;");
ROOT.gROOT.ProcessLine("using namespace valor::util;");
ROOT.gROOT.ProcessLine("using namespace valor::conv;");

R = ROOT

valor = ROOT.valor
conv  = valor.conv
util  = valor.util
opt   = valor.Opt.Instance()
rnd   = valor.Rnd.Instance()
nr    = util.NameRegistry.Instance()
es    = valor.ExperimentSetup.Instance()

expt_name = es.ExperimentName();
print "Experiment:",expt_name

try:
  import numpy as np
except:
  print "Warning: Numpy not loaded"

opt.gDoNotDie = True # We're interactive, so don't die unless you have to.

# Make float formatting strings
for n in xrange(1,9):
  globals()["to"+`n`+"dp"] = "{0:."+`n`+"f}"
  globals()["to"+`n`+"sf"] = "{0:."+`n-1`+"e}"
  
  
# Touch every VALOR object so they appear in tab completion
import os
for root, dirs, files in itertools.chain(os.walk(os.environ['VALOR_FMWK']),os.walk(os.environ['VALOR_DUNE'])):
  for f in files:
    if f.endswith(".cxx"):
      classname = f[:-4]
      try:
        getattr(valor,classname)
      except:
        pass
  
# Quick and dirty function to get every object in a file
def fileburst(f):
  for k in f.GetListOfKeys():
    obj = k.ReadObj()
    if (obj.ClassName()=="TTree"):
      if obj.GetEntries():
        obj.GetEntry(0)
    globals()[k.GetName()] = obj
  return
  
rootargs = [x for x in sys.argv if x.endswith(".root")]
i=0
for f in rootargs:
  varname = "_file"+`i`
  print "Attaching file ",f," as ",varname
  globals()[varname] = ROOT.TFile(f)
  i+=1
  if i > 999: break

if (i==1):
  fileburst(_file0)
