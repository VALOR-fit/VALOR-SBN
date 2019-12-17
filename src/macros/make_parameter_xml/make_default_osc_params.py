#!/usr/bin/python

import ROOT
import os
from collections import namedtuple

ROOT.PyConfig.IgnoreCommandLineOptions = True

try:
  ROOT.valor
except:
  ROOT.gROOT.ProcessLine(".x $VALOR_EXPT/root/valor_expt.C");

valor = ROOT.valor
util =  valor.util
conv =  valor.conv
opt  =  valor.Opt.Instance()
env  =  valor.Env.Instance()

ROOT.gROOT.SetBatch(1)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

_xmleng = 0
_xmldoc = 0
_default_root_node_name = "param_list"

_param_fields = namedtuple('param_fields',
                           [
                             'name_simple',
                             'type',
                             'limits',
                             'init',
                             'error',
                             'range_mode',
                             'range',
                             'step_mode',
                             'step'
                           ])

#______________________________________________________________________________________________________________________________


def main(filename, overwrite):
  global _xmleng
  global _xmldoc

  # Check if the output file already exists
  exists = os.path.isfile(filename)
  if not exists:
    print "Creating new file", filename
  else:
    if overwrite and filename != "":
      print "Overwriting file", filename
      os.remove(filename)
    else:
      print "A file named", filename, "already exists and the --overwrite option was not specified. Exiting."
      util.Die(-1)

  # Set up the XML file
  _xmleng = ROOT.TXMLEngine()
  _xmldoc = _xmleng.NewDoc()
  if not _xmldoc:
    print "FATAL: Could not create the XML document in file", filename, ". Exiting."
    util.Die(-1)

  # Create a root node if one doesn't exist already
  root_node = make_root_node("default_osc_param_values")

  # Read the attributes of each oscillation parameter and write to the XML file
  for p in range(0, conv.knppmax):
    # Skip non-osc params
    if util.IsSystematic(p):
      continue

    # Set all of the possible XML fields
    fields = _param_fields(
      name_simple     = util.NameRegistry.Instance().ParamAsStringVerySimple(p),
      type            = "special",
      limits          = get_limits(p),
      init            = get_init(p),
      error           = get_error(p),
      range_mode      = "value",
      range           = get_range(p),
      step_mode       = "value",
      step            = get_step(p),
    )
    print "For param", util.NameRegistry.Instance().ParamAsStringVerySimple(p), "the following fields have been set:\n", fields

    # Write all parameter fields to the output XML file
    add_param(root_node, fields)

    del fields
    print "\n\n"

  _xmleng.SaveDoc(_xmldoc, filename)
  _xmleng.FreeDoc(_xmldoc)

  print "Successfully wrote the parameter file", filename
  print "Done!"
  return


def get_init(p):
  use_p = get_non_barred_param(p)
  return str(util.OscParamInitValue(use_p))


def get_error(p):
  use_p = get_non_barred_param(p)
  return str(util.OscParamInitError(use_p))


def get_step(p):
  use_p = get_non_barred_param(p)
  return str(util.OscParamStepSize(use_p))


def get_range(p):
  use_p = get_non_barred_param(p)
  min = util.OscParamMinValue(use_p)
  max = util.OscParamMaxValue(use_p)
  limits_str = ""
  if min == -9E9:
    limits_str += "-inf"
  else:
    limits_str += str(min)
  limits_str += ", "
  if max == 9E9:
    limits_str += "inf"
  else:
    limits_str += str(max)
  return limits_str


def get_limits(p):
  use_p = get_non_barred_param(p)
  min = valor.PhysicalParameterLimits.Instance().MinValue(use_p)
  if util.IsMixingAngle(use_p) and min == -1:
    min = 0
  if use_p == conv.kPhypCPV:
    min = -3.1416
    max =  3.1416
  max = valor.PhysicalParameterLimits.Instance().MaxValue(use_p)
  limits_str = ""
  if min == -9E9:
    limits_str += "-inf"
  else:
    limits_str += str(min)
  limits_str += ", "
  if max == 9E9:
    limits_str += "inf"
  else:
    limits_str += str(max)
  return limits_str


