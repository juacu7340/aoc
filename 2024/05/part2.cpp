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

void filter(const std::vector<int>& n, std::vector<std::vector<int>>& incorrect_numbers) {
    for (auto it = n.begin(); it != n.end(); ++it) {
        if (rules.contains(*it)) {
            auto match = rules.find(*it);

            for (auto n_it = n.begin(); n_it != it; ++n_it) {
                for (auto value : match->second) {
                    if (*n_it == value) {
                        incorrect_numbers.push_back(n); 
                        return;
                    }
                }
            }
        }
    }
}

std::vector<std::vector<int>> filter(const std::vector<std::vector<int>> numbers) {
    std::vector<std::vector<int>> incorrect_numbers;

    for (auto n : numbers) {
        filter(n, incorrect_numbers);
    }

    return incorrect_numbers;
}

int fix(std::vector<int>& n) {
    for (auto it = n.begin(); it != n.end(); ++it) {
        if (rules.contains(*it)) {
            auto match = rules.find(*it);

            for (auto n_it = n.begin(); n_it != it; ++n_it) {
                for (auto value : match->second) {
                    if (*n_it == value) {
                        std::iter_swap(it, n_it);
                        return fix(n);
                    }
                }
            }
        }
    }

    return n[n.size() / 2];
}


int main() {
    std::vector<std::vector<int>> numbers;
    get_input(numbers);
    auto incorrect_numbers = std::move(filter(numbers));

    int result = 0;

    for (auto & n : incorrect_numbers) {
        result += fix(n);
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}
