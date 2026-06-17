#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>
using namespace std ;

double simulate(double currentStockPrice, double optionPrice, double priceExpiry, double stockVolatility, int numSimulations, double riskFreeRate) {
    mt19937 mt{ static_cast<std::mt19937::result_type>(
		chrono::steady_clock::now().time_since_epoch().count()
		) };
    double s = currentStockPrice ;
    double r = riskFreeRate ;
    double σ = stockVolatility;
    double t = priceExpiry ;
    double mean = 0.0;
    double standardDeviation = 1.0;
    normal_distribution<double> numGen{mean, standardDeviation}; 
    double total = 0 ;
    for (int i = 0; i < numSimulations ; i++) {
        double z = numGen(mt) ;
        double finalPrice = s * exp((r - 0.5 * pow(σ, 2)) * t + σ * sqrt(t) * z);
        double payOff = max(finalPrice - optionPrice, 0.0);
        total += payOff;
    }
    double average = total / numSimulations ;
    return average * exp(-r * t);
    };

int main() {
    double currentStockPrice = 100;
    double optionPrice = 105 ;
    double priceExpiry = 1.0 ;
    double stockVolatility = 0.20;
    int numSimulations = 100000;
    double riskFreeRate = 0.05;
    double result = simulate(currentStockPrice, optionPrice, priceExpiry, stockVolatility, numSimulations, riskFreeRate);
    cout << result << endl ;
    return 0;
}