#include <string>
#include <iostream>
#include <random>
using namespace std ;


struct MonteCarloPricer {
    
};

int main() {
    mt19937 mt{ static_cast<std::mt19937::result_type>(
		chrono::steady_clock::now().time_since_epoch().count()
		) };
    double currentStockPrice;
    double optionPrice;
    double priceExpiry;
    double stockVolatility;
    int numberOfSimulations;
    double riskFreeRate;

    double simulate(double currentStockPrice, double optionPrice, double priceExpiry, double stockVolatility, int numSimulations, double riskFreeRate) {
        double mean = 0.0;
        double standardDeviation = 1.0;
        normal_distribution<double> numGen{mean, standard_deviation};
        };
    return 0;
}