///-------------------------------------------------------------------------------------------------
///
/// @file       base_graph.hpp
/// @brief      Definition of the main Graph/Digraph class
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       04/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_BGRAPHBASE_H
#define BSTREAM_BGRAPHBASE_H

#include <boost/graph/adjacency_list.hpp>

namespace boost::bstream
{
    /**
     * @brief class basegraph
     * @tparam DirectedS
     */
    template<typename DirectedS>
    class BaseGraph
    {
    public:
        typedef adjacency_list <
                vecS,
                vecS,
                DirectedS
        > Adjacency;

        typedef graph_traits <Adjacency> traits;
        typedef typename traits::vertex_descriptor vertex_t;
        typedef typename traits::edge_descriptor edge_t;
        typedef typename traits::directed_category directed_category;
        typedef typename traits::vertex_iterator vertex_iterator;
        typedef typename traits::edge_iterator edge_iterator;
        typedef typename traits::vertices_size_type vertex_size_t;
        typedef typename traits::edges_size_type edge_size_t;

        BaseGraph() {};

        BaseGraph(int num_vertex);

        ~BaseGraph() = default;

        /**
         * @brief Return true if graph is directed.
         * @return boolean
         */
        virtual bool is_directed() const;

        /**
         * @brief Add a single node and update node attributes.
         * @return vertex_descriptor
         */
        virtual vertex_t add_vertex();

        /**
         * @brief The number of edges in the graph.
         * @return edge_size_t
         */
        virtual edge_t add_edge(vertex_t& s, vertex_t& t);

        /**
         * @brief The number of vertices in the graph.
         * @return vertex_size_t
         */
        virtual vertex_size_t num_vertices();

        /**
         * @brief The number of edges in the graph.
         * @return edge_size_t
         */
        virtual edge_size_t num_edges();

        /**
         * @brief test if the edge (u,v) exist
         * @param s
         * @param t
         * @return boolean
         */
        virtual bool has_edge(vertex_t& s, vertex_t& t);

        /**
         * @brief remove the a vertex and his adjacent edge
         * @param v vertex_t
         */
        void remove_vertex(vertex_t& v);

        /**
         * @brief remove an edge between two vertex
         * @param s
         * @param t
         */
        virtual void remove_edge(vertex_t& s, vertex_t& t);

        virtual void remove_edge(edge_t& e);

        /**
         * @brief a vertex iterator
         * @return pair<begin, end>
         */
        std::pair<vertex_iterator, vertex_iterator> vertices();

        std::pair<edge_iterator, edge_iterator> edges();


        /**
         * @brief return the degree of a vertex
         * if the graph is directed, we return the sum of indegree and outdegree
         * @param v vertex_t
         * @return the number of edge adjacent to a vertex
         */
        virtual vertex_size_t degree(vertex_t& v);

        /**
         * @brief return in_degree of a vertex
         * @param v vertex_t
         * @return the number of in-edge adjacent to a vertex
         */
        virtual vertex_size_t in_degree(vertex_t& v);

        virtual vertex_size_t out_degree(vertex_t& v);

    protected:
        /**
         * Adjacency list of the graph
         */
        Adjacency G;
    };

} // end namespace boost::src

#endif //BSTREAM_BGRAPHBASE_H
