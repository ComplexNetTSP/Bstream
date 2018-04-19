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
    class LinkStreamBaseException: public GraphBaseException
    {
    public:
        LinkStreamBaseException(const std::string& what): GraphBaseException(what) {};
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

        double num_edges();

        typename GraphBase<DirectedS>::edge_t
        add_edge(const typename GraphBase<DirectedS>::vertex_t& s,
                 const typename GraphBase<DirectedS>::vertex_t& t);

        typename GraphBase<DirectedS>::edge_t
        add_edge_w_time(const typename GraphBase<DirectedS>::vertex_t& s,
                        const typename GraphBase<DirectedS>::vertex_t& t,
                        time_t b, time_t e);

        typename GraphBase<DirectedS>::edge_t
        add_edge_w_time(const std::string& s,
                        const std::string& t,
                        time_t b, time_t e);


        std::pair<typename GraphBase<DirectedS>::edge_t, bool>
        is_edge_active(const typename GraphBase<DirectedS>::vertex_t& s,
                       const typename GraphBase<DirectedS>::vertex_t& t,
                       time_t b, time_t e);

        double degree(const typename GraphBase<DirectedS>::vertex_t& v);

        //todo: add the remove vertex method, check first about the graph properties
        //void remove_vertex(typename GraphBase<DirectedS>::vertex_t& v);

        double density();

        void print_edges();

        friend std::ostream & operator<<(std::ostream &out, LinkStreamBase &l)
        {
            if(l.is_directed())
                out << "DiLinkStream(|V|=" << l.num_vertices() << ", |E|=" << l.num_edges() << ")";
            else
                out << "LinkStream(|V|=" << l.num_vertices() << ", |E|=" << l.num_edges()
                    <<  ", T=" << l.interval_def << ")" ;
            return out;
        }


    protected:
        TimeInterval interval_def;
        std::map<typename GraphBase<DirectedS>::edge_t, TimeIntervalSet> TimeIntervalSetVertexMap;
    };
}

#endif //BSTREAM_LINKSTREAM_HPP
