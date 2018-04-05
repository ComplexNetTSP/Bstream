///-------------------------------------------------------------------------------------------------
///
/// @file       Interface.cpp
/// @brief      Description
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

PYBIND11_MODULE(pybstream, m) {
    graph_interface(m);
    tinterval_interface(m);
    tintervalset_interface(m);
}