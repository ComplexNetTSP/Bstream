///-------------------------------------------------------------------------------------------------
///
/// @file       graph_tests.cpp
/// @brief      Tests for the Graph clas
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       05/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#include "GraphType.hpp"
#include "bipartite.hpp"
#include <boost/graph/detail/edge.hpp>

#define BOOST_TEST_MODULE BGraph_tests

#include <boost/test/included/unit_test.hpp>
#include <memory>

using namespace std;
using namespace boost;
using namespace boost::bstream;

BOOST_AUTO_TEST_CASE(GraphBase_undirected_constructor)
{
    // build undirected graph
    Graph g;
    BOOST_CHECK(g.is_directed() == false);
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);

    Graph g1(100);
    BOOST_CHECK(g1.num_vertices() == 100);

    auto v_iterator = g1.vertices();
    unsigned i = 0;
    for(auto it = v_iterator.first; it != v_iterator.second; ++it)
        BOOST_CHECK(*it == i++);
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
    BOOST_CHECK(g.has_vertex(10) == false);

    g.add_edge(a, b);
    g.add_edge(b, c);
    g.add_edge(c, a);

    Graph gprime(g);
    BOOST_CHECK(gprime.num_vertices() == g.num_vertices());
    BOOST_CHECK(gprime.num_edges() == g.num_edges());
    for(auto it = g.vertices().first; it != g.vertices().second; ++it)
        BOOST_CHECK(g.vertex_name(*it) == gprime.vertex_name(*it));
}


BOOST_AUTO_TEST_CASE(GraphBase_directed_constructor)
{
    // build directed graph
    DiGraph g;
    BOOST_CHECK(g.is_directed());
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);

    DiGraph g1(100);
    BOOST_CHECK(g1.num_vertices() == 100);

    auto v_iterator = g1.vertices();
    unsigned i = 0;
    for(auto it = v_iterator.first; it != v_iterator.second; ++it)
        BOOST_CHECK(*it == i++);
}

BOOST_AUTO_TEST_CASE(GraphBase_add_edges)
{
    // build undirected graph
    Graph g;
    BOOST_CHECK(g.is_directed() == false);
    BOOST_CHECK(g.num_vertices() == 0);
    BOOST_CHECK(g.num_edges() == 0);

    g.add_edge(2, 3);
    g.add_edge(10, 5);
    BOOST_CHECK(g.num_vertices() == 2);
    BOOST_CHECK(g.num_edges() == 2);
}


BOOST_AUTO_TEST_CASE(GraphBase_directed_add_vertex){
    // build undirected graph
    DiGraph g;
    g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 1);
    g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 2);
}

BOOST_AUTO_TEST_CASE(GraphBase_undirected_add_vertex){
    // build undirected graph
    Graph g;
    g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 1);
    g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 2);
}

BOOST_AUTO_TEST_CASE(GraphBase_undirected_add_edge){
    // build undirected graph
    Graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    g.add_vertex();
    g.add_edge(v1, v2);
    BOOST_CHECK(g.has_edge(v1, v2));
    BOOST_CHECK(g.has_edge(v2, v1));
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 1);
}

BOOST_AUTO_TEST_CASE(GraphBase_directed_add_edge){
    // build directed graph
    DiGraph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    g.add_vertex();
    g.add_edge(v1, v2);
    BOOST_CHECK(g.has_edge(v1, v2));
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 1);
}

BOOST_AUTO_TEST_CASE(GraphBase_undirected_remove_vertex){
    // build undirected graph
    Graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();
    g.add_edge(v1, v2);
    g.add_edge(v2, v3);
    g.add_edge(v3, v1);
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 3);

    g.remove_vertex(v1);
    BOOST_CHECK(g.has_vertex(v1) == false);
    BOOST_CHECK(g.num_vertices() == 2);
    BOOST_CHECK(g.num_edges() == 1);

}

BOOST_AUTO_TEST_CASE(GraphBase_directed_remove_vertex){
    // build directed graph
    DiGraph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();
    g.add_edge(v1, v2);
    g.add_edge(v2, v3);
    g.add_edge(v3, v1);
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 3);

    g.remove_vertex(v1);
    BOOST_CHECK(g.num_vertices() == 2);
    BOOST_CHECK(g.num_edges() == 1);

}

BOOST_AUTO_TEST_CASE(GraphBase_directed_degree)
{
    // build directed graph
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

BOOST_AUTO_TEST_CASE(GraphBase_undirected_degree)
{
    // build undirected graph
    Graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();
    g.add_edge(v1, v2);
    g.add_edge(v2, v3);
    g.add_edge(v3, v1);
    BOOST_CHECK(g.out_degree(v1) == 2);
    BOOST_CHECK(g.in_degree(v1) == 2);
    BOOST_CHECK(g.degree(v1) == 2);

    // check the handshaking lemma
    double sum_degree = 0;
    for(auto it = g.vertices().first; it!= g.vertices().second; ++it)
        sum_degree += g.degree(*it);
    BOOST_CHECK(sum_degree == 2 * g.num_edges());
}

BOOST_AUTO_TEST_CASE(GraphBase_undirected_remove_edge)
{
    // build undirected graph
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
}

BOOST_AUTO_TEST_CASE(GraphBase_directed_remove_edge)
{
    // build directed graph
    DiGraph g;
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
}

BOOST_AUTO_TEST_CASE(GraphBase_add_vertex_with_name)
{
    Graph g;
    auto v1 = g.add_vertex("A");
    auto v2 = g.add_vertex("B");
    auto v3 = g.add_vertex("C");
    auto v4 = g.add_vertex();
    BOOST_CHECK(g.vertex_name(v1) == "A");
    BOOST_CHECK(g.vertex_name(v2) == "B");
    BOOST_CHECK(g.vertex_name(v3) == "C");
    BOOST_CHECK(g.vertex_name(v4) == "3");
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

*/
/*
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