//
// Created by Vincent Gauthier on 06/04/2018.
//

#ifndef BSTREAM_LINKSTREAM_HPP
#define BSTREAM_LINKSTREAM_HPP

#include <map>
#include <ctime>
#include <stdexcept>

#include "GraphBase.hpp"
#include "TimeIntervalSet.hpp"

namespace boost::bstream
{
    class LinkStreamBaseException: public std::runtime_error
    {
    public:
        LinkStreamBaseException(const std::string& what): std::runtime_error(what) {};
    };

    template <typename DirectedS>
    class LinkStreamBase: public GraphBase<DirectedS>
    {
    public:
        LinkStreamBase(time_t b=0, time_t e=0);

        LinkStreamBase(int num_vertex, time_t b=0, time_t e=0);

        ~LinkStreamBase() = default;

        std::pair<time_t, time_t> definition() const;

        time_t definition_length();

        typename GraphBase<DirectedS>::edge_t
        add_edge(typename GraphBase<DirectedS>::vertex_t& s, typename GraphBase<DirectedS>::vertex_t& t);

        typename GraphBase<DirectedS>::edge_t
        add_edge(typename GraphBase<DirectedS>::vertex_t& s, typename GraphBase<DirectedS>::vertex_t& t, time_t b, time_t e);

        std::pair<typename GraphBase<DirectedS>::edge_t, bool>
        is_edge_active(typename GraphBase<DirectedS>::vertex_t& s, typename GraphBase<DirectedS>::vertex_t& t, time_t b, time_t e);

        void remove_vertex(typename GraphBase<DirectedS>::vertex_t& v);

        void print_edges();

        friend std::ostream & operator<<(std::ostream &out, LinkStreamBase &l)
        {
            if(l.is_directed())
                out << "DiLinkStream(|V|=" << l.num_vertices() << ", |E|=" << l.num_edges() << ")" << std::endl;
            else
                out << "LinkStream(|V|=" << l.num_vertices() << ", |E|=" << l.num_edges()
                    <<  ", T=" << l.interval_def << ")" << std::endl;
            return out;
        }


    protected:
        TimeInterval interval_def;
        std::map<typename GraphBase<DirectedS>::edge_t, TimeIntervalSet> TimeIntervalSetVertexMap;
    };
}

#endif //BSTREAM_LINKSTREAM_HPP
