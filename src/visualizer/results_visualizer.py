#!/usr/bin/env python
import json
import sys
import re # For regular expressions.

# Utilities declarations
def make_id(vertex_name):
    """
    Extracts the ID from the label of the vertex, to use it.
    """
    match_z = re.search("ID: -1", vertex_name)
    if match_z:
        return "ZERO"

    match = re.search("ID: ([0-9]+|-1)", vertex_name)
    if match:
        return "ID_" + match.group(1)
    

def make_vertex(vertex_name):
    """
    A function that will return the vertex name between quotation marks
    """
    # The result sometimes has the name
    # of the method as a prefix
    text = ""
    if (re.match("[a-zA-Z]+::", vertex_name)):
        # we return the suffix only
        text = vertex_name.split("::")[1]
    else:
        text = vertex_name

    return text[0:30]


def make_vertices(dataflow_data):
    """A function that will create vertex labels"""
    text = ""
    for v in dataflow_data:
        text += "\n"
        text += make_id(v) + " " + "[label=\"{0}\"]".format(make_vertex(v))

    return text


def make_edges(dataflow_data):
    """ A function that will create the string for edges spec"""
    text = ""
    for (vertex, info) in dataflow_data.items():
        facts = info["Facts"]
        targets = [f[0] for f in facts]
        for target in targets:
            line = "{0} -- {1};".format(
                make_id(vertex),
                make_id(target))
            text += line + "\n"

    return text


def make_graph(dataflow_data):
    return 'graph DataFlow {{\n{vertices}\n{edges}}}'.format(
        vertices=make_vertices(dataflow_data),
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
