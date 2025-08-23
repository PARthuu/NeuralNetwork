#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>

class Utils
{
public:
    // Struct to hold input/output data
    struct Data
    {
        std::vector<std::vector<double>> inputs;
        std::vector<std::vector<double>> targets;
    };

    // Load flattened binary data from CSV
    static Data load_data(const std::string &filepath);

    // Future utility functions can go here
};

#endif // UTILS_HPP
