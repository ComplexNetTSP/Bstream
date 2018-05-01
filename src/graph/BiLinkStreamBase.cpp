//
// Created by Vincent Gauthier on 30/04/2018.
//

#include "BiLinkStreamBase.hpp"

namespace boost::bstream
{
    ///**************************************************************************************************
    ///
    ///  Graph methods
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    int BiLinkStreamBase<DirectedS>::num_top_vertices()
    {
        int num = 0;
        for (auto it = this->vertices().first; it != this->vertices().second; ++it) {
            if (this->group(*it) == GraphBase<DirectedS>::bipartite::top)
                num++;
        }
        return num;
    }

    template<typename DirectedS>
    int BiLinkStreamBase<DirectedS>::num_bottom_vertices()
    {
        int num = 0;
        for (auto it = this->vertices().first; it != this->vertices().second; ++it) {
            if (this->group(*it) == GraphBase<DirectedS>::bipartite::bottom)
                num++;
        }
        return num;
    }

    template<typename DirectedS>
    void BiLinkStreamBase<DirectedS>::print_edges()
    {
        std::cout << *this << std::endl;
        auto e_iterator = this->edges();
        for(auto it=e_iterator.first; it != e_iterator.second; ++it){
            auto s = boost::source(*it, this->G);
            auto t = boost::target(*it, this->G);
            auto s_name = this->label(s);
            auto t_name = this->label(t);
            std::cout << "\t" << this->TimeIntervalSetVertexMap[*it] << " x "
                 << "(" << s << "," << t << ")" ;
            if(!s_name.empty() && !t_name.empty())
                std::cout << " with name (" << s_name << "," << t_name << ")" ;
            std::cout << " with group (" << std::to_string(this->group(s)) << "," << std::to_string(this->group(t))<< ")" ;
            std::cout << std::endl;
        }
    }

    ///**************************************************************************************************
    ///
    ///  Edge methods
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    typename BiLinkStreamBase<DirectedS>::edge_t
    BiLinkStreamBase<DirectedS>::add_edge_w_time(const std::string &s, const std::string &t, time_t b, time_t e)
    {
        // check if vertices exist
        if (!this->has_vertex(s))
            this->add_vertex_w_group(GraphBase<DirectedS>::bipartite::top, s);
        if (!this->has_vertex(t))
            this->add_vertex_w_group(GraphBase<DirectedS>::bipartite::bottom, t);
        return this->add_edge_w_time(this->vertex(s), this->vertex(t), b, e);
    }

    template<typename DirectedS>
    typename BiLinkStreamBase<DirectedS>::edge_t
    BiLinkStreamBase<DirectedS>::add_edge_w_time(const typename BiLinkStreamBase<DirectedS>::vertex_t &s,
                                                 const typename BiLinkStreamBase<DirectedS>::vertex_t &t,
                                                 time_t b, time_t e)
    {
        // check if vertices exist
        if (!this->has_vertex(s)) {
            std::string msg = "Vertex " + std::to_string(s) + " doesn't exist";
            throw BiLinkStreamBaseException(msg);
        }
        if (!this->has_vertex(t)) {
            std::string msg = "Vertex " + std::to_string(t) + " doesn't exist";
            throw BiLinkStreamBaseException(msg);
        }
        if (this->group(s) == this->group(t) or this->group(s) == 0 or this->group(t) == 0) {
            std::string msg = "Vertices (" + this->label(s) + " and " + this->label(t) + ") belong to the same group";
            throw BiLinkStreamBaseException(msg);
        }

        return LinkStreamBase<DirectedS>::add_edge_w_time(s, t, b, e);
    }

    ///**************************************************************************************************
    ///
    ///  Vertex methods
    ///
    ///**************************************************************************************************

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