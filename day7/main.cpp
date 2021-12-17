#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream {s};
    while(std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> load_data() {
    std::ifstream file {"input.txt"};
    if(!file.is_open()) {
        std::cerr << "Unable to open file input.txt!" << std::endl;
        throw std::runtime_error("Unable to open file input.txt!");
    }


    std::string line;
    std::getline(file, line);
    auto loaded_data = split(line, ',');
    return loaded_data;
}


int distance(int x, std::vector<int>& crabs) {
    int movement = 0;
    for(auto& crab : crabs) {
        //part 1
        //movement += std::abs((crab - x));

        //part 2
        int n = std::abs((crab - x));
        movement += ((n*(n+1))/2);
    }
    return movement;
}

int main() {

    auto data = load_data();
    std::vector<int> transformed_data {};

    std::transform(data.begin(), data.end(), std::back_inserter(transformed_data), [](auto x){return std::stoi(x);});

    std::tuple<int,int> min = std::make_tuple(0,distance(0,transformed_data));

    for(int i = 1; i < 2000; i++) {
        int current_distance = distance(i, transformed_data);
        if(current_distance < std::get<1>(min)) {
            min = std::make_tuple(i, current_distance);
        }
    }

    std::cout << "Spot x: " << std::get<0>(min) << " has distance " << std::get<1>(min) << std::endl;

    return 0;
}