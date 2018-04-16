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
#include <iostream>

#include "GraphType.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

void graph_interface(py::module &m)
{
    py::class_<bs::Graph::edge_t> edge(m, "edge_undirected");

    edge.def(py::init<>());
    edge.def(py::self == py::self);
    edge.def(py::self != py::self);
    edge.def("__repr__", [](bs::Graph::edge_t &e){
                std::ostringstream stream;
                stream << "<class Graph::edge_t link: "  << e << ">";
                return stream.str();
    });

    py::class_<bs::DiGraph::edge_t> diedge(m, "edge_directed");

    diedge.def(py::init<>());
    diedge.def(py::self == py::self);
    diedge.def(py::self != py::self);
    diedge.def("__repr__", [](bs::Graph::edge_t &e){
                std::ostringstream stream;
                stream << "<class Digraph::edge_t link: "  << e << ">";
                return stream.str();
    });

    py::class_<bs::Graph> graph(m, "Graph");

    graph.def(py::init<>());
    graph.def(py::init<int>());
    graph.def(py::init<const bs::Graph &>());
    graph.def("is_directed", &bs::Graph::is_directed);
    graph.def("add_vertex", &bs::Graph::add_vertex, py::arg("name")="");
    graph.def("vertex_label", &bs::Graph::vertex_label);
    graph.def("add_edge", py::overload_cast<const bs::Graph::vertex_t&, const bs::Graph::vertex_t&>(&bs::Graph::add_edge));
    graph.def("add_edge", py::overload_cast<const std::string&, const std::string&>(&bs::Graph::add_edge));
    graph.def("num_vertices", &bs::Graph::num_vertices);
    graph.def("num_edges", &bs::Graph::num_edges);
    graph.def("has_edge", py::overload_cast<const bs::Graph::vertex_t&, const bs::Graph::vertex_t&>(&bs::Graph::has_edge));
    graph.def("has_edge", py::overload_cast<const std::string&, const std::string&>(&bs::Graph::has_edge));
    graph.def("degree", py::overload_cast<const std::string&>(&bs::Graph::degree));
    graph.def("degree", py::overload_cast<const bs::Graph::vertex_t&>(&bs::Graph::degree));
    graph.def("in_degree", py::overload_cast<const std::string&>(&bs::Graph::in_degree));
    graph.def("in_degree", py::overload_cast<const bs::Graph::vertex_t&>(&bs::Graph::in_degree));
    graph.def("out_degree", py::overload_cast<const std::string&>(&bs::Graph::out_degree));
    graph.def("out_degree", py::overload_cast<const bs::Graph::vertex_t&>(&bs::Graph::out_degree));

    graph.def("vertices", [](bs::Graph &g){
        auto it = g.vertices();
        return py::make_iterator(it.first, it.second);
    }, py::keep_alive<0, 1>());

    graph.def("__repr__", [](bs::Graph &g) {
        return "<class Graph>";
    });

    py::class_<bs::DiGraph> digraph(m, "DiGraph");

    digraph.def(py::init<>());
    digraph.def(py::init<int>());
    digraph.def(py::init<const bs::DiGraph &>());
    digraph.def("is_directed", &bs::DiGraph::is_directed);
    digraph.def("add_vertex", &bs::DiGraph::add_vertex, py::arg("name")="");
    digraph.def("add_edge", py::overload_cast<const bs::DiGraph::vertex_t&, const bs::DiGraph::vertex_t&>(&bs::DiGraph::add_edge));
    digraph.def("add_edge", py::overload_cast<const std::string&, const std::string&>(&bs::DiGraph::add_edge));
    digraph.def("num_vertices", &bs::DiGraph::num_vertices);
    digraph.def("num_edges", &bs::DiGraph::num_edges);
    digraph.def("has_edge", py::overload_cast<const bs::DiGraph::vertex_t&, const bs::DiGraph::vertex_t&>(&bs::DiGraph::has_edge));
    digraph.def("has_edge", py::overload_cast<const std::string&, const std::string&>(&bs::DiGraph::has_edge));
    digraph.def("degree", py::overload_cast<const std::string&>(&bs::DiGraph::degree));
    digraph.def("degree", py::overload_cast<const bs::DiGraph::vertex_t&>(&bs::DiGraph::degree));
    digraph.def("in_degree", py::overload_cast<const std::string&>(&bs::DiGraph::in_degree));
    digraph.def("in_degree", py::overload_cast<const bs::DiGraph::vertex_t&>(&bs::DiGraph::in_degree));
    digraph.def("out_degree", py::overload_cast<const std::string&>(&bs::DiGraph::out_degree));
    digraph.def("out_degree", py::overload_cast<const bs::DiGraph::vertex_t&>(&bs::DiGraph::out_degree));
    digraph.def("vertices", [](bs::DiGraph &g){
        auto it = g.vertices();
        return py::make_iterator(it.first, it.second);
    }, py::keep_alive<0, 1>());
    digraph.def("__repr__", [](bs::DiGraph &g) {
        return "<class DiGraph>";
    });

}