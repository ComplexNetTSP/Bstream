///-------------------------------------------------------------------------------------------------
///
/// @file       DiLinkStream.hpp
/// @brief      Bipartite LinkStream class definition
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       30/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_DILINKSTREAM_HPP
#define BSTREAM_DILINKSTREAM_HPP

#include <string>

#include "GraphBase.hpp"
#include "LinkStreamBase.hpp"
#include "TimeIntervalSet.hpp"

namespace boost::bstream
{
    class BiLinkStreamBaseException : public LinkStreamBaseException
    {
    public:
        BiLinkStreamBaseException(const std::string &what) : LinkStreamBaseException(what)
        {};
    };

    template<typename DirectedS>
    class BiLinkStreamBase : public LinkStreamBase<DirectedS>
    {
    public:

        ///**************************************************************************************************
        ///
        ///  Constructors & destructor
        ///
        ///**************************************************************************************************

        BiLinkStreamBase() : LinkStreamBase<DirectedS>()
        {};

        BiLinkStreamBase(int num_vertex) : LinkStreamBase<DirectedS>(num_vertex)
        {};

        BiLinkStreamBase(time_t b, time_t e) : LinkStreamBase<DirectedS>(b, e)
        {};

        BiLinkStreamBase(int num_vertex, time_t b, time_t e) : LinkStreamBase<DirectedS>(num_vertex, b, e)
        {};

        ~BiLinkStreamBase() = default;

        ///**************************************************************************************************
        ///
        ///  Graph methods
        ///
        ///**************************************************************************************************

        virtual int num_top_vertices();

        virtual int num_bottom_vertices();

        std::string print_edges();

        ///**************************************************************************************************
        ///
        ///  Vertex methods
        ///
        ///**************************************************************************************************

        virtual typename GraphBase<DirectedS>::vertex_t add_vertex_w_group(int group, const std::string &label = "");

        virtual int group(const typename GraphBase<DirectedS>::vertex_t &v);

        virtual int group(const std::string &v);

        std::map<time_t, int> instantaneous_group_degree(vertex_group group);

        virtual void clear_vertex_w_group(vertex_group group);

        ///**************************************************************************************************
        ///
        ///  Edge methods
        ///
        ///**************************************************************************************************

        typename BiLinkStreamBase<DirectedS>::edge_t add_edge_w_time(
                const typename BiLinkStreamBase<DirectedS>::vertex_t &s,
                const typename BiLinkStreamBase<DirectedS>::vertex_t &t,
                time_t b, time_t e);

        typename BiLinkStreamBase<DirectedS>::edge_t add_edge_w_time(
                const std::string &s,
                const std::string &t,
                time_t b, time_t e);

        friend std::ostream &operator<<(std::ostream &out, BiLinkStreamBase &l)
        {
            out << "BiLinkStream(|V|=" << l.num_vertices() << ", |E|=" << l.num_edges()
                << ", T=" << l.interval_def << ")";
            return out;
        }
    };
} // end namespace boost::bstream

#endif //BSTREAM_DILINKSTREAM_HPP
