#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <cmath>

const std::string_view input_file = "input.txt";

void get_input(std::vector<int> & a, std::vector<int> & b) {
    std::ifstream input_stream(input_file);

    std::string line;

    while(std::getline(input_stream, line)) {
        //std::cout << line;
        int left, right;
        std::istringstream input_string_stream(line);

        input_string_stream >> left >> right;
        a.push_back(left); b.push_back(right);
    }
}

int main() {
    std::vector<int> left_list, right_list;
    get_input(left_list, right_list);

    std::ranges::sort(left_list);
    std::ranges::sort(right_list);

    int sum = 0;
    for (int i = 0; i < left_list.size(); ++i) {
        sum += std::abs(left_list[i] - right_list[i]);
    }

    std::cout << "Result: " << sum << '\n';

    return 0;
}
