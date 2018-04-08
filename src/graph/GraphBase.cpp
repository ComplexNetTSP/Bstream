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
#include "GraphBase.hpp"

using namespace std;

namespace boost::bstream
{

    template<typename DirectedS>
    GraphBase<DirectedS>::GraphBase(int num_vertex)
    {
        for(auto i=0; i < num_vertex; ++i)
            add_vertex();
    }

    template<typename DirectedS>
    bool GraphBase<DirectedS>::is_directed() const
    {
        return detail::is_directed(directed_category());
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_t
    GraphBase<DirectedS>::add_vertex(const std::string name)
    {
        auto v= boost::add_vertex(G);
        G[v].name = name;
        return v;
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    GraphBase<DirectedS>::add_edge(GraphBase<DirectedS>::vertex_t& s, GraphBase<DirectedS>::vertex_t& t)
    {
        bool ok;
        edge_t e;
        tie(e, ok) = boost::add_edge(s, t, G);
        return e;
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_size_t
    GraphBase<DirectedS>::num_vertices()
    {
        return boost::num_vertices(G);
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_size_t
    GraphBase<DirectedS>::num_edges()
    {
        if(is_directed())
            return boost::num_edges(G);
        else
            return 2 * boost::num_edges(G);
    }

    template<typename DirectedS>
    bool GraphBase<DirectedS>::has_edge(GraphBase<DirectedS>::vertex_t& s, GraphBase<DirectedS>::vertex_t& t)
    {
        return boost::edge(s, t, G).second;
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_vertex(GraphBase<DirectedS>::vertex_t &v)
    {
        boost::clear_vertex(v, G);
        boost::remove_vertex(v, G);
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_edge(GraphBase<DirectedS>::vertex_t &s, GraphBase<DirectedS>::vertex_t &t)
    {
        GraphBase<DirectedS>::edge_t e;
        bool exist;
        std::tie(e, exist) = boost::edge(s,t,G);
        if(exist)
            boost::remove_edge(e, G);
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_edge(GraphBase<DirectedS>::edge_t &e)
    {
        boost::remove_edge(e, G);
    }

    template<typename DirectedS>
    std::pair<typename GraphBase<DirectedS>::vertex_iterator, typename GraphBase<DirectedS>::vertex_iterator>
    GraphBase<DirectedS>::vertices()
    {
        return boost::vertices(G);
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::degree(GraphBase<DirectedS>::vertex_t& v)
    {
        return static_cast<double>(boost::degree(v, G));
    }

    //todo: change the return type to double and add test
    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_size_t
    GraphBase<DirectedS>::in_degree(GraphBase<DirectedS>::vertex_t& v)
    {
        return boost::in_degree(v, G);
    }

    //todo: change the return type to double and add test
    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_size_t
    GraphBase<DirectedS>::out_degree(GraphBase<DirectedS>::vertex_t& v)
    {
        return boost::out_degree(v, G);
    }

    template<typename DirectedS>
    pair<typename GraphBase<DirectedS>::edge_iterator, typename GraphBase<DirectedS>::edge_iterator>
    GraphBase<DirectedS>::edges()
    {
        return boost::edges(G);;
    }

    template<typename DirectedS>
    std::string GraphBase<DirectedS>::vertex_name(GraphBase::vertex_t &v)
    {
        return G[v].name;
    }

    template<typename DirectedS>
    pair<typename GraphBase<DirectedS>::adjacency_iterator, typename GraphBase<DirectedS>::adjacency_iterator>
    GraphBase<DirectedS>::neighbors(GraphBase::vertex_t &v)
    {
        return boost::adjacent_vertices(v, G);
    }

    template class GraphBase<boost::undirectedS>;
    template class GraphBase<boost::bidirectionalS>;

}
