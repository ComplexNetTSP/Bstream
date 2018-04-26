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
    py::class_<bs::Graph::edge_t> edge(m, "edge_u");

    edge.def(py::init<>());
    edge.def(py::self == py::self);
    edge.def(py::self != py::self);
    edge.def("__repr__", [](bs::Graph::edge_t &e){
                std::ostringstream stream;
                stream << "<class Graph::edge_t link: "  << e << ">";
                return stream.str();
    });

    ///**************************************************************************************************
    ///
    ///  Graph
    ///
    ///**************************************************************************************************

    py::class_<bs::Graph> graph(m, "Graph");

    graph.doc() = R"pbdoc(
Base class for undirected graphs.
    )pbdoc";

    graph.def(py::init<>(), R"pbdoc(
Construct an empty graph         
    )pbdoc");
    graph.def(py::init<int>(), py::arg("num_vertex"), R"pbdoc(
construct graph with `num_vertex` initial node
    
Args:
    num_vertices (int): number of vertices
    )pbdoc");
    graph.def(py::init<const bs::Graph &>(), py::arg("Graph"));
    graph.def("is_directed", &bs::Graph::is_directed);
    graph.def("add_vertex", &bs::Graph::add_vertex, py::arg("label")="", R"pbdoc(
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
    )pbdoc");
    graph.def("label", &bs::Graph::label, py::arg("vertex"));
    graph.def("add_edge", py::overload_cast<const bs::Graph::vertex_t&, const bs::Graph::vertex_t&>(&bs::Graph::add_edge),
              py::arg("source"), py::arg("target"), R"pbdoc(
Add an edge between s and t.

Args:
    source (vertex_u): source vertex
    target (vertex_u): target vertex

Returns:
    edge

Example:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> s = G.add_vertex()
    >>> t = G.add_vertex()
    >>> G.add_adge(s, t)
    >>> G.num_edges()
    1
    )pbdoc");
    graph.def("add_edge", py::overload_cast<const std::string&, const std::string&>(&bs::Graph::add_edge), py::arg("source"), py::arg("target"), R"pbdoc(
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
    >>> G.add_adge('A', ''B)
    >>> G.num_edges()
    1
    )pbdoc");
    graph.def("num_vertices", &bs::Graph::num_vertices, R"pbdoc(
    return the number of vertices in the graph.

    Returns:
        float: number of vertices in the graph

    Example:
        >>> G = pb.Graph()  # or DiGraph, etc
        >>> G.add_vertex('A')
        >>> G.add_vertex('B')
        >>> G.add_adge('A', ''B)
        >>> G.num_vertices()
        2
    )pbdoc");
    graph.def("num_edges", &bs::Graph::num_edges, R"pbdoc(
return the number of edges in the graph.

Returns:
    float: number of edges in the graph

Example:
    >>> G = pb.Graph()  # or DiGraph, etc
    >>> G.add_vertex('A')
    >>> G.add_vertex('B')
    >>> G.add_adge('A', ''B)
    >>> G.num_edges()
    1
    )pbdoc");
    graph.def("has_edge", py::overload_cast<const bs::Graph::vertex_t&, const bs::Graph::vertex_t&>(&bs::Graph::has_edge));
    graph.def("has_edge", py::overload_cast<const std::string&, const std::string&>(&bs::Graph::has_edge));
    graph.def("degree", py::overload_cast<const std::string&>(&bs::Graph::degree));
    graph.def("degree", py::overload_cast<const bs::Graph::vertex_t&>(&bs::Graph::degree));
    graph.def("in_degree", py::overload_cast<const std::string&>(&bs::Graph::in_degree));
    graph.def("in_degree", py::overload_cast<const bs::Graph::vertex_t&>(&bs::Graph::in_degree));
    graph.def("out_degree", py::overload_cast<const std::string&>(&bs::Graph::out_degree));
    graph.def("out_degree", py::overload_cast<const bs::Graph::vertex_t&>(&bs::Graph::out_degree));
    graph.def("adjacency", &bs::Graph::adjacency);
    graph.def("read_csv", &bs::Graph::read_csv, py::arg("path"), py::arg("delimiter")=',');

    graph.def("vertices", [](bs::Graph &g){
        auto it = g.vertices();
        return py::make_iterator(it.first, it.second);
    }, py::keep_alive<0, 1>());

    graph.def("edges", [](bs::Graph &g){
        auto it = g.edges();
        return py::make_iterator(it.first, it.second);
    }, py::keep_alive<0, 1>());

    graph.def("__repr__", [](bs::Graph &g) {
        std::ostringstream out;
        out << "<class " << g << ">";
        return out.str();
    });
}