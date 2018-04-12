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
    template <typename DirectedS>
    GraphBase<DirectedS>& projected_graph(GraphBase<DirectedS> &g, int group);
}


#endif //BSTREAM_BIPARTITE_HPP
