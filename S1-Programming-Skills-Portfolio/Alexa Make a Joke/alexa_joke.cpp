// alexa_joke.cpp
// Reads jokes from randomJokes.txt, picks one at random, and reveals the
// punchline only after the user presses Enter — mimicking an Alexa interaction.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

int main() {
  try {
    std::vector<std::string> setups, punchlines;
    std::ifstream file("randomJokes.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open randomJokes.txt\n";
        return 1;
    }

    // Each line is "setup? punchline"; split on the first '?'
    std::string line;
    while (std::getline(file, line)) {
        size_t dot = line.find('?');
        if (dot != std::string::npos) {
            setups.push_back(line.substr(0, dot + 1));
            punchlines.push_back(line.substr(dot + 1));
        }
    }

    if (setups.empty()) {
        std::cerr << "Error: No jokes found in file.\n";
        return 1;
    }

    // Pick a random joke index
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, setups.size() - 1);
    size_t index = dist(rng);

    std::cout << "Alexa: " << setups[index] << std::endl;
    std::cout << "Press Enter for the punchline...";
    std::cin.get();
    std::cout << "Alexa: " << punchlines[index] << std::endl;

  } catch (const std::exception& e) {
      std::cerr << "Unexpected error: " << e.what() << "\n";
      return 1;
  }

    return 0;
}
