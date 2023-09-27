#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr const int ARGS = 2;

enum Move { Rock = 0x41, Paper = 0x42, Scissors = 0x43 };

int main(int argc, char **argv) {

  if (argc != ARGS) {
    std::cerr << "Syntax: exe <input file>" << std::endl;
    return -1;
  }

  std::string file = argv[1];
  std::ifstream input_file(file);

  std::string line;
  char move1, move2;
  int total_score = 0;

  while (std::getline(input_file, line)) {
    std::istringstream move(line);

    move >> move1 >> move2;
    move2 -= 0x17;
    total_score += static_cast<int>(move2 - 0x40);

    switch (static_cast<Move>(move2)) {
    case Rock:
      switch (static_cast<Move>(move1)) {
      case Scissors:
        total_score += 3;
      case Rock:
        total_score += 3;
      default:
        break;
      }
      break;
    case Paper:
      switch (static_cast<Move>(move1)) {
      case Rock:
        total_score += 3;
      case Paper:
        total_score += 3;
      default:
        break;
      }
      break;
    case Scissors:
      switch (static_cast<Move>(move1)) {
      case Paper:
        total_score += 3;
      case Scissors:
        total_score += 3;
      default:
        break;
      }
      break;
    }
  }

  std::cout << total_score << std::endl;

  return 0;
}
