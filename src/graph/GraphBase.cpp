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
    ///**************************************************************************************************
    ///
    ///  Constructor
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    GraphBase<DirectedS>::GraphBase(const GraphBase<DirectedS> &g)
    {
        boost::copy_graph(g.G, this->G);
        this->m = g.m;
        this->label_map = g.label_map;
        this->vertex_set = g.vertex_set;
    }

    template<typename DirectedS>
    GraphBase<DirectedS>::GraphBase(int num_vertex): m(0)
    {
        for(auto i=0; i < num_vertex; ++i)
            this->add_vertex();
    }

    ///**************************************************************************************************
    ///
    ///  Graph methods
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    bool GraphBase<DirectedS>::is_directed() const
    {
        return detail::is_directed(directed_category());
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
    void GraphBase<DirectedS>::clear()
    {
        this->G.clear();
    }

    template<typename DirectedS>
    MatrixXd GraphBase<DirectedS>::adjacency()
    {
        MatrixXd m = Eigen::MatrixXd::Zero(this->num_vertices(),this->num_vertices());

        for(auto i = this->vertices().first; i != this->vertices().second; ++i){
            for(auto j = this->vertices().first; j != this->vertices().second; ++j){
                if(this->has_edge(*i,*j))
                    m(*i,*j) = 1;
            }
        }
        return m;
    }

    ///**************************************************************************************************
    ///
    ///  Vertex medthods
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_t
    GraphBase<DirectedS>::add_vertex(const std::string label)
    {
        std::string name;
        if(label.empty())
            name = to_string(m);
        else
            name = label;

        if(label_map.find(name) != label_map.end())
            throw GraphBaseException("Vertex label is not unique");
        auto vp = VertexBaseProperty(name, bipartite::null);
        auto v = boost::add_vertex(vp, G);
        label_map.insert(make_pair(name, v));
        vertex_set.insert(v);
        m++;
        return v;
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_t
    GraphBase<DirectedS>::vertex(const std::string label)
    {
        return label_map[label];
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_size_t
    GraphBase<DirectedS>::num_vertices()
    {
        return boost::num_vertices(G);
    }

    template<typename DirectedS>
    std::string GraphBase<DirectedS>::label(const GraphBase::vertex_t &v) const
    {
        return G[v].label;
    }

    template<typename DirectedS>
    std::vector<std::string> GraphBase<DirectedS>::labels() const
    {
        std::vector<std::string> labels;
        for(auto it = label_map.begin(); it != label_map.end(); ++it)
            labels.push_back(it->first);
        return labels;
    }


    template<typename DirectedS>
    bool GraphBase<DirectedS>::has_vertex(const GraphBase::vertex_t &v)
    {
        return vertex_set.find(v) != vertex_set.end();
    }

    template<typename DirectedS>
    bool GraphBase<DirectedS>::has_vertex(const std::string &label)
    {
        return label_map.find(label) != label_map.end();
    }


    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_vertex(const std::string &label)
    {
        auto v = this->vertex(label);
        if(this->has_vertex(v)) {
            boost::clear_vertex(v, G);
            boost::remove_vertex(v, G);
        }

        label_map.clear();
        vertex_set.clear();
        for(auto it=this->vertices().first; it!=this->vertices().second; ++it){
            vertex_set.insert(*it);
            label_map.insert(make_pair(G[*it].label, *it));
        }

    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_vertex(const GraphBase<DirectedS>::vertex_t &v)
    {
        if(this->has_vertex(v)) {
            boost::clear_vertex(v, G);
            boost::remove_vertex(v, G);
        }

        label_map.clear();
        vertex_set.clear();
        for(auto it=this->vertices().first; it!=this->vertices().second; ++it){
            vertex_set.insert(*it);
            label_map.insert(make_pair(G[*it].label, *it));
        }
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::clear_vertices()
    {
        std::set<std::string> labels;
        for(auto it = label_map.begin(); it != label_map.end(); ++it)
            labels.insert(it->first);

        for(auto it = labels.begin(); it != labels.end(); ++it)
            this->remove_vertex(*it);
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::degree(const GraphBase<DirectedS>::vertex_t& v)
    {
        return static_cast<double>(boost::degree(v, G));
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::degree(const std::string& v)
    {
        return static_cast<double>(boost::degree(vertex(v), G));
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::in_degree(const GraphBase<DirectedS>::vertex_t& v)
    {
        return static_cast<double>(boost::in_degree(v, G));
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::in_degree(const std::string& v)
    {
        return static_cast<double>(boost::in_degree(vertex(v), G));
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::out_degree(const GraphBase<DirectedS>::vertex_t& v)
    {
        return static_cast<double>(boost::out_degree(v, G));
    }

    template<typename DirectedS>
    double GraphBase<DirectedS>::out_degree(const std::string& v)
    {
        return static_cast<double>(boost::out_degree(vertex(v), G));
    }

    template<typename DirectedS>
    std::pair<typename GraphBase<DirectedS>::vertex_iterator, typename GraphBase<DirectedS>::vertex_iterator>
    GraphBase<DirectedS>::vertices()
    {
        return boost::vertices(G);
    }


    ///**************************************************************************************************
    ///
    ///  Edge medthods
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    GraphBase<DirectedS>::add_edge(const GraphBase<DirectedS>::vertex_t& s, const GraphBase<DirectedS>::vertex_t& t)
    {
        bool ok;
        edge_t e;
        // test if vertices at the end of edge exist
        if (has_vertex(s) && has_vertex(t)) {
            // we check if edge already exist
            std::tie(e, ok) = boost::edge(s, t, G);
            if(!ok) {
                tie(e, ok) = boost::add_edge(s, t, G);
                if (!ok)
                    throw GraphBaseException("Unable to add the edge");
            }
        }else{
            throw GraphBaseException("Vertex must exist");
        }
        return e;
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    GraphBase<DirectedS>::add_edge(const std::string& s, const std::string& t)
    {
        vertex_t vs, vt;
        if (has_vertex(s) && has_vertex(t)) {
            return this->add_edge(this->vertex(s), this->vertex(t));
        }else{
            if(!has_vertex(s))
                vs = this->add_vertex(s);
            else
                vs = this->vertex(s);

            if(!has_vertex(t))
                vt = this->add_vertex(t);
            else
                vt = this->vertex(t);
            return this->add_edge(vs, vt);
        }
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
    bool GraphBase<DirectedS>::has_edge(const std::string& s, const std::string& t)
    {
        return boost::edge(vertex(s), vertex(t), G).second;
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_edge(const GraphBase<DirectedS>::vertex_t &s, const GraphBase<DirectedS>::vertex_t &t)
    {
        GraphBase<DirectedS>::edge_t e;
        bool exist;
        std::tie(e, exist) = boost::edge(s,t,G);
        if(exist)
            boost::remove_edge(e, G);
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_edge(const std::string &s, const std::string &t)
    {
        edge_t e;
        bool exist;
        std::tie(e, exist) = boost::edge(vertex(s), vertex(t), G);
        if(exist)
            boost::remove_edge(e, G);
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::remove_edge(const GraphBase<DirectedS>::edge_t &e)
    {
        boost::remove_edge(e, G);
    }

    template<typename DirectedS>
    void GraphBase<DirectedS>::clear_edges()
    {
        vertex_iterator vit, vit_end;
        for(boost::tie(vit, vit_end) = this->vertices(); vit != vit_end; ++vit){
            boost::clear_vertex(*vit, G);
        }
    }

    template<typename DirectedS>
    pair<typename GraphBase<DirectedS>::edge_iterator, typename GraphBase<DirectedS>::edge_iterator>
    GraphBase<DirectedS>::edges()
    {
        return boost::edges(G);;
    }

    template<typename DirectedS>
    pair<typename GraphBase<DirectedS>::adjacency_iterator, typename GraphBase<DirectedS>::adjacency_iterator>
    GraphBase<DirectedS>::neighbors(const GraphBase::vertex_t &v)
    {
        return boost::adjacent_vertices(v, G);
    }

    template<typename DirectedS>
    pair<typename GraphBase<DirectedS>::adjacency_iterator, typename GraphBase<DirectedS>::adjacency_iterator>
    GraphBase<DirectedS>::neighbors(const std::string &v)
    {
        return boost::adjacent_vertices(vertex(v), G);
    }

    template class GraphBase<boost::undirectedS>;
    template class GraphBase<boost::bidirectionalS>;

}
