# CO2 Calculator

A C++ command-line tool that estimates your annual carbon footprint based on UK emission factors (BEIS 2024).

## How it works
Asks questions across 5 categories and calculates your total CO2 in tonnes:

1. **Home Energy** — electricity and gas usage, supply type
2. **Transport** — car type, annual miles, public transport
3. **Air Travel** — short and long-haul flights
4. **Food & Diet** — meat consumption and local/seasonal buying habits
5. **Consumer Goods** — monthly spending on new items

Compares your result against the UK average (5.5 tonnes CO2/year).

## References
- UK Government — BEIS Greenhouse Gas Conversion Factors 2024: https://www.gov.uk/government/collections/government-conversion-factors-for-company-reporting
- UK Carbon Calculator (emission factor guidance): https://www.ukcalculator.co.uk

## Files
- `co2_calculator.cpp` — main program

## How to run
```bash
g++ co2_calculator.cpp -o co2_calculator
./co2_calculator
```

## Example output
```
=== Your Annual Carbon Footprint ===
Home energy:     1.2 t
Transport:       1.89 t
Flights:         0.5 t
Food & diet:     1.3 t
Consumer goods:  0.7 t
-----------------------------
TOTAL:           5.59 tonnes CO2
UK average:      5.5 tonnes CO2
You're above the UK average. Consider reducing high-impact areas.
```
