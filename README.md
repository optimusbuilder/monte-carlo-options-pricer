
---

# Monte Carlo Options Pricer — C++

A Monte Carlo simulation that prices European call options using Geometric Brownian Motion. Built to understand how quant desks price derivatives without closed-form solutions.

---

## How It Works

A call option gives you the right to buy a stock at a fixed price (the strike) at expiry. The question is — what is that right worth today?

This pricer answers that by simulating 100,000 possible future price paths for the stock, calculating the payoff at expiry for each path, and averaging them. That average, discounted back to today using the risk-free rate, is the fair option price.

The more simulations you run, the closer the result converges to the true price: the law of large numbers in action.

---

## The Math

Each simulated price path uses Geometric Brownian Motion:

```
S_final = S * exp((r - 0.5σ²) * T + σ * √T * Z)
```

Where Z is a random draw from a standard normal distribution. Payoff is then `max(S_final - Strike, 0)`, discounted back by `e^(-r*T)`.

---

## Inputs

| Parameter | Description | Example |
|---|---|---|
| Stock price | Current market price | $100 |
| Strike price | Price to buy at expiry | $105 |
| Time to expiry | In years | 1.0 |
| Volatility | Annual volatility (decimal) | 0.20 |
| Risk-free rate | Safe investment return (decimal) | 0.05 |
| Simulations | Number of random paths | 100,000 |

---

## Sample Output

```
Option price: $8.02
```

This matches the Black-Scholes analytical price of ~$8.02 for these inputs, validating the simulation.

---

## Run It

```bash
g++ -std=c++17 main.cpp -o pricer
./pricer
```