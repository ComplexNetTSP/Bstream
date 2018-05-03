///-------------------------------------------------------------------------------------------------
///
/// @file       utils.hpp
/// @brief      Description
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       03/05/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_UTILS_HPP
#define BSTREAM_UTILS_HPP

#include <iostream>
#include <vector>

namespace boost::bstream
{
    inline std::vector<std::string>
    split(const std::string &s, const char sep = ',')
    {
        std::string buff{""};
        std::vector<std::string> tokens;
        for (auto it: s) {
            if (it != sep) {
                buff += it;
            } else if (it == sep && buff != "") {
                tokens.push_back(buff);
                buff = "";
            }
        }
        if (buff != "")
            tokens.push_back(buff);

        return tokens;
    }
} // end namespace boost::bstream
#endif //BSTREAM_UTILS_HPP
