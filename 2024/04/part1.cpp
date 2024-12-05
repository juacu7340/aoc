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

enum States {
    N,
    X,
    M,
    A,
    S
};

enum Direction {
    None,
    U,
    D,
    L,
    R,
    UL,
    UR,
    DL,
    DR
};

void get_direction(int & row, int & col, Direction direction) {
    switch (direction) {
        case None:
            row = row; col = col;
            break;
        case U:
            row -= 1; col = col;
            break;
        case D:
            row += 1; col = col;
            break;
        case L:
            row = row; col -= 1;
            break;
        case R:
            row = row; col += 1;
            break;
        case UL:
            row -= 1; col -= 1;
            break;
        case UR:
            row -= 1; col += 1;
            break;
        case DL:
            row += 1; col -= 1;
            break;
        case DR:
            row += 1; col += 1;
            break;
    }
}

int count(const std::vector<std::vector<char>>& words, int row, int col, States state, Direction
direction) {
    auto max_row = words.size();
    auto max_col = words.size();

    if (row < 0 || col < 0 || row >= max_row || col >= max_row) {
        return 0;
    }

    char c = words[row][col];

    switch (state) {
        case N:
            if (c == 'X' && direction == None) {
                return
                    count(words, row + 0, col + 1, X, R) +
                    count(words, row + 0, col - 1, X, L) +
                    count(words, row + 1, col + 0, X, D) + 
                    count(words, row - 1, col + 0, X, U) + 
                    count(words, row + 1, col + 1, X, DR) + 
                    count(words, row + 1, col - 1, X, DL) + 
                    count(words, row - 1, col - 1, X, UL) + 
                    count(words, row - 1, col + 1, X, UR); 
            }
            return 0;
        case X:
            if (c == 'M') {
                get_direction(row, col, direction);
                return count(words, row, col, M, direction);
            }
            return 0;
        case M:
            if (c == 'A') {
                get_direction(row, col, direction);
                return count(words, row, col, A, direction);
            }
            return 0;
        case A:
            if (c == 'S') {
                return 1;
            }
            return 0;
        default: return 0;
    }
}

int main() {
    std::vector<std::vector<char>> words;
    get_input(words);

    int result = 0;

    for (int row = 0; row < words.size(); ++row) {
        for(int col = 0; col < words.size(); ++col) {
            result += count(words, row, col, N, None);
        }
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}
