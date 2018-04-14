///-------------------------------------------------------------------------------------------------
///
/// @file       bipartite_tests.cpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       14/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#include "GraphType.hpp"

#define BOOST_TEST_MODULE BipatiteBase_tests

#include <boost/test/included/unit_test.hpp>

using namespace boost::bstream;

BOOST_AUTO_TEST_CASE(BipartiteBase_constructor)
{
    Bipartite g;
}

BOOST_AUTO_TEST_CASE(BipartiteBase_add_vertex)
{
    Bipartite g;

    g.add_vertex(Bipartite::bipartite::top);
    g.add_vertex(Bipartite::bipartite::top);
}

/*

BOOST_AUTO_TEST_CASE(GraphBase_biparti)
        {
                Graph g(true);

        auto a = g.add_vertex_with_group(Graph::bipartite::top);
        auto b = g.add_vertex_with_group(Graph::bipartite::bottom);
        auto c = g.add_vertex_with_group(Graph::bipartite::top);

        g.add_edge(a,b);
        BOOST_CHECK_THROW(g.add_edge(a,c), GraphBaseException);
        }

BOOST_AUTO_TEST_CASE(GraphBase_biparti_projected)
        {
                Graph g(true);

        auto a = g.add_vertex_with_group(Graph::bipartite::top);
        auto b = g.add_vertex_with_group(Graph::bipartite::bottom);
        auto c = g.add_vertex_with_group(Graph::bipartite::top);
        g.add_edge(a,b);
        g.add_edge(c,b);

        projected_graph(g, Graph::bipartite::top);
                //BOOST_CHECK(gprime.num_vertices() == 2);
                //BOOST_CHECK(gprime.num_edges() == 1);
        }

*/