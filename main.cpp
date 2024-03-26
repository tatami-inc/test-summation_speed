#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <random>
#include <cmath>
#include <algorithm>
#include <vector>

int main() {
    std::mt19937_64 rng(123456);
    std::vector<double> stuff(1e7);
    std::normal_distribution<double> ndist;
    for (auto& s : stuff) {
        s = ndist(rng);
    }

    double expected = std::accumulate(stuff.begin(), stuff.end(), 0.0);
    std::cout << "Expecting a sum of " << expected << std::endl;

    ankerl::nanobench::Bench().run("naive", [&](){
        double sum = std::accumulate(stuff.begin(), stuff.end(), static_cast<double>(0));
        if (sum != expected) {
            std::cerr << "WARNING: different result from naive summation (" << sum << ")" << std::endl;
        }
    });

    ankerl::nanobench::Bench().run("kahan", [&](){
        double sum = 0, error = 0;
        for (auto s : stuff) {
            auto y = s - error;
            auto t = sum + y;
            error = (t - sum) - y;
            sum = t;
        }
        if (sum == expected) {
            std::cerr << "WARNING: unexpectedly consistent result from Kahan summation (" << sum << ")" << std::endl;
        }
    });

    ankerl::nanobench::Bench().run("neumaier", [&](){
        double sum = 0, error = 0;
        for (auto s : stuff) {
            auto t = sum + s;
            if (std::abs(sum) >= std::abs(s)) {
                error += (sum - t) + s;
            } else {
                error += (s - t) + sum;
            }
            sum = t;
        }
        if (sum != expected) {
            std::cerr << "WARNING: different result from Neumaier summation (" << sum << ")" << std::endl;
        }
        if (error == 0) {
            std::cerr << "WARNING: Neumaier error is zero" << std::endl;
        }
    });

    return 0;
}
