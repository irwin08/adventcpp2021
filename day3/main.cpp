#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>

std::vector<std::string> load_data() {
    std::ifstream file {"input.txt"};
    if(!file.is_open()) {
        std::cerr << "Unable to open file input.txt!" << std::endl;
        throw std::runtime_error("Unable to open file input.txt!");
    }

    std::vector<std::string> loaded_data;
    std::string line;
    while(std::getline(file, line)) {
        loaded_data.push_back(line);
    }

    return loaded_data;
}


char generate_gamma_at(int index, std::vector<std::string> data) {

    int counter = 0;
    for(auto str : data) {
        if(str[index] == '1') 
            counter++;
        else if(str[index] == '0')
            counter--;
    }
    if(counter >= 0)
        return '1';
    else
        return '0';

}

char generate_epsilon_at(int index, std::vector<std::string> data) {

    int counter = 0;
    for(auto str : data) {
        if(str[index] == '0') 
            counter++;
        else if(str[index] == '1')
            counter--;
    }
    if(counter > 0)
        return '1';
    else
        return '0';
}


int main() {

    auto data = load_data();

    std::array counter = {0,0,0,0,0,0,0,0,0,0,0,0}; //12 bits so length 12

    //loop over each column
    for(auto str : data) {
        for(int i = 0; i < str.size(); i++) {
            if(str[i] == '1') {
                counter[i]++;
            }
            else if(str[i] == '0') {
                counter[i]--;
            }
        }
    }

    std::string gamma;
    std::string epsilon;

    for(int i : counter) {
        if(i > 0) {
            gamma.append("1");
            epsilon.append("0");
        }
        else if(i < 0) {
            gamma.append("0");
            epsilon.append("1");
        }
    }

    std::cout << gamma << std::endl;
    std::cout << epsilon << std::endl;

    std::cout << std::stoi(gamma, 0, 2) * std::stoi(epsilon, 0, 2) << std::endl;


    //part 2

    auto data_2 = data;

    //loop over each column
    for(int i = 0; i < 12; i++) {
        data.erase(std::remove_if(
            data.begin(),
            data.end(),
            [i,data](std::string element) {
                return element[i] != generate_gamma_at(i,data);
            }
        ),
        data.end());
        if(data.size() == 1)
            break;
    }

    for(int i = 0; i < 12; i++) {
        data_2.erase(std::remove_if(
            data_2.begin(),
            data_2.end(),
            [i,data_2](std::string element) {
                return element[i] != generate_epsilon_at(i,data_2);
            }
        ),
        data_2.end());
        if(data_2.size() == 1)
            break;
    }


    std::cout << std::stoi(data[0],0,2)*std::stoi(data_2[0],0,2) << std::endl;

    return 0;
}