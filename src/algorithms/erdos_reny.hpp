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
    //todo make test erdos_renyi_graph

    template <typename DirectedS>
    void erdos_renyi_graph(int n, float p, GraphBase<DirectedS>& graph)
    {
        boost::minstd_rand gen;
        typedef typename GraphBase<DirectedS>::Adjacency Adjacency;
        typedef boost::erdos_renyi_iterator<boost::minstd_rand, Adjacency> ERGen;
        Adjacency g(ERGen(gen, n, p), ERGen(), n);
        graph.set_adjacency(g);
    }
} //end namespace boost::bstream


#endif //BSTREAM_ERDOS_RENY_HPP
