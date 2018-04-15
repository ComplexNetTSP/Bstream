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
    LinkStream CSVReader::read_linkstream(const std::string &path)
    {
        int lineCount = 0;
        std::string line;
        int consecutiveID = 0;
        std::ifstream file(path, std::ios::in);
        std::map<std::string, LinkStream::vertex_t> mapNodeIds;
        time_t tmin=std::numeric_limits<time_t>::max(), tmax=0;

        if (file.fail())
            throw CSVReaderException("Could not open file");

        // first pass create the vertices
        while(!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                if (line.compare(0, this->commentPrefix.length(), this->commentPrefix) != 0) {
                    ++lineCount;
                    auto tokens = split(line);
                    if (tokens.size() == 4) {
                        if(mapNodeIds.insert(std::make_pair(tokens[0], consecutiveID)).second)
                            consecutiveID++;
                        if(mapNodeIds.insert(std::make_pair(tokens[1], consecutiveID)).second)
                            consecutiveID++;
                        if(std::stoi(tokens[2]) < tmin)
                            tmin = std::stoi(tokens[2]);
                        if(std::stoi(tokens[3]) > tmax)
                            tmax = std::stoi(tokens[3]);
                    } else {
                        throw CSVReaderException("Unsupported file format");
                    }
                }
            }
        }

        auto G = LinkStream(static_cast<int>(mapNodeIds.size()), tmin, tmax);

        // second pass create the edges
        file.clear();
        file.seekg(0, std::ios::beg);

        while(!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                if (line.compare(0, this->commentPrefix.length(), this->commentPrefix) != 0){
                    auto tokens = split(line, this->delimiter);
                    if (tokens.size() == 4) {
                        auto u = mapNodeIds[tokens[0]];
                        auto v = mapNodeIds[tokens[1]];
                        auto b = std::stoi(tokens[2]);
                        auto e = std::stoi(tokens[3]);
                        G.add_edge_w_time(u, v, b, e);
                    }
                }
            }
        }
        return G;
    }

    DiLinkStream CSVReader::read_dilinkstream(const std::string &path)
    {
        int lineCount = 0;
        std::string line;
        int consecutiveID = 0;
        std::ifstream file(path, std::ios::in);
        std::map<std::string, LinkStream::vertex_t> mapNodeIds;
        time_t tmin=std::numeric_limits<time_t>::max(), tmax=0;

        if (file.fail())
            throw CSVReaderException("Could not open file");

        // first pass create the vertices
        while(!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                if (line.compare(0, this->commentPrefix.length(), this->commentPrefix) != 0) {
                    ++lineCount;
                    auto tokens = split(line);
                    if (tokens.size() == 4) {
                        if(mapNodeIds.insert(std::make_pair(tokens[0], consecutiveID)).second)
                            consecutiveID++;
                        if(mapNodeIds.insert(std::make_pair(tokens[1], consecutiveID)).second)
                            consecutiveID++;
                        if(std::stoi(tokens[2]) < tmin)
                            tmin = std::stoi(tokens[2]);
                        if(std::stoi(tokens[3]) > tmax)
                            tmax = std::stoi(tokens[3]);
                    } else {
                        throw CSVReaderException("Unsupported file format");
                    }
                }
            }
        }

        auto G = DiLinkStream(static_cast<int>(mapNodeIds.size()), tmin, tmax);

        // second pass create the edges
        file.clear();
        file.seekg(0, std::ios::beg);

        while(!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                if (line.compare(0, this->commentPrefix.length(), this->commentPrefix) != 0){
                    auto tokens = split(line, this->delimiter);
                    if (tokens.size() == 4) {
                        auto u = mapNodeIds[tokens[0]];
                        auto v = mapNodeIds[tokens[1]];
                        auto b = std::stoi(tokens[2]);
                        auto e = std::stoi(tokens[3]);
                        G.add_edge_w_time(u, v, b, e);
                    }
                }
            }
        }
        return G;
    }

    Graph CSVReader::read_graph(const std::string &path)
    {
        int lineCount = 0;
        std::string line;
        int consecutiveID = 0;
        std::ifstream file(path, std::ios::in);
        std::map<std::string, LinkStream::vertex_t> mapNodeIds;

        if (file.fail())
            throw CSVReaderException("Could not open file");

        // first pass create the vertices
        while(!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                if (line.compare(0, this->commentPrefix.length(), this->commentPrefix) != 0) {
                    ++lineCount;
                    auto tokens = split(line);
                    if (tokens.size() == 2) {
                        if(mapNodeIds.insert(std::make_pair(tokens[0], consecutiveID)).second)
                            consecutiveID++;
                        if(mapNodeIds.insert(std::make_pair(tokens[1], consecutiveID)).second)
                            consecutiveID++;
                    } else {
                        throw CSVReaderException("Unsupported file format");
                    }
                }
            }
        }

        auto G = Graph(static_cast<int>(mapNodeIds.size()));

        // second pass create the edges
        file.clear();
        file.seekg(0, std::ios::beg);

        while(!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                if (line.compare(0, this->commentPrefix.length(), this->commentPrefix) != 0){
                    auto tokens = split(line, this->delimiter);
                    if (tokens.size() == 2) {
                        auto u = mapNodeIds[tokens[0]];
                        auto v = mapNodeIds[tokens[1]];
                        G.add_edge(u, v);
                    }
                }
            }
        }
        return G;
    }
}

