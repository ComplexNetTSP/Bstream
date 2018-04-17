///-------------------------------------------------------------------------------------------------
///
/// @file       bipartite.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       12/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#ifndef BSTREAM_BIPARTITE_HPP
#define BSTREAM_BIPARTITE_HPP

#include "GraphType.hpp"

namespace boost::bstream
{
    template<typename DirectedS>
    GraphBase<DirectedS> projected_graph(BipartiteBase<DirectedS> &g, int group)
    {
        typename GraphBase<DirectedS>::vertex_iterator vit, vit_end;
        BipartiteBase<DirectedS> gprime(g);
        gprime.clear_edges();

        // remove nodes that don't belong to the group
        if(Graph::bipartite::top == group)
            group = BipartiteBase<DirectedS>::bipartite::bottom ;
        else
            group = BipartiteBase<DirectedS>::bipartite::top ;

        gprime.clear_vertex_w_group(group);

        auto gb = static_cast<GraphBase<DirectedS>>(gprime);
        for(auto i = g.vertices().first; i != g.vertices().second; ++i){
            for(auto j = g.vertices().first; j != g.vertices().second; ++j){
                for(auto k = g.vertices().first; k != g.vertices().second; ++k){
                    if(g.has_edge(*i, *k) && g.has_edge(*j, *k) && *i != *k && *j != *k && *i != *j){
                        gb.add_edge(g.label(*i), g.label(*j));
                    }
                }
            }
        }
        return gb;
    }
}


#endif //BSTREAM_BIPARTITE_HPP
