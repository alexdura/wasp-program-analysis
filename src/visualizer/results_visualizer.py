def make_vertex(vertex_name):
    """
    A function that will return the vertex name between quotation marks
    """
    # The result sometimes has the name
    # of the method as a prefix
    if (re.match("[a-zA-Z]+::", vertex_name)):
        # we return the suffix only
        return "\"{0}\"".format(
            vertex_name.split("::")[1])
    else:
        return "\"{0}\"".format(vertex_name)


def make_vertices(dataflow_data):
    """A function that will create vertex labels"""
    text = ""
    for v in dataflow_data:
        text += "\n"
        text += make_vertex(v)

    return text


def make_edges(dataflow_data):
    """ A function that will create the string for edges spec"""
    text = ""
    for (vertex, info) in dataflow_data.items():
        facts = info["Facts"]
        targets = [f[0] for f in facts]
        for target in targets:
            line = "{0} -- {1};".format(
                make_vertex(vertex),
                make_vertex(target))
            text += line + "\n"

    return text


def make_graph(dataflow_data):
    return 'graph DataFlow {{\n{vertices}\n{edges}}}'.format(
        vertices=make_vertices(dataflow_data),
        edges=make_edges(dataflow_data))


import json
import sys
import re # For regular expressions.

if sys.argv[0]:
    filename = sys.argv[0]
else:
    filename = "results.json"

f = open(filename)
json_data = json.load(f)
dataflow_data = [d for d in json_data if d["DataFlow"]][0]["DataFlow"]
with open("results.dot", 'w') as output_file:
    output_text = make_graph(dataflow_data)
    output_file.write(output_text)
