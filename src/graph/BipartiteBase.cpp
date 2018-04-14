///-------------------------------------------------------------------------------------------------
///
/// @file       BipartiteBase.cpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       14/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#include <string>
#include "BipartiteBase.hpp"

namespace boost::bstream
{
    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_t
    BipartiteBase<DirectedS>::add_vertex(int group, const std::string label)
    {
        auto v = GraphBase<DirectedS>::add_vertex(label);
        this->G[v].group = group;
        return v;
    }

} // end namespace boost::bstream