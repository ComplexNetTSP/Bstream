//
// Created by Vincent Gauthier on 07/04/2018.
//

#ifndef BSTREAM_GRAPHIO_HPP
#define BSTREAM_GRAPHIO_HPP

#include <iostream>

#include "GraphType.hpp"

namespace boost::bstream
{
    //todo implement the readfile for tsv file
    LinkStream read_tsv(std::string path);
}
#endif //BSTREAM_GRAPHIO_HPP
