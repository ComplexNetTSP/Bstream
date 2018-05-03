///-------------------------------------------------------------------------------------------------
///
/// @file       clustering.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       03/05/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_CLUSTERING_HPP
#define BSTREAM_CLUSTERING_HPP

#include "GraphType.hpp"

namespace boost::bstream
{
    template<typename DirectedS>
    double avg_clustering(GraphBase<DirectedS> &g)
    {
        double avg_clustering = 0.0;
        for (auto v = g.vertices().first; v != g.vertices().second; ++v) {
            avg_clustering += g.clustering(*v);
        }
        return avg_clustering / g.num_vertices();
    }
} // end namespace boost::bstream

#endif //BSTREAM_CLUSTERING_HPP
