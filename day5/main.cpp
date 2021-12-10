#include <iostream>
#include <array>
#include <tuple>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream {s};
    while(std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void generate_line(std::array<std::array<int, 1000>, 1000> arr, std::tuple<int,int> from, std::tuple<int, int> to) {
    //calculate slope
    double slope = (std::get<1>(to)-(std::get<1>(from)))/(std::get<0>(to)-(std::get<0>(from)));

    for(int x_1 = std::get<0>(from); x_1 != std::get<0>(to); x_1++ ) {
        for(int y_1 = std::get<1>(from); y_1 != std::get<1>(to); y_1 += slope) {
            arr[x_1][y_1]++;
        }
    }
}


std::array<std::array<int, 1000>, 1000> generate_map() {
    std::array<std::array<int, 1000>, 1000> map {};

    std::ifstream file {"input.txt"};

    if(!file.is_open()) {
        std::cerr << "Unable to open file input.txt!" << std::endl;
        throw std::runtime_error("Unable to open file input.txt!");
    }

    std::string line;
    while(std::getline(file, line)) {
        auto tok = split(line, ' ');

        auto vec_1 = split(tok[0], ',');
        auto vec_2 = split(tok[2], ',');

        auto tuple_1 = std::make_tuple(std::stoi(vec_1[0]), std::stoi(vec_1[1]));
        auto tuple_2 = std::make_tuple(std::stoi(vec_2[0]), std::stoi(vec_2[1]));

        // part 1 skip non-horizontal/vertical
        if(vec_1[0] == vec_2[0] || vec_1[1] == vec_1[1])
            continue;

        generate_line(map, tuple_1, tuple_2);
    }

    return map;
}


int main() {

    auto map = generate_map();

    int count = 0;

    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            if(map[i][j] >= 2)
                count++;
        }
    }

    std::cout  << count << std::endl;

    return 0;
}