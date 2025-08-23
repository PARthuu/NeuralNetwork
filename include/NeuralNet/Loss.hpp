#ifndef LOSS_HPP
#define LOSS_HPP

#include <vector>

class Loss
{
public:
        static double mse(const std::vector<double> &predicted, const std::vector<double> &target);
        static std::vector<double> mse_derivative(const std::vector<double> &predicted, const std::vector<double> &target);
};

#endif
