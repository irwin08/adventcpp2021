#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
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

std::vector<std::tuple<std::string, int>> load_data() {
    std::ifstream file {"input.txt"};
    if(!file.is_open()) {
        std::cerr << "Unable to open file input.txt!" << std::endl;
        throw std::runtime_error("Unable to open file input.txt!");
    }

    std::vector<std::tuple<std::string, int>> loaded_data;
    std::string line;
    while(std::getline(file, line)) {
        auto components = split(line, ' ');
        auto tuple = std::make_tuple(components[0], std::stoi(components[1]));
        loaded_data.push_back(tuple);
    }

    return loaded_data;
}




int main() {
    auto data = load_data();

    //part 1

    int x = 0;
    int y = 0;

    for(auto tuple : data) {
        if(std::get<0>(tuple) == "forward")
        {
            x += std::get<1>(tuple);
        }
        else if(std::get<0>(tuple) == "up") {
            y -= std::get<1>(tuple);
        }
        else if(std::get<0>(tuple) == "down") {
            y += std::get<1>(tuple);
        }
    }

    std::cout << "Depth * Horizontal Position: "<< x*y << std::endl;

    //part 2
    x = 0;
    y = 0;
    int aim = 0;

    for(auto tuple : data) {
        if(std::get<0>(tuple) == "forward")
        {
            x += std::get<1>(tuple);
            y += (aim*std::get<1>(tuple));
        }
        else if(std::get<0>(tuple) == "up") {
            aim -= std::get<1>(tuple);
        }
        else if(std::get<0>(tuple) == "down") {
            aim += std::get<1>(tuple);
        }
    }

    std::cout << "(Part 2) Depth * Horizontal Position: "<< x*y << std::endl;


    return 0;
}
