#include <algorithm>
#include <array>
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

  int total_priority = 0;

  std::array<std::string, 3> group;
  while (std::getline(input_file, group[0]) &&
         std::getline(input_file, group[1]) &&
         std::getline(input_file, group[2])) {

    std::sort(std::begin(group[0]), std::end(group[0]));
    std::sort(std::begin(group[1]), std::end(group[1]));
    std::sort(std::begin(group[2]), std::end(group[2]));

    std::string intersections;
    std::set_intersection(std::begin(group[0]), std::end(group[0]),
                          std::begin(group[1]), std::end(group[1]),
                          std::back_inserter(intersections));

    int selection_len = intersections.length();
    std::set_intersection(std::begin(intersections), std::end(intersections),
                          std::begin(group[2]), std::end(group[2]),
                          std::back_inserter(intersections));

    intersections.erase(0, selection_len);
    intersections.erase(
        std::unique(std::begin(intersections), std::end(intersections)));

    std::for_each(std::begin(intersections), std::end(intersections),
                  [&total_priority](char item) {
                    total_priority += (std::islower(item))
                                          ? item - 0x60
                                          : (item - 0x41) + 0x1B;
                  });
  }

  std::cout << total_priority << std::endl;
  return 0;
}
