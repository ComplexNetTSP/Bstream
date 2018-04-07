//
// Created by Vincent Gauthier on 27/03/2018.
//

#ifndef BSTREAM_GRAPH_TYPE_H
#define BSTREAM_GRAPH_TYPE_H

#include <boost/graph/detail/edge.hpp>

#include "GraphBase.hpp"
#include "LinkStreamBase.hpp"

namespace boost::bstream
{
    typedef LinkStreamBaseException LinkStreamException;
    typedef LinkStreamBaseException DiLinkStreamException;
    typedef GraphBase<undirectedS> Graph;
    typedef GraphBase<bidirectionalS> DiGraph;
    typedef LinkStreamBase<undirectedS> LinkStream;
    typedef LinkStreamBase<bidirectionalS> DiLinkStream;
} // end namespace boost::src

#endif //BSTREAM_GRAPH_TYPE_H
