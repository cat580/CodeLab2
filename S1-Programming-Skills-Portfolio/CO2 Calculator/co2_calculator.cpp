#include <iostream>

// Emission factors (kg CO2) - BEIS 2024 / ukcalculator.com
const double CAR_PETROL   = 0.27;
const double CAR_DIESEL   = 0.28;
const double CAR_HYBRID   = 0.16;
const double CAR_ELECTRIC = 0.08;
const double ELEC_GRID      = 0.233;
const double ELEC_RENEWABLE = 0.05;
const double ELEC_SOLAR     = 0.10;
const double GAS_KWH = 0.184;
const double PUBLIC_TRANSPORT = 0.08;
const double FLIGHT_SHORT = 250.0;
const double FLIGHT_LONG  = 1500.0;
const double DIET_HIGH_MEAT   = 2500.0;
const double DIET_MEDIUM_MEAT = 1800.0;
const double DIET_LOW_MEAT    = 1300.0;
const double DIET_VEGETARIAN  = 1000.0;
const double DIET_VEGAN       = 700.0;
const double LOCAL_NEVER     = 1.00;
const double LOCAL_SOMETIMES = 0.90;
const double LOCAL_MOSTLY    = 0.75;
const double LOCAL_ALWAYS    = 0.60;
const double GOODS_LOW      = 400.0;
const double GOODS_MEDIUM   = 700.0;
const double GOODS_HIGH     = 1200.0;
const double GOODS_VERY_HIGH = 2000.0;

int readInt(int min, int max) {
    int val;
    while (!(std::cin >> val) || val < min || val > max) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input, enter a number between " << min << " and " << max << ": ";
    }
    return val;
}

double readDouble() {
    double val;
    while (!(std::cin >> val) || val < 0) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input, enter a non-negative number: ";
    }
    return val;
}

double homeEnergy() {
    std::cout << "Annual electricity usage (kWh, UK avg 3100): ";
    double elec = readDouble();
    std::cout << "Annual gas usage (kWh, UK avg 12000): ";
    double gas = readDouble();
    std::cout << "Electricity supply: 1) Standard grid  2) 100% Renewable  3) Solar+Grid\nChoice: ";
    int type = readInt(1, 3);

    double elecFactor;
    switch (type) {
        case 2:  elecFactor = ELEC_RENEWABLE; break;
        case 3:  elecFactor = ELEC_SOLAR;     break;
        default: elecFactor = ELEC_GRID;      break;
    }
    return elec * elecFactor + gas * GAS_KWH;
}

double transport() {
    std::cout << "Car type: 1) Petrol  2) Diesel  3) Hybrid  4) Electric  5) No car\nChoice: ";
    int carType = readInt(1, 5);
    std::cout << "Annual car miles (UK avg 7000): ";
    double carMiles = readDouble();
    std::cout << "Weekly public transport miles (bus/train/tube): ";
    double pubMilesWeekly = readDouble();

    double carFactor;
    switch (carType) {
        case 1:  carFactor = CAR_PETROL;   break;
        case 2:  carFactor = CAR_DIESEL;   break;
        case 3:  carFactor = CAR_HYBRID;   break;
        case 4:  carFactor = CAR_ELECTRIC; break;
        default: carFactor = 0.0;          break;
    }
    return carMiles * carFactor + pubMilesWeekly * 52 * PUBLIC_TRANSPORT;
}

double flights() {
    std::cout << "Short-haul return flights (e.g. London-Paris): ";
    int shortTrips = readInt(0, 100);
    std::cout << "Long-haul return flights (e.g. London-NYC): ";
    int longTrips = readInt(0, 100);
    return shortTrips * FLIGHT_SHORT + longTrips * FLIGHT_LONG;
}

double diet() {
    std::cout << "Diet: 1) High meat (daily)  2) Medium meat (3-4x/week)  3) Low meat (1-2x/week)  4) Vegetarian  5) Vegan\nChoice: ";
    int type = readInt(1, 5);
    std::cout << "Buy local/seasonal food: 1) Rarely  2) Sometimes  3) Mostly  4) Always\nChoice: ";
    int local = readInt(1, 4);

    double base;
    switch (type) {
        case 1:  base = DIET_HIGH_MEAT;   break;
        case 3:  base = DIET_LOW_MEAT;    break;
        case 4:  base = DIET_VEGETARIAN;  break;
        case 5:  base = DIET_VEGAN;       break;
        default: base = DIET_MEDIUM_MEAT; break;
    }

    double localFactor;
    switch (local) {
        case 1:  localFactor = LOCAL_NEVER;     break;
        case 3:  localFactor = LOCAL_MOSTLY;    break;
        case 4:  localFactor = LOCAL_ALWAYS;    break;
        default: localFactor = LOCAL_SOMETIMES; break;
    }
    return base * localFactor;
}

double goods() {
    std::cout << "Monthly spending on new goods: 1) Under £200  2) £200-500  3) £500-1000  4) Over £1000\nChoice: ";
    int level = readInt(1, 4);
    switch (level) {
        case 1:  return GOODS_LOW;
        case 3:  return GOODS_HIGH;
        case 4:  return GOODS_VERY_HIGH;
        default: return GOODS_MEDIUM;
    }
}

int main() {
  try {
    std::cout << "\n=== CO2 Calculator (UK) ===\n";

    std::cout << "\n-- Home Energy --\n";
    double home = homeEnergy();

    std::cout << "\n-- Transport --\n";
    double trans = transport();

    std::cout << "\n-- Air Travel --\n";
    double air = flights();

    std::cout << "\n-- Food & Diet --\n";
    double food = diet();

    std::cout << "\n-- Consumer Goods --\n";
    double shopping = goods();

    double totalKg     = home + trans + air + food + shopping;
    double totalTonnes = totalKg / 1000.0;
    double ukAvg       = 5.5;

    std::cout << "\n=== Your Annual Carbon Footprint ===\n";
    std::cout << "Home energy:     " << home     / 1000.0 << " t\n";
    std::cout << "Transport:       " << trans    / 1000.0 << " t\n";
    std::cout << "Flights:         " << air      / 1000.0 << " t\n";
    std::cout << "Food & diet:     " << food     / 1000.0 << " t\n";
    std::cout << "Consumer goods:  " << shopping / 1000.0 << " t\n";
    std::cout << "-----------------------------\n";
    std::cout << "TOTAL:           " << totalTonnes << " tonnes CO2\n";
    std::cout << "UK average:      " << ukAvg << " tonnes CO2\n";

    if (totalTonnes < 3.0)
        std::cout << "Excellent! You're on track for Net Zero 2050 targets.\n";
    else if (totalTonnes < ukAvg)
        std::cout << "Good! You're below the UK average.\n";
    else if (totalTonnes < 8.0)
        std::cout << "You're above the UK average. Consider reducing high-impact areas.\n";
    else
        std::cout << "Your footprint is significantly above average.\n";

  } catch (const std::exception& e) {
      std::cerr << "Unexpected error: " << e.what() << "\n";
      return 1;
  }

    return 0;
}
