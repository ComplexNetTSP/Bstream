//
// Created by Vincent Gauthier on 16/04/2018.
//

#ifndef BSTREAM_BIPARTITE_INTERFACE_HPP
#define BSTREAM_BIPARTITE_INTERFACE_HPP

#include "GraphType.hpp"

void bipartite_interface(py::module &m)
{
    ///**************************************************************************************************
    ///
    ///  Bipartite
    ///
    ///**************************************************************************************************

    py::class_<bs::Bipartite, bs::Graph> bipartite(m, "Bipartite");
    bipartite.def(py::init<>());
    bipartite.def("add_vertex_w_group", &bs::Bipartite::add_vertex_w_group, py::arg("group"), py::arg("label")="");
    bipartite.def("add_edge", py::overload_cast<const bs::Graph::vertex_t&, const bs::Graph::vertex_t&>(&bs::Bipartite::add_edge));
    bipartite.def("add_edge", py::overload_cast<const std::string&, const std::string&>(&bs::Bipartite::add_edge));
    bipartite.def("group", py::overload_cast<const bs::Graph::vertex_t&>(&bs::Bipartite::group));
    bipartite.def("group", py::overload_cast<const std::string&>(&bs::Bipartite::group));
    bipartite.def("__repr__", [](bs::Graph &g) {
        return "<class Bipartite>";
    });

    ///**************************************************************************************************
    ///
    ///  DiBipartite
    ///
    ///**************************************************************************************************

    py::class_<bs::DiBipartite, bs::DiGraph> dibipartite(m, "DiBipartite");
    dibipartite.def(py::init<>());
    dibipartite.def("add_vertex_w_group", &bs::DiBipartite::add_vertex_w_group, py::arg("group"), py::arg("label")="");
    dibipartite.def("add_edge", py::overload_cast<const bs::DiGraph::vertex_t&, const bs::DiGraph::vertex_t&>(&bs::DiBipartite::add_edge));
    dibipartite.def("add_edge", py::overload_cast<const std::string&, const std::string&>(&bs::DiBipartite::add_edge));
    dibipartite.def("group", py::overload_cast<const bs::DiGraph::vertex_t&>(&bs::DiBipartite::group));
    dibipartite.def("group", py::overload_cast<const std::string&>(&bs::DiBipartite::group));
    dibipartite.def("__repr__", [](bs::Graph &g) {
        return "<class DiBipartite>";
    });
}
#endif //BSTREAM_BIPARTITE_INTERFACE_HPP
