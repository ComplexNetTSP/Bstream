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
    for (auto it = v_iterator.first; it != v_iterator.second; ++it)
        BOOST_CHECK(*it == i++);

    LinkStream g2(100, 0, 10);
    BOOST_CHECK(g2.num_vertices() == 100);
    BOOST_CHECK(g2.definition().first == 0);
    BOOST_CHECK(g2.definition().second == 10);
}

BOOST_AUTO_TEST_CASE(LinkStream_neighbors)
{
    LinkStream g(0, 10);
    auto a = g.add_vertex("A");
    auto b = g.add_vertex("B");
    auto c = g.add_vertex("C");
    g.add_edge_w_time(a, b, 0, 10);
    g.add_edge_w_time(b, c, 0, 10);
    g.add_edge_w_time(c, a, 0, 10);

    auto cpt = 0;
    for (auto it = g.neighbors("A").first; it != g.neighbors("A").second; ++it) {
        cpt++;
    }
    BOOST_CHECK(cpt == 2);

    cpt = 0;
    for (auto it = g.neighbors(a).first; it != g.neighbors(a).second; ++it) {
        cpt++;
    }

    BOOST_CHECK(cpt == 2);
}

BOOST_AUTO_TEST_CASE(LinkStream_remove_vertex)
{
    LinkStream g(0, 10);
    auto a = g.add_vertex("A");
    auto b = g.add_vertex("B");
    auto c = g.add_vertex("C");
    g.add_edge_w_time(a, b, 0, 10);
    g.add_edge_w_time(b, c, 0, 10);
    g.add_edge_w_time(c, a, 0, 10);
    g.remove_vertex("A");

    BOOST_CHECK(g.num_vertices() == 2);
    BOOST_CHECK(g.num_edges() == 1);

    BOOST_CHECK_THROW(g.edge_tinterval_set("A", "B"), boost::bstream::LinkStreamBaseException);
}

BOOST_AUTO_TEST_CASE(LinkStream_add_edge_simple)
{
    LinkStream::vertex_t a = 0, b = 1, c = 2, d = 3;
    LinkStream g(4, 0, 10);

    g.add_edge(a, b);
    g.add_edge(a, c);
    g.add_edge(b, c);
    g.add_edge(b, d);
    g.add_edge(c, d);

    BOOST_CHECK(g.num_vertices() == 4);
}

BOOST_AUTO_TEST_CASE(LinkStream_add_edge)
{
    LinkStream::vertex_t a = 0, b = 1, c = 2, d = 3;
    LinkStream g(4, 0, 10);
    g.add_edge_w_time(a, b, 0, 4);
    g.add_edge_w_time(a, b, 6, 9);
    g.add_edge_w_time(a, c, 2, 5);
    g.add_edge_w_time(b, c, 1, 8);
    g.add_edge_w_time(b, d, 7, 10);
    g.add_edge_w_time(c, d, 6, 9);
}

BOOST_AUTO_TEST_CASE(LinkStream_exception)
{
    LinkStream::vertex_t a = 0, b = 1;
    LinkStream g(4, 0, 10);
    BOOST_CHECK_THROW(g.add_edge_w_time(a, b, 0, 13), LinkStreamException);
}

BOOST_AUTO_TEST_CASE(LinkStream_read_edgefile)
{
    LinkStream g;
    g.read_csv("./edges.csv");
    BOOST_CHECK(g.num_vertices() == 4);
    auto def = g.definition();
    BOOST_CHECK(def.first == 0);
    BOOST_CHECK(def.second == 10);
    BOOST_CHECK(g.num_edges() == 2.3);
}


