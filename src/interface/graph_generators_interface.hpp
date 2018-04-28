///-------------------------------------------------------------------------------------------------
///
/// @file       graph_generators_interface.hpp
/// @brief      Python interface for the graph generator algorithms
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       28/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#ifndef BSTREAM_GRAPH_GENERATORS_INTERFACE_HPP
#define BSTREAM_GRAPH_GENERATORS_INTERFACE_HPP

namespace py = pybind11;
namespace bs = boost::bstream;

#include "generators/erdos_reny.hpp"
#include "GraphType.hpp"

void graph_generators_interface(py::module &m)
{

    ///**************************************************************************************************
    ///
    ///  Erdos reny interface
    ///
    ///**************************************************************************************************

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

#endif //BSTREAM_GRAPH_GENERATORS_INTERFACE_HPP
