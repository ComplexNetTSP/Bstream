///-------------------------------------------------------------------------------------------------
///
/// @file       bipartite_interface.hpp
/// @brief      Bipartie graph python interface
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       26/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


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

    py::enum_<bs::Bipartite::bipartite>(bipartite, "vertex_group")
            .value("null", bs::Bipartite::bipartite::null)
            .value("top", bs::Bipartite::bipartite::top)
            .value("bottom", bs::Bipartite::bipartite::bottom)
            .export_values();

    ///**************************************************************************************************
    ///
    ///  DiBipartite
    ///
    ///**************************************************************************************************
    /*
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
    */
}
#endif //BSTREAM_BIPARTITE_INTERFACE_HPP
