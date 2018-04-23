//
// Created by Vincent Gauthier on 07/04/2018.
//
#include <fstream>
#include <iostream>
#include <ctime>
#include <limits>

#include "CSVReader.hpp"
#include "utils.hpp"
#include "GraphType.hpp"

namespace boost::bstream
{
    std::vector<std::vector<std::string>>
    CSVReader::read(const std::string &path)
    {
        std::string line;
        std::ifstream file(path, std::ios::in);
        std::vector<std::vector<std::string>> nodeIds;

        if (file.fail())
            throw CSVReaderException("Could not open file");

        while(!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                if (line.compare(0, this->commentPrefix.length(), this->commentPrefix) != 0){
                    auto tokens = split(line, this->delimiter);
                    if (tokens.size() >= 2) {
                        nodeIds.push_back(tokens);
                    }else{
                        throw CSVReaderException("Corrupted CVS file");
                    }
                }
            }
        }
        return nodeIds;
    }
}

