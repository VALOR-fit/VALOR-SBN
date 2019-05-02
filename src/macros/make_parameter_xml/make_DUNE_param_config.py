#!/usr/bin/python

import ROOT
import os
from collections import namedtuple

ROOT.PyConfig.IgnoreCommandLineOptions = True

try:
    ROOT.valor
except:
    ROOT.gROOT.ProcessLine(".x $VALOR_DUNE/root/valor_dune.C");

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
       'name_rootex',
       'name_tex',
       'kine_ranges',
       'type',
       'category',
       'apply_detector',
       'apply_beam',
       'apply_selection',
       'apply_flav',
       'apply_osc',
       'apply_reac',
       'apply_target',
       'limits'
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
    root_node = make_root_node("DUNE")

    # For printing debug info
    params_without_cats = []
    params_without_kvs  = []

    # Read the attributes of each DUNE systematic parameter and write to the XML file
    for ip in range(0, conv.kNFitParams):
        p = util.GetFitParam(ip)
        # Skip osc params
        if util.IsOscParam(p):
            continue

        # Get the overall apply mask for this param
        mask_all = util.GetApplyMask(ip)

        # Set all of the possible XML fields
        fields = _param_fields(
            name_simple     = util.ParamAsString(p),
            name_rootex     = get_tex_name(p, True),
            name_tex        = get_tex_name(p, False),
            kine_ranges     = {},
            type            = get_type(p),
            category        = [],
            apply_detector  = util.DetectorMaskAsString(mask_all.detector),
            apply_beam      = util.BeamMaskAsString    (mask_all.beam),
            apply_selection = util.SelecMaskAsString   (mask_all.selec),
            apply_flav      = util.FlavMaskAsString    (mask_all.flav),
            apply_osc       = "all",
            apply_reac      = util.ReacTypeMaskAsString(mask_all.reactype),
            apply_target    = util.NuclearTargetMaskAsString(mask_all.target),
            limits          = get_limits(p)
        )
        auto_set_kv  = set_kine_range(ip, fields)
        auto_set_cat = set_category(p, fields)
        print "For param", util.ParamAsString(p), "the following fields have been set:\n", fields

        # Debug info
        if len(fields.category) == 0 or auto_set_cat:
            params_without_cats.append(fields.name_simple)
        if len(fields.kine_ranges) == 0 or auto_set_kv:
            params_without_kvs.append(fields.name_simple)

        # Write all parameter fields to the output XML file
        add_param(root_node, fields)

        del fields
        print "\n\n"

    _xmleng.SaveDoc(_xmldoc, filename)
    _xmleng.FreeDoc(_xmldoc)

    # Print debug info
    if len(params_without_cats) != 0:
        print "WARNING: The following params have no categories set or were automatically assumed:\n", params_without_cats

    if len(params_without_kvs) != 0:
        print "WARNING: The following params have no kine var ranges set or were automatically assumed:\n", params_without_kvs


    print "Successfully wrote the parameter file", filename
    print "Done!"
    return


def get_tex_name(p, is_rootex):
    name = util.ParamAsStringTeX(p, is_rootex)
    if name == "--":
        return ""   # Leave blank so that Parameter can assign its default
    else:
        return name


def get_type(p):
    if util.ParamHasSplines(p):
        return "response"
    else:
        return "normalisation"


def get_limits(p):
    lims = valor.PhysicalParameterLimits.Instance()
    lims.SetDefaults()
    min = lims.MinValue(p)
    max = lims.MaxValue(p)
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


# Get kinematic ranges of parameter
def set_kine_range(ip, fields):
    auto_set = False
    has_reco_depenence = util.ParamHasRecoDependence(ip)
    if has_reco_depenence:
        range_erec = util.ParamErecoRange(ip)
        range_yrec = util.ParamYrecoRange(ip)
        fields.kine_ranges["Ereco"] = str(range_erec[0]) + ", " + str(range_erec[1])
        fields.kine_ranges["yreco"] = str(range_yrec[0]) + ", " + str(range_yrec[1])

    has_true_depenence = util.ParamHasTrueDependence(ip)
    if has_true_depenence:
        range_etrue = util.ParamEtrueRange(ip)
        range_qsq   = util.ParamQ2trueRange(ip)
        fields.kine_ranges["Etrue"]  = str(range_etrue[0]) + ", " + str(range_etrue[1])
        fields.kine_ranges["Q2true"] = str(range_qsq[0])   + ", " + str(range_qsq[1])

    # Some of the DUNE params have no kinevar ranges set, so I'll just assume the full Etrue and Q2true ranges
    # TODO: Add the misisng params to the arrays in the FitParamArray files
    if len(fields.kine_ranges) == 0:
        fields.kine_ranges["Etrue"]  = str(0.0) + ", " + str(conv.kEtrueMax)
        fields.kine_ranges["Q2true"] = str(0.0) + ", " + str(conv.kQ2trueMax)
        auto_set = True

    return auto_set


