#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

struct Line {
    std::stack<char> opening {};
    std::stack<char> closing {};

    std::vector<char> opening_chars = {'[', '{', '<', '('};
    std::vector<char> closing_chars = {']', '}', '>', ')'};
    

    //returns line with error, -1 if good
    int process(std::string line) {
        for(int i = 0; i < line.length(); i++) {
            if((opening.empty()) && (std::find(closing_chars.begin(), closing_chars.end(), line[i])!= closing_chars.end())) {
                return i;
            }
            auto it_closing = std::find(closing_chars.begin(), closing_chars.end(), line[i]);
            auto it_opening = std::find(opening_chars.begin(), opening_chars.end(), line[i]);
            if(it_closing != closing_chars.end()) {
                closing.push(*it_closing);
                if(opening.top() != opening_chars[it_closing - closing_chars.begin()]) {
                    //mismatch
                    return i;
                }
                else {
                    closing.pop();
                    opening.pop();
                }
            }
            if(it_opening != opening_chars.end()) {
                opening.push(*it_opening);
            }
        }



        return -1;
    }

    std::string complete(std::string line) {
        opening = std::stack<char>{};
        closing = std::stack<char>{};

        process(line);

        std::string complete {};

        while(opening.size() > closing.size()) {
            auto opener = opening.top();
            auto it = std::find(opening_chars.begin(), opening_chars.end(), opener);
            int index = std::distance(opening_chars.begin(), it);

            complete.push_back(closing_chars[index]);

            opening.pop();
        }

        return complete;
    }
};


int main() {

    Line line {};

    std::ifstream file {"input.txt"};
    std::string s;

    std::vector<int> points = {57, 1197, 25137, 3};
    std::vector<char> closing_chars = {']', '}', '>', ')'};

    int score = 0;
    std::vector<unsigned long long> completion_scores {};
    while(std::getline(file, s)) {
        int round = line.process(s);
        if(round != -1) {
            auto it = std::find(closing_chars.begin(), closing_chars.end(), s[round]);
            score += points[it - closing_chars.begin()];
    
        }
        else {
            std::vector<int> score_guide {2, 3, 4, 1};
            auto str = line.complete(s);
            unsigned long long score_2 = 0;

            for(int i = 0; i < str.length(); i++) {
                auto it = std::find(closing_chars.begin(), closing_chars.end(), str[i]);
                int index = std::distance(closing_chars.begin(), it);
                score_2 = (score_2*5) + (unsigned long long)score_guide[index];
            }

            completion_scores.push_back(score_2);
            
        }
    }

    std::cout << "Score: " << score << std::endl;

    std::sort(completion_scores.begin(), completion_scores.end(), [](unsigned long long i, unsigned long long j){return i > j;});

    std::cout << "Middle score: " << completion_scores[(completion_scores.size()-1)/2] << std::endl;

    return 0;
}