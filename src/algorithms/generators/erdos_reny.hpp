///-------------------------------------------------------------------------------------------------
///
/// @file       erdos_reny.hpp
/// @brief      Erdos Reny graph generator
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       27/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_ERDOS_RENY_HPP
#define BSTREAM_ERDOS_RENY_HPP

#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <ctime>

#include "GraphType.hpp"

namespace boost::bstream
{
    template <typename DirectedS>
    void erdos_renyi_graph(int n, float p, GraphBase<DirectedS>& graph, int seed=0)
    {
        typedef boost::minstd_rand RNG;
        RNG rng;
        if(seed != 0)
            rng.seed(seed);
        else
            rng.seed(time(0));

        typedef typename GraphBase<DirectedS>::Adjacency Adjacency;
        typedef boost::erdos_renyi_iterator<boost::minstd_rand, Adjacency> ERGen;
        Adjacency g(ERGen(rng, n, p), ERGen(), n);
        graph.copy_adjacency(g);
    }
} //end namespace boost::bstream


#endif //BSTREAM_ERDOS_RENY_HPP
