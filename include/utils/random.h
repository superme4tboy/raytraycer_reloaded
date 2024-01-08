#pragma once
#include <random>

class Random
{
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;

public:
    Random() : distribution(0.0, 1.0)
    {
        std::uniform_real_distribution<double> distribution(0.1, 1.0);
    }
    
    Random(float min,float max) : distribution(min,max) {
        std::uniform_real_distribution<double> distribution(min, max);
    }

    double getRandom() {
        return distribution(generator);
    }
};