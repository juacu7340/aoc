#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <numeric>
#include <sstream>

constexpr const int ARGS = 2;

int64_t next(const std::vector<int64_t> & sequence) {
    std::vector<int64_t> new_sequence;

    if(std::adjacent_find(sequence.begin(), sequence.end(), std::not_equal_to<int64_t>()) == sequence.end()) return sequence[0];

    for (int i = 0; i < sequence.size() - 1; ++i) {
        new_sequence.push_back(sequence[i+1] - sequence[i]);
    }
    auto & last = sequence[sequence.size() - 1];
    auto n = next(new_sequence);
    return last + n;
}

int main(int argc, char ** argv) {
    if (argc != ARGS) {
        std::cerr << "Syntax: exe <input file>" << std::endl;
        return -1;
    }

    std::string file = argv[1];
    std::ifstream input_file(file);


    int64_t result = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        std::istringstream iss(line);
        std::vector<int64_t> sequence;
        int64_t num;
        while(iss >> num) {
            sequence.push_back(num);
        }
        
        auto v = next(sequence);
        result += v;
    }
    std::cout << result << std::endl;
    return 0;
}