#include <iostream>
#include "NeuralNet/Network.hpp"
#include "NeuralNet/Loss.hpp"
#include "NeuralNet/DataLoader.hpp"

int main(int argc, char* argv[])
{
	// Check if a file path was passed as an argument
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
		return 1;
	}

	std::string filePath = argv[1];

	srand(time(0));

	Network net(70, {40, 40}, 256);

	DataLoader::Data data = DataLoader::load_data(filePath);

	// Training loop
	int epochs = 5000;
	double learningRate = 20;

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
		}
	}

	// Final predictions
	std::cout << "\nFinal predictions after training:\n";

	auto prediction = net.predict(data.inputs[1000]);
	std::cout << "\n";

	for (size_t i = 0; i < prediction.size(); ++i)
	{
		std::cout << (data.targets[0][i] == (prediction[i] < 0.5 ? 0.0 : 1.0) ? "1" : "0");
	}

	return 0;
}
