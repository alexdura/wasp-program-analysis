#!/usr/bin/env python
import json
import sys
import re # For regular expressions.
import textwrap

# Utilities declarations
def make_id(vertex_name):
    """
    Extracts the ID from the label of the vertex, to use it.
    """
    match_z = re.search("ID: -1", vertex_name)
    if match_z:
        return "ZERO"

    # The function name is what comes
    # Before the '::' separator
    match = re.search("ID: ([0-9]+|-1)", vertex_name)
    if match:
        return "ID_{instr}".format(instr=match.group(1))



def make_vertex(vertex_name):
    """
    A function that will return the vertex name between quotation marks
    """
    return make_id(vertex_name) + " " + "[label=\"{0}\"]".format(vertex_name)


def make_vertices(dataflow_data):
    """A function that will create vertex labels"""
    text = ""
    for v in dataflow_data:
        text += "\n"
        text += make_vertex(v)

    return text


def make_edge(vertex, target):
    """
    A function creating a spec for one edge
    """
    line = "{1} -> {0};".format(
        make_id(vertex),
        make_id(target))
    return line
    
def make_edges(dataflow_data):
    """ A function that will create the string for edges spec"""
    text = ""
    for (vertex, info) in dataflow_data.items():
        facts = info["Facts"]
        targets = [f[0] for f in facts]
        for target in targets:
            text += make_edge(vertex, target) + "\n"
    return text


def extract_function(instruction_label):
    """
    Returns the name of the function the instruction
    is into"""
    return instruction_label.split("::")[0]


def group_by_function(dataflow_data):
    """
    A function that takes dataflow_data
    and returns instructions grouped by
    function name"""
    groups = {}
    for inst in dataflow_data:
        # We get the key
        function_label = extract_function(inst)
	targets = [f[0] for f in dataflow_data[inst]['Facts']]
	(source, targets) = (inst, targets)
        if function_label in groups:
            groups[function_label].append((source, targets)) 
        else:
            groups[function_label] = []
            groups[function_label].append((source, targets)) 
    return groups


def make_subgraphs(dataflow_data):
    """
    A function taking dataflow data and
    returning text for dot subgraphs for all functions
    """
    groups = group_by_function(dataflow_data)
    subgraphs_text = ""
    for (cluster_name, cluster_spec) in groups.items():
        edges_defs = [make_edge(s, t) for (s, ts) in cluster_spec
                      for t in ts]
		      
        # We put the vertices that are sources in this
        # Subgraph too!
        vertices = [make_vertex(s) for (s, ts) in cluster_spec]
        vertices_text = ""
        for s in vertices:
            vertices_text += "    " + s + "\n"
        
        edges_text = ""
        for e in edges_defs:
            edges_text += "    " + e + "\n"

            

        subgraphs_text += """
subgraph cluster_{cluster_name} {{
    style=filled
    color=lightgray
    label=\"{cluster_name}\"
{vertices_text}
}};\n""".format(cluster_name=cluster_name,
                vertices_text=vertices_text,
                   edges_text=edges_text)
	 
    return subgraphs_text
def make_graph(dataflow_data):
    return 'digraph DataFlow {{\n{subgraphs}\n{edges}}}'.format(
        subgraphs=make_subgraphs(dataflow_data),
        edges=make_edges(dataflow_data))


if __name__ == "__main__":
    if len(sys.argv) != 1:
        filename = sys.argv[1]
    else:
        filename = "results.json"
    
    print("Loading from '{0}'...'".format(filename))
    
    f = open(filename)
    json_data = json.load(f)
    dataflow_data = [d for d in json_data if d["DataFlow"]][0]["DataFlow"]
    with open("results.dot", 'w') as output_file:
        output_text = make_graph(dataflow_data)
        output_file.write(output_text)
