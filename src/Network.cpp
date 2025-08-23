#include "NeuralNet/Network.hpp"
#include "NeuralNet/Loss.hpp"
#include "NeuralNet/Activations.hpp"

Network::Network(int inputSize, const std::vector<int> &hiddenSizes, int outputSize)
	: outputLayer(hiddenSizes.empty() ? inputSize : hiddenSizes.back(), outputSize)
{
	// Create input layer
	int previousSize = inputSize;

	// Create all hidden layers
	for (int hiddenSize : hiddenSizes)
	{
		hiddenLayers.emplace_back(previousSize, hiddenSize);
		previousSize = hiddenSize;
	}
	// Create output layer
	outputLayer = Layer(previousSize, outputSize);
}

std::vector<double> Network::predict(const std::vector<double> &inputs)
{
	std::vector<double> output = inputs;

	for (auto &layer : hiddenLayers)
	{
		output = layer.forward(output);
	}

	return outputLayer.forward(output);
}

void Network::train(const std::vector<double> &inputs, const std::vector<double> &targets, double learningRate)
{
	std::vector<double> output = inputs;

	// Forward pass through hidden layers
	for (auto &layer : hiddenLayers)
	{
		output = layer.forward(output);
	}

	// Forward pass through output layer
	std::vector<double> finalOutput = outputLayer.forward(output);

	// Backpropagation: output layer
	std::vector<double> outputError = Loss::mse_derivative(finalOutput, targets);
	std::vector<double> prevError = outputLayer.backward(outputError, learningRate);

	// Backpropagate through hidden layers in reverse order
	for (int i = static_cast<int>(hiddenLayers.size()) - 1; i >= 0; --i)
	{
		prevError = hiddenLayers[i].backward(prevError, learningRate);
	}
}
