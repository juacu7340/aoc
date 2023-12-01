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

  std::string line;
  while (std::getline(input_file, line)) {
    for (int i = 1, j = 0; i < line.length(); i = i + 4, ++j) {
      data[j] = line[i];
    }
  }

  while () {
    switch (line[0]) {
    case case '[':

      break;
    case 'm':
      break;
    default:
      break;
    }
  }

  return 0;
}
