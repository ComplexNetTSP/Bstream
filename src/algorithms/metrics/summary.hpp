///-------------------------------------------------------------------------------------------------
///
/// @file       summary.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       03/05/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_SUMMARY_HPP
#define BSTREAM_SUMMARY_HPP

#include <iostream>

#include "clustering.hpp"
#include "degree.hpp"
#include "GraphType.hpp"

namespace boost::bstream
{
    template<typename DirectedS>
    void summary(GraphBase<DirectedS> &g)
    {
        std::cout << g << std::endl;
        std::cout << "avg. degree: " << avg_degree(g) << std::endl;
        std::cout << "avg. clustering: " << avg_clustering(g) << std::endl;
    }
} // end namespace boost::bstream

#endif //BSTREAM_SUMMARY_HPP
