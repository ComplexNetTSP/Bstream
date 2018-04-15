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
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);
    BOOST_CHECK(g.is_directed() == false);
}

BOOST_AUTO_TEST_CASE(BipartiteBase_add_vertex)
{
    Bipartite g;

    auto v1 = g.add_vertex_with_group(Bipartite::bipartite::top, "A");
    g.add_vertex_with_group(Bipartite::bipartite::bottom, "B");
    g.add_vertex_with_group(Bipartite::bipartite::top, "C");
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 0);
    BOOST_CHECK(g.is_directed() == false);
    BOOST_CHECK(g.group(v1) == Bipartite::bipartite::top);
    BOOST_CHECK(g.group("A") == Bipartite::bipartite::top);
}

BOOST_AUTO_TEST_CASE(BipartiteBase_add_edge)
{

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