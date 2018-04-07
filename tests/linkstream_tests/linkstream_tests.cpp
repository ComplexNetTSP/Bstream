//
// Created by Vincent Gauthier on 06/04/2018.
//

#include "GraphType.hpp"

#define BOOST_TEST_MODULE LinkStreamBase_tests

#include <boost/test/included/unit_test.hpp>
#include <memory>

using namespace std;
using namespace boost;
using namespace boost::bstream;

BOOST_AUTO_TEST_CASE(linkstream_constructor)
{
    // build undirected graph
    LinkStream g;
    BOOST_CHECK(g.is_directed() == false);
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

BOOST_AUTO_TEST_CASE(linkstream_add_edge)
{
    LinkStream::vertex_t a=0, b=1, c=2, d=3;
    LinkStream g(4, 0, 10);
    g.add_edge(a, b, 0, 4);
    g.add_edge(a, b, 6, 9);
    g.add_edge(a, c, 2, 5);
    g.add_edge(b, c, 1, 8);
    g.add_edge(b, d, 7, 10);
    g.add_edge(c, d, 6, 9);

    g.print_edges();
}

BOOST_AUTO_TEST_CASE(linkstream_exception)
{
    LinkStream::vertex_t a=0, b=1;
    LinkStream g(4, 0, 10);
    BOOST_CHECK_THROW( g.add_edge(a, b, 0, 13), LinkStreamException);
}