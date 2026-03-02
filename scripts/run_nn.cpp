#include <iostream>
#include <string>

#include "NeuralNet/DataLoader.hpp"
#include "NeuralNet/Utils.hpp"


int main(int argc, char* argv[])
{

    std::string model_path = "models/hash.model";
    std::string data_path = "data/small-test.csv";
    int pos = -1;

    for (int i = 1; i<argc; ++i) {
        std::string arg = argv[i];

        if ( (arg == "-f" || arg == "--file") && (i+1 < argc)) {
            model_path = argv[++i];
        }else if ((arg == "-d" || arg == "--data") && (i+1 < argc)) {
            data_path = argv[++i];
        }else if ((arg == "-p") && (i+1 < argc)) {
            pos = std::stoi(argv[++i]);
        }

    }

    DataLoader::Data data = DataLoader::load_data(data_path);

    Network net = Utils::loadNetwork(model_path);

    std::cout << "\nFinal predictions after training:\n";
    std::cout << "\n";


    if (pos == -1) {
        for (int j=0; j<data.targets.size(); ++j) {
            auto prediction = net.predict(data.inputs[j]);
            for (size_t i = 0; i < prediction.size(); ++i)
            {
                std::cout << (data.targets[j][i] == (prediction[i] < 0.5 ? 0.0 : 1.0) ? "1" : "0");
            }
            std::cout << "\n";
        }
    }else {
        auto prediction = net.predict(data.inputs[pos]);
        for (size_t i = 0; i < prediction.size(); ++i)
        {

            std::cout << (data.targets[pos][i] == (prediction[i] < 0.5 ? 0.0 : 1.0) ? "1" : "0");
            std::cout << "\n";
        }
    }

    return 0;
}
