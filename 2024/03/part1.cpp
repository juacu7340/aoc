#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <cmath>

enum States {
    NORMAL,
    M,
    U,
    L,
    OP,
    FN,
    C,
    SN,
};

const std::string_view input_file = "input.txt";

void get_input(std::vector<std::string> & a) {
    std::ifstream input_stream(input_file);

    std::string line;

    while(std::getline(input_stream, line)) {
        a.push_back(line);
    }
}

int main() {
    std::vector<std::string> memory;
    get_input(memory);

    int sum = 0;
    for (auto& row : memory) {
        States current_state = NORMAL;
        std::string first = "", second = "";
        for (int i = 0; i < row.length(); ++i) {
            char c = row[i];
            switch (current_state) {
                case NORMAL:
                    if (c == 'm') {
                        current_state = M;
                    } else {
                        current_state = NORMAL;
                    }
                    break;
                case M:
                    if (c == 'u') {
                        current_state = U;
                    } else {
                        current_state = NORMAL;
                    }
                    break;
                case U:
                    if (c == 'l') {
                        current_state = L;
                    } else {
                        current_state = NORMAL;
                    }
                    break;
                case L:
                    if (c == '(') {
                        current_state = OP;
                    } else {
                        current_state = NORMAL;
                    }
                    break;
                case OP:
                    if (std::isdigit(c) != 0) {
                        first = c;
                        current_state = FN;
                    } else {
                        current_state = NORMAL;
                    }
                    break;
                case FN:
                    if (std::isdigit(c) != 0) {
                        first.push_back(c);
                    } else if (c == ',') {
                        current_state = C;
                    } else {
                        current_state = NORMAL;
                        first = "";
                    }
                    break;
                case C:
                    if (std::isdigit(c) != 0) {
                        second = c;
                        current_state = SN;
                    } else {
                        current_state = NORMAL;
                    }
                    break;
                case SN:
                    if (std::isdigit(c) != 0) {
                        second.push_back(c);
                    } else if (c == ')') {
                        sum += (std::stoi(first) * std::stoi(second));
                        current_state = NORMAL;
                    } else {
                        current_state = NORMAL;
                        second = "";
                    }
                    break;
            }
        }
    }

    std::cout << "Result: " << sum << '\n';

    return 0;
}
