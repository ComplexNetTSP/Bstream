//
// Created by Vincent Gauthier on 06/04/2018.
//

#include <limits>

#include "LinkStreamBase.hpp"

using namespace std;

namespace boost::bstream
{
    template<typename DirectedS>
    LinkStreamBase<DirectedS>::LinkStreamBase(time_t b, time_t e) {
        if(b==0 && e==0)
            interval_def = make_time_interval(0, std::numeric_limits<time_t>::max());
        else
            interval_def = make_time_interval(b, e);
    }

    template<typename DirectedS>
    LinkStreamBase<DirectedS>::LinkStreamBase(int num_vertex, time_t b, time_t e): LinkStreamBase(b,e){
        for(auto i=0; i< num_vertex; ++i)
            this->add_vertex();
    }

    template<typename DirectedS>
    void LinkStreamBase<DirectedS>::remove_vertex(typename BaseGraph<DirectedS>::vertex_t& v)
    {
        //todo: remove all the TimeIntervalSet of the corresponding edge adjacent to the vertex v
        BaseGraph<DirectedS>::remove_vertex(v);
    }

    template<typename DirectedS>
    time_t LinkStreamBase<DirectedS>::definition_length()
    {
        return interval_def.upper() - interval_def.lower();
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::edge_t
    LinkStreamBase<DirectedS>::add_edge(typename BaseGraph<DirectedS>::vertex_t& s,
                                        typename BaseGraph<DirectedS>::vertex_t& t)
    {
        typename BaseGraph<DirectedS>::edge_t e_exist;
        bool ok;
        std::tie(e_exist, ok) = boost::edge(s, t, BaseGraph<DirectedS>::G);
        if(ok){
            TimeIntervalVertexMap[e_exist].append(interval_def.lower(), interval_def.upper());
            return e_exist;
        }else{
            auto e = BaseGraph<DirectedS>::add_edge(s, t);
            TimeIntervalVertexMap[e].append(interval_def.lower(), interval_def.upper());
            return e;
        }
    }

    template<typename DirectedS>
    typename BaseGraph<DirectedS>::edge_t
    LinkStreamBase<DirectedS>::add_edge(typename BaseGraph<DirectedS>::vertex_t& s,
                                        typename BaseGraph<DirectedS>::vertex_t& t,
                                        time_t b,
                                        time_t e)
    {
        typename BaseGraph<DirectedS>::edge_t edge_exist;
        bool ok;
        std::tie(edge_exist, ok) = boost::edge(s, t, BaseGraph<DirectedS>::G);
        if(ok){
            TimeIntervalVertexMap[edge_exist].append(b, e);
            return edge_exist;
        }else{
            auto edge = BaseGraph<DirectedS>::add_edge(s, t);
            TimeIntervalVertexMap[edge].append(b, e);
            return edge;
        }
    }

    template<typename DirectedS>
    std::pair<time_t, time_t> LinkStreamBase<DirectedS>::definition() const
    {
        return std::make_pair<time_t, time_t>(interval_def.lower(), interval_def.upper());
    }

    template<typename DirectedS>
    void LinkStreamBase<DirectedS>::print_edges()
    {
        cout << "LinkStream def:" << interval_def << endl;
        auto e_iterator = BaseGraph<DirectedS>::edges();
        for(auto it=e_iterator.first; it != e_iterator.second; ++it){
            cout << "\t" << boost::source(*it, BaseGraph<DirectedS>::G)
                 << "," << boost::target(*it, BaseGraph<DirectedS>::G)
                 << " " << TimeIntervalVertexMap[*it] << endl;
        }
    }

    template class LinkStreamBase<boost::undirectedS>;
    template class LinkStreamBase<boost::bidirectionalS>;
}
