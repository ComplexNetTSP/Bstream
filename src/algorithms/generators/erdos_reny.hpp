//
// Created by Vincent Gauthier on 26/04/2018.
//

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
        graph.set_adjacency(g);
    }
} //end namespace boost::bstream


#endif //BSTREAM_ERDOS_RENY_HPP