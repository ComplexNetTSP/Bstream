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

    g.add_vertex_w_group(Bipartite::bipartite::top, "A");
    g.add_vertex_w_group(Bipartite::bipartite::bottom, "B");
    g.add_vertex_w_group(Bipartite::bipartite::top, "C");
    g.add_edge("A", "B");
    g.add_edge("C", "B");

    auto gproj = projected_graph(g, Bipartite::bipartite::top);
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
    g.clear_vertex_w_group(Bipartite::bipartite::top);
    BOOST_CHECK(g.num_vertices() == 1);
    BOOST_CHECK(g.num_edges() == 0);
}