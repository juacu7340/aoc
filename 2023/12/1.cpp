#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <numeric>
#include <sstream>

constexpr const int ARGS = 2;

int countWords(const std::string& input) {
    std::istringstream iss(input);
    std::string word;
    int count = 0;

    while (std::getline(iss, word, '.')) {
        if (!word.empty()) {
            count++;
        }
    }

    return count;
}

bool validate(std::string&& gen, const std::string& pattern, int count) {
    if (gen.length() != pattern.length()) return false;
    
    // first validations
    for (int i = 0; i < gen.length(); ++i) {
        if(gen[i] != pattern[i] && pattern[i] != '?') return false;
    }
    
    auto last = std::unique(gen.begin(), gen.end());
    gen.erase(last, gen.end());

    if(countWords(gen) != count) return false;
    return true;
}

std::vector<std::string> gen1(int n, int w) {
    std::vector<std::string> result;

    for(int i = 0; i < (n-w+1); ++i) {
        std::string x = "";
        if(i > 0) x += std::string(i,'.');
        x += std::string(w,'#');
        if((n-w)-i > 0) x += std::string((n-w)-i,'.');
        result.push_back(x);
    }
    return result;
}



std::vector<std::string> generate(int count, const std::vector<int>& nums) {
    std::vector<std::string> result;
    auto accumulate = std::accumulate(std::begin(nums), std::end(nums), 0);
    
    return result;
}

int main(int argc, char ** argv) {
    if (argc != ARGS) {
        std::cerr << "Syntax: exe <input file>" << std::endl;
        return -1;
    }

    std::string file = argv[1];
    std::ifstream input_file(file);

    std::string line;
    while (std::getline(input_file, line)) {
    }

    auto x = gen1(6, 3);
    for(auto w : x) {
        std::cout << w << std::endl;
    }

    return 0;
}