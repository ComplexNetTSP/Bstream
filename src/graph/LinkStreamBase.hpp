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
    class LinkStreamBaseException : public GraphBaseException
    {
    public:
        LinkStreamBaseException(const std::string &what) : GraphBaseException(what)
        {};
    };

    template<typename DirectedS>
    class LinkStreamBase : public GraphBase<DirectedS>
    {
    public:
        static const int default_max_interval = 1000; ///< default interaval [0, default_max_interval)

        ///**************************************************************************************************
        ///
        ///  Constructor
        ///
        ///**************************************************************************************************

        LinkStreamBase();

        LinkStreamBase(int num_vertex);

        LinkStreamBase(time_t b, time_t e);

        LinkStreamBase(int num_vertex, time_t b, time_t e);

        ~LinkStreamBase() = default;

        ///**************************************************************************************************
        ///
        ///  Graph methods
        ///
        ///**************************************************************************************************

        void set_definition(const time_t t1, time_t t2);

        std::pair<time_t, time_t> definition() const;

        time_t definition_length();

        double num_edges();

        double density();

        void print_edges();

        void read_csv(std::string path, char delimiter = ',');

        ///**************************************************************************************************
        ///
        ///  Vertex method
        ///
        ///**************************************************************************************************

        double degree(const typename GraphBase<DirectedS>::vertex_t &v);

        //todo: add the remove vertex method, check first about the graph properties
        //void remove_vertex(typename GraphBase<DirectedS>::vertex_t& v);

        ///**************************************************************************************************
        ///
        ///  Edge method
        ///
        ///**************************************************************************************************

        typename LinkStreamBase<DirectedS>::edge_t
        add_edge(const typename LinkStreamBase<DirectedS>::vertex_t &s,
                 const typename LinkStreamBase<DirectedS>::vertex_t &t);

        typename LinkStreamBase<DirectedS>::edge_t
        add_edge(const std::string &s, const std::string &t);


        virtual typename LinkStreamBase<DirectedS>::edge_t
        add_edge_w_time(const typename GraphBase<DirectedS>::vertex_t &s,
                        const typename GraphBase<DirectedS>::vertex_t &t,
                        time_t b, time_t e);

        virtual typename LinkStreamBase<DirectedS>::edge_t
        add_edge_w_time(const std::string &s,
                        const std::string &t,
                        time_t b, time_t e);


        std::pair<typename GraphBase<DirectedS>::edge_t, bool>
        is_edge_active(const typename GraphBase<DirectedS>::vertex_t &s,
                       const typename GraphBase<DirectedS>::vertex_t &t,
                       time_t b, time_t e);

        friend std::ostream &operator<<(std::ostream &out, LinkStreamBase &l)
        {
            if (l.is_directed())
                out << "DiLinkStream(|V|=" << l.num_vertices() << ", |E|=" << l.num_edges() << ")";
            else
                out << "LinkStream(|V|=" << l.num_vertices() << ", |E|=" << l.num_edges()
                    << ", T=" << l.interval_def << ")";
            return out;
        }


    protected:
        TimeInterval interval_def;
        std::map<typename GraphBase<DirectedS>::edge_t, TimeIntervalSet> TimeIntervalSetVertexMap;
    };
}

#endif //BSTREAM_LINKSTREAM_HPP
