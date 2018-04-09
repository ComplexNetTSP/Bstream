///-------------------------------------------------------------------------------------------------
///
/// @file       linkstream_tests.cpp
/// @brief      Tests for the LinkStreamBase class
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       08/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#include "GraphType.hpp"
#include "CSVReader.hpp"

#define BOOST_TEST_MODULE LinkStreamBase_tests

#include <boost/test/included/unit_test.hpp>
#include <memory>

using namespace boost::bstream;
using namespace std;
using namespace boost::icl;

BOOST_AUTO_TEST_CASE(LinkStream_constructor)
{
    // build undirected graph
    LinkStream g;
    BOOST_CHECK(!g.is_directed());
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);

    LinkStream g1(100);
    BOOST_CHECK(g1.num_vertices() == 100);

    auto v_iterator = g1.vertices();
    unsigned i = 0;
    for(auto it = v_iterator.first; it != v_iterator.second; ++it)
        BOOST_CHECK(*it == i++);

    LinkStream g2(100, 0, 10);
    BOOST_CHECK(g2.num_vertices() == 100);
    BOOST_CHECK(g2.definition().first == 0);
    BOOST_CHECK(g2.definition().second == 10);
}

BOOST_AUTO_TEST_CASE(LinkStream_add_edge)
{
    LinkStream::vertex_t a=0, b=1, c=2, d=3;
    LinkStream g(4, 0, 10);
    g.add_edge(a, b, 0, 4);
    g.add_edge(a, b, 6, 9);
    g.add_edge(a, c, 2, 5);
    g.add_edge(b, c, 1, 8);
    g.add_edge(b, d, 7, 10);
    g.add_edge(c, d, 6, 9);
}

BOOST_AUTO_TEST_CASE(LinkStream_exception)
{
    LinkStream::vertex_t a=0, b=1;
    LinkStream g(4, 0, 10);
    BOOST_CHECK_THROW( g.add_edge(a, b, 0, 13), LinkStreamException);
}


BOOST_AUTO_TEST_CASE(LinkStream_read_edgefile)
{
    auto cvs = CSVReader(',', "#");
    auto L = cvs.read_linkstream("./edges.csv");

    BOOST_CHECK_THROW(cvs.read_linkstream("./xxxx.csv"), CSVReaderException);
}


BOOST_AUTO_TEST_CASE(LinkStream_is_active)
{
    LinkStream g(0, 10);
    auto a = g.add_vertex("A");
    auto b = g.add_vertex("B");
    auto c = g.add_vertex("C");
    auto d = g.add_vertex("D");
    g.add_edge(a, b, 0, 4);
    g.add_edge(a, b, 6, 9);
    g.add_edge(a, c, 2, 5);
    g.add_edge(b, c, 1, 8);
    g.add_edge(b, d, 7, 10);
    g.add_edge(c, d, 6, 9);

    BOOST_CHECK(g.is_edge_active(a, b, 7, 8).second);
    BOOST_CHECK(g.is_edge_active(a, b, 1, 2).second);
    BOOST_CHECK(!g.is_edge_active(a, b, 7, 15).second);
}

///*********************************************************************************************************************
///
/// Example taken from fig. 5 in [1]
///
/// [1] M. Latapy, T. Viard, C. Magnien,
///     Stream Graphs and Link Streams for the Modeling of Interactions over Time, 2018.
///     https://arxiv.org/pdf/1710.04073.pdf
///
///*********************************************************************************************************************
BOOST_AUTO_TEST_CASE(LinkStream_degree)
{
    LinkStream L(0, 10);
    auto a = L.add_vertex("A");
    auto b = L.add_vertex("B");
    auto c = L.add_vertex("C");
    auto d = L.add_vertex("D");
    L.add_edge(a, b, 0, 4);
    L.add_edge(a, b, 6, 9);
    L.add_edge(b, d, 7, 10);

    L.add_edge(b, c, 1, 8);
    L.add_edge(a, c, 2, 5);
    L.add_edge(d, c, 6, 9);

    //L.print_edges();

    // check the handshaking lemma
    BOOST_CHECK(L.degree(c) == 1.3);
    double sum_degree = 0;
    for(auto it = L.vertices().first; it!= L.vertices().second; ++it)
        sum_degree += L.degree(*it);
    BOOST_CHECK(sum_degree == 2 * L.num_edges());
}

BOOST_AUTO_TEST_CASE(LinkStream_handshaking_lemma)
{
    LinkStream L(0, 10);
    auto a = L.add_vertex("A");
    auto b = L.add_vertex("B");
    auto c = L.add_vertex("C");
    auto d = L.add_vertex("D");
    L.add_edge(a, b, 0, 10);
    L.add_edge(a, b, 0, 10);
    L.add_edge(b, d, 0, 10);

    L.add_edge(b, c, 0, 10);
    L.add_edge(a, c, 0, 10);
    L.add_edge(d, c, 0, 10);

    // check the handshaking lemma
    double sum_degree = 0;
    for(auto it = L.vertices().first; it!= L.vertices().second; ++it)
        sum_degree += L.degree(*it);
    BOOST_CHECK(sum_degree == 2 * L.num_edges());
}