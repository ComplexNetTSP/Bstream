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

    void projected_graph(int group, Bipartite &g, Graph &gproj)
    {
        Bipartite gprime(g);
        gprime.clear_edges();
        int group_to_del;

        // remove nodes that don't belong to the group
        if(Graph::bipartite::top == group)
            group_to_del = Bipartite::bipartite::bottom ;
        else
            group_to_del = Bipartite::bipartite::top ;

        gprime.clear_vertex_w_group(group_to_del);

        gproj.copy_graph(gprime);
        for(auto i = g.vertices().first; i != g.vertices().second; ++i){
            for(auto j = g.vertices().first; j != g.vertices().second; ++j){
                for(auto k = g.vertices().first; k != g.vertices().second; ++k){
                    if(g.has_edge(*i, *k) && g.has_edge(*j, *k) && *i != *k && *j != *k && *i != *j){
                        gproj.add_edge(g.label(*i), g.label(*j));
                    }
                }
            }
        }
    }
}


#endif //BSTREAM_BIPARTITE_HPP