def set_category(p, fields):
    auto_set = False
    if util.IsNuFluxRelated(p):
        fields.category.append("flux")
    if util.IsNuIntRelated(p):
        fields.category.append("int")
    if util.IsNuDetRelated(p):
        fields.category.append("det")
    if util.IsFSI(p):
        fields.category.append("fsi")
    if util.IsNDFluxRelated(p) or util.IsNuNDDetRelated(p):
        fields.category.append("nd")
    if util.IsFDFluxRelated(p) or util.IsNuFDDetRelated(p):
        fields.category.append("fd")

    # Some DUNE params are missing from the above functions and don't have a category set,
    # so assume categories based on the names
    # TODO: Add the misisng params to the above functions
    if len(fields.category) == 0:
        if fields.name_simple in ['f_eff_fd_nuelike_cclow', 'f_eff_numucc0pi1trk',
                                  'f_eff_numucc0pi2trk', 'f_eff_numuccwsgn']:
            fields.category.append("det")
            auto_set = True
        if fields.name_simple in ['f_eff_numucc1pic', 'f_eff_numucc1pi0', 'f_eff_numucc1pic1piz',
                                  'f_eff_numuccoth', 'f_eff_nuecc', 'f_eff_nc']:
            fields.category.append("int")
            auto_set = True
    return auto_set


    # Check if a root node already exists. If not, create one.
def make_root_node(list_name):
    root_node = _xmleng.NewChild(0, 0, _default_root_node_name)
    _xmleng.NewAttr(root_node, 0, "name", list_name)
    _xmleng.DocSetRootElement(_xmldoc, root_node)
    print "Creating a root node with attribute \'name\' =", list_name
    return root_node


def add_param(root_node, fields):
    # Check whether a parameter with this simple name already exists in the file
    check_param_exists(root_node, fields.name_simple)

    # Get max text widths for each group (makes visually reading the file easier)
    len_names_node     = len("<simple>")
    len_names_content  = max(len(fields.name_simple), len(fields.name_rootex), len(fields.name_tex))
    len_kv_node        = 0
    len_kv_content     = 0
    for kv in fields.kine_ranges:
        len_kv_node    = max(len_kv_node, len(kv)+2)
        len_kv_content = max(len_kv_content, len(fields.kine_ranges[kv]))
    len_cat_node       = len("<category>")
    len_cat_content    = 0
    if len(fields.category) > 0:
        for category in fields.category:
            len_cat_content = max(len_cat_content, len(category))
    len_apply_node     = len("<selection>")
    len_apply_content  = max(len(fields.apply_detector), len(fields.apply_beam), len(fields.apply_selection),
                             len(fields.apply_reac), len(fields.apply_flav), len(fields.apply_osc), len(fields.apply_target))


    # This structure for a parameter is according to Parameter.h
    param_node        = add_node(root_node , "param"         , ""                     , False, True , 0,              0                )
    name_node         = add_node(param_node, "name"          , ""                     , True , True , 0,              0                )
    simple_name_node  = add_node(name_node , "simple"        , fields.name_simple     , False, False, len_names_node, len_names_content)
    rootex_name_node  = add_node(name_node , "rootex"        , fields.name_rootex     , False, False, len_names_node, len_names_content)
    tex_name_node     = add_node(name_node , "tex"           , fields.name_tex        , False, False, len_names_node, len_names_content)
    range_node        = add_node(param_node, "apply_to_range", ""                     , True , True , 0,              0                )
    for kv in fields.kine_ranges:
        kine_node     = add_node(range_node, kv              , fields.kine_ranges[kv] , False, False, len_kv_node,    len_kv_content   )
    type_node         = add_node(param_node, "type"          , fields.type            , True , False, 0,              0                )
    cats_node         = add_node(param_node, "categories"    , ""                     , True , True , 0,              0                )
    if len(fields.category) > 0:
        for category in fields.category:
            cat_node  = add_node(cats_node , "category"      , category               , False, False, len_cat_node,   len_cat_content)
    else:
        cat_node      = add_node(cats_node , "category"      , ""                     , False, False, 0,              0                )
    apply_node        = add_node(param_node, "apply_to"      , ""                     , True , True , 0,              0                )
    apply_det_node    = add_node(apply_node, "detector"      , fields.apply_detector  , False, False, len_apply_node, len_apply_content)
    apply_beam_node   = add_node(apply_node, "beam"          , fields.apply_beam      , False, False, len_apply_node, len_apply_content)
    apply_selec_node  = add_node(apply_node, "selection"     , fields.apply_selection , False, False, len_apply_node, len_apply_content)
    apply_reac_node   = add_node(apply_node, "reac_type"     , fields.apply_reac      , False, False, len_apply_node, len_apply_content)
    apply_flav_node   = add_node(apply_node, "flav"          , fields.apply_flav      , False, False, len_apply_node, len_apply_content)
    apply_flav_node   = add_node(apply_node, "osc"           , fields.apply_osc       , False, False, len_apply_node, len_apply_content)
    apply_target_node = add_node(apply_node, "target"        , fields.apply_target    , False, False, len_apply_node, len_apply_content)
    limits_node       = add_node(param_node, "limits"        , fields.limits          , False, False, 0,              0                )
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
