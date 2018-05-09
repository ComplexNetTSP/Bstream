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
#include <boost/graph/labeled_graph.hpp>
#include <iostream>
#include <stdexcept>
#include <set>
#include <Eigen/Core>

#include "GraphAbstract.hpp"

using Eigen::MatrixXd;

namespace boost::bstream
{
    class GraphBaseException : public std::runtime_error
    {
    public:
        GraphBaseException(const std::string &what) : std::runtime_error(what)
        {};
    };

    class VertexBaseProperty
    {
    public:
        VertexBaseProperty() : group(0), label("")
        {};

        VertexBaseProperty(std::string label, int group) : group(group), label(label)
        {};

        int group;
        std::string label;
    };

    /**
     * @brief class basegraph
     * @tparam DirectedS
     */
    template<typename DirectedS>
    class GraphBase : public GraphAbstract
    {
    public:
        typedef adjacency_list<
                listS,
                vecS,
                DirectedS,
                VertexBaseProperty
        > Adjacency;

        typedef graph_traits<Adjacency> traits;
        typedef typename traits::vertex_descriptor vertex_t;
        typedef typename traits::edge_descriptor edge_t;
        typedef typename traits::directed_category directed_category;
        typedef typename traits::vertex_iterator vertex_iterator;
        typedef typename traits::edge_iterator edge_iterator;
        typedef typename traits::vertices_size_type vertex_size_t;
        typedef typename traits::edges_size_type edge_size_t;
        typedef typename traits::adjacency_iterator adjacency_iterator;

        enum bipartite
        {
            null, top, bottom
        };

        ///**************************************************************************************************
        ///
        ///  Constructor
        ///
        ///**************************************************************************************************

        GraphBase() : m(0)
        {};

        GraphBase(const GraphBase<DirectedS> &g);

        GraphBase(int num_vertex);

        ~GraphBase() = default;

        ///**************************************************************************************************
        ///
        ///  Graph method
        ///
        ///**************************************************************************************************

        /**
         * @brief Return true if graph is directed.
         * @return boolean
         */
        bool is_directed() const;

        double density();

        virtual void copy_graph(const GraphBase<DirectedS> &g);

        virtual void copy_adjacency(const Adjacency &g);

        MatrixXd adjacency();

        void read_csv(std::string path, char delimiter = ',');

        /**
         * @brief The number of vertices in the graph.
         * @return vertex_size_t
         */
        double num_vertices();

        /**
         * @brief The number of edges in the graph.
         * @return edge_size_t
         */
        double num_edges();

        std::string print_edges();

        void clear_vertices();

        void clear_edges();

        void clear();

        virtual vertex_t &operator[](const std::string &label);

        virtual std::string &operator[](const vertex_t &v);

        ///**************************************************************************************************
        ///
        ///  Vertex method
        ///
        ///**************************************************************************************************

        /**
         * @brief Add a single node and update node attributes.
         * @return vertex_descriptor
         */
        virtual vertex_t add_vertex(const std::string name = "");

        virtual std::string label(const vertex_t &v) const;

        virtual std::vector<std::string> labels() const;

        virtual vertex_t vertex(const std::string label);

        virtual bool has_vertex(const vertex_t &v);

        virtual bool has_vertex(const std::string &label);

        /**
         * @brief a vertex iterator
         * @return pair<begin, end>
         */
        std::pair<vertex_iterator, vertex_iterator> vertices();

        /**
         * @brief return the degree of a vertex
         * if the graph is directed, we return the sum of indegree and outdegree
         * @param v vertex_t
         * @return the number of edge adjacent to a vertex
         */
        virtual double degree(const vertex_t &v);

        virtual double degree(const std::string &v);

        virtual double clustering(const std::string &v);

        virtual double clustering(const vertex_t &v);

        /**
         * @brief return in_degree of a vertex
         * @param v vertex_t
         * @return the number of in-edge adjacent to a vertex
         */
        virtual double in_degree(const vertex_t &v);

        virtual double in_degree(const std::string &v);

        virtual double out_degree(const vertex_t &v);

        virtual double out_degree(const std::string &v);

        virtual std::pair<adjacency_iterator, adjacency_iterator> neighbors(const vertex_t &v);

        virtual std::pair<adjacency_iterator, adjacency_iterator> neighbors(const std::string &v);

        /**
         * @brief remove the a vertex and his adjacent edge
         * @param v vertex_t
         */
        virtual void remove_vertex(const std::string &label);

        ///**************************************************************************************************
        ///
        ///  Edge method
        ///
        ///**************************************************************************************************

        /**
         * @brief The number of edges in the graph.
         * @return edge_size_t
         */
        virtual edge_t add_edge(const vertex_t &s, const vertex_t &t);

        virtual edge_t add_edge(const std::string &s, const std::string &t);

        virtual std::pair<edge_t, bool> edge(const vertex_t &s, const vertex_t &t);

        virtual std::pair<edge_t, bool> edge(const std::string &s, const std::string &t);

        virtual std::pair<vertex_t, vertex_t> edge_endpoint(const edge_t &e);

        /**
         * @brief test if the edge (u,v) exist
         * @param s
         * @param t
         * @return boolean
         */
        virtual bool has_edge(const vertex_t &s, const vertex_t &t);

        virtual bool has_edge(const std::string &s, const std::string &t);

        /**
         * @brief remove an edge between two vertex
         * @param s
         * @param t
         */
        virtual void remove_edge(const vertex_t &s, const vertex_t &t);

        virtual void remove_edge(const std::string &s, const std::string &t);

        std::pair<edge_iterator, edge_iterator> edges();

        ///**************************************************************************************************
        ///
        ///  Property method
        ///
        ///**************************************************************************************************


        friend std::ostream &operator<<(std::ostream &out, GraphBase &g)
        {
            if (g.is_directed())
                out << "DiGraph(|V|=" << g.num_vertices() << ", |E|=" << g.num_edges() << ")";
            else
                out << "Graph(|V|=" << g.num_vertices() << ", |E|=" << g.num_edges() << ")";
            return out;
        }

    protected:
        /**
         * Adjacency list of the graph
         */
        Adjacency G;
        std::map<std::string, vertex_t> label_map;
        std::set<vertex_t, std::less<vertex_t>> vertex_set;
        int m; //!< next vertex_id

        virtual void remove_edge(const edge_t &e);

        virtual void remove_vertex(const vertex_t &v);
    };

} // end namespace boost::bstream

#endif //BSTREAM_BGRAPHBASE_H
