//
// Created by Vincent Gauthier on 27/03/2018.
//

#ifndef BSTREAM_GRAPH_TYPE_H
#define BSTREAM_GRAPH_TYPE_H

#include <boost/graph/detail/edge.hpp>

#include "BaseGraph.hpp"

namespace boost::bstream
{
    typedef BaseGraph<undirectedS> Graph;
    typedef BaseGraph<bidirectionalS> DiGraph;
} // end namespace boost::src

#endif //BSTREAM_GRAPH_TYPE_H
