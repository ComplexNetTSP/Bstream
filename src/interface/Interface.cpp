///-------------------------------------------------------------------------------------------------
///
/// @file       Interface.cpp
/// @brief      Main file for the Python wrapper
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       05/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "GraphType.hpp"

#include "graph_interface.hpp"
#include "digraph_interface.hpp"
#include "tintervalset_interface.hpp"
#include "bipartite_interface.hpp"
#include "linkstream_interface.hpp"
#include "bilinkstream_interface.hpp"
#include "algorithms_interface.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

PYBIND11_MODULE(pybstream, m) {
    py::enum_<bs::vertex_group>(m, "vertex_group")
            .value("null", bs::vertex_group::null)
            .value("top", bs::vertex_group::top)
            .value("bottom", bs::vertex_group::bottom)
            .export_values();

    graph_interface(m);
    digraph_interface(m);
    tinterval_interface(m);
    tintervalset_interface(m);
    bipartite_interface(m);
    linkstream_interface(m);
    bilinkstream_interface(m);
    algorithms_interface(m);
}