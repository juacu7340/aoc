#include <algorithm>
#include <bitset>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

constexpr const int ARGS = 2;

int main(int argc, char **argv) {

  if (argc != ARGS) {
    std::cerr << "Syntax: exe <input file>" << std::endl;
    return -1;
  }

  std::string file = argv[1];
  std::ifstream input_file(file);

  std::string datastream;
  std::getline(input_file, datastream);

  std::bitset<26> window(0);
  int pos[26] = {0};
  int result;

  std::string::iterator sop = std::begin(datastream);
  while (sop != std::end(datastream)) {
    if (window.test(*sop - 0x61)) {
      sop = std::begin(datastream) + pos[*sop - 0x61] + 1;
      window.reset();
    } else {
      pos[*sop - 0x61] = sop - std::begin(datastream);
      window.set(*sop - 0x61);
      if (window.count() == 14) {
        result = pos[*sop - 0x61] + 1;
        break;
      }
      sop++;
    }
  }
  std::cout << result << std::endl;
}
