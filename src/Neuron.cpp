#include "NeuralNet/Neuron.hpp"
#include <cstdlib>

Neuron::Neuron(int inputSize)
{
        for (int i = 0; i < inputSize; ++i)
        {
                weights.push_back(0.0);
        }
        bias = (double)rand() / RAND_MAX;
}

double Neuron::activate(const std::vector<double> &inputs)
{
        lastInputs = inputs;
        double sum = 0.0;
        for (size_t i = 0; i < inputs.size(); ++i)
        {
                sum += weights[i] * inputs[i];
        }
        sum += bias;
        lastOutput = sigmoid(sum);
        return lastOutput;
}

void Neuron::updateWeights(const std::vector<double> &dWeights, double dBias, double learningRate)
{
        for (size_t i = 0; i < weights.size(); ++i)
        {
                weights[i] -= learningRate * dWeights[i];
        }
        bias -= learningRate * dBias;
}
