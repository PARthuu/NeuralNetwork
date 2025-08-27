// Utils.hpp

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "Network.hpp"
class Utils
{
public:
    static void saveNetwork(const Network &network, const std::string &filename);
    static Network loadNetwork(const std::string& filename);
};

#endif // UTILS_HPP
