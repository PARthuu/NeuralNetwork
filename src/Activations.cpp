#include "NeuralNet/Activations.hpp"
#include <cmath>
#include <algorithm> // for std::max

// ---------------------
// Scalar Functions
// ---------------------
double ActivationFunctions::custom(double x)
{
    return 1.0 / (1.0 + std::exp(-x));
}

double ActivationFunctions::sigmoid(double x)
{
    return 1.0 / (1.0 + std::exp(-x));
}

double ActivationFunctions::relu(double x)
{
    return std::max(0.0, x);
}

double ActivationFunctions::tanh(double x)
{
    return std::tanh(x);
}

double ActivationFunctions::sigmoidDerivative(double x)
{
    double s = sigmoid(x);
    return s * (1 - s);
}

double ActivationFunctions::reluDerivative(double x)
{
    return x > 0 ? 1.0 : 0.0;
}

double ActivationFunctions::tanhDerivative(double x)
{
    double t = tanh(x);
    return 1.0 - t * t;
}

// ---------------------
// Vector Functions
// ---------------------
std::vector<double> ActivationFunctions::custom(const std::vector<double> &vec)
{
    std::vector<double> result;
    result.reserve(vec.size());
    for (double x : vec)
        result.push_back(custom(x));
    return result;
}

std::vector<double> ActivationFunctions::sigmoid(const std::vector<double> &vec)
{
    std::vector<double> result;
    result.reserve(vec.size());
    for (double x : vec)
        result.push_back(sigmoid(x));
    return result;
}

std::vector<double> ActivationFunctions::relu(const std::vector<double> &vec)
{
    std::vector<double> result;
    result.reserve(vec.size());
    for (double x : vec)
        result.push_back(relu(x));
    return result;
}

std::vector<double> ActivationFunctions::tanh(const std::vector<double> &vec)
{
    std::vector<double> result;
    result.reserve(vec.size());
    for (double x : vec)
        result.push_back(tanh(x));
    return result;
}

std::vector<double> ActivationFunctions::sigmoidDerivative(const std::vector<double> &vec)
{
    std::vector<double> result;
    result.reserve(vec.size());
    for (double x : vec)
        result.push_back(sigmoidDerivative(x));
    return result;
}

std::vector<double> ActivationFunctions::reluDerivative(const std::vector<double> &vec)
{
    std::vector<double> result;
    result.reserve(vec.size());
    for (double x : vec)
        result.push_back(reluDerivative(x));
    return result;
}

std::vector<double> ActivationFunctions::tanhDerivative(const std::vector<double> &vec)
{
    std::vector<double> result;
    result.reserve(vec.size());
    for (double x : vec)
        result.push_back(tanhDerivative(x));
    return result;
}
