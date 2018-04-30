//
// Created by Vincent Gauthier on 30/04/2018.
//

#include "BiLinkStreamBase.hpp"

namespace boost::bstream
{
    template<typename DirectedS>
    typename GraphBase<DirectedS>::edge_t
    BiLinkStreamBase<DirectedS>::add_edge_w_time(const std::string &s, const std::string &t, time_t b, time_t e)
    {
        // check if vertices exist
        if (!this->has_vertex(s))
            this->add_vertex_w_group(GraphBase<DirectedS>::bipartite::top, s);
        if (!this->has_vertex(t))
            this->add_vertex_w_group(GraphBase<DirectedS>::bipartite::bottom, t);
        return LinkStreamBase<DirectedS>::add_edge_w_time(s, t, b, e);
    }

    template<typename DirectedS>
    typename GraphBase<DirectedS>::vertex_t
    BiLinkStreamBase<DirectedS>::add_vertex_w_group(int group, const std::string &label)
    {
        auto v = this->add_vertex(label);
        this->G[v].group = group;
        return v;
    }

    template<typename DirectedS>
    int BiLinkStreamBase<DirectedS>::group(const typename GraphBase<DirectedS>::vertex_t &v)
    {
        return this->G[v].group;
    }

    template<typename DirectedS>
    int BiLinkStreamBase<DirectedS>::group(const std::string &v)
    {
        return this->G[this->vertex(v)].group;
    }

    template
    class BiLinkStreamBase<boost::undirectedS>;
} // end namespace boost::bstream