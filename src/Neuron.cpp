#include "NeuralNet/Neuron.hpp"
#include "NeuralNet/Activations.hpp"
#include <cstdlib>
#include <cmath>

Neuron::Neuron(int inputSize)
{
        for (int i = 0; i < inputSize; ++i)
        {
                weights.push_back((double)rand() / RAND_MAX);
        }
        bias = (double)rand() / RAND_MAX;
}

double Neuron::sigmoid(double x)
{
        return 1.0 / (1.0 + std::exp(-x));
}

double Neuron::sigmoid_derivative(double x)
{
        return x * (1 - x); // assuming x is the sigmoid output
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
