//
// Created by Vincent Gauthier on 16/04/2018.
//

#ifndef BSTREAM_BIPARTITE_INTERFACE_HPP
#define BSTREAM_BIPARTITE_INTERFACE_HPP

#include <boost/graph/detail/edge.hpp>

#include "GraphType.hpp"
#include "bipartite.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

void bipartite_interface(py::module &m)
{
    ///**************************************************************************************************
    ///
    ///  Functions
    ///
    ///**************************************************************************************************
    m.def("projected_graph", bs::projected_graph<boost::undirectedS>, py::arg("Graph"), py::arg("projection_node"));
    m.def("projected_graph", bs::projected_graph<boost::bidirectionalS>, py::arg("DiGraph"), py::arg("projection_node"),
          R"pbdoc(
    Returns the projection of B onto one of its node sets.

    Returns the graph G that is the projection of the bipartite graph B
    onto the specified nodes. They retain their attributes and are connected
    in G if they have a common neighbor in B.

    Parameters
    ----------
    B : DiBipartite/Bipartie Graph
      The input graph should be bipartite.

    group : int
      Group Nodes to project onto (the "bottom" nodes or the top nodes).
         1 : top node
         2 : bottom node

    Returns
    -------
    DiGraph/Graph : graph
       A graph that is the projection onto the given nodes.

    )pbdoc");

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

    bipartite.def("__repr__", [](bs::Bipartite &g) {
        std::ostringstream out;
        out << "<class " << g << ">";
        return out.str();
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
    dibipartite.def("__repr__", [](bs::DiBipartite &g) {
        std::ostringstream out;
        out << "<class " << g << ">";
        return out.str();
    });
}
#endif //BSTREAM_BIPARTITE_INTERFACE_HPP
