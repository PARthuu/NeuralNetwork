#include <iostream>
#include <string>

#include "NeuralNet/Loss.hpp"
#include "NeuralNet/DataLoader.hpp"
#include "NeuralNet/Utils.hpp"


int main(int argc, char* argv[])
{
    std::string model_path = "models/hash.model";
    std::string filePath;

    int inputSize;
    int outputSize;
    std::vector<int> hiddenLayers;

    // Training loop
    int epochs = 1000;
    double learningRate = 20;


    for (int i = 1; i<argc; ++i) {
        std::string arg = argv[i];

        if ( (arg == "-f" || arg == "--file") && (i+1 < argc)) {
            filePath = argv[++i];
        }
        else if ( (arg == "-e" || arg == "--epochs") && (i+1 < argc)) {
            epochs = std::stoi(argv[++i]);
        }
        else if ((arg == "-l" || arg == "--learningRate") && (i+1 < argc)) {
            learningRate = std::stoi(argv[++i]);
        }
        else if ((arg == "-m" || arg == "--modelPath") && (i+1 < argc)) {
            model_path = argv[++i];
        }
        else if ( (arg == "-n" || arg == "--network") && (i+1 < argc)) {
            std::string input = argv[++i];
            std::vector<int> values;
            size_t pos = 0;

            while ((pos = input.find(',')) != std::string::npos) {
                values.push_back(std::stoi(input.substr(0, pos)));
                input.erase(0, pos + 1);
            }
            values.push_back(std::stoi(input)); // last value

            if (values.size() < 2) {
                std::cerr << "Error: -n/--network requires at least two comma-separated values.\n";
                exit(1);
            }

            inputSize = values.front();
            outputSize = values.back();
            hiddenLayers.assign(values.begin() + 1, values.end() - 1);
        }
    }


    Network net(inputSize, hiddenLayers, outputSize);

    DataLoader::Data data = DataLoader::load_data(filePath);

    for (int epoch = 0; epoch < epochs; epoch++)
    {
        double totalLoss = 0.0;
        for (size_t i = 0; i < data.inputs.size(); ++i)
        {
            net.train(data.inputs[i], data.targets[i], learningRate);
            auto prediction = net.predict(data.inputs[i]);
            totalLoss += Loss::mse(prediction, data.targets[i]);
        }

        // if (totalLoss < 0.0001)
        //         break;

        if (epoch % 100 == 0)
        {
            std::cout << "Epoch " << epoch << ", Loss: " << totalLoss << std::endl;
            Utils::saveNetwork(net, model_path);
        }
    }

    Utils::saveNetwork(net, model_path);

    return 0;
}
