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

#include "graph_interface.hpp"
#include "digraph_interface.hpp"
#include "tintervalset_interface.hpp"
#include "bipartite_interface.hpp"
#include "linkstream_interface.hpp"

PYBIND11_MODULE(pybstream, m) {
    graph_interface(m);
    digraph_interface(m);
    tinterval_interface(m);
    tintervalset_interface(m);
    bipartite_interface(m);
    linkstream_interface(m);
}