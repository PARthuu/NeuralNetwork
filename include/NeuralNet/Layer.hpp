#ifndef LAYER_HPP
#define LAYER_HPP

#include "Neuron.hpp"
#include <vector>

class Layer
{
public:
    std::vector<Neuron> neurons;
    std::vector<double> lastOutputs;

    Layer(int inputSize, int neuronCount);
    Layer() = default;

    std::vector<double> forward(const std::vector<double> &inputs);
    std::vector<double> backward(const std::vector<double> &dOutputs, double learningRate);
};

#endif
