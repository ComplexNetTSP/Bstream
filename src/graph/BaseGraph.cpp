///-------------------------------------------------------------------------------------------------
///
/// @file       base_graph.cpp
/// @brief      Implementation of the Digraph/Graph class
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       04/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#include <tuple>
#include "BaseGraph.hpp"

using namespace std;

namespace boost::bstream
{

    template<typename DirectedS>
    BaseGraph<DirectedS>::BaseGraph(int num_vertex)
    {
        for(auto i=0; i < num_vertex; ++i)
            add_vertex();
    }

    template<typename DirectedS>
    bool BaseGraph<DirectedS>::is_directed() const
    {
        return detail::is_directed(directed_category());
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::vertex_t
    BaseGraph<DirectedS>::add_vertex()
    {
        return boost::add_vertex(G);
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::edge_t
    BaseGraph<DirectedS>::add_edge(BaseGraph<DirectedS>::vertex_t& s, BaseGraph<DirectedS>::vertex_t& t)
    {
        bool ok;
        edge_t e;
        tie(e, ok) = boost::add_edge(s, t, G);
        return e;
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::vertex_size_t
    BaseGraph<DirectedS>::num_vertices()
    {
        return boost::num_vertices(G);
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::edge_size_t
    BaseGraph<DirectedS>::num_edges()
    {
        if(is_directed())
            return boost::num_edges(G);
        else
            return 2 * boost::num_edges(G);
    }

    template<typename DirectedS>
    bool BaseGraph<DirectedS>::has_edge(BaseGraph<DirectedS>::vertex_t& s, BaseGraph<DirectedS>::vertex_t& t)
    {
        return boost::edge(s, t, G).second;
    }

    template<typename DirectedS>
    void BaseGraph<DirectedS>::remove_vertex(BaseGraph<DirectedS>::vertex_t &v)
    {
        boost::clear_vertex(v, G);
        boost::remove_vertex(v, G);
    }

    template<typename DirectedS>
    void BaseGraph<DirectedS>::remove_edge(BaseGraph<DirectedS>::vertex_t &s, BaseGraph<DirectedS>::vertex_t &t)
    {
        BaseGraph<DirectedS>::edge_t e;
        bool exist;
        std::tie(e, exist) = boost::edge(s,t,G);
        if(exist)
            boost::remove_edge(e, G);
    }

    template<typename DirectedS>
    void BaseGraph<DirectedS>::remove_edge(BaseGraph<DirectedS>::edge_t &e)
    {
        boost::remove_edge(e, G);
    }

    template<typename DirectedS>
    std::pair<typename BaseGraph<DirectedS>::vertex_iterator, typename BaseGraph<DirectedS>::vertex_iterator>
    BaseGraph<DirectedS>::vertices()
    {
        return boost::vertices(G);
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::vertex_size_t
    BaseGraph<DirectedS>::degree(BaseGraph<DirectedS>::vertex_t& v)
    {
        return boost::degree(v, G);
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::vertex_size_t
    BaseGraph<DirectedS>::in_degree(BaseGraph<DirectedS>::vertex_t& v)
    {
        return boost::in_degree(v, G);
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::vertex_size_t
    BaseGraph<DirectedS>::out_degree(BaseGraph<DirectedS>::vertex_t& v)
    {
        return boost::out_degree(v, G);
    }

    template<typename DirectedS>
    pair<typename BaseGraph<DirectedS>::edge_iterator, typename BaseGraph<DirectedS>::edge_iterator>
    BaseGraph<DirectedS>::edges()
    {
        return boost::edges(G);;
    }

    template class BaseGraph<boost::undirectedS>;
    template class BaseGraph<boost::bidirectionalS>;

}
