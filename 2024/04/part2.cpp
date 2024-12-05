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
get_input(std::vector<std::vector<char>> & words) {
    std::ifstream input_stream(input_file);
    std::string line;

    while(std::getline(input_stream, line)) {
        words.emplace_back(std::vector<char>(std::ranges::begin(line), std::ranges::end(line)));
    }
}

bool check(const std::vector<std::vector<char>> & words, int row, int col, char match) {
    auto max_row = words.size();
    auto max_col = words.size();

    if (row < 0 || col < 0 || row >= max_row || col >= max_row) {
        return false;
    }

    return (words[row][col] == match);
}

int main() {
    std::vector<std::vector<char>> words;
    get_input(words);

    int result = 0;

    for (int row = 0; row < words.size(); ++row) {
        for(int col = 0; col < words.size(); ++col) {
            if (words[row][col] == 'A') {
                if(
                    ((check(words, row + 1, col + 1, 'M') &&
                    check(words, row - 1, col - 1, 'S')) ||
                    (check(words, row + 1, col + 1, 'S') &&
                    check(words, row - 1, col - 1, 'M'))) 
                    &&
                    ((check(words, row + 1, col - 1, 'M') &&
                    check(words, row - 1, col + 1, 'S')) ||
                    (check(words, row + 1, col - 1, 'S') &&
                    check(words, row - 1, col + 1, 'M')))) {
                    result++;
                }
            }
        }
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}
