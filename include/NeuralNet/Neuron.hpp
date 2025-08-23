#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>

class Neuron
{
public:
        std::vector<double> weights;
        double bias;
        double lastOutput;
        std::vector<double> lastInputs;

        Neuron(int inputSize);

        double activate(const std::vector<double> &inputs);
        double sigmoid(double x);
        double sigmoid_derivative(double x);
        void updateWeights(const std::vector<double> &dWeights, double dBias, double learningRate);
};

#endif
