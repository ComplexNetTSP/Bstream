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

        virtual typename GraphBase<DirectedS>::vertex_t
        add_vertex_with_group(int group, const std::string& label="");

        virtual int group(const typename GraphBase<DirectedS>::vertex_t& v);
        virtual int group(const std::string& v);

        ///**************************************************************************************************
        ///
        ///  Edge method
        ///
        ///**************************************************************************************************

        typename GraphBase<DirectedS>::edge_t
        add_edge(const typename GraphBase<DirectedS>::vertex_t& s, const typename GraphBase<DirectedS>::vertex_t& t);

        typename GraphBase<DirectedS>::edge_t
        add_edge(const std::string& s, const std::string& t);


    };
} // end namespace boost::bstream

#endif //BSTREAM_BIPARTITEBASE_HPP
