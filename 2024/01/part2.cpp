#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <unordered_map>

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

std::unordered_map<int, int> cached_scores;

int main() {
    std::vector<int> left_list, right_list;
    get_input(left_list, right_list);

    int sum = 0;
    for (int number : left_list) {
        int counter;
        if (auto search = cached_scores.find(number); search != cached_scores.end()) {
            counter = search->second;
        } else {
            counter = std::ranges::count(right_list, number);
            cached_scores[number] = counter;
        }
        sum += (number * counter);
    }

    std::cout << "Result: " << sum << '\n';

    return 0;
}
