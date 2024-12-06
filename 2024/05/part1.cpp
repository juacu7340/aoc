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
#include <ranges>

const std::string_view input_file = "input.txt";

std::unordered_map<int, std::vector<int>> rules;

void insert_rule(int key, int value) {
    if (rules.contains(key)) {
        auto match = rules.find(key);
        (match->second).push_back(value);
    } else {
        rules.emplace(std::make_pair(key, std::vector<int>{value}));
    }
}

void get_input(std::vector<std::vector<int>> & a) {
    std::ifstream input_stream(input_file);

    std::string line;
    char delim = '|';
    while(std::getline(input_stream, line)) {
        if(line.empty()) {
            delim = ',';
            continue;
        }

        std::vector<int> numbers;
        std::ranges::for_each(line | std::ranges::views::split(delim)
            | std::ranges::views::transform([](auto&& subrange) {
                return std::stoi(std::string(subrange.begin(), subrange.end()));
            }), [&numbers](int number) {
                numbers.push_back(number);
            });

        switch (delim) {
            case '|':
                insert_rule(numbers[0], numbers[1]);
                break;
            case ',':
                a.push_back(std::move(numbers));
                break;
            default: break;
        }
    }
}

int middle(const std::vector<int> numbers) {
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (rules.contains(*it)) {
            auto match = rules.find(*it);

            for (auto n_it = numbers.begin(); n_it != it; ++n_it) {
                for (auto value : match->second) {
                    if (*n_it == value) {
                        return 0; 
                    }
                }
            }

        }
    }

    return numbers[numbers.size() / 2];
}


int main() {
    std::vector<std::vector<int>> numbers;
    get_input(numbers);

    int result = 0;

    for (auto & n : numbers) {
        result += middle(n);
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}
