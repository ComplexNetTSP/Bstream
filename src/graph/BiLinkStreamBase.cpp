//
// Created by Vincent Gauthier on 30/04/2018.
//

#include <iostream>
#include <sstream>
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
    std::string BiLinkStreamBase<DirectedS>::print_edges()
    {
        std::ostringstream os;
        os << *this << std::endl;
        auto e_iterator = this->edges();
        for(auto it=e_iterator.first; it != e_iterator.second; ++it){
            auto s = boost::source(*it, this->G);
            auto t = boost::target(*it, this->G);
            auto s_name = this->label(s);
            auto t_name = this->label(t);
            os << "\t" << this->TimeIntervalSetVertexMap[*it] << " x "
                 << "(" << s << "," << t << ")" ;
            if(!s_name.empty() && !t_name.empty())
                os << " with name (" << s_name << "," << t_name << ")" ;
            os << " with group (" << std::to_string(this->group(s)) << "," << std::to_string(this->group(t))<< ")" ;
            os << std::endl;
        }
        return os.str();
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

    template<typename DirectedS>
    void BiLinkStreamBase<DirectedS>::clear_vertex_w_group(vertex_group group)
    {
        auto labels = this->labels();
        for (auto it = labels.begin(); it != labels.end(); ++it) {
            auto v = this->vertex(*it);
            if (this->group(v) == vertex_group::null)
                throw BiLinkStreamBaseException("Malformed Bipartie Graph");
            if (this->group(v) == group) {
                this->remove_vertex(this->label(v));
            }
        }
    }

    template<typename DirectedS>
    std::map<time_t, int> BiLinkStreamBase<DirectedS>::instantaneous_group_degree(vertex_group group)
    {
        std::map<time_t, int> inst_degree ;
        std::map<time_t, int> cum_inst_degree ;

        for(auto v = this->vertices().first; v != this->vertices().second; ++v) {
            if(this->group(*v) == group) {
                for (auto it = this->neighbors(*v).first; it != this->neighbors(*v).second; ++it) {
                    auto e = this->edge(*v, *it);
                    for (auto ti = this->TimeIntervalSetVertexMap[e.first].begin();
                        ti != this->TimeIntervalSetVertexMap[e.first].end(); ++ti) {
                        auto map_it_lower = inst_degree.find((*ti).lower());

                        if (map_it_lower != inst_degree.end()) {
                            ++inst_degree[(*ti).lower()];
                        } else {
                            inst_degree.insert(std::make_pair((*ti).lower(), +1));
                        }

                        auto map_it_upper = inst_degree.find((*ti).upper());
                        if (map_it_upper != inst_degree.end()) {
                            --inst_degree[(*ti).upper()];
                        } else {
                            inst_degree.insert(std::make_pair((*ti).upper(), -1));
                        }
                    }
                }
            }
        }

        ///< compute the cumsum of the degree over time
        double cumsum = 0;
        for(auto it = inst_degree.begin(); it != inst_degree.end(); ++it){
            cumsum += (*it).second;
            cum_inst_degree.insert( std::make_pair((*it).first, cumsum ) );
        }

        return cum_inst_degree;
    }

    template
    class BiLinkStreamBase<boost::undirectedS>;
} // end namespace boost::bstream