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

int main() {
    std::vector<std::vector<int>> reports;
    get_input(reports);

    int safe_reports = 0;

    for (const auto & report : reports) {
        if (eval_report(report) == true) {
            safe_reports++;
        }
    }

    std::cout << "Result: " << safe_reports << '\n';

    return 0;
}
