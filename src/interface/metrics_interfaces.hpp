///-------------------------------------------------------------------------------------------------
///
/// @file       metrics_interfaces.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       03/05/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#ifndef BSTREAM_METRICS_INTERFACES_HPP
#define BSTREAM_METRICS_INTERFACES_HPP

namespace py = pybind11;
namespace bs = boost::bstream;

#include "metrics/summary.hpp"
#include "metrics/degree.hpp"
#include "metrics/clustering.hpp"
#include "GraphType.hpp"

void metrics_interface(py::module &m)
{
    m.def("summary", &bs::summary<boost::undirectedS>);
    m.def("summary", &bs::summary<boost::bidirectionalS>);
    m.def("avg_degree", &bs::avg_degree<boost::undirectedS>);
    m.def("avg_degree", &bs::avg_degree<boost::bidirectionalS>);
    m.def("avg_clustering", &bs::avg_clustering<boost::undirectedS>);
    m.def("avg_clustering", &bs::avg_clustering<boost::bidirectionalS>);
}

#endif //BSTREAM_METRICS_INTERFACES_HPP
