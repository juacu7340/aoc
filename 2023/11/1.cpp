#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <numeric>
#include <sstream>

constexpr const int ARGS = 2;

struct point_t {
    int row;
    int col;
};

int distance(point_t p1, point_t p2) {
    return abs(p1.row - p2.row) + abs(p1.col - p2.col);
}

int smallest_distance(point_t p, std::vector<point_t> points){
    if (points.size() == 0) return -1;
    //int d = distance(p, points[0]);

    int result = 0;
    for(int i = 1; i < points.size(); ++i) {
        int v = distance(p, points[i]);
        std::cout << "[" << p.row << "," << p.col <<"]:[" << points[i].row << "," << points[i].col<<"]=" << v << std::endl;
        result += v;
        //int x = distance(p, points[i]);
        //if (x < d) d = x;
    }

    return result;
}

void empty_row(std::vector<std::vector<char>> & space, int row) {
    std::cout << "adding empty row at:" << row << std::endl;
    std::vector<char> aux(space[0].size());
    std:fill(std::begin(aux), std::end(aux), '.');

    space.insert(std::begin(space) + (row), aux);
} 

void empty_col(std::vector<std::vector<char>> & space, int col) {
    std::cout << "adding empty col at:" << col << std::endl;
    for(auto & v : space) {
        v.insert(std::begin(v) + (col), '.');
    }
}

void check_expansion(std::vector<std::vector<char>>& space) {
    std::vector<int> rows, cols;

    for(int row = 0; row < space.size(); ++row) {
        if(std::adjacent_find(space[row].begin(), space[row].end(), std::not_equal_to<int64_t>()) == space[row].end()) {
            std::cout << "empty row at:" << row << std::endl;
            rows.push_back(row);
        }
    }

    for(int col = 0; col < space[0].size(); ++col) {
        int counter = 0;
        for(int row = 0; row < space.size(); ++row) {
            if(space[row][col] != '.') {
                break;
            }
            counter++;
        }
        if(counter == space[0].size()) {
            cols.push_back(col);
        }
    }

    for(int i = 0; i < rows.size(); ++i) {
        empty_row(space, rows[i] + i);
    }

    for(int i = 0; i < cols.size(); ++i) {
        empty_col(space, cols[i] + i);
    }
}


int main(int argc, char ** argv) {
    if (argc != ARGS) {
        std::cerr << "Syntax: exe <input file>" << std::endl;
        return -1;
    }

    std::string file = argv[1];
    std::ifstream input_file(file);

    std::vector<std::vector<char>> space;

    int64_t result = 0;
    std::string line;
    while (std::getline(input_file, line)) {
        char p;
        std::istringstream iss(line);
        std::vector<char> x;
        while(iss>>p) {
            x.push_back(p);
        }
        space.push_back(x);
    }

    check_expansion(space);

    std::vector<point_t> points;
    for(int row = 0; row < space.size(); ++row) {
        for(int col = 0; col < space[row].size(); ++ col) {
            if(space[row][col] == '#') {
                points.push_back(point_t{row, col});
            }
        }
    }

    std::cout << "p:" << points.size() << std::endl;
    for(int p = 0; p < points.size(); ++p) {
        std::cout << "[" << points[p].row << "," << points[p].col << "]";
    }
    std::cout << std::endl;

    for(int i = 0; i < points.size() - 1; ++i) {
        std::vector<point_t> x(points.begin() + (i), points.end());
        result += smallest_distance(points[i], x);
    }

    std::cout << result << std::endl;
    return 0;
}