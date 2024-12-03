#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>

const std::string_view input_file = "input.txt";

void
get_input(std::vector<std::vector<int>> & reports) {
    std::ifstream input_stream(input_file);
    std::string line;

    while(std::getline(input_stream, line)) {
        std::istringstream input_string_stream(line);
        std::vector<int> report;

        int number;
        while (input_string_stream >> number) {
            report.push_back(number);
        }

        reports.push_back(report);
    }
}

bool check_order(const std::vector<int> & report) {
    if (std::ranges::is_sorted(report) == true) {
        return true;
    }

    if (std::ranges::is_sorted(report,
        std::ranges::greater {}) == true) {
        return true;
    }

    return false;
}

bool eval_report(const std::vector<int> & report) {
    if (check_order(report) == false) {
        return false;
    }

    auto find = std::ranges::adjacent_find(report,[](int a, int b) {
            int difference = std::abs(a - b);
            return difference > 3 || difference == 0;
        });

    if (find != report.end()) {
        return false;
    }

    return true;
}

template<typename C>
bool compare(int a, int b, C cmp) {
     return cmp(a, b);
}

bool less(int a, int b) {
    return a < b;
}

bool greater(int a, int b) {
    return a > b;
}

void fix_attempt(std::vector<int>& bad_report) {
    auto& br = bad_report;
    int first_level = bad_report[0];
    int level_counter = 0;

    bool(*cmp)(int, int) = less;

    for (int i = 1; i < br.size(); ++i) {
        if (br[i-1] > br[i]) {
            level_counter++;
        }
    }

    if (level_counter < br.size() / 2) {
        cmp = greater;
    }

    for (int i = 1; i < br.size(); ++i) {
        if (cmp(br[i-1], br[i]) == false) {
            if (cmp == greater) {
                br.erase(br.begin() + (i-1));
                return;
            } else {
                br.erase(br.begin() + i);
                return;
            }
        }
    }

    for (int i = 1; i < br.size(); ++i) {
        if (std::abs(br[i-1] - br[i]) > 3) {
            if (cmp == greater) {
                br.erase(br.begin() + (i-1));
                return;
            } else {
                br.erase(br.begin() + i);
                return;
            }
        }
    }
}

bool brute_force(const std::vector<int>& report) {
    std::vector<int> copy = report;

    for(int i = 0; i < report.size(); ++i) {
        copy.erase(copy.begin() + i);
        if (eval_report(copy) == true) {
            return true;
        }
        copy = report;
    }

    return false;
}

int main() {
    std::vector<std::vector<int>> reports;
    get_input(reports);

    int safe_reports = 0;

    for (auto & report : reports) {

        if (eval_report(report) == false) {
            if(brute_force(report) == false) {
                continue;
            }
        }

        safe_reports++;
    }

    std::cout << "Result: " << safe_reports << '\n';

    return 0;
}
