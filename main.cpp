#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<double> stringToDoubleVector(const std::string &str, size_t expectedLength)
{
    std::vector<double> vec;
    vec.reserve(expectedLength);

    for (char ch : str)
    {
        if (ch == '0' || ch == '1')
        {
            vec.push_back(static_cast<double>(ch - '0')); // '0' -> 0.0, '1' -> 1.0
        }
        else
        {
            throw std::runtime_error("Invalid character in input: " + std::string(1, ch));
        }
    }

    if (vec.size() != expectedLength)
    {
        throw std::runtime_error("Expected " + std::to_string(expectedLength) +
                                 " values, but got " + std::to_string(vec.size()));
    }

    return vec;
}

int main()
{
    const std::string filePath = "data/small-test.csv";
    const size_t inputLength = 70;
    const size_t outputLength = 256;

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return 1;
    }

    std::string line;

    std::vector<std::vector<double>> inputs;
    std::vector<std::vector<double>> outputs;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string inputStr, outputStr;

        std::getline(ss, inputStr, ',');
        std::getline(ss, outputStr);

        try
        {
            std::vector<double> inputVec = stringToDoubleVector(inputStr, inputLength);
            std::vector<double> outputVec = stringToDoubleVector(outputStr, outputLength);

            inputs.push_back(inputVec);
            outputs.push_back(outputVec);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing line: " << e.what() << "\n";
            continue;
        }
    }

    file.close();

    // Optional: confirm data loaded
    std::cout << "Loaded " << inputs.size() << " input/output pairs.\n";
    std::cout << "First input: ";
    for (double val : inputs[0])
        std::cout << val;
    std::cout << "\nFirst output: ";
    for (double val : outputs[0])
        std::cout << val;
    std::cout << "\n";

    return 0;
}
