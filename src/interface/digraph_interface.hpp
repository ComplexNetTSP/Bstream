

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/eigen.h>
#include <iostream>

#include "GraphType.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

void digraph_interface(py::module &m)
{
    py::class_<bs::DiGraph::edge_t> diedge(m, "edge_d");

    diedge.def(py::init<>());
    diedge.def(py::self == py::self);
    diedge.def(py::self != py::self);
    diedge.def("__repr__", [](bs::Graph::edge_t &e){
                std::ostringstream stream;
                stream << "<class Digraph::edge_t link: "  << e << ">";
                return stream.str();
    });
    
    ///**************************************************************************************************
    ///
    ///  DiGraph
    ///
    ///**************************************************************************************************

    py::class_<bs::DiGraph> digraph(m, "DiGraph");

    digraph.doc() = R"pbdoc(
    Base class for directed graphs.
    )pbdoc";

    digraph.def(py::init<>());
    digraph.def(py::init<int>());
    digraph.def(py::init<const bs::DiGraph &>());
    digraph.def("is_directed", &bs::DiGraph::is_directed);
    digraph.def("add_vertex", &bs::DiGraph::add_vertex, py::arg("name")="");
    digraph.def("label", &bs::DiGraph::label);
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
    digraph.def("adjacency", &bs::DiGraph::adjacency);
    digraph.def("read_csv", &bs::DiGraph::read_csv,py::arg("path"), py::arg("delimiter")=',');

    digraph.def("vertices", [](bs::DiGraph &g){
        auto it = g.vertices();
        return py::make_iterator(it.first, it.second);
    }, py::keep_alive<0, 1>());

    digraph.def("edges", [](bs::DiGraph &g){
        auto it = g.edges();
        return py::make_iterator(it.first, it.second);
    }, py::keep_alive<0, 1>());

    digraph.def("__repr__", [](bs::DiGraph &g) {
        std::ostringstream out;
        out << "<class " << g << ">";
        return out.str();
    });
}