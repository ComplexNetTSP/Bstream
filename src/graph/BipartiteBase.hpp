///-------------------------------------------------------------------------------------------------
///
/// @file       BipartiteBase.hpp
/// @brief      Bipartite Graph definitions
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       14/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_BIPARTITEBASE_HPP
#define BSTREAM_BIPARTITEBASE_HPP

#include <string>
#include <Eigen/Core>

#include "GraphBase.hpp"

namespace boost::bstream
{
    class BipartiteBaseException: public GraphBaseException
    {
    public:
        BipartiteBaseException(const std::string& what): GraphBaseException(what) {};
    };

    template<typename DirectedS>
    class BipartiteBase: public GraphBase<DirectedS>
    {
    public:

        ///**************************************************************************************************
        ///
        ///  Constructor
        ///
        ///**************************************************************************************************

        BipartiteBase(): GraphBase<DirectedS>::GraphBase() {};
        ~BipartiteBase() = default;

        ///**************************************************************************************************
        ///
        ///  Graph method
        ///
        ///**************************************************************************************************

        MatrixXd adjacency();

        int num_top_vertices();

        int num_bottom_vertices();

        ///**************************************************************************************************
        ///
        ///  Vertex method
        ///
        ///**************************************************************************************************

        virtual typename GraphBase<DirectedS>::vertex_t
        add_vertex_w_group(int group, const std::string& label="");

        virtual int group(const typename GraphBase<DirectedS>::vertex_t& v);

        virtual int group(const std::string& v);

        virtual void clear_vertex_w_group(int group);

        ///**************************************************************************************************
        ///
        ///  Edge method
        ///
        ///**************************************************************************************************

        typename GraphBase<DirectedS>::edge_t
        add_edge(const typename GraphBase<DirectedS>::vertex_t& s, const typename GraphBase<DirectedS>::vertex_t& t);

        typename GraphBase<DirectedS>::edge_t
        add_edge(const std::string& s, const std::string& t);

        friend std::ostream & operator<<(std::ostream &out, BipartiteBase &g)
        {
            if(g.is_directed())
                out << "DiBipartite(|V|=" << g.num_vertices() << ", |E|=" << g.num_edges() << ")";
            else
                out << "Bipartite(|V|=" << g.num_vertices() << ", |E|=" << g.num_edges() << ")";
            return out;
        }


    };
} // end namespace boost::bstream

#endif //BSTREAM_BIPARTITEBASE_HPP
