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
    BipartiteBase<DirectedS>::add_vertex_with_group(int group, const std::string& label)
    {
        auto v = GraphBase<DirectedS>::add_vertex(label);
        this->G[v].group = group;
        return v;
    }

    template<typename DirectedS>
    int BipartiteBase<DirectedS>::group(const typename GraphBase<DirectedS>::vertex_t& v)
    {
        return this->G[v].group;
    }

    template<typename DirectedS>
    int BipartiteBase<DirectedS>::group(const std::string& v)
    {
        return this->G[this->vertex(v)].group;
    }

    ///**************************************************************************************************
    ///
    ///  Edge method
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    BipartiteBase<DirectedS>::add_edge(const typename GraphBase<DirectedS>::vertex_t& s, const typename GraphBase<DirectedS>::vertex_t& t)
    {
        if(this->group(s) != this->group(t)){
            return GraphBase<DirectedS>::add_edge(s,t);
        }else{
            throw BipartiteBaseException("Both vertex belong to the same group");
        }
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    BipartiteBase<DirectedS>::add_edge(const std::string& s, const std::string& t)
    {
        if(this->group(s) != this->group(t)){
            return GraphBase<DirectedS>::add_edge(s,t);
        }else{
            throw BipartiteBaseException("Both vertex belong to the same group");
        }
    }

    template class BipartiteBase<boost::undirectedS>;
    template class BipartiteBase<boost::bidirectionalS>;

} // end namespace boost::bstream