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

#include "GraphType.hpp"

namespace boost::bstream
{
    template <typename DirectedS>
    void erdos_renyi_graph(int n, float p, GraphBase<DirectedS>& graph, int seed=0)
    {
        boost::minstd_rand gen;
        if(seed != 0)
            gen.seed(seed);

        typedef typename GraphBase<DirectedS>::Adjacency Adjacency;
        typedef boost::erdos_renyi_iterator<boost::minstd_rand, Adjacency> ERGen;
        Adjacency g(ERGen(gen, n, p), ERGen(), n);
        graph.copy_adjacency(g);
    }
} //end namespace boost::bstream


#endif //BSTREAM_ERDOS_RENY_HPP
