///-------------------------------------------------------------------------------------------------
///
/// @file       BipartiteBase.cpp
/// @brief      BipartiteBase definition
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

    ///**************************************************************************************************
    ///
    ///  Graph method
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    int BipartiteBase<DirectedS>::num_top_vertices()
    {
        int num = 0;
        for (auto it = this->vertices().first; it != this->vertices().second; ++it) {
            if (this->group(*it) == GraphBase<DirectedS>::bipartite::top)
                num++;
        }
        return num;
    }

    template<typename DirectedS>
    int BipartiteBase<DirectedS>::num_bottom_vertices()
    {
        int num = 0;
        for (auto it = this->vertices().first; it != this->vertices().second; ++it) {
            if (this->group(*it) == GraphBase<DirectedS>::bipartite::bottom)
                num++;
        }
        return num;
    }

    template<typename DirectedS>
    double BipartiteBase<DirectedS>::density()
    {
        return this->num_edges()/(num_bottom_vertices() * num_top_vertices());
    }

    template<typename DirectedS>
    MatrixXd BipartiteBase<DirectedS>::adjacency()
    {
        MatrixXd m = Eigen::MatrixXd::Zero(this->num_top_vertices(), this->num_bottom_vertices());
        int t = 0, b = 0;
        for (auto i = this->vertices().first; i != this->vertices().second; ++i) {
            if (this->group(*i) == GraphBase<DirectedS>::bipartite::top) {
                b = 0;
                for (auto j = this->vertices().first; j != this->vertices().second; ++j) {
                    if (this->group(*j) == GraphBase<DirectedS>::bipartite::bottom) {
                        if (this->has_edge(*i, *j))
                            m(t, b) = 1;
                        b++;
                    }
                }
                t++;
            }
        }
        return m;
    }

    ///**************************************************************************************************
    ///
    ///  Vertex method
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_t
    BipartiteBase<DirectedS>::add_vertex_w_group(int group, const std::string &label)
    {
        auto v = GraphBase<DirectedS>::add_vertex(label);
        this->G[v].group = group;
        return v;
    }

    template<typename DirectedS>
    int BipartiteBase<DirectedS>::group(const typename GraphBase<DirectedS>::vertex_t &v)
    {
        return this->G[v].group;
    }

    template<typename DirectedS>
    int BipartiteBase<DirectedS>::group(const std::string &v)
    {
        return this->G[this->vertex(v)].group;
    }

    template<typename DirectedS>
    void BipartiteBase<DirectedS>::clear_vertex_w_group(vertex_group group)
    {
        auto labels = this->labels();
        for (auto it = labels.begin(); it != labels.end(); ++it) {
            auto v = this->vertex(*it);
            if (this->group(v) == vertex_group::null)
                throw BipartiteBaseException("Malformed Bipartie Graph");
            if (this->group(v) == group) {
                this->remove_vertex(v);
            }
        }
    }

    ///**************************************************************************************************
    ///
    ///  Edge method
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    BipartiteBase<DirectedS>::add_edge(const typename GraphBase<DirectedS>::vertex_t &s,
                                       const typename GraphBase<DirectedS>::vertex_t &t)
    {
        if (this->group(s) == this->group(t) or this->group(s) == 0 or this->group(t) == 0) {
            throw BipartiteBaseException("Both vertex belong to the same group");
        }
        return GraphBase<DirectedS>::add_edge(s, t);
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    BipartiteBase<DirectedS>::add_edge(const std::string &s, const std::string &t)
    {
        // if the node doesn't exist we consider that s belong to the top nodes and t belong to the bottom node
        if (!this->has_vertex(s))
            this->add_vertex_w_group(GraphBase<DirectedS>::bipartite::top, s);
        if (!this->has_vertex(t))
            this->add_vertex_w_group(GraphBase<DirectedS>::bipartite::bottom, t);

        return this->add_edge(this->vertex(s), this->vertex(t));
    }

    template
    class BipartiteBase<boost::undirectedS>;
    //template class BipartiteBase<boost::bidirectionalS>;

} // end namespace boost::bstream