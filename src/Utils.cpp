#include "NeuralNet/Utils.hpp"
#include "NeuralNet/Layer.hpp"
#include <fstream>
#include <stdexcept>

// Helper functions to read/write vector<double>
static void writeVector(std::ofstream &out, const std::vector<double> &vec)
{
    size_t size = vec.size();
    out.write(reinterpret_cast<const char *>(&size), sizeof(size));
    out.write(reinterpret_cast<const char *>(vec.data()), size * sizeof(double));
}

static void readVector(std::ifstream &in, std::vector<double> &vec)
{
    size_t size;
    in.read(reinterpret_cast<char *>(&size), sizeof(size));
    vec.resize(size);
    in.read(reinterpret_cast<char *>(vec.data()), size * sizeof(double));
}

// Save network
void Utils::saveNetwork(const Network &network, const std::string &filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out)
        throw std::runtime_error("Failed to open file for saving.");

    std::vector<Layer> layers = network.hiddenLayers;
    layers.push_back(network.outputLayer);

    size_t numLayers = layers.size();
    out.write(reinterpret_cast<const char *>(&numLayers), sizeof(numLayers));

    for (const Layer &layer : layers)
    {
        size_t numNeurons = layer.neurons.size();
        out.write(reinterpret_cast<const char *>(&numNeurons), sizeof(numNeurons));

        for (const Neuron &neuron : layer.neurons)
        {
            writeVector(out, neuron.weights);
            out.write(reinterpret_cast<const char *>(&neuron.bias), sizeof(neuron.bias));
            out.write(reinterpret_cast<const char *>(&neuron.lastOutput), sizeof(neuron.lastOutput));
            writeVector(out, neuron.lastInputs);
        }
    }

    out.close();
}

Network Utils::loadNetwork(const std::string &filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
        throw std::runtime_error("Failed to open file for loading.");

    size_t numLayers;
    in.read(reinterpret_cast<char *>(&numLayers), sizeof(numLayers));

    std::vector<Layer> layers;
    layers.reserve(numLayers);

    for (size_t i = 0; i < numLayers; ++i)
    {
        size_t numNeurons;
        in.read(reinterpret_cast<char *>(&numNeurons), sizeof(numNeurons));

        Layer layer;
        layer.neurons.reserve(numNeurons);

        for (size_t j = 0; j < numNeurons; ++j)
        {
            Neuron neuron;
            readVector(in, neuron.weights);        // std::vector<double>
            in.read(reinterpret_cast<char *>(&neuron.bias), sizeof(neuron.bias));
            in.read(reinterpret_cast<char *>(&neuron.lastOutput), sizeof(neuron.lastOutput));
            readVector(in, neuron.lastInputs);     // std::vector<double>
            layer.neurons.push_back(std::move(neuron));
        }

        layers.push_back(std::move(layer));
    }

    in.close();

    Network network;
    if (!layers.empty())
    {
        network.outputLayer = std::move(layers.back());
        layers.pop_back();
    }
    network.hiddenLayers = std::move(layers);

    return network;
}

