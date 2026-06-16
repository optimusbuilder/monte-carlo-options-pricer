#include <string>
#include <iostream>
using namespace std ;


struct MonteCarloPricer {
    int currentStockPrice;
    int optionPrice;
    string priceExpiry;
    int stockVolatility;
    int numberOfSimulations;

};