///-------------------------------------------------------------------------------------------------
///
/// @file       degree.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       03/05/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#ifndef BSTREAM_DEGREE_HPP
#define BSTREAM_DEGREE_HPP

#include "GraphType.hpp"

namespace boost::bstream
{
    template<typename DirectedS>
    double avg_degree(GraphBase<DirectedS> &g)
    {
        double avg_degree = 0.0;
        for (auto v = g.vertices().first; v != g.vertices().second; ++v) {
            avg_degree += g.degree(*v);
        }
        return avg_degree / g.num_vertices();
    }
} // end namespace boost::bstream
#endif //BSTREAM_DEGREE_HPP
