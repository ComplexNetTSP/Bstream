///-------------------------------------------------------------------------------------------------
///
/// @file       bipartite.cpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       12/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#include "bipartite.hpp"

namespace boost::bstream
{
    template<typename DirectedS>
    GraphBase<DirectedS> projected_graph(GraphBase<DirectedS> g, int group)
    {
        auto edges_list = g.edges();
    }
}

