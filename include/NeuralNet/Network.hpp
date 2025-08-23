#include <vector>
#include "Layer.hpp"

class Network
{
public:
        std::vector<Layer> hiddenLayers;
        Layer outputLayer;

        Network(int inputSize, const std::vector<int> &hiddenSizes, int outputSize);

        std::vector<double> predict(const std::vector<double> &inputs);
        void train(const std::vector<double> &inputs, const std::vector<double> &targets, double learningRate);
};
