///-------------------------------------------------------------------------------------------------
///
/// @file       algorithms_tests.cpp
/// @brief      Test file forall the algorithms definied
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       14/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------

#include "GraphType.hpp"
#include "generators/erdos_reny.hpp"

#define BOOST_TEST_MODULE Algorithms_tests

#include <boost/test/included/unit_test.hpp>

using namespace boost::bstream;
using namespace std;

//todo enhance the test case

BOOST_AUTO_TEST_CASE(Algorithms_erdos_reny)
{
    int seed = 11;
    Graph g;
    erdos_renyi_graph(10000, 0.0002, g, seed);
    BOOST_CHECK(g.num_vertices() == 10000);

    DiGraph d;
    erdos_renyi_graph(100, 0.02, d, seed);
    BOOST_CHECK(d.num_vertices() == 100);
    BOOST_CHECK(d.num_edges() == 199);
}

//todo: add test with more complex example with time_t variable