def get_non_barred_param(p):
  if p == conv.kPhypMixing23Bar: return conv.kPhypMixing23
  if p == conv.kPhypMixing13Bar: return conv.kPhypMixing13
  if p == conv.kPhypMixing12Bar: return conv.kPhypMixing12
  if p == conv.kPhypCPVBar:      return conv.kPhypCPV
  if p == conv.kPhypDm23sqBar:   return conv.kPhypDm23sq
  if p == conv.kPhypDm12sqBar:   return conv.kPhypDm12sq
  return p



  # Check if a root node already exists. If not, create one.
def make_root_node(list_name):
  root_node = _xmleng.NewChild(0, 0, _default_root_node_name)
  _xmleng.NewAttr(root_node, 0, "name", list_name)
  _xmleng.DocSetRootElement(_xmldoc, root_node)
  print "Creating a root node with attribute \'name\' =", list_name
  return root_node


def add_param(root_node, fields):
  # Check whether a parameter with this simple name already exists in the file
  #check_param_exists(root_node, fields.name_simple)

  # This structure for a parameter is according to Parameter.h
  param_node        = add_node(root_node , "param"     , ""                , False, True , 0, 0)
  name_node         = add_node(param_node, "name"      , ""                , True , True , 0, 0)
  simple_name_node  = add_node(name_node , "simple"    , fields.name_simple, False, False, 0, 0)
  type_node         = add_node(param_node, "type"      , fields.type       , True , False, 0, 0)
  limits_node       = add_node(param_node, "limits"    , fields.limits     , True , False, 0, 0)
  rmode_node        = add_node(param_node, "range_mode", fields.range_mode , False, False, 0, 0)
  range_node        = add_node(param_node, "range"     , fields.range      , True , False, 0, 0)
  smode_node        = add_node(param_node, "step_mode" , fields.step_mode  , False, False, 0, 0)
  step_node         = add_node(param_node, "step"      , fields.step       , True , False, 0, 0)
  init_node         = add_node(param_node, "init"      , fields.init       , False, False, 0, 0)
  error_node        = add_node(param_node, "error"     , fields.error      , False, False, 0, 0)
  _xmleng.AddRawLine(root_node, "\n\n")     # Additional blank lines after each parameter, for readability


def check_param_exists(root_node, simple_name):
  all_param_nodes = util.FindAllNodes(_xmleng, root_node)
  for param_node in all_param_nodes:
    if util.NodeExists(_xmleng, param_node, "name/simple"):
      param_name = util.XML2String(_xmleng, param_node, "name/simple")
      param_name_check = util.TrimSpaces(param_name)
      if param_name_check == simple_name:
        print "FATAL: A parameter with simple name", simple_name, "already exists. Simple names must be unique. Exiting"
        util.Die(-1)


# Improve readability and make it easier to manually insert node content (changes e.g. <node\> to <node>  <\node>)
def add_node(parent_node, node_name, node_content_in, blank_line_after = False, should_always_be_empty = False, maxlen_node = 0, maxlen_content = 0):
  node_content_print = ""
  if not should_always_be_empty:
    if maxlen_node == 0 or maxlen_content == 0:
      node_content_print = "  " + node_content_in + "  "
    else:
      node_content_print = " "*(maxlen_node-len(node_name)) + node_content_in + " "*(2+maxlen_content-len(node_content_in))
  new_node = _xmleng.NewChild(parent_node, 0, node_name, node_content_print)
  if blank_line_after:
    _xmleng.AddRawLine(parent_node, "")  # spacing between groups of nodes
  return new_node


if __name__=="__main__":

  import optparse
  parser = optparse.OptionParser(usage="%prog [options]..",description="Create an SDK parameter XML file with hard-coded T2K-specific parameter information.")
  parser.add_option('-f', '--file'  , dest='filename', default="systematic_params.xml", help="Name of the output parameter config file.")
  parser.add_option("-w", "--overwrite", dest="overwrite", action="store_true", help="If this option is specified, any existing file with the same output name will be deleted and overwritten.")

  o,other = parser.parse_args()
  main(o.filename, o.overwrite)

  if other:
    print "Warning - ignored arguments: ",other
