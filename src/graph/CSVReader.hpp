//
// Created by Vincent Gauthier on 07/04/2018.
//

#ifndef BSTREAM_TSVREADER_HPP
#define BSTREAM_TSVREADER_HPP

#include <string>
#include <map>
#include <stdexcept>
#include <boost/graph/detail/edge.hpp>

#include "GraphType.hpp"

namespace boost::bstream
{
    class CSVReaderException: public std::runtime_error
    {
    public:
        CSVReaderException(const std::string& what): std::runtime_error(what) {};
    };

    /**
     * @class   CSVReader
     * @brief   Class definition that enable to read edge files.
     */
    class CSVReader
    {
    private:
        std::string commentPrefix;
        char delimiter;
        bool isDirected;
    public:
        /**
         * @brief   Initialize a CSVReader.
         * @param   commentPrefix Character use define a comment in the edge file.
         * @param   delimiter Character use to delimit a fields in the edge file.
         */
        CSVReader(std::string commentPrefix="#", char delimiter=',')
                :commentPrefix(commentPrefix), delimiter(delimiter) {}

        /**
         * @brief   Read a edge file.
         * @param   path File path of the edge file to be read.
         * @return  Graph
         */
        LinkStream read_undirected(const std::string &path);

        DiLinkStream read_directed(const std::string &path);
    };

} // end namspace boost::bstream


#endif //BSTREAM_TSVREADER_HPP
