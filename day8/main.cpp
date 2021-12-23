#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream {s};
    while(std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void rtrim(std::string& str) {
    auto end_it = str.rbegin();
    while((end_it != str.rend()) && std::isspace(*end_it)) {
        end_it++;
    }
    if(end_it == str.rend())
        return;

    str.erase(end_it.base(), str.rbegin().base());
}

void ltrim(std::string& str) {
    auto start_it = str.begin();
    while((start_it != str.end()) && std::isspace(*start_it)) {
        start_it++;
    }
    if(start_it == str.end())
        return;

    str.erase(str.begin(), start_it);
}

void trim(std::string& str) {
    ltrim(str);
    rtrim(str);
}




int main() {
    
    std::vector<std::string> lines;

    std::string line;
    std::ifstream file_stream {"input.txt"};

    while(std::getline(file_stream, line)) {
        auto split_line = split(line, '|');
        trim(split_line[1]);
        lines.push_back(split_line[1]);
    }

    int one_count = 0;
    int four_count = 0;
    int seven_count = 0;
    int eight_count = 0;

    for(auto str : lines) {
        auto segments = split(str, ' ');

        for(auto seg : segments) {
            switch(seg.length()) {
            case 2:
                one_count++;
                break;
            case 4:
                four_count++;
                break;
            case 3:
                seven_count++;
                break;
            case 7:
                eight_count++;
                break;
            }
        }
    }

    std::cout << "Ones: " << one_count << std::endl;
    std::cout << "Fours: " << four_count << std::endl;
    std::cout << "Sevens: " << seven_count << std::endl;
    std::cout << "Eights: " << eight_count << std::endl;
    std::cout << "Total: " << one_count+four_count+seven_count+eight_count << std::endl;

    return 0;
}