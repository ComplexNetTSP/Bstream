///-------------------------------------------------------------------------------------------------
///
/// @file       graph_tests.cpp
/// @brief      Tests for the Graph class
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       05/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#include <Eigen/Core>
#include "GraphType.hpp"

#define BOOST_TEST_MODULE GraphBase_tests

#include <boost/test/included/unit_test.hpp>

using namespace std;
using namespace boost;
using namespace boost::bstream;
using Eigen::MatrixXd;

BOOST_AUTO_TEST_CASE(GraphBase_constructor)
{
    // build undirected graph
    Graph g;
    BOOST_CHECK(g.is_directed() == false);
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);
}

BOOST_AUTO_TEST_CASE(GraphBase_constructor_bulk)
{
    Graph g(10);
    BOOST_CHECK(g.num_vertices() == 10);
    BOOST_CHECK(g.num_edges() == 0);

    int i = 0;
    for(auto it=g.vertices().first; it!=g.vertices().second; ++it) {
        BOOST_CHECK(g.label(*it) == to_string(i));
        i++;
    }
}


BOOST_AUTO_TEST_CASE(GraphBase_add_vertex)
{
    Graph g;
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);

    auto v1 = g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 1);
    BOOST_CHECK(g.label(v1) == "0");
    BOOST_CHECK(g.vertex("0") == v1);
    BOOST_CHECK(g.has_vertex(v1));
    BOOST_CHECK(g.has_vertex("0"));

    auto v2 = g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 2);
    BOOST_CHECK(g.label(v2) == "1");
    BOOST_CHECK(g.vertex("1") == v2);
    BOOST_CHECK(g.has_vertex(v2));
    BOOST_CHECK(g.has_vertex("1"));
}


BOOST_AUTO_TEST_CASE(GraphBase_remove_vertex)
{
    Graph g;
    g.add_vertex("A");
    g.add_vertex("B");
    BOOST_CHECK(g.num_vertices() == 2);

    g.remove_vertex("A");
    BOOST_CHECK(g.num_vertices() == 1);

    g.remove_vertex("B");
    BOOST_CHECK(g.num_vertices() == 0);
}



BOOST_AUTO_TEST_CASE(GraphBase_add_edge){
    Graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    g.add_edge(v1, v2);

    BOOST_CHECK(g.has_edge(v1, v2));
    BOOST_CHECK(g.has_edge(v2, v1));
    BOOST_CHECK(g.num_vertices() == 2);
    BOOST_CHECK(g.num_edges() == 1);
}


BOOST_AUTO_TEST_CASE(GraphBase_add_edge_bis){
    Graph g;

    g.add_edge("A", "B");
    BOOST_CHECK(g.num_vertices() == 2);
    BOOST_CHECK(g.num_edges() == 1);

    g.add_edge("A", "C");
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 2);

    g.add_edge("B", "C");
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 3);
}

BOOST_AUTO_TEST_CASE(GraphBase_remove_edge_by_vertex_desc)
{
    Graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v1, v2);
    g.add_edge(v2, v3);
    g.add_edge(v3, v1);
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 3);

    g.remove_edge(v1, v2);
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 2);

    g.remove_edge(v3, v1);
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 1);

    g.remove_edge(v2, v3);
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 0);

}

BOOST_AUTO_TEST_CASE(GraphBase_remove_edge_by_name)
{
    Graph g;

    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");

    g.add_edge("A", "B");
    g.add_edge("B", "C");
    g.add_edge("C", "A");
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 3);

    g.remove_edge("A", "B");
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 2);

    g.remove_edge("A", "C");
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 1);

    g.remove_edge("B", "C");
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 0);
}

BOOST_AUTO_TEST_CASE(GraphBase_density)
{
    Graph g;
    auto a = g.add_vertex("a");
    auto b = g.add_vertex("b");
    auto c = g.add_vertex("c");
    g.add_edge(a, b);
    g.add_edge(b, c);
    g.add_edge(c, a);

    BOOST_CHECK(g.density() == 1);

    DiGraph ug;
    auto d = ug.add_vertex("a");
    auto e = ug.add_vertex("b");
    auto f = ug.add_vertex("c");
    ug.add_edge(d, e);
    ug.add_edge(e, f);
    ug.add_edge(f, d);

    BOOST_CHECK(ug.density() == 0.5);
}

BOOST_AUTO_TEST_CASE(GraphBase_degree)
{
    DiGraph g;

    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v1, v2);
    g.add_edge(v2, v3);
    g.add_edge(v3, v1);

    BOOST_CHECK(g.out_degree(v1) == 1);
    BOOST_CHECK(g.in_degree(v1) == 1);
    BOOST_CHECK(g.degree(v1) == 2);

    // check the handshaking lemma
    double sum_degree = 0;
    for(auto it = g.vertices().first; it!= g.vertices().second; ++it)
        sum_degree += g.degree(*it);
    BOOST_CHECK(sum_degree == 2 * g.num_edges());
}

