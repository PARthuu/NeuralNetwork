#ifndef ACTIVATION_FUNCTIONS_HPP
#define ACTIVATION_FUNCTIONS_HPP

#include <vector>

class ActivationFunctions
{
public:
    // Scalar activation functions
    static double sigmoid(double x);
    static double relu(double x);
    static double tanh(double x);
    static double custom(double x);

    // Derivatives
    static double sigmoidDerivative(double x);
    static double reluDerivative(double x);
    static double tanhDerivative(double x);

    // Vector versions (applied element-wise)
    static std::vector<double> sigmoid(const std::vector<double> &vec);
    static std::vector<double> relu(const std::vector<double> &vec);
    static std::vector<double> tanh(const std::vector<double> &vec);
    static std::vector<double> custom(const std::vector<double> &vec);

    static std::vector<double> sigmoidDerivative(const std::vector<double> &vec);
    static std::vector<double> reluDerivative(const std::vector<double> &vec);
    static std::vector<double> tanhDerivative(const std::vector<double> &vec);
};

#endif // ACTIVATION_FUNCTIONS_HPP