BOOST_AUTO_TEST_CASE(LinkStream_is_active)
{
    LinkStream g(0, 10);
    auto a = g.add_vertex("A");
    auto b = g.add_vertex("B");
    auto c = g.add_vertex("C");
    auto d = g.add_vertex("D");
    g.add_edge_w_time(a, b, 0, 4);
    g.add_edge_w_time(a, b, 6, 9);
    g.add_edge_w_time(a, c, 2, 5);
    g.add_edge_w_time(b, c, 1, 8);
    g.add_edge_w_time(b, d, 7, 10);
    g.add_edge_w_time(c, d, 6, 9);

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
    L.add_edge_w_time(a, b, 0, 4);
    L.add_edge_w_time(a, b, 6, 9);
    L.add_edge_w_time(b, d, 7, 10);

    L.add_edge_w_time(b, c, 1, 8);
    L.add_edge_w_time(a, c, 2, 5);
    L.add_edge_w_time(d, c, 6, 9);

    ///< check the handshaking lemma
    BOOST_CHECK(L.degree(c) == 1.3);
    double sum_degree = 0;
    for (auto it = L.vertices().first; it != L.vertices().second; ++it)
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
    L.add_edge_w_time(a, b, 0, 10);
    L.add_edge_w_time(a, b, 0, 10);
    L.add_edge_w_time(b, d, 0, 10);

    L.add_edge_w_time(b, c, 0, 10);
    L.add_edge_w_time(a, c, 0, 10);
    L.add_edge_w_time(d, c, 0, 10);

    // check the handshaking lemma
    double sum_degree = 0;
    for (auto it = L.vertices().first; it != L.vertices().second; ++it)
        sum_degree += L.degree(*it);
    BOOST_CHECK(sum_degree == 2 * L.num_edges());
}

///*********************************************************************************************************************
///
/// Example taken from eq 2.6 in [1]
///
/// [1] Noe GAUMONT
///     GROUPES ET COMMUNAUTES DANS LES FLOTS DE LIENS: DES DONNEES AUX ALGORITHMES
///     http://www.complexnetworks.fr/wp-content/uploads/2016/11/These_Noe.pdf
///
///*********************************************************************************************************************
BOOST_AUTO_TEST_CASE(LinkStream_density)
{
    LinkStream L(0, 10);
    auto a = L.add_vertex("A");
    auto b = L.add_vertex("B");
    auto c = L.add_vertex("C");
    L.add_edge_w_time(a, b, 0, 10);
    L.add_edge_w_time(b, c, 0, 10);
    L.add_edge_w_time(c, a, 0, 10);
    auto d = 2 * L.num_edges() / (L.num_vertices() * (L.num_vertices() - 1));
    BOOST_CHECK(L.density() == d); // 1

    LinkStream LL(0, 10);
    auto aa = LL.add_vertex("A");
    auto bb = LL.add_vertex("B");
    auto cc = LL.add_vertex("C");
    LL.add_edge_w_time(aa, bb, 0, 5);
    LL.add_edge_w_time(bb, cc, 0, 5);
    LL.add_edge_w_time(cc, aa, 0, 5);
    auto density = 2 * LL.num_edges() / (LL.num_vertices() * (LL.num_vertices() - 1));
    BOOST_CHECK(LL.density() == density); // 0.5
}


BOOST_AUTO_TEST_CASE(LinkStream_add_edge_with_timeintervalset)
{
    LinkStream L(0, 10);
    TimeIntervalSet t1(0, 10);
    t1.append(0, 2);
    t1.append(3, 5);

    TimeIntervalSet t2(0, 10);
    t2.append(6, 7);
    t2.append(8, 10);

    auto e1 = L.add_edge_w_time("A", "B", t1);
    auto e1_prime = L.add_edge_w_time("A", "B", t2);
    BOOST_CHECK(e1 == e1_prime);
    BOOST_CHECK(L.edge_tinterval_set("A", "B").length() == 7);
    BOOST_CHECK(L.edge_tinterval_set(e1).length() == 7);

    auto def = L.edge_tinterval_set(e1).definition();
    BOOST_CHECK(def.first == 0);
    BOOST_CHECK(def.second == 10);
}