#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

constexpr const int ARGS = 2;

int main(int argc, char **argv) {

  if (argc != ARGS) {
    std::cerr << "Syntax: exe <input file>" << std::endl;
    return -1;
  }

  std::string file = argv[1];
  std::ifstream input_file(file);

  int result = 0;

  std::string line;
  std::regex pattern("((\\d+)-(\\d+),(\\d+)-(\\d+))");
  std::smatch matches;

  while (std::getline(input_file, line)) {
    int a1, a2, b1, b2;

    if (std::regex_match(line, matches, pattern)) {
      a1 = std::stoi(matches[2]);
      a2 = std::stoi(matches[3]);
      b1 = std::stoi(matches[4]);
      b2 = std::stoi(matches[5]);

      result += ((a1 <= b1 && a2 >= b2) || (b1 <= a1 && b2 >= a2));
    }
  }

  std::cout << result << std::endl;

  return 0;
}