BOOST_AUTO_TEST_CASE(GraphBase_degree_by_name)
{
    DiGraph g;

    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");

    g.add_edge("A", "B");
    g.add_edge("B", "C");
    g.add_edge("C", "A");

    BOOST_CHECK(g.out_degree("A") == 1);
    BOOST_CHECK(g.in_degree("A") == 1);
    BOOST_CHECK(g.degree("A") == 2);

    // check the handshaking lemma
    double sum_degree = 0;
    for(auto it = g.vertices().first; it!= g.vertices().second; ++it)
        sum_degree += g.degree(*it);
    BOOST_CHECK(sum_degree == 2 * g.num_edges());
}

BOOST_AUTO_TEST_CASE(GraphBase_has_edge)
{
    Graph g;
    auto v1 = g.add_vertex("A");
    auto v2 = g.add_vertex("B");
    g.add_vertex("C");

    g.add_edge("A", "B");
    g.add_edge("B", "C");
    g.add_edge("C", "A");

    BOOST_CHECK(g.has_edge("A", "B"));
    BOOST_CHECK(g.has_edge(v1, v2));
}

BOOST_AUTO_TEST_CASE(GraphBase_copy_constructor)
{
    Graph g;
    auto a = g.add_vertex("a");
    auto b = g.add_vertex("b");
    auto c = g.add_vertex("c");

    BOOST_CHECK(g.has_vertex(a) == true);
    BOOST_CHECK(g.has_vertex(b) == true);
    BOOST_CHECK(g.has_vertex(c) == true);

    g.add_edge(a, b);
    g.add_edge(b, c);
    g.add_edge(c, a);

    Graph gprime = g;
    BOOST_CHECK(gprime.num_vertices() == g.num_vertices());
    BOOST_CHECK(gprime.num_edges() == g.num_edges());

    for(auto it = g.vertices().first; it != g.vertices().second; ++it)
        BOOST_CHECK(g.label(*it) == gprime.label(*it));

    auto vprime = gprime.add_vertex("d");
    auto v = g.add_vertex("d");
    BOOST_CHECK(vprime == v);
}

BOOST_AUTO_TEST_CASE(GraphBase_clear_vertices)
{
    Graph g;

    g.add_edge("A", "B");
    g.add_edge("B", "C");
    g.add_edge("C", "A");

    g.clear_vertices();
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);
}

BOOST_AUTO_TEST_CASE(GraphBase_neighbors)
{
    Graph g;

    g.add_edge("A", "B");
    g.add_edge("B", "C");
    g.add_edge("C", "A");

    std::vector<std::string> res = {"B", "C"};
    auto res_it = res.begin();

    for(auto it=g.neighbors("A").first; it!=g.neighbors("A").second; ++it){
        BOOST_CHECK(g.label(*it) == *res_it);
        res_it++;
    }
}

BOOST_AUTO_TEST_CASE(GraphBase_clear_edges)
{
    Graph g;
    auto a = g.add_vertex("a");
    auto b = g.add_vertex("b");
    auto c = g.add_vertex("c");
    g.add_edge(a, b);
    g.add_edge(b, c);
    g.add_edge(c, a);
    BOOST_CHECK(g.num_edges() == 3);
    g.clear_edges();
    BOOST_CHECK(g.num_edges() == 0);
}

BOOST_AUTO_TEST_CASE(GraphBase_adjacency)
{
    Graph u;
    auto a = u.add_vertex("a");
    auto b = u.add_vertex("b");
    auto c = u.add_vertex("c");
    u.add_edge(a, b);
    u.add_edge(b, c);
    u.add_edge(c, a);

    MatrixXd m(3,3);
    m(0,0) = 0;
    m(0,1) = 1;
    m(0,2) = 1;

    m(1,0) = 1;
    m(1,1) = 0;
    m(1,2) = 1;

    m(2,0) = 1;
    m(2,1) = 1;
    m(2,2) = 0;
    BOOST_CHECK(u.adjacency() == m);

    DiGraph d;
    a = d.add_vertex("a");
    b = d.add_vertex("b");
    c = d.add_vertex("c");
    d.add_edge(a, b);
    d.add_edge(b, c);
    d.add_edge(c, a);

    MatrixXd m1(3,3);
    m1(0,0) = 0;
    m1(0,1) = 1;
    m1(0,2) = 0;

    m1(1,0) = 0;
    m1(1,1) = 0;
    m1(1,2) = 1;

    m1(2,0) = 1;
    m1(2,1) = 0;
    m1(2,2) = 0;
    BOOST_CHECK(d.adjacency() == m1);
}