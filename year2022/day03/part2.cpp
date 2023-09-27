#include <algorithm>
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

  std::string line;
  std::string compartment1, compartment2;

  int total_priority = 0;

  while (std::getline(input_file, line)) {
    compartment1 = line.substr(0, line.length() / 2);
    compartment2 = line.substr(line.length() / 2, line.length() / 2);

    std::sort(std::begin(compartment1), std::end(compartment1));
    std::sort(std::begin(compartment2), std::end(compartment2));

    std::string intersections;
    std::set_intersection(std::begin(compartment1), std::end(compartment1),
                          std::begin(compartment2), std::end(compartment2),
                          std::back_inserter(intersections));

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
