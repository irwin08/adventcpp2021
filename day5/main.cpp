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

void generate_line(std::vector<std::vector<int>>& arr, std::tuple<int,int> from, std::tuple<int, int> to) {


    //check for vertical slope
    if(std::get<0>(from) == std::get<0>(to)) {
        int direction = (std::get<1>(to) > std::get<1>(from) ? 1 : -1);
        for(int y = std::get<1>(from); y != std::get<1>(to); y += direction) {
            try {
                arr.at(std::get<0>(from)).at(y) += 1;
            }
            catch(std::out_of_range ex) {
                std::cout <<"Out of range exception" << std::endl;
            }
        }
        arr.at(std::get<0>(from)).at(std::get<1>(to)) += 1;
        return;
    }

    //calculate slope
    int slope = (std::get<1>(to)-(std::get<1>(from)))/(std::get<0>(to)-(std::get<0>(from)));

    int direction_x = (std::get<0>(to) > std::get<0>(from) ? 1 : -1);


    int x_1 = std::get<0>(from);
    int y_1 = std::get<1>(from);

    while((x_1 != std::get<0>(to)) || (y_1 != std::get<1>(to))) {
       
        arr.at(x_1).at(y_1) += 1;

        x_1 += direction_x;
        y_1 += (direction_x * slope);
    }
    arr.at(x_1).at(y_1) += 1;
}


std::vector<std::vector<int>> generate_map() {
    std::vector<std::vector<int>> map(1000, std::vector<int>(1000));

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
        /*if(!(std::get<0>(tuple_1) == std::get<0>(tuple_2) || std::get<1>(tuple_1) == std::get<1>(tuple_2)))
        {
            continue;
        }*/

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