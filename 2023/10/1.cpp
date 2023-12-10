#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <numeric>
#include <sstream>

constexpr const int ARGS = 2;

struct vert{
    int row;
    int col;
};

int64_t explore(std::vector<vert> & verts, const std::vector<std::vector<char>>& diagram, int last_row, int last_col, int row, int col ) {
    int delta_row = 0, delta_col = 0;
    switch (diagram[row][col]) {
        case 'J':
        verts.push_back(vert{row, col});
        if (last_row < row) {
            delta_col = -1;    
        } else {
            delta_row = -1;
        }
        break;
        case '7': 
        verts.push_back(vert{row, col});
        if (last_row > row) {
            delta_col = -1;    
        } else {
            delta_row = 1;
        }
        break;
        case 'F': 
        verts.push_back(vert{row, col});
        if (last_row > row) {
            delta_col = 1;    
        } else {
            delta_row = 1;
        }
        break;
        case 'L':
        verts.push_back(vert{row, col});
        if (last_row < row) {
            delta_col = 1;    
        } else {
            delta_row = -1;
        }
        break;
        case '-':
        if (last_col < col) {
            delta_col = 1;    
        } else {
            delta_col = -1;    
        }
        break;
        case '|':
        if (last_row < row) {
            delta_row = 1;
        } else {
            delta_row = -1;
        }
        break;
        default: return -99999;
    }

    char next = diagram[row + delta_row][col + delta_col];
    
    if (next == 'S') return 1;
 
    return 1 + explore(verts, diagram, row, col, row + delta_row, col + delta_col);
}

int main(int argc, char ** argv) {
    if (argc != ARGS) {
        std::cerr << "Syntax: exe <input file>" << std::endl;
        return -1;
    }

    std::string file = argv[1];
    std::ifstream input_file(file);


    int64_t result = 0;
    std::vector<std::vector<char>> diagram;
    std::string line;
    while (std::getline(input_file, line)) {
        char u;
        std::istringstream iss(line);
        std::vector<char> v;
        while (iss>>u) {
            v.push_back(u);
        }
        diagram.push_back(v);
    }

    std::vector<vert> verts;
    for(int row = 0; row < diagram.size(); ++row) {
        for(int col = 0; col < diagram[row].size(); ++col) {
            if(diagram[row][col] == 'S') {
                result = 1 + explore(verts, diagram, row, col, row, col-1);
                row = diagram.size();
                col = diagram[row].size();
            }
        }
    }
    
    verts.push_back(vert{62,111});
    verts.push_back(verts[0]);
     int64_t aux = 0;

    for (int i = 0; i < verts.size() -1 ; ++i) {
        int64_t g = ((verts[i].row * verts[i+1].col) - (verts[i].col * verts[i+1].row));
        aux += g;
    }

aux *= -1;
    std::cout << (aux/2) - ((result / 2) -1) << std::endl;
    return 0;
}