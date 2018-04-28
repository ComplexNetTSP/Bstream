///-------------------------------------------------------------------------------------------------
///
/// @file       algorithms_interface.hpp
/// @brief      Python interface for all the algorithms
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       27/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#ifndef BSTREAM_ALGORITHMS_HPP
#define BSTREAM_ALGORITHMS_HPP

namespace py = pybind11;
namespace bs = boost::bstream;

#include "GraphType.hpp"
#include "graph_generators_interface.hpp"
#include "bipartite_algorithms_interface.hpp"

void algorithms_interface(py::module &m)
{
    bipartite_algorithms_interface(m);
    graph_generators_interface(m);
}

#endif //BSTREAM_ALGORITHMS_HPP
