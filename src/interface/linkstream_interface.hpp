///-------------------------------------------------------------------------------------------------
///
/// @file       linkstream_interface.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       19/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_LINKSTREAM_INTERFACE_HPP
#define BSTREAM_LINKSTREAM_INTERFACE_HPP

#include <ctime>
#include <iostream>

#include "GraphType.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

void linkstream_interface(py::module &m)
{
    py::class_<bs::LinkStream, bs::Graph> linkstream(m, "LinkStream");
    linkstream.def(py::init<>());
    linkstream.def(py::init<int>());
    linkstream.def(py::init<time_t, time_t>());
    linkstream.def(py::init<int, time_t, time_t>());
    linkstream.def("set_definition", &bs::LinkStream::set_definition);
    linkstream.def("definition", &bs::LinkStream::definition);
    linkstream.def("definition_length", &bs::LinkStream::definition_length);

    linkstream.def("add_edge", py::overload_cast<const bs::LinkStream::vertex_t &, const bs::LinkStream::vertex_t &>(
            &bs::LinkStream::add_edge));

    linkstream.def("add_edge", py::overload_cast<const std::string &, const std::string &>(&bs::LinkStream::add_edge));

    linkstream.def("add_edge_w_time",
                   py::overload_cast<const bs::LinkStream::vertex_t &, const bs::LinkStream::vertex_t &, time_t, time_t>(
                           &bs::LinkStream::add_edge_w_time));

    linkstream.def("add_edge_w_time", py::overload_cast<const std::string &, const std::string &, time_t, time_t>(
            &bs::LinkStream::add_edge_w_time));

    linkstream.def("edge_tinterval_set", py::overload_cast<const bs::LinkStream::edge_t &>(&bs::LinkStream::edge_tinterval_set));
    // todo: add edge_tinterval_set method for the other interface


    linkstream.def("is_edge_active", &bs::LinkStream::is_edge_active);
    linkstream.def("degree",  py::overload_cast<const typename bs::LinkStream::vertex_t &>(&bs::LinkStream::degree));
    linkstream.def("degree",  py::overload_cast<const std::string & >(&bs::LinkStream::degree));
    linkstream.def("instantaneous_degree",  py::overload_cast<const std::string &>(&bs::LinkStream::instantaneous_degree));
    linkstream.def("instantaneous_degree",  py::overload_cast<const typename bs::LinkStream::vertex_t &>(&bs::LinkStream::instantaneous_degree));
    linkstream.def("density", &bs::LinkStream::density);

    linkstream.def("read_csv", &bs::LinkStream::read_csv, py::arg("path"), py::arg("delimiter") = ',');

    linkstream.def("print_edges", &bs::LinkStream::print_edges);

    linkstream.def("__repr__", [](bs::LinkStream &g) {
        std::ostringstream out;
        out << "<class " << g << ">";
        return out.str();
    });

}

#endif //BSTREAM_LINKSTREAM_INTERFACE_HPP
