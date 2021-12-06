#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <tuple>
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


class Board {
    public:
        Board(std::string board_data);

        bool bingo = false;
        bool call(int num); //number to call, returns true if bingo, false otherwise.

        bool get_square(int x, int y);

        int sum_of_uncalled();

        friend std::ostream& operator<<(std::ostream& os, const Board& board);

    private:
        std::array<std::array<std::tuple<int, bool>, 5>, 5> _board;
        bool check_bingo();
};

//assume well-formed board data
Board::Board(std::string board_data) {
    auto rows = split(board_data, '\n');
    for(int i = 0; i < 5; i++) {
        auto cols = split(rows[i], ' ');
        for(int j = 0; j < 5; j++) 
            _board[i][j] = std::make_tuple(std::stoi(cols[j]),false); 
    }
}

bool Board::check_bingo() {
    //check horizontally
    for(int i = 0; i < 5; i++) {
        if(std::all_of(_board[i].begin(), _board[i].end(), [](const std::tuple<int,bool> t){ return std::get<bool>(t);})) {
            bingo = true;
            return bingo;
        }
    }

    //check vertically
    for(int i = 0; i < 5; i++) {
        int counter = 0;
        for(int j = 0; j < 5; j++) {
            if(std::get<bool>(_board[j][i]))
                counter++;
        }
        if(counter == 5) {
            bingo = true;
            return bingo;
        }
    }

    //check diagonally
    int j = 0;
    int counter = 0;
    for(int i = 0; i < 5; i++){
        if(std::get<bool>(_board[i][j]))
            counter++;

        j++;
    }
    if(counter == 5) {
        bingo = true;
        return bingo;
    }

    j = 0;
    counter = 0;
    for(int i = 4; i >= 0; i--) {
        if(std::get<bool>(_board[i][j]))
            counter++;

        j++;
    }
    if(counter == 5) {
        bingo = true;
        return bingo;
    }

    //all checks failed, no bingo
    return false;
}

bool Board::call(int num) {
    for(auto& row : _board) {
        for(auto& col : row) {
            if(std::get<int>(col) == num) {
                std::get<bool>(col) = true;
            }
        }
    }

    return check_bingo();
}

bool Board::get_square(int x, int y) {
    return std::get<bool>(_board[x][y]);
}

int Board::sum_of_uncalled() {
    int sum = 0;
    for(auto row : _board) {
        for(auto col : row) {
            if(!std::get<bool>(col))
                sum += std::get<int>(col);
        }
    }

    return sum;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    std::string board_string;
    for(auto row : board._board) {
        for(auto col : row) {
            std::ostringstream oss;
            oss << std::get<int>(col);
            board_string.append(oss.str());
            board_string.append(" ");
        }
        board_string.append("\n");
    }

    os << board_string;
    return os;
}