#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <numeric>
#include <sstream>

enum handtype_t {five, four, full, three, two, one, high};

struct hand_t {
    handtype_t hand_type;
    std::string hand;
    int bid;
};

const std::string cards = "AKQJT98765432";
bool cmp_hands(const std::string& h1, const std::string & h2) {
    for (int i = 0; i < 5; ++i) {
        auto f1 = std::find(std::begin(cards), std::end(cards), h1[i]);
        auto f2 = std::find(std::begin(cards), std::end(cards), h2[i]);
        if(f1 == f2) continue;
        return f1 > f2; 
    }
    return false;
}
handtype_t eval_hand(const std::string& hand) {
    int k[5] = {0};
    if (hand.length() != 5) static_assert("eval_hand length");
    for (int i = 0; i < 5; ++i) {
        k[i] = std::count(std::begin(hand), std::end(hand), hand[i]);
    }
    
    switch (std::accumulate(k, k+5, 0)) {
        case 25: return five;
        case 17: return four;
        case 13: return full;
        case 11: return three;
        case 9: return two;
        case 7: return one;
        case 5: return high;
    }
    return high;
}

constexpr const int ARGS = 2;

int main(int argc, char ** argv) {
    if (argc != ARGS) {
        std::cerr << "Syntax: exe <input file>" << std::endl;
        return -1;
    }

    std::string file = argv[1];
    std::ifstream input_file(file);

    std::vector<hand_t> hands;

    std::string line;
    while (std::getline(input_file, line)) {
        hand_t hand;
        std::istringstream hand_bid(line);
        hand_bid >> hand.hand >> hand.bid;
        hand.hand_type = eval_hand(hand.hand);
        std::cout << hand.hand << ":" << hand.bid << ":" << hand.hand_type << std::endl;
        hands.push_back(hand);
    }
    

    std::sort(std::begin(hands), std::end(hands), [](auto v1, auto v2){
        if(v1.hand_type == v2.hand_type) {
            return cmp_hands(v1.hand, v2.hand);
        }
        return v1.hand_type > v2.hand_type;
    });

    int result = 0;
    for (int i = 0; i < hands.size(); ++i) {
        result += (i+1)*hands[i].bid;
    } 
    std::cout << result << std::endl;
    return 0;
}