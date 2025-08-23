#include "NeuralNet/Utils.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

static std::vector<double> stringToDoubleVector(const std::string &str, size_t expectedLength)
{
	std::vector<double> vec;
	vec.reserve(expectedLength);

	for (char ch : str)
	{
		vec.push_back(static_cast<double>(ch - '0'));
		// if (ch == '0' || ch == '1')
		// {
		// 	vec.push_back(static_cast<double>(ch - '0'));
		// }
		// else
		// {
		// 	throw std::runtime_error("Invalid character in input: " + std::string(1, ch));
		// }
	}

	// if (vec.size() != expectedLength)
	// {
	// 	throw std::runtime_error("Expected " + std::to_string(expectedLength) +
	// 							 " values, but got " + std::to_string(vec.size()));
	// }

	return vec;
}

Utils::Data Utils::load_data(const std::string &filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + filepath);
	}

	std::string line;

	const size_t input_length = 70;
	const size_t target_length = 256;
	Data data;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string inputStr, outputStr;

		std::getline(ss, inputStr, ',');
		std::getline(ss, outputStr);

		// if (!std::getline(ss, inputStr, ',') || !std::getline(ss, outputStr))
		// {
		// 	std::cerr << "Skipping malformed line: " << line << "\n";
		// 	continue;
		// }

		try
		{
			std::vector<double> inVec = stringToDoubleVector(inputStr, input_length);
			std::vector<double> outVec = stringToDoubleVector(outputStr, target_length);

			data.inputs.push_back(inVec);
			data.targets.push_back(outVec);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error parsing line: " << e.what() << "\n";
		}
	}

	return data;
}
