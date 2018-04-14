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
    void projected_graph(Graph &g, int group)
    {
        //int group_to_remove = Graph::bipartite::null;
        Graph gprime;

        /*
        gprime.remove_all_edges();

        // remove nodes that don't belong to the group
        if(Graph::bipartite::top == group)
            group_to_remove = Graph::bipartite::top ;
        else
            group_to_remove = Graph::bipartite::bottom ;
        for(auto it = gprime.vertices().first; it != gprime.vertices().second; ++it){
            if(gprime.is_group(*it, group_to_remove)){
                gprime.remove_vertex(*it);
            }
        }
        */
        for(auto i = g.vertices().first; i != g.vertices().second; ++i){
            for(auto j = g.vertices().first; j != g.vertices().second; ++j){
                for(auto k = g.vertices().first; k != g.vertices().second; ++k){
                    if(g.has_edge(*i, *k) && g.has_edge(*j, *k) && *i != *k && *j != *k && *i != *j){
                        gprime.add_edge(*i, *j);
                        std::cout << *i << " " << *j << std::endl;
                    }
                }
            }
        }
    }
}


#endif //BSTREAM_BIPARTITE_HPP
