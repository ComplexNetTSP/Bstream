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

#define BOOST_TEST_MODULE BGraph_tests

#include <boost/test/included/unit_test.hpp>
#include <memory>

using namespace std;
using namespace boost;
using namespace boost::bstream;

BOOST_AUTO_TEST_CASE(generate_undirected_graph)
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


BOOST_AUTO_TEST_CASE(generate_directed_graph)
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


BOOST_AUTO_TEST_CASE(add_vertex_directed_graph){
    // build undirected graph
    DiGraph g;
    g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 1);
    //auto vp1 = g.vertex_properties(v1);
    //BOOST_CHECK(vp1.id == 0);
    g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 2);
    //auto vp2 = g.vertex_properties(v2);
    //BOOST_CHECK(vp2.id == 1);
}

BOOST_AUTO_TEST_CASE(add_vertex_undirected_graph){
    // build undirected graph
    Graph g;
    g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 1);
    //auto vp1 = g.vertex_properties(v1);
    //BOOST_CHECK(vp1.id == 0);
    g.add_vertex();
    BOOST_CHECK(g.num_vertices() == 2);
    //auto vp2 = g.vertex_properties(v2);
    //BOOST_CHECK(vp2.id == 1);
}

BOOST_AUTO_TEST_CASE(add_edge_undirected_graph){
    // build undirected graph
    Graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    g.add_vertex();
    g.add_edge(v1, v2);
    BOOST_CHECK(g.has_edge(v1, v2));
    BOOST_CHECK(g.has_edge(v2, v1));
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 2);
}

BOOST_AUTO_TEST_CASE(add_edge_directed_graph){
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

BOOST_AUTO_TEST_CASE(remove_vertex_undirected_graph){
    // build undirected graph
    Graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();
    g.add_edge(v1, v2);
    g.add_edge(v2, v3);
    g.add_edge(v3, v1);
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 6);

    g.remove_vertex(v1);
    BOOST_CHECK(g.num_vertices() == 2);
    BOOST_CHECK(g.num_edges() == 2);

}

BOOST_AUTO_TEST_CASE(remove_vertex_directed_graph){
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


BOOST_AUTO_TEST_CASE(degree_directed_graph)
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
}

BOOST_AUTO_TEST_CASE(degree_undirected_graph)
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
}


BOOST_AUTO_TEST_CASE(undirected_remove_edge)
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
    BOOST_CHECK(g.num_edges() == 6);
    g.remove_edge(v1, v2);
    BOOST_CHECK(g.num_vertices() == 3);
    BOOST_CHECK(g.num_edges() == 4);
}

BOOST_AUTO_TEST_CASE(directed_remove_edge)
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
    BOOST_CHECK(g.vertex_name(v4).empty());
}