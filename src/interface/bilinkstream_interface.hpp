///-------------------------------------------------------------------------------------------------
///
/// @file       bilinkstream_interface.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       01/05/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#ifndef BSTREAM_BILINKSTREAM_INTERFACE_HPP
#define BSTREAM_BILINKSTREAM_INTERFACE_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/eigen.h>
#include <iostream>
#include <string>
#include <ctime>

#include "GraphType.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

void bilinkstream_interface(py::module &m)
{

    py::class_<bs::BiLinkStream, bs::LinkStream> bilinkstream(m, "BiLinkStream");

    bilinkstream.doc() =
            R"pbdoc(
Base class for undirected graphs.
)pbdoc";

    ///**************************************************************************************************
    ///
    ///  Constructors
    ///
    ///**************************************************************************************************

    bilinkstream.def(py::init<>());
    bilinkstream.def(py::init<int>());
    bilinkstream.def(py::init<time_t, time_t>());
    bilinkstream.def(py::init<int, time_t, time_t>());

    ///**************************************************************************************************
    ///
    ///  Graph methods
    ///
    ///**************************************************************************************************

    bilinkstream.def("num_top_vertices", &bs::BiLinkStream::num_top_vertices);
    bilinkstream.def("num_bottom_vertices", &bs::BiLinkStream::num_bottom_vertices);
    bilinkstream.def("print_edges", &bs::BiLinkStream::print_edges);

    ///**************************************************************************************************
    ///
    ///  Vertex methods
    ///
    ///**************************************************************************************************

    bilinkstream.def("add_vertex_w_group", &bs::BiLinkStream::add_vertex_w_group,
                     py::arg("group"), py::arg("label") = "");
    bilinkstream.def("group", py::overload_cast<const std::string &>(&bs::BiLinkStream::group));
    bilinkstream.def("group", py::overload_cast<const bs::BiLinkStream::vertex_t &>(&bs::BiLinkStream::group));
    bilinkstream.def("instantaneous_group_degree", &bs::BiLinkStream::instantaneous_group_degree);
    ///**************************************************************************************************
    ///
    ///  Edge methods
    ///
    ///**************************************************************************************************

    bilinkstream.def("add_edge_w_time",
                     py::overload_cast<const bs::BiLinkStream::vertex_t &, const bs::BiLinkStream::vertex_t &, time_t, time_t>(
                             &bs::BiLinkStream::add_edge_w_time));
    bilinkstream.def("add_edge_w_time", py::overload_cast<const std::string &, const std::string &, time_t, time_t>(
            &bs::BiLinkStream::add_edge_w_time));

    bilinkstream.def("__repr__", [](bs::BiLinkStream &g) {
        std::ostringstream out;
        out << "<class " << g << ">";
        return out.str();
    });
}

#endif //BSTREAM_BILINKSTREAM_INTERFACE_HPP
