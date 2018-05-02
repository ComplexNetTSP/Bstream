///-------------------------------------------------------------------------------------------------
///
/// @file       bilinkstream_tests.cpp
/// @brief      Test case for the BilinkStream class (Bipartite LinkStream)
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       30/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#include "GraphType.hpp"
#include "bipartite.hpp"

#define BOOST_TEST_MODULE BiLinkStream_tests

#include <boost/test/included/unit_test.hpp>
#include <limits>
#include <ctime>

using namespace boost::bstream;
using namespace std;

BOOST_AUTO_TEST_CASE(BiLinStream_constructors)
{
    BiLinkStream g;
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);
    BOOST_CHECK(g.definition().second == BiLinkStream::default_max_interval);
    BOOST_CHECK(g.definition().first == 0);

    // with initial definition interval
    BiLinkStream g1(0, 10);
    BOOST_CHECK(g1.num_vertices() == 0);
    BOOST_CHECK(g1.num_edges() == 0);
    BOOST_CHECK(g1.definition().second == 10);
    BOOST_CHECK(g1.definition().first == 0);

    // with initial definition interval and 10 initial vertices
    BiLinkStream g2(10, 0, 10);
    BOOST_CHECK(g2.num_vertices() == 10);
    BOOST_CHECK(g2.num_edges() == 0);
    BOOST_CHECK(g2.definition().second == 10);
    BOOST_CHECK(g2.definition().first == 0);
}

BOOST_AUTO_TEST_CASE(BiLinStream_add_edge_by_label)
{
    // with initial definition interval
    BiLinkStream g(0, 10);
    g.add_edge_w_time("A", "B", 0, 5);
    g.add_edge_w_time("C", "B", 0, 5);
    BOOST_CHECK(g.group("B") == 2);
    BOOST_CHECK(g.group("A") == 1);
    BOOST_CHECK(g.group("C") == 1);
    BOOST_CHECK(g.has_edge("A", "B"));
    BOOST_CHECK(g.has_edge("C", "B"));
    BOOST_CHECK(g.has_edge("A", "C") == false);
    BOOST_CHECK(g.num_top_vertices() == 2);
    BOOST_CHECK(g.num_bottom_vertices() == 1);
    BOOST_CHECK((g.num_bottom_vertices() + g.num_top_vertices()) == g.num_vertices());
}

BOOST_AUTO_TEST_CASE(BiLinStream_add_edge)
{
    // with initial definition interval
    BiLinkStream g(0, 10);
    auto A = g.add_vertex_w_group(BiLinkStream::bipartite::bottom);
    auto B = g.add_vertex_w_group(BiLinkStream::bipartite::top);
    auto C = g.add_vertex_w_group(BiLinkStream::bipartite::bottom);

    g.add_edge_w_time(A, B, 0, 5);
    g.add_edge_w_time(C, B, 0, 5);
    BOOST_CHECK(g.group(A) == BiLinkStream::bipartite::bottom);
    BOOST_CHECK(g.group(B) == BiLinkStream::bipartite::top);
    BOOST_CHECK(g.group(C) == BiLinkStream::bipartite::bottom);
    BOOST_CHECK(g.has_edge(A, B));
    BOOST_CHECK(g.has_edge(C, B));
    BOOST_CHECK(g.has_edge(A, C) == false);
    BOOST_CHECK(g.num_top_vertices() == 1);
    BOOST_CHECK(g.num_bottom_vertices() == 2);
    BOOST_CHECK((g.num_bottom_vertices() + g.num_top_vertices()) == g.num_vertices());
    //g.print_edges();
}


///*********************************************************************************************************************
///
/// Example taken from fig. 22 in [1]
///
/// [1] M. Latapy, T. Viard, C. Magnien,
///     Stream Graphs and Link Streams for the Modeling of Interactions over Time, 2018.
///     https://arxiv.org/pdf/1710.04073.pdf
///
///*********************************************************************************************************************
BOOST_AUTO_TEST_CASE(BiLinStream_test_projection)
{
    // with initial definition interval
    BiLinkStream g(0, 10);
    g.add_vertex_w_group(vertex_group::top, "a");
    g.add_vertex_w_group(vertex_group::top, "b");
    g.add_vertex_w_group(vertex_group::top, "c");
    g.add_vertex_w_group(vertex_group::bottom, "u");
    g.add_vertex_w_group(vertex_group::bottom, "v");

    g.add_edge_w_time("u", "a", 0, 2);
    g.add_edge_w_time("u", "a", 3, 9);

    g.add_edge_w_time("u", "b", 4, 5);
    g.add_edge_w_time("u", "b", 8, 10);

    g.add_edge_w_time("u", "c", 1, 5);

    g.add_edge_w_time("v", "b", 2, 7);

    g.add_edge_w_time("v", "c", 0, 8);

    //g.print_edges();

    LinkStream gproj;
    projected_graph(vertex_group::top, g, gproj);
    std::cout << gproj ;
}