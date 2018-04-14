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
#include "tintervalset_interface.hpp"
#include "csvreader_interface.hpp"

#include "bipartite.hpp"

PYBIND11_MODULE(pybstream, m) {
    graph_interface(m);
    tinterval_interface(m);
    tintervalset_interface(m);
    csvreader_interface(m);
}