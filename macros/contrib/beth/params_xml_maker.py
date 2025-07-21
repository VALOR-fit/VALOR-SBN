import xml.etree.ElementTree as ET

def create_param_element(simple_name):
    long_name = simple_name.replace('_', ' ')
    rootex_tex = f"f_{{{simple_name}}}"

    param = ET.Element("param")

    # Name block
    name = ET.SubElement(param, "name")
    ET.SubElement(name, "simple").text = f"  {simple_name} "
    ET.SubElement(name, "long").text = f"    {long_name} "
    ET.SubElement(name, "rootex").text = f"  {rootex_tex} "
    ET.SubElement(name, "tex").text = f"     {rootex_tex} "

    # Apply to range
    apply_to_range = ET.SubElement(param, "apply_to_range")
    ET.SubElement(apply_to_range, "Etrue").text = " 0, 10. "
    ET.SubElement(apply_to_range, "Ereco").text = " 0, 10. "

    # Type
    ET.SubElement(param, "type").text = "  response  "

    # Categories
    categories = ET.SubElement(param, "categories")
    ET.SubElement(categories, "category").text = " flux "
    ET.SubElement(categories, "category").text = " flux_uncorr "

    # Apply to
    apply_to = ET.SubElement(param, "apply_to")
    ET.SubElement(apply_to, "detector").text = "    allsbn    "
    ET.SubElement(apply_to, "beam").text = "        fhc       "
    ET.SubElement(apply_to, "selection").text = "   all       "
    ET.SubElement(apply_to, "reac_type").text = "   all       "
    ET.SubElement(apply_to, "flav_init").text = "   all       "
    ET.SubElement(apply_to, "flav_final").text = "  all       "
    ET.SubElement(apply_to, "target").text = "      all       "

    # Limits, update, range
    ET.SubElement(param, "limits").text = "  -inf, inf  "
    ET.SubElement(param, "update_from_cov_matrix").text = " true  "
    ET.SubElement(param, "range_mode").text = "             sigma "
    ET.SubElement(param, "range").text = "                  -5,5  "

    return param

def generate_xml_from_out(file_path, output_xml_path):
    with open(file_path, 'r') as f:
        lines = [line.strip() for line in f if line.strip()]

    root = ET.Element("param_list", name="v9_response_parameters")

    comment = ET.Comment("=" * 91)
    root.append(comment)

    for simple_name in lines:
        param_element = create_param_element(simple_name)
        root.append(param_element)

    tree = ET.ElementTree(root)
    ET.indent(tree, space="  ", level=0)  # Python 3.9+
    tree.write(output_xml_path, encoding='utf-8', xml_declaration=True)

if __name__ == "__main__":
    generate_xml_from_out("param_list.out", "v9_params.xml")
