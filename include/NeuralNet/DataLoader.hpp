#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <vector>
#include <string>

class DataLoader
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

};

#endif // DATALOADER_HPP
