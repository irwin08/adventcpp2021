#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> load_data() {
    std::ifstream file {"input.txt"};
    if(!file.is_open()) {
        std::cerr << "Unable to open file input.txt!" << std::endl;
        throw std::runtime_error("Unable to open file input.txt!");
    }

    std::vector<int> loaded_data;
    std::string line;
    while(std::getline(file, line)) {
        loaded_data.push_back(std::stoi(line));
    }

    return loaded_data;
}

std::vector<int> generate_windows(std::vector<int>& data) {
    std::vector<int> new_data;

    for(int i = 0; i < (data.size() - 2); i++) {
        int sum = data[i] + data[i+1] + data[i+2];
        new_data.push_back(sum);
    }

    return new_data;
}

bool is_increasing(int val_1, int val_2) {
    
    return (val_2 > val_1);
}

int main() {
    auto data = load_data();

    //part 1

    int counter = 0;
    for(int i = 1; i < data.size(); i++) {
        if (is_increasing(data[i-1], data[i])) {
            counter++;
        }
    }

    std::cout << "Number of increasing: "<< counter << std::endl;

    //part 2
    auto windowed_data = generate_windows(data);
    counter = 0;
    for(int i = 1; i < windowed_data.size(); i++) {
        if(is_increasing(windowed_data[i-1], windowed_data[i])) {
            counter++;
        }
    }

    std::cout << "Number of increasing: " << counter << std::endl;

    return 0;
}