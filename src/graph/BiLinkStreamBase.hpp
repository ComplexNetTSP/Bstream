///-------------------------------------------------------------------------------------------------
///
/// @file       DiLinkStream.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       30/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_DILINKSTREAM_HPP
#define BSTREAM_DILINKSTREAM_HPP

#include "GraphBase.hpp"
#include "LinkStreamBase.hpp"

namespace boost::bstream
{
    class BiLinkStreamBaseException: public LinkStreamBaseException
    {
    public:
        BiLinkStreamBaseException(const std::string& what): LinkStreamBaseException(what) {};
    };

    template <typename DirectedS>
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
        ///  Vertex methods
        ///
        ///**************************************************************************************************

        virtual typename GraphBase<DirectedS>::vertex_t add_vertex_w_group(int group, const std::string &label = "");

        virtual int group(const typename GraphBase<DirectedS>::vertex_t& v);

        virtual int group(const std::string& v);

        ///**************************************************************************************************
        ///
        ///  Edge methods
        ///
        ///**************************************************************************************************

        typename GraphBase<DirectedS>::edge_t add_edge_w_time(
                const typename GraphBase<DirectedS>::vertex_t &s,
                const typename GraphBase<DirectedS>::vertex_t &t,
                time_t b, time_t e);

        typename GraphBase<DirectedS>::edge_t add_edge_w_time(
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
