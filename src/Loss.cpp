#include "NeuralNet/Loss.hpp"
#include <cmath>
#include <iostream>

double Loss::mse(const std::vector<double> &predicted, const std::vector<double> &target)
{
        double sum = 0.0;
        for (size_t i = 0; i < predicted.size(); ++i)
        {
                double diff = predicted[i] - target[i];
                sum += diff * diff;
        }
        return sum / predicted.size();
}

std::vector<double> Loss::mse_derivative(const std::vector<double> &predicted, const std::vector<double> &target)
{
        std::vector<double> derivatives;
        for (size_t i = 0; i < predicted.size(); ++i)
        {
                derivatives.push_back(2 * (predicted[i] - target[i]) / predicted.size());
        }
        return derivatives;
}
