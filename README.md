# Monte Carlo Option Pricing in C++

A practical look at pricing options using Monte Carlo simulations. This project compares standard European options against Asian path-dependent options, and includes a version using Antithetic Variates to show how you can get cleaner data with fewer simulations.

## 🤔 How It Works (The Intuition)

Instead of relying on heavy calculus, this code simulates thousands of possible random price paths for a stock to see where it lands at expiration, calculates the payoff, and discounts it back to today.

### European vs. Asian Options: Why the Prices Differ

If you run the code, you'll notice the Asian option is always cheaper than the European option. Here's why:

- **European Options** only care about the final price at the exact moment of expiry. If the stock spikes on the very last day, the payoff skyrockets.
- **Asian Options** take the average price across the entire lifetime (simulated here across 252 trading days). Because we're averaging the steps, those extreme random spikes get smoothed out. Lower volatility in the path means a lower average payoff, which naturally drives the option price down.

### The Antithetic Trick

Standard Monte Carlo needs a lot of runs to get an accurate price because random numbers tend to clump together.

To fix that, the antithetic version generates two paths for the price of one. For every random path generated using a jump (z), it simultaneously spawns a twin path using the exact opposite jump (−z). This balances out the randomness and cuts down the noise (variance) in the final estimate.

## 📊 Variance Reduction Results (Real Data)

To prove the antithetic technique actually works, here's the spread across 5 consecutive runs using 1,000 simulations per run.

| Run | European Price | Standard Asian Price | Asian Antithetic Price |
|---|---|---|---|
| Run 1 | 8.61 | 3.49 | 3.51 |
| Run 2 | 8.13 | 3.52 | 3.61 |
| Run 3 | 8.16 | 3.24 | 3.63 |
| Run 4 | 7.82 | 3.98 | 3.64 |
| Run 5 | 8.24 | 3.44 | 3.49 |
| **Spread (Max − Min)** | **0.79** | **0.74** | **0.15** |

### What This Shows

The standard Asian pricer has a spread of 0.74 across 5 runs at 1,000 simulations. By introducing antithetic paths, the spread drops to 0.15 — roughly a 5x tighter result at the same computational cost. That means you get a more stable price without needing to crank simulations up into the tens of thousands.

## 💻 Getting Started

### Prerequisites

A modern C++ compiler supporting at least C++11 (like g++, clang++, or MSVC).

### Compilation

```bash
g++ -O3 -std=c++11 main.cpp -o option_pricer
```

(The `-O3` flag is recommended to speed up the simulation loops.)

### Running the Executable

```bash
./option_pricer
```

## ⚙️ Parameters Used in Main

| Parameter | Description | Default Value |
|---|---|---|
| currentStockPrice | Spot price of the underlying asset | 100.0 |
| optionPrice | Strike price of the option | 105.0 |
| priceExpiry | Time to expiration in years | 1.0 (1 Year) |
| stockVolatility | Annualized volatility of the asset | 0.20 (20%) |
| numSimulations | Number of Monte Carlo iterations | 1000 |
| riskFreeRate | Continuous risk-free interest rate | 0.05 (5%) |