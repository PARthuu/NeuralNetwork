#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include "Activations.hpp"

class Neuron : public ActivationFunctions
{
public:
    std::vector<double> weights;
    double bias;
    double lastOutput;
    std::vector<double> lastInputs;

    Neuron(int inputSize);
    Neuron() = default;

    double activate(const std::vector<double> &inputs);
    void updateWeights(const std::vector<double> &dWeights, double dBias, double learningRate);
};

#endif
