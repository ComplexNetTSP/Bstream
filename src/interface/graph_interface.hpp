///-------------------------------------------------------------------------------------------------
///
/// @file       graph_interface.hpp
/// @brief      Python wrapper for the Graph class
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       05/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/eigen.h>
#include <iostream>

#include "GraphType.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

void graph_interface(py::module &m)
{

    ///**************************************************************************************************
    ///
    ///  Edge
    ///
    ///**************************************************************************************************

    py::class_<bs::Graph::edge_t> edge(m, "edge_t");
    edge.doc() =
            R"pbdoc(
Base class for Graph's edge.
)pbdoc";

    edge.def(py::init<>());

    edge.def(py::self == py::self);
    edge.def(py::self != py::self);

    edge.def("__repr__",
             [](bs::Graph::edge_t &e) {
                 std::ostringstream stream;
                 stream << "<class edge_t: " << e << ">";
                 return stream.str();
             });

    ///**************************************************************************************************
    ///
    ///  Graph
    ///
    ///**************************************************************************************************

    py::class_<bs::Graph> graph(m, "Graph");

    graph.doc() =
            R"pbdoc(
Base class for undirected graphs.
)pbdoc";

    graph.def(py::init<>());
    graph.def(py::init<int>(), py::arg("num_vertex"));
    graph.def(py::init<const bs::Graph &>(), py::arg("Graph"),
              R"pbdoc(
Constructors of the Graph class

Args:
    num_vertices (int): Construct a graph with `num_vertex` initial node.
    Graph: Graph to copy from.
)pbdoc"
    );

    graph.def("is_directed", &bs::Graph::is_directed, R"pbdoc(
Test if the graph is directed or not 

Returns:
    bool: True if the graph is direct and False else
)pbdoc"
    );

    graph.def("add_vertex", &bs::Graph::add_vertex, py::arg("label") = "",
              R"pbdoc(
Add a single node with a name attribute.

Args:
    label (str, optional): node label, (default: None)

Returns: 
    int: vertex id

Examples:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> G.add_vertex('A')
    >>> G.add_vertex('B')
    >>> G.num_vertices()
    2
    >>> v2 = G.add_vertex() # automaticaly label the vertex v2 as '2'
    >>> v3 = G.add_vertex() # automaticaly label the vertex v3 as '3'
    >>> G.num_vertices()
    4
)pbdoc"
    );

    graph.def("label", &bs::Graph::label,
              py::arg("v"),
              R"pbdoc(
Return the label of the vertex v.

Args:
    v (int): vertex id

Returns:
    str: vertex's label
)pbdoc"
    );

    graph.def("vertex", &bs::Graph::vertex,
              py::arg("label"),
              R"pbdoc(
Return the vertex id of correponding the vertex label.

Args:
    label (str): vertex's label

Returns:
    int: vertex's id
)pbdoc"
    );

    graph.def("labels", &bs::Graph::labels,
              R"pbdoc(
Return the list of vertex labels

Returns:
    list: vertex's label
)pbdoc");

    graph.def("add_edge",
              py::overload_cast<const bs::Graph::vertex_t &, const bs::Graph::vertex_t &>(&bs::Graph::add_edge),
              py::arg("source"), py::arg("target"));

    graph.def("add_edge", py::overload_cast<const std::string &, const std::string &>(&bs::Graph::add_edge),
              py::arg("source"), py::arg("target"),
              R"pbdoc(
Add an edge between s and t.

Args:
    source (int, str): source vertex, could be a vertex id or a vertex label
    target (int, str): target vertex, could be a vertex id or a vertex label

Returns:
    edge_t: edge

Examples:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> G.add_vertex('A')
    >>> G.add_vertex('B')
    >>> G.add_adge('A', 'B')
    >>> G.num_edges()
    1
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> s = G.add_vertex()
    >>> t = G.add_vertex()
    >>> G.add_adge(s, t)
    >>> G.num_edges()
    1
)pbdoc"
    );

    graph.def("num_vertices", &bs::Graph::num_vertices,
              R"pbdoc(
Return the number of vertices in the graph.

Returns:
    float: number of vertices in the graph

Example:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> G.add_vertex('A')
    >>> G.add_vertex('B')
    >>> G.add_adge('A', 'B')
    >>> G.num_vertices()
    2
)pbdoc"
    );

    graph.def("num_edges", &bs::Graph::num_edges,
              R"pbdoc(
Return the number of edges in the graph.

Returns:
    float: number of edges in the graph

Example:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> G.add_vertex('A')
    >>> G.add_vertex('B')
    >>> G.add_adge('A', 'B')
    >>> G.num_edges()
    1
)pbdoc"
    );

    graph.def("print_edges", &bs::Graph::print_edges,
              R"pbdoc(
Print the edge list of the graph G
)pbdoc");

    graph.def("has_edge",
              py::overload_cast<const bs::Graph::vertex_t &, const bs::Graph::vertex_t &>(&bs::Graph::has_edge),
              py::arg("s"), py::arg("t"));

    graph.def("has_edge", py::overload_cast<const std::string &, const std::string &>(&bs::Graph::has_edge),
              py::arg("s"), py::arg("t"),
              R"pbdoc(
Test if there is an edge (s,t)

Args:
    s (str, int): source vertex, could be a vertex label or a vertex id.
    t (str, int): target vertex, could be a vertex label or a vertex id.

Returns:
    bool: True if the edge exist else False

Examples:
    >>> G = pb.Graph()
    >>> G.add_edge("A", "B")
    >>> G.has_edge("A", "B")
    True
    >>> v2 = G.add_vertex()
    >>> v3 = G.add_vertex()
    >>> G.has_edge(v2, v3)
    True
)pbdoc"
    );

    graph.def("degree", py::overload_cast<const std::string &>(&bs::Graph::degree),
              py::arg("v"));

    graph.def("degree", py::overload_cast<const bs::Graph::vertex_t &>(&bs::Graph::degree),
              py::arg("v"),
              R"pbdoc(
Return the degree of a vertex or nodes.

The node degree is the number of edges adjacent to that node.

Args:
    v (str, int): vertex id or a vertex label

Returns:
    float: number of edges adjacent to that vertex v
)pbdoc"
    );

    graph.def("adjacency", &bs::Graph::adjacency,
              R"pbdoc(
Return the adjacency matrix of the Graph

Returns:
    ndarray: adjaceny matrix of the graph
)pbdoc"
    );

    graph.def("read_csv", &bs::Graph::read_csv,
              py::arg("path"),
              py::arg("delimiter") = ',',
              R"pbdoc(
Read the edge file
        
Args:
    path (str): file path of the csv file
    delimiter (str): field delimiter

Example:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> G.read_csv("edges.csv")
    >>> G.num_edges()
    ... 
)pbdoc");

    graph.def("vertices", [](bs::Graph &g) {
                  auto it = g.vertices();
                  return py::make_iterator(it.first, it.second);
              }, py::keep_alive<0, 1>(),
              R"pbdoc(
Vertices iterator

Returns: 
    iterator: return a list of vertex

Example:
    >>> pb.Graph() # DiGraph, Bipartite ..etc
    >>> G.add_edge(
    >>> for e in G.vertices:
        ... G.degree(v)
    1
    2
    ...
)pbdoc"
    );

    graph.def("edges", [](bs::Graph &g) {
                  auto it = g.edges();
                  return py::make_iterator(it.first, it.second);
              }, py::keep_alive<0, 1>(),
              R"pbdoc(
Edges iterator

Returns: 
    iterator: An iterator of edge_t.
)pbdoc"
    );

    graph.def("remove_vertex", py::overload_cast<const std::string &>(&bs::Graph::remove_vertex),
              py::arg("v"),
              R"pbdoc(
Remove vertex v

Args:
    v (str): vertex label of the vertex to be removed
)pbdoc"
    );


    graph.def("clear", &bs::Graph::clear, R"pbdoc(
Remove all the vertices and edges present inside the adjacency list.
)pbdoc");

    graph.def("__repr__", [](bs::Graph &g) {
        std::ostringstream out;
        out << "<class " << g << ">";
        return out.str();
    });

    graph.def("__getitem__", py::overload_cast<const std::string &>(&bs::Graph::operator[]), py::arg("label"));
    graph.def("__getitem__", py::overload_cast<const bs::Graph::vertex_t &>(&bs::Graph::operator[]),
              py::arg("v"),
              R"pbdoc(
Return the label or the vertex id of a given vertex

Args:
    v (int): vertex id
    label (str): vertex label

Examples:
    >>> G = pb.Graph() # DiGraph, Bipartite ..etc
    >>> G.add_edge("A", "B")
    >>> G[0]
    "A"
    >>> G["A"]
    0
)pbdoc");
}