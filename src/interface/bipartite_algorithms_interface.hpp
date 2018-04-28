///-------------------------------------------------------------------------------------------------
///
/// @file       bipartite_algorithms_interface.hpp
/// @brief      Python interface for the algorithms related to bipartite graph
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       28/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_BIPARTITE_ALGORITHMS_INTERFACE_HPP
#define BSTREAM_BIPARTITE_ALGORITHMS_INTERFACE_HPP

namespace py = pybind11;
namespace bs = boost::bstream;

#include "bipartite.hpp"
#include "GraphType.hpp"

void bipartite_algorithms_interface(py::module &m)
{
    ///**************************************************************************************************
    ///
    ///  Projection algorithms for bipartite graph
    ///
    ///**************************************************************************************************

    m.def("projected_graph", [](int projection_node, bs::Bipartite& b){
        bs::Graph *g = new bs::Graph();
        bs::projected_graph(projection_node, b, *g);
        return g;
    }, py::arg("projection_node"), py::arg("Bipartite"), R"pbdoc(
    Returns the projection of B onto one of its node sets.

    Returns the graph G that is the projection of the bipartite graph B
    onto the specified nodes. They retain their attributes and are connected
    in G if they have a common neighbor in B.

    Args:
        B (Bipartie): The input graph should be bipartite.
        group (int): Group Nodes to project onto (the "bottom" nodes or the top nodes).
            1 : top node
            2 : bottom node

    Returns:
        Graph: A graph that is the projection onto the given nodes.

    )pbdoc");
}

#endif //BSTREAM_BIPARTITE_ALGORITHMS_INTERFACE_HPP
