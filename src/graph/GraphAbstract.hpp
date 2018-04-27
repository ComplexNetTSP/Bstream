///-------------------------------------------------------------------------------------------------
///
/// @file       GraphAbstract.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       27/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_GRAPHABSTRACT_HPP
#define BSTREAM_GRAPHABSTRACT_HPP

#include <string>
#include <Eigen/Core>

using Eigen::MatrixXd;

namespace boost::bstream
{
    class GraphAbstract
    {
    public:
        ///**************************************************************************************************
        ///
        ///  Constructor method
        ///
        ///**************************************************************************************************

        GraphAbstract(){};

        ///**************************************************************************************************
        ///
        ///  Graph method
        ///
        ///**************************************************************************************************
        virtual bool is_directed() const = 0;

        virtual MatrixXd adjacency() = 0;
        virtual void read_csv(std::string path, char delimiter = ',') = 0;

        virtual double num_vertices() = 0;
        virtual double num_edges() = 0;
        virtual double density() = 0;

        virtual void clear_vertices() = 0;
        virtual void clear_edges() = 0;
        virtual void clear() = 0;

        ///**************************************************************************************************
        ///
        ///  Vertex method
        ///
        ///**************************************************************************************************

        virtual std::vector<std::string> labels() const = 0;
        virtual bool has_vertex(const std::string& label) = 0;
        virtual double degree(const std::string& v) = 0;
        virtual double in_degree(const std::string& v) = 0;
        virtual double out_degree(const std::string& v) = 0;
        virtual void remove_vertex(const std::string& label) = 0;

        ///**************************************************************************************************
        ///
        ///  Edge method
        ///
        ///**************************************************************************************************

        virtual bool has_edge(const std::string& s, const std::string& t) = 0;
    };

} // end namespace boost:bstream

#endif //BSTREAM_GRAPHABSTRACT_HPP
