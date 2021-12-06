#include <iostream>
#include <fstream>
#include "board.h"



std::vector<int> load_calls() {
    std::ifstream file {"input.txt"};
    if(!file.is_open()) {
        std::cerr << "Unable to open file input.txt!" << std::endl;
        throw std::runtime_error("Unable to open file input.txt!");
    }

    std::vector<int> loaded_data;
    std::string line;
    std::getline(file, line);

    auto split_data = split(line, ',');
    for(auto data : split_data) {
        loaded_data.push_back(std::stoi(data));
    }

    return loaded_data;
}

void trim_whitespace(std::string &str) {
    char prev_char = 'a';
    for(auto it = str.begin(); it != str.end();) {
        if (*it == ' '){
            if(prev_char == ' ') {
                it = str.erase(it);
                //it--; //we don't need an increment here.
                prev_char = ' ';
                continue;
            }
            else if(*it == ' ' && it == str.begin()) {
                it = str.erase(it);
                prev_char = ' ';
                continue;
            }
        }
        prev_char = *it;
        it++;
    }
}


std::vector<Board> load_boards() {
    std::ifstream file {"input.txt"};
    if(!file.is_open()) {
        std::cerr << "Unable to open file input.txt!" << std::endl;
        throw std::runtime_error("Unable to open file input.txt!");
    }

    std::string line;
    //throw out first two lines
    std::getline(file, line);
    std::getline(file, line); 

    std::vector<std::string> board_strings;

    int counter = 0;
    std::string board_string;
    while(std::getline(file,line)) {
        if(counter == 5) {
            trim_whitespace(board_string);
            board_strings.push_back(board_string);
            board_string.clear();
        }
        else {
            trim_whitespace(line);
            board_string.append(line);
            board_string.append("\n");
        }
        counter = ((++counter) % 6);
    }

    std::vector<Board> boards;

    for(auto s : board_strings) {
        Board b {s};
        boards.push_back(b);
    }

    return boards;
}


int main() {
    auto calls = load_calls();
    auto boards = load_boards();


    for(auto call : calls) {

        std::vector<Board> bingos;

        for(auto &b : boards) {
            if(b.call(call)) {
                bingos.push_back(b);
            }
        }

        boards.erase(std::remove_if(boards.begin(),
                        boards.end(),
                        [](const Board& board){ return board.bingo; } ),
                            boards.end());

        std::cout << "Bingos this round: " << std::endl;
        for(auto b : bingos) {
            std::cout << b << std::endl;
            std::cout << "Score: " << (b.sum_of_uncalled() * call) << std::endl;
        }
    }


    std::cout << "All done" << std::endl;

    return 0;
}