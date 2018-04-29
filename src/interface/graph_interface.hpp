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
Base class for edge of graph.
)pbdoc";

    edge.def(py::init<>());

    edge.def(py::self == py::self);
    edge.def(py::self != py::self);

    edge.def("__repr__",
             [](bs::Graph::edge_t &e) {
                 std::ostringstream stream;
                 stream << "<class Graph::edge_t link: " << e << ">";
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

    graph.def(py::init<>(),
              R"pbdoc(
Construct an empty graph
)pbdoc"
    );

    graph.def(py::init<int>(), py::arg("num_vertex"),
              R"pbdoc(
Construct a graph with `num_vertex` initial node

Args:
    num_vertices (int): number of vertices
)pbdoc"
    );

    graph.def(py::init<const bs::Graph &>(), py::arg("Graph"),
              R"pbdoc(
Copy constructor

Args:
    Graph: Graph to copy from
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

Example:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> G.add_vertex('A')
    >>> G.add_vertex('B')
    >>> G.num_vertices()
    2
)pbdoc"
    );

    graph.def("label", &bs::Graph::label,
              py::arg("v"),
              R"pbdoc(
Return the label of the vertex v.

Args:
    v (vertex): vertex

Returns:
    str: vertex's label
)pbdoc"
    );

    graph.def("add_edge",
              py::overload_cast<const bs::Graph::vertex_t &, const bs::Graph::vertex_t &>(&bs::Graph::add_edge),
              py::arg("source"), py::arg("target"),
              R"pbdoc(
Add an edge between s and t.
    
Args:
    source (int): source vertex
    target (int): target vertex
    
Returns:
    edge_t
    
Example:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> s = G.add_vertex()
    >>> t = G.add_vertex()
    >>> G.add_adge(s, t)
    >>> G.num_edges()
    1
)pbdoc"
    );

    graph.def("add_edge", py::overload_cast<const std::string &, const std::string &>(&bs::Graph::add_edge),
              py::arg("source"), py::arg("target"),
              R"pbdoc(
Add an edge between s and t.

Args:
    source (str): source vertex
    target (str): target vertex

Returns:
    edge_u

Example:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> G.add_vertex('A')
    >>> G.add_vertex('B')
    >>> G.add_adge('A', 'B')
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

    graph.def("has_edge",
              py::overload_cast<const bs::Graph::vertex_t &, const bs::Graph::vertex_t &>(&bs::Graph::has_edge),
              py::arg("s"), py::arg("t"),
              R"pbdoc(
Test if there is an edge (s,t)

Args:
    s (vertex_t): source vertex
    t (vertex_t): target vertex

Returns:
    bool: True if the edge exist else False
)pbdoc"
    );

    graph.def("has_edge", py::overload_cast<const std::string &, const std::string &>(&bs::Graph::has_edge),
              py::arg("s"), py::arg("t"),
              R"pbdoc(
Test if there is an edge (s,t)

Args:
    s (str): source vertex
    t (str): target vertex

Returns:
    bool: True if the edge exist else False
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
    v (str, vertex): vertex id or a vertex label

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
    >>> pb.Graph()
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
    v (str): vertex label of teh vertex to be removed
)pbdoc"
    );

    graph.def("__repr__", [](bs::Graph &g) {
        std::ostringstream out;
        out << "<class " << g << ">";
        return out.str();
    });
}