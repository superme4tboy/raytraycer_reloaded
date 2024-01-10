#include <random>
#include <chrono>

class Random {
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;

public:
    Random() : distribution(0.0, 1.0) {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);
    }
    
    Random(float min, float max) : distribution(min, max) {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);
    }

    double getRandom() {
        return distribution(generator);
    }
};
