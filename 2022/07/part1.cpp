#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

constexpr const int ARGS = 2;

int main(int argc, char **argv) {

  if (argc != ARGS) {
    std::cerr << "Syntax: exe <input file>" << std::endl;
    return -1;
  }

  std::string file = argv[1];
  std::ifstream input_file(file);

  std::unordered_map<std::string, int> directories;
  std::stack<std::string> cwd;

  std::string line;
  while (std::getline(input_file, line)) {
    std::istringstream iss(line);
    std::istream_iterator<std::string> begin(iss);
    std::istream_iterator<std::string> end; // default cted is eos

    std::vector<std::string> cmd(begin, end);

    if (!cmd[1].compare("ls") || !cmd[0].compare("dir")) {

    } else

      std::for_each(std::begin(cmd), std::end(cmd),
                    [](auto &s) { std::cout << s << ' '; });
  }

  return 0;
}
