///-------------------------------------------------------------------------------------------------
///
/// @file       algorithms_interface.hpp
/// @brief      Python interface the algorithms
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

#include "generators/erdos_reny.hpp"
#include "bipartite.hpp"
#include "GraphType.hpp"

void algorithms_interface(py::module &m)
{
    ///**************************************************************************************************
    ///
    ///  for bipartite graph
    ///
    ///**************************************************************************************************

    m.def("projected_graph", bs::projected_graph<boost::undirectedS>, py::arg("Bipartite"), py::arg("projection_node"), R"pbdoc(
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

    m.def("erdos_renyi_graph", [](int n, float p, bool directed, int seed){
        if(directed){
            bs::DiGraph *g = new bs::DiGraph();
            bs::erdos_renyi_graph(n, p, *g, seed);
            bs::GraphAbstract *ga = g;
            return ga;
        }else{
            bs::Graph *g = new bs::Graph();
            bs::erdos_renyi_graph(n, p, *g, seed);
            bs::GraphAbstract *ga = g;
            return ga;
        }
    }, py::arg("n"), py::arg("p"), py::arg("directed")=false, py::arg("seed")=0, R"pbdoc(
    Returns a G_{n,p} random graph, also known as an Erdős-Rényi graph or a binomial graph.

    The G_{n,p} model chooses each of the possible edges with probability p.

    Args:
        n (int): The number of nodes.
        p (float): Probability for edge creation.
        directed (bool, optional): If True, this function returns a directed graph (default=False).
        seed (int, optional): Seed for random number generator (default=0).

    Returns:
        Graph: directed or undirected

    References:
        .. Erdős and A. Rényi, On Random Graphs, Publ. Math. 6, 290 (1959).
        .. Gilbert, Random Graphs, Ann. Math. Stat., 30, 1141 (1959).
    )pbdoc");

}

#endif //BSTREAM_ALGORITHMS_HPP
