#include <algorithm>
#include <cstdio>
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
  char move1, move2;
  int total_score = 0;
  int points[3] = {1, 2, 3};
  int score_points[3] = {2, 0, 1};
  int index_increment, score_increment;

  while (std::getline(input_file, line)) {
    std::istringstream move(line);

    move >> move1 >> move2;

    index_increment = score_points[move2 - 0x58];
    score_increment = (move2 - 0x58) * 3;
    total_score += score_increment + ((points[(index + index_increment) % 3]));
  }

  std::cout << total_score << std::endl;

  return 0;
}
