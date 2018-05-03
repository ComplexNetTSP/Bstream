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
#include "bipartite.hpp"

#define BOOST_TEST_MODULE BipatiteBase_tests

#include <boost/test/included/unit_test.hpp>

using namespace boost::bstream;
using namespace std;

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

    auto v1 = g.add_vertex_w_group(Bipartite::bipartite::top, "A");
    g.add_vertex_w_group(Bipartite::bipartite::bottom, "B");
    g.add_vertex_w_group(Bipartite::bipartite::top, "C");
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 0);
    BOOST_CHECK(g.is_directed() == false);
    BOOST_CHECK(g.group(v1) == Bipartite::bipartite::top);
    BOOST_CHECK(g.group("A") == Bipartite::bipartite::top);
}

BOOST_AUTO_TEST_CASE(BipartiteBase_add_edge)
{
    Bipartite g;

    auto v1 = g.add_vertex_w_group(Bipartite::bipartite::top, "A");
    g.add_vertex_w_group(Bipartite::bipartite::bottom, "B");
    g.add_vertex_w_group(Bipartite::bipartite::top, "C");

    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 0);
    BOOST_CHECK(g.is_directed() == false);
    BOOST_CHECK(g.group(v1) == Bipartite::bipartite::top);
    BOOST_CHECK(g.group("A") == Bipartite::bipartite::top);

    g.add_edge("A", "B");
    g.add_edge("C", "B");
}

BOOST_AUTO_TEST_CASE(BipartiteBase_add_edge_exception)
{
    Bipartite g;

    auto v1 = g.add_vertex_w_group(Bipartite::bipartite::top, "A");
    g.add_vertex_w_group(Bipartite::bipartite::bottom, "B");
    g.add_vertex_w_group(Bipartite::bipartite::top, "C");

    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 0);
    BOOST_CHECK(g.is_directed() == false);
    BOOST_CHECK(g.group(v1) == Bipartite::bipartite::top);
    BOOST_CHECK(g.group("A") == Bipartite::bipartite::top);

    BOOST_CHECK_THROW(g.add_edge("A", "C"), BipartiteBaseException);
}

BOOST_AUTO_TEST_CASE(BipartiteBase_projected_graph)
{
    Bipartite g;
    Graph gproj;

    g.add_vertex_w_group(Bipartite::bipartite::top, "A");
    g.add_vertex_w_group(Bipartite::bipartite::bottom, "B");
    g.add_vertex_w_group(Bipartite::bipartite::top, "C");
    g.add_edge("A", "B");
    g.add_edge("C", "B");

    projected_graph(Bipartite::bipartite::top, g, gproj);
    BOOST_CHECK(gproj.num_vertices() == 2);
    BOOST_CHECK(gproj.num_edges() == 1);
    BOOST_CHECK(gproj.is_directed() == false);
    BOOST_CHECK(gproj.has_edge("A", "C"));
}

BOOST_AUTO_TEST_CASE(BipartiteBase_clear_vertex_w_group)
{
    Bipartite g;

    g.add_vertex_w_group(Bipartite::bipartite::top, "A");
    g.add_vertex_w_group(Bipartite::bipartite::bottom, "B");
    g.add_vertex_w_group(Bipartite::bipartite::top, "C");
    g.add_edge("A", "B");
    g.add_edge("C", "B");
    g.clear_vertex_w_group(vertex_group::top);
    BOOST_CHECK(g.num_vertices() == 1);
    BOOST_CHECK(g.num_edges() == 0);
}

BOOST_AUTO_TEST_CASE(BipartiteBase_adjacency)
{
    Bipartite g;

    g.add_vertex_w_group(vertex_group::top, "1");
    g.add_vertex_w_group(vertex_group::bottom, "A");
    g.add_vertex_w_group(vertex_group::top, "2");
    g.add_vertex_w_group(vertex_group::bottom, "B");
    g.add_vertex_w_group(vertex_group::top, "3");

    g.add_edge("1", "A");
    g.add_edge("2", "A");
    g.add_edge("2", "B");
    g.add_edge("3", "B");

    MatrixXd m(3,2);
    m(0,0) = 1;
    m(0,1) = 0;

    m(1,0) = 1;
    m(1,1) = 1;

    m(2,0) = 0;
    m(2,1) = 1;
    BOOST_CHECK(g.adjacency() == m);
}

BOOST_AUTO_TEST_CASE(BipartiteBase_read_csv)
{
    Bipartite g;
    g.read_csv("edges.csv");
    BOOST_CHECK(g.num_vertices() == 7);
    BOOST_CHECK(g.num_top_vertices() == 3);
    BOOST_CHECK(g.num_bottom_vertices() == 4);
    BOOST_CHECK(g.num_edges() == 6);
    BOOST_CHECK(g.has_vertex("A"));
    BOOST_CHECK(g.has_vertex("B"));
    BOOST_CHECK(g.has_vertex("C"));

    BOOST_CHECK(g.has_vertex("1"));
    BOOST_CHECK(g.has_vertex("2"));
    BOOST_CHECK(g.has_vertex("3"));
    BOOST_CHECK(g.has_vertex("4"));

    BOOST_CHECK(g.has_edge("A", "1"));
    BOOST_CHECK(g.has_edge("A", "2"));
}

BOOST_AUTO_TEST_CASE(BipartiteBase_density)
{
    Bipartite g;

    g.add_vertex_w_group(vertex_group::top, "1");
    g.add_vertex_w_group(vertex_group::top, "2");
    g.add_vertex_w_group(vertex_group::top, "3");
    g.add_vertex_w_group(vertex_group::bottom, "A");
    g.add_vertex_w_group(vertex_group::bottom, "B");


    g.add_edge("1", "A");
    g.add_edge("2", "A");
    g.add_edge("2", "B");
    g.add_edge("3", "B");

    BOOST_CHECK(g.density() == 2.0/3); ///< should be 4 /(3 * 2)
}