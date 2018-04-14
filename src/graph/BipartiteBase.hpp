///-------------------------------------------------------------------------------------------------
///
/// @file       BipartiteBase.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       14/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_BIPARTITEBASE_HPP
#define BSTREAM_BIPARTITEBASE_HPP

#include <string>

#include "GraphBase.hpp"

namespace boost::bstream
{
    template<typename DirectedS>
    class BipartiteBase: public GraphBase<DirectedS>
    {
    public:

        ///**************************************************************************************************
        ///
        ///  Constructor
        ///
        ///**************************************************************************************************

        BipartiteBase(): GraphBase<DirectedS>::GraphBase() {};
        ~BipartiteBase() = default;

        ///**************************************************************************************************
        ///
        ///  Vertex method
        ///
        ///**************************************************************************************************

        typename GraphBase<DirectedS>::vertex_t
        add_vertex(int group, const std::string label="");
    };
} // end namespace boost::bstream

#endif //BSTREAM_BIPARTITEBASE_HPP
