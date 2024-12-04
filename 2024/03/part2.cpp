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
    DO_D,
    DO_O,
    DO_OP,
    DONT_D,
    DONT_O,
    DONT_N,
    DONT_A,
    DONT_T,
    DONT_OP,
};

const std::string_view input_file = "input.txt";

void get_input(std::vector<std::string> & a) {
    std::ifstream input_stream(input_file);

    std::string line;

    while(std::getline(input_stream, line)) {
        a.push_back(line);
    }
}

void format(std::string & row) {
    while (true) {
        int dont = row.find("don't()");
        int doo = row.find("do()");

        
        if (dont == std::string::npos || doo == std::string::npos) {
            break;
        }

        int diff = doo - dont;

        if (diff > 0) {
            // remove from dont to doo
            row.erase(dont, diff + 4);
        } else {
            // remove doo
            row.erase(doo, 4);
        }
    }
}

int main() {
    std::vector<std::string> memory;
    get_input(memory);

    int sum = 0;
    bool enabled = true;
    for (auto& row : memory) {
        //std::cout << row << std::endl;
        //format(row);
        States current_state = NORMAL;
        std::string first = "", second = "";
        for (int i = 0; i < row.length(); ++i) {
            char c = row[i];
            if (enabled == true) {
                switch (current_state) {
                    case NORMAL:
                        if (c == 'm') {
                            current_state = M;
                        }
                        else if (c == 'd') {
                            current_state = DONT_D;
                        }
                        else {
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
                    case DONT_D:
                        if (c == 'o') {
                            current_state = DONT_O;
                        } else {
                            current_state = NORMAL;
                        }
                        break;
                    case DONT_O:
                        if (c == 'n') {
                            current_state = DONT_N;
                        } else {
                            current_state = NORMAL;
                        }
                        break;
                    case DONT_N:
                        if (c == '\'') {
                            current_state = DONT_A;
                        } else {
                            current_state = NORMAL;
                        }
                        break;
                    case DONT_A:
                        if (c == 't') {
                            current_state = DONT_T;
                        } else {
                            current_state = NORMAL;
                        }
                        break;
                    case DONT_T:
                        if (c == '(') {
                            current_state = DONT_OP;
                        } else {
                            current_state = NORMAL;
                        }
                        break;
                    case DONT_OP:
                        if (c == ')') {
                            enabled = false;
                        }
                        current_state = NORMAL;
                        break;
                    default: break;
                }
            } else {
                switch (current_state) {
                    case NORMAL:
                        if (c == 'd') {
                            current_state = DO_D;
                        } else {
                            current_state = NORMAL;
                        }
                        break;
                    case DO_D:
                        if (c == 'o') {
                            current_state = DO_O;
                        } else {
                            current_state = NORMAL;
                        }
                        break;
                    case DO_O:
                        if (c == '(') {
                            current_state = DO_OP;
                        } else {
                            current_state = NORMAL;
                        }
                        break;
                    case DO_OP:
                        if (c == ')') {
                            enabled = true;
                        }
                        current_state = NORMAL;
                        break;
                    default: break;
                }
            }
        }
    }

    std::cout << "Result: " << sum << '\n';

    return 0;
}
