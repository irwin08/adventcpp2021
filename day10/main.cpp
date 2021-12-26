#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

struct Line {
    std::stack<char> opening {};
    std::stack<char> closing {};

    std::vector<char> opening_chars = {'[', '{', '<', '('};
    std::vector<char> closing_chars = {']', '}', '>', ')'};

    //returns line with error, -1 if good
    int process(std::string line) {
        for(int i = 0; i < line.length(); i++) {
            if((closing.empty()) && (std::find(closing_chars.begin(), closing_chars.end(), line[i])!= closing_chars.end())) {
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
};


int main() {

    Line line {};

    std::cout << line.process(std::string("([])")) << std::endl;

    return 0;
}