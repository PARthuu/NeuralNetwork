#include "NeuralNet/Layer.hpp"

Layer::Layer(int inputSize, int neuronCount)
{
        for (int i = 0; i < neuronCount; ++i)
        {
                neurons.emplace_back(inputSize);
        }
}

std::vector<double> Layer::forward(const std::vector<double> &inputs)
{
        lastOutputs.clear();
        for (auto &neuron : neurons)
        {
                lastOutputs.push_back(neuron.activate(inputs));
        }
        return lastOutputs;
}

std::vector<double> Layer::backward(const std::vector<double> &dOutputs, double learningRate)
{
        std::vector<double> dInputs(neurons[0].weights.size(), 0.0);

        for (size_t i = 0; i < neurons.size(); ++i)
        {
                Neuron &neuron = neurons[i];
                double delta = dOutputs[i] * neuron.sigmoid_derivative(neuron.lastOutput);

                std::vector<double> dWeights;
                for (double input : neuron.lastInputs)
                {
                        dWeights.push_back(input * delta);
                }

                for (size_t j = 0; j < dInputs.size(); ++j)
                {
                        dInputs[j] += neuron.weights[j] * delta;
                }

                neuron.updateWeights(dWeights, delta, learningRate);
        }

        return dInputs;
}
