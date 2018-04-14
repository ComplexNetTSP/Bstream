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
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/copy.hpp>
#include "GraphBase.hpp"

using namespace std;

namespace boost::bstream
{
    template<typename DirectedS>
    GraphBase<DirectedS>::GraphBase(GraphBase<DirectedS> &g)
    {
        boost::copy_graph(g.G, this->G);
    }

    template<typename DirectedS>
    GraphBase<DirectedS>::GraphBase(int num_vertex, bool is_bipartite): is_bipartite(is_bipartite)
    {
        for(auto i=0; i < num_vertex; ++i)
            this->add_vertex();
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
        auto v = boost::add_vertex(G);
        if(name.empty())
            G[v].name = to_string(v);
        else
            G[v].name = name;
        G[v].group = 0;
        vertex_set.insert(v);
        return v;
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_t
    GraphBase<DirectedS>::add_vertex_with_group(int group, const string name)
    {
        auto v = boost::add_vertex(G);
        G[v].name = name;
        G[v].group = group;
        return v;
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    GraphBase<DirectedS>::add_edge(const GraphBase<DirectedS>::vertex_t& s,
                                   const GraphBase<DirectedS>::vertex_t& t,
                                   int s_group,
                                   int t_group)
    {

        bool ok;
        edge_t e;

        // for bipartite only
        if(is_bipartite) {
            if(this->has_vertex(s) && this->has_vertex(t)){
                // check if vertex already exist

                if (G[s].group == G[t].group)
                    throw GraphBaseException("Biparti graph: don't connect vertices form the same group");
                tie(e, ok) = boost::add_edge(s, t, G);
                if (!ok)
                    throw GraphBaseException("Unable to add the edge");
            }else {
                //if vertex do not exist add edge
                if (s_group == t_group) {
                    throw GraphBaseException("Biparti graph: don't connect vertices form the same group");
                } else {
                    tie(e, ok) = boost::add_edge(s, t, G);
                    if (!ok)
                        throw GraphBaseException("Unable to add the edge");
                    G[s].name = to_string(s);
                    G[t].name = to_string(t);
                    G[s].group = s_group;
                    G[t].group = t_group;
                    vertex_set.insert(source(e, G));
                    vertex_set.insert(target(e, G));
                }
            }
        }else{
            // not bipartite
            tie(e, ok) = boost::add_edge(s, t, G);
            if (!ok)
                throw GraphBaseException("Unable to add the edge");
            G[s].name = to_string(s);
            G[t].name = to_string(t);
            G[s].group = s_group;
            G[t].group = t_group;
            vertex_set.insert(source(e, G));
            vertex_set.insert(target(e, G));
        }
        return e;
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_size_t
    GraphBase<DirectedS>::num_vertices()
    {
        return boost::num_vertices(G);
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::num_edges()
    {
        return static_cast<double>(boost::num_edges(G));
    }

    template<typename DirectedS>
    bool GraphBase<DirectedS>::has_edge(const GraphBase<DirectedS>::vertex_t& s, const GraphBase<DirectedS>::vertex_t& t)
    {
        return boost::edge(s, t, G).second;
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_vertex(const GraphBase<DirectedS>::vertex_t &v)
    {
        vertex_set.erase(v);
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
    void GraphBase<DirectedS>::remove_edge(GraphBase<DirectedS>::edge_t e)
    {
        boost::remove_edge(e, G);
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_all_edges()
    {
        for(auto it=this->edges().first; it!=this->edges().second; ++it)
            this->remove_edge(*it);
    }

    template<typename DirectedS>
    std::pair<typename GraphBase<DirectedS>::vertex_iterator, typename GraphBase<DirectedS>::vertex_iterator>
    GraphBase<DirectedS>::vertices()
    {
        return boost::vertices(G);
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::degree(const GraphBase<DirectedS>::vertex_t& v)
    {
        return static_cast<double>(boost::degree(v, G));
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::in_degree(const GraphBase<DirectedS>::vertex_t& v)
    {
        return static_cast<double>(boost::in_degree(v, G));
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::out_degree(const GraphBase<DirectedS>::vertex_t& v)
    {
        return static_cast<double>(boost::out_degree(v, G));
    }

    template<typename DirectedS>
    pair<typename GraphBase<DirectedS>::edge_iterator, typename GraphBase<DirectedS>::edge_iterator>
    GraphBase<DirectedS>::edges()
    {
        return boost::edges(G);;
    }

    template<typename DirectedS>
    std::string GraphBase<DirectedS>::vertex_name(const GraphBase::vertex_t &v)
    {
        return G[v].name;
    }

    template<typename DirectedS>
    pair<typename GraphBase<DirectedS>::adjacency_iterator, typename GraphBase<DirectedS>::adjacency_iterator>
    GraphBase<DirectedS>::neighbors(const GraphBase::vertex_t &v)
    {
        return boost::adjacent_vertices(v, G);
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::density()
    {
        if(this->is_directed())
            return static_cast<double>(this->num_edges())/(this->num_vertices() * (this->num_vertices()-1));
        else
            return static_cast<double>(2 * this->num_edges())/(this->num_vertices() * (this->num_vertices()-1));
    }

    template<typename DirectedS>
    bool GraphBase<DirectedS>::is_group(const GraphBase::vertex_t &v, int group)
    {
        if(G[v].group == group)
            return true;
        else
            return false;
    }

    template<typename DirectedS>
    bool GraphBase<DirectedS>::has_vertex(const GraphBase::vertex_t &v)
    {
        return vertex_set.find(v) != vertex_set.end();
    }


    template class GraphBase<boost::undirectedS>;
    template class GraphBase<boost::bidirectionalS>;

}
