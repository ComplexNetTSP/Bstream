///-------------------------------------------------------------------------------------------------
///
/// @file       LinkStreamBase.hpp
/// @brief      LinkStreamBase Declaration
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       08/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


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
        LinkStreamBase();

        LinkStreamBase(int num_vertex);

        LinkStreamBase(time_t b, time_t e);

        LinkStreamBase(int num_vertex, time_t b, time_t e);

        ~LinkStreamBase() = default;

        void set_definition(const time_t t1, time_t t2);

        std::pair<time_t, time_t> definition() const;

        time_t definition_length();

        //todo: implement the method num_edge specific for linkstream and change the definition in GraphBase
        double num_edges();

        typename GraphBase<DirectedS>::edge_t
        add_edge(typename GraphBase<DirectedS>::vertex_t& s,
                 typename GraphBase<DirectedS>::vertex_t& t);

        typename GraphBase<DirectedS>::edge_t
        add_edge(typename GraphBase<DirectedS>::vertex_t& s,
                 typename GraphBase<DirectedS>::vertex_t& t,
                 time_t b, time_t e);

        std::pair<typename GraphBase<DirectedS>::edge_t, bool>
        is_edge_active(typename GraphBase<DirectedS>::vertex_t& s,
                       typename GraphBase<DirectedS>::vertex_t& t,
                       time_t b, time_t e);

        double degree(const typename GraphBase<DirectedS>::vertex_t& v);

        //todo: add the remove vertex method, check first about the graph properties
        void remove_vertex(typename GraphBase<DirectedS>::vertex_t& v);

        double density();

        void print_edges();

        //todo density

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
