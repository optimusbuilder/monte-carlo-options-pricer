#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>
using namespace std ;

double simulateEuropean(double currentStockPrice, double optionPrice, double priceExpiry, double stockVolatility, int numSimulations, double riskFreeRate) {
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


double simulateAsian(double currentStockPrice, double optionPrice, double priceExpiry, double stockVolatility, int numSimulations, double riskFreeRate) {
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
    int number_of_steps = 252;
    double dt = priceExpiry / number_of_steps;
    for (int i = 0; i < numSimulations ; i++) {
        double asian_option_price = 0;
        s = currentStockPrice ;
        for (int t = 0; t <number_of_steps; t++){ 
            double z = numGen(mt) ;
            s = s * exp((r - 0.5 * pow(σ, 2)) * dt + σ * sqrt(dt) * z);
            asian_option_price += s;
        }
        double avg_price = asian_option_price / number_of_steps;
        double payOff = max(avg_price - optionPrice, 0.0);
        total += payOff;
    }
    double average = total / numSimulations ;
    return average * exp(-r * t);

}




double simulateAsianAntithetic(double currentStockPrice, double optionPrice, double priceExpiry, double stockVolatility, int numSimulations, double riskFreeRate) {
    mt19937 mt{ static_cast<std::mt19937::result_type>(
		chrono::steady_clock::now().time_since_epoch().count()
		) };
    double sA = currentStockPrice ;
    double sB = currentStockPrice;
    double r = riskFreeRate ;
    double σ = stockVolatility;
    double t = priceExpiry ;
    double mean = 0.0;
    double standardDeviation = 1.0;
    normal_distribution<double> numGen{mean, standardDeviation}; 
    double total = 0 ;
    int number_of_steps = 252;
    double dt = priceExpiry / number_of_steps;
    for (int i = 0; i < numSimulations ; i++) {
        double asian_option_price_A = 0;
        double asian_option_price_B = 0;
        sA = currentStockPrice ;
        sB = currentStockPrice;
        for (int t = 0; t <number_of_steps; t++){ 
            double z = numGen(mt) ;
            sA = sA * exp((r - 0.5 * pow(σ, 2)) * dt + σ * sqrt(dt) * z);
            sB = sB * exp((r - 0.5 * pow(σ, 2)) * dt + σ * sqrt(dt) * -z);
            asian_option_price_A += sA;
            asian_option_price_B += sB;

        }
        double avg_price_A = asian_option_price_A / number_of_steps;
        double avg_price_B = asian_option_price_B / number_of_steps;
        double payOff_A = max(avg_price_A - optionPrice, 0.0);
        double payOff_B = max(avg_price_B - optionPrice, 0.0);
        total += ((payOff_A + payOff_B) / 2);
    }
    double average = total / numSimulations ;
    return average * exp(-r * t);
    };

int main() {
    //Testing the functions
    double currentStockPrice = 100;
    double optionPrice = 105 ;
    double priceExpiry = 1.0 ;
    double stockVolatility = 0.20;
    int numSimulations = 1000;
    double riskFreeRate = 0.05;
    double resultEuropean = simulateEuropean(currentStockPrice, optionPrice, priceExpiry, stockVolatility, numSimulations, riskFreeRate);
    double resultAsian = simulateAsian(currentStockPrice, optionPrice, priceExpiry, stockVolatility, numSimulations, riskFreeRate);
    double resultAsianAntithetic = simulateAsianAntithetic(currentStockPrice, optionPrice, priceExpiry, stockVolatility, numSimulations, riskFreeRate);
    cout << "Result for European simulation: "<< resultEuropean <<endl;
    cout << "Result for Asian simulation: "<< resultAsian <<endl;
    cout << "Result for Asian simulation with antithetic variation: "<< resultAsianAntithetic <<endl;
    return 0;
}