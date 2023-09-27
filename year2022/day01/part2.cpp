#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr const int ARGS = 2;

int main(int argc, char **argv) {

  if (argc != ARGS) {
    std::cerr << "Syntax: exe <input file>" << std::endl;
    return -1;
  }

  std::string file = argv[1];
  std::ifstream input_file(file);

  std::string line;

  int index = 0, sum = 0;
  std::vector<int> calories = {0};

  while (std::getline(input_file, line)) {
    if (line.empty()) {
      calories.push_back(0);
      index++;
      sum = 0;
    }

    std::istringstream filter(line);

    filter >> sum;
    calories[index] += sum;
  }

  std::sort(std::begin(calories), std::end(calories),
            [](int a, int b) { return a > b; });
  std::cout << calories[0] + calories[1] + calories[2] << std::endl;

  return 0;
}